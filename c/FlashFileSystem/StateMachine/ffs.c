// ffs.c Flash File System
// 
// This module implements a simple flash file system.
// 
// To port it to a specific flash device(s) the programmer needs to 
// implement the following three functions (search for "IMPLEMENT FOR ACTUAL FLASH"):
// 
//    _ReadFlash()
//    _StateErasing()
//    _StateWriting()
// 
// The file system may be implemented with four or more contiguous flash 
// blocks (a block is here-in defined as an erasable unit).  The final 
// block is reserved for temporary storage during the defragmentation 
// (defrag) process.
// 
// Files are written sequentially in flash.  An identical header and tail
// is included which contains the buffer size, data size, file id (an 
// integer) and a filler word.
// 
// When a file is "deleted" it's size is set to zero (a characteristic of
// flash is that bits may be zeroed but a block must be erased to set the
// bit back to one).  
// 
// If insufficient space remains at the end of flash when a write is 
// attempted, then the file system checks if defragmentation will free
// up enough space to write the file.  If enough space does exist, then
// the defrag process shuffles data back and forth to the final block
// in order to compress the files into lower memory.
// 
// Special care has been taken to assure that the filesystem can recover
// if a power-down occurs at any time (with the possible loss of the
// final in-process file-write).  Testing has been performed simulating
// interruption during write of each byte in a sequence of file 
// write/erase operations.
// 
// Limitations (remember this is a simple implementation) include the
// following:
// 
// . files must be written in their entirety (no partial writes)
// . there is no wear levelling implemented (possible future enhancement)
// . filenames are not supported, files identified by an integer "handle"
// 
// Typical use of the file system would be as follows:
// . The file system should be initialized after power up with a call
//   to FfsInit.
// . The application code performs some combination of FfsWriteFile and
//   FfsDeleteFile to save and delete data as required.
// . On successive power-ups the application code will build it's 
//   data-base of saved data by calling FfsGetNextFileId and FfsReadFile
//   to determine the current file configuration.  Typically the 
//   beginning of each file will contain an application specific header
//   defining the type of data contained in the file.
// 
// Note that the FFS is implemented as a collection of state machines since
// various operations on the flash device (erase/write) can take significant
// time (it is assumed that reads can occur without delays).  In order for the
// state machine to operate, the higher level code (i.e. then main program 
// loop) must make periodic calls to FfsCheck().  The define FFS_MAX_MILLISECONDS
// specifies how much time the FFS is allowed to consume during each call
// to FfsCheck().  
//
// Additional functions provided include (see below for descriptions):
// 
//    FfsEraseAll
//    FfsGetFreeSpace


#define CONSOLE_TEST 0 // tim_todo TEST 
#define FFS_EMBEDDED 0 // tim_todo TEST 


// INCLUDES ==========================================================

#include "types.h"
#include "ffs.h"

#if CONSOLE_TEST // tim_todo TEST 
#endif

#if FFS_EMBEDDED
#include "Flash.h" 
#include "IssDefs.h" 
#include "IssMemory.h" 
#else
#include <memory.h>
#include <stdio.h> 
#include <stddef.h>
#endif // FFS_EMBEDDED


// DEFINES ===========================================================

// region for storing files
#define FFS_OFFSET_MAX  ( FFS_TOTAL_SIZE - BLOCK_SIZE - FFS_STATE_SIZE )  

// the last block is used for a temporary buffer during defrag
#define FLASHBUFF_BLOCK  ( NUM_BLOCKS - 1 )

// it's offset is here
#define FLASHBUFF_OFFSET ( BLOCK_SIZE * FLASHBUFF_BLOCK )

// the preceding block is where flags are stored during defrag
#define FLAGS_BLOCK      ( FLASHBUFF_BLOCK - 1 )

#define ERASED_BYTE  0xff
#define BLOCK_ERASED 0xfe  // one bit cleared for erase
#define BLOCK_MOVED  0xfc  // two bits cleared for erased and moved

#define FILLER_VALUE 0x11223344

#define FFS_WRAPPER_SIZE ( 2 * FILE_DESC_SIZE ) 

#define FFS_MAX_STATES 32

#define FFS_MAX_MILLISECONDS 10000


// TYPEDEFS ==========================================================

#pragma pack( 1 )

// File descriptor (goes in both head and tail)
typedef struct FILE_DESC
{
  tULong sizeBuff ;    // number of bytes possible for data
  tULong fileId ;      // the file ID (a handle returned by FfsWriteFile
  tULong sizeData ;    // the actual number of data bytes (set to zero when deleted)
  tULong filler ;      // filler value
} FILE_DESC ;

#define FILE_DESC_SIZE  ( (int)sizeof( FILE_DESC ) ) 


// File system state placed at end of data region
typedef struct FFS_STATE
{
  FILE_DESC head ;                       // this remains all FF to indicate end of linked list
  tUByte    defragFlags[ NUM_BLOCKS ] ;  // flags indicating defrag state
} FFS_STATE ;

#define FFS_STATE_SIZE  ( (int)sizeof( FFS_STATE ) ) 


// PROTOTYPES ========================================================

// local function prototypes
static tBoolean _BlockMoved( int block ) ;
static tBoolean _CheckFileSystem( int* lastGood ) ;
static tVoid    _ClearDefragFlag( int block , tBoolean start ) ;
static tVoid    _ClearFileTable() ;
static tVoid    _CopyBlock( int src , int dst ) ;
static tVoid    _Defrag() ;
static int      _DefragIncomplete() ;
static tVoid    _DefragPartial( int blockStart ) ;
tVoid           _DefragTotal() ; // tim_todo TEST
//static tVoid _DefragTotal() ;
static tVoid    _EraseBlock( int blockNumber ) ;
static int      _FfsGetCurrentState() ;
static int      _FfsPopState() ;
static tVoid    _FfsPushState( int state ) ;
static tVoid    _GetFileDescriptor( int offset , FILE_DESC* pDesc ) ;
static int      _GetFileOffset( int fileId ) ;
static int      _GetNextId() ;
static tBoolean _IsErased( int offset , int size ) ;
static tVoid    _ReadFlash( int offset , tUByte* dst , int size ) ;
static tVoid    _RebuildFileTable() ;
static tBoolean _RecoverFilesystem( tULong lastGood ) ;
static tVoid    _SetFileOffset( int fileId , int offset ) ;
static tBoolean _StateDefrag() ;
static tBoolean _StateEraseAll() ;
static tBoolean _StateErasing() ;
static tBoolean _StateInit() ;
static tBoolean _StateWriteFile() ;
static tBoolean _StateWriting() ;
static tBoolean _StateWriteFile() ;
static tBoolean _TimeOk( tBoolean init ) ;
static int      _WriteFlash( int offset , tUByte* buff , int size ) ;
static tVoid    _WriteFlashNext( tUByte* buff , int size ) ;


// LOCALS ============================================================

static int _ffsOffset ;
static int _ffsFree ;
static int _fileTable[ MAX_FILES ] ;
static int _FfsStates[ FFS_MAX_STATES ] ;
static int _FfsStateIndex = 0 ;

#if !FFS_EMBEDDED
tUByte _flash[ FFS_TOTAL_SIZE ] ;  // for testing only
#endif // FFS_EMBEDDED


// buffer for constructing file
static struct
  {
  FILE_DESC head ;
  tUByte    data[ MAX_FILE_SIZE ] ;
  FILE_DESC tail ;
}  _filebuff ;


// structure for storing WriteState state data
static struct
{
  int     written ;
  int     offset ; 
  tUByte* buff ; 
  int     size ;
  
} _writeState ;


// structure for storing WriteFile state data
static struct
{
  tUByte* buff ;
  int size     ;
} _writefileState ;


// structure for storing Erasing state data (simple for now)
static struct
{
  int block ;
} _erasingState ;


// structure for storing Defrag state data
static struct
{
  int offsetSrc ;       // initial offset of file within flash
  int offsetDst ;       // final offset of file within flash
  int written ;         // result of last _WriteFlash() call
  int remaining  ;      // how many bytes of current file are yet to be written to flash buff
  tUByte* fileptr ;     // pointer into current file buffer
  int nextEraseBlock ;  // next block to be erased
  int offsetBuff  ;     // current offset within temp flash buffer 
} _frag ;


// GLOBALS ===========================================================

int    gTestCount ; // tim_todo TEST - remove


// SPECIAL - states (must be same length/order) ======================

enum
{
  FFS_STATE_DORMANT   ,
  FFS_STATE_ERASING   ,
  FFS_STATE_WRITING   ,
  FFS_STATE_DEFRAG    ,
  FFS_STATE_INIT      ,
  FFS_STATE_WRITEFILE ,
  FFS_STATE_ERASEALL  ,
  NUM_FFS_STATES      
} ;

#if CONSOLE_TEST  // tim_todo TEST 
char* FfsStateStrings[] = 
{
  "FFS_STATE_DORMANT    " ,
  "FFS_STATE_ERASING    " ,
  "FFS_STATE_WRITING    " ,
  "FFS_STATE_DEFRAG     " ,
  "FFS_STATE_INIT       " ,
  "\nFFS_STATE_WRITEFILE" ,
  "\nFFS_STATE_ERASEALL " 
} ;
#endif // CONSOLE_TEST

typedef tBoolean (*pftn)() ;
static pftn _StateFunctions[] =
{
  NULL            ,  // dormant state has no function
  _StateErasing   ,
  _StateWriting   ,
  _StateDefrag    ,
  _StateInit      ,
  _StateWriteFile ,
  _StateEraseAll  ,
} ;


// FUNCTION DEFINITIONS ==============================================

// FfsCheck
//
// Check if the flash file system requires servicing.  This function must be 
// called periodically (typically from the main program loop).
//
// Parameter(s):
//    none
//
// Return:
//    TRUE if still performing tasks, FALSE otherwise.
//
tBoolean FfsCheck()
{
  static int state ;
  
  _TimeOk( TRUE ) ; // initialize timer
  
  while( ( state = _FfsGetCurrentState() ) && _TimeOk( FALSE ) )
  {
    #if CONSOLE_TEST  // tim_todo TEST 
    printf( "%s\n" , FfsStateStrings[ state ] ) ;
    #endif // CONSOLE_TEST
   
    // error check (note - no function for dormant state )  
    if( state > 0 && state < NUM_FFS_STATES ) 
    {
      if( _StateFunctions[ state ]() )
      {
        _FfsPopState() ;
      }  
    }
  }
  
  return ( state != FFS_STATE_DORMANT )  ;
}


// FfsGetFileSize
// 
// Get File size.
//
// Parameter(s):
//    fileId - The file ID
//
// Return:
//    The file size in bytes.
//
int FfsGetFileSize( int fileId )
{
  FILE_DESC head ;
  int offset ;
  head.sizeData = FFS_ERROR ;

  offset = _GetFileOffset( fileId ) ;
  if( offset != FFS_ERROR )
  {
    _GetFileDescriptor( offset , &head ) ;
  }

  return head.sizeData ;
}


// FfsGetNextFileId
// 
// Get the next file ID.  Initially called with parameter first set TRUE to get the
// first ID.  Successive calls (with first set FALSE) return the successive IDs.
//
// Parameter(s):
//    first - TRUE for first file, FALSE for successive file.
//
// Return:
//    FFS_ERROR if no next file, otherwise the file ID.
//
int FfsGetNextFileId( tBoolean first )
{
  static int offset = 0 ;
  FILE_DESC head ;

  if( first )
  {
    offset = 0 ;
  }

  if( offset != FFS_ERROR )
  {
    _GetFileDescriptor( offset , &head ) ;
    if( head.sizeBuff != FFS_ERROR )
    {
      offset += head.sizeBuff + FFS_WRAPPER_SIZE ;
    }
    else
    {
      offset = FFS_ERROR ;  // end file indicator
    }
  }

  return head.fileId ;
}


// FfsGetFreeSpace
// 
// Get the amount of free space remaining in the file system.  This is the
// largest file size which can be written (wrapper size has been subtracted.
//
// Parameter(s):
//    none
//
// Return:
//    Number of free bytes remaining.
//
int FfsGetFreeSpace()
{
  return ( _ffsFree - FFS_WRAPPER_SIZE ) ;
}


// FfsReadFile
// 
// Read a file from the flash file system.
//
// Parameter(s):
//    fileId  - the ID of the file to be read.
//    buff    - pointer to a buffer to store data.
//    maxsize - maximum number of bytes to read.
//
// Return:
//    The number of bytes read.
//
int FfsReadFile( int fileId , tUByte* buff , tULong maxsize )
{
  int offset ;
  FILE_DESC head ;
  int bytesRead = 0 ;

  offset = _GetFileOffset( fileId ) ;
  _GetFileDescriptor( offset , &head ) ;
  if( head.sizeData != FFS_ERROR )
  {
    if( head.sizeData <= maxsize )
    {
      offset += sizeof( FILE_DESC ) ;
      _ReadFlash( offset , buff , head.sizeData ) ;
      bytesRead = head.sizeData ;
    }
  }

  return  bytesRead ;
}


// FfsDeleteFile
// 
// Delete a file from the flash file system.
//
// Parameter(s):
//    fileId - the ID of the file to be deleted.
//
// Return:
//    none.
//
tVoid FfsDeleteFile( int fileId )
{
  int offset ;

  offset = _GetFileOffset( fileId ) ;
  if( offset  != FFS_ERROR )
  {
    _SetFileOffset( fileId , FFS_ERROR ) ;

    _GetFileDescriptor( offset , &_filebuff.head ) ;

    _ffsFree += ( _filebuff.head.sizeData + FILE_DESC_SIZE ) ;

    _filebuff.head.sizeData = 0 ;
    _WriteFlash( offset + offsetof( FILE_DESC , sizeData ) , 
      (tUByte*)&(_filebuff.head.sizeData) , 
      sizeof( _filebuff.head.sizeData ) ) ;
  }
}


// FfsEraseAll
// 
// Erase the entire flash file system.
//
// Parameter(s):
//    none
//
// Return:
//    none
//
tVoid FfsEraseAll()
{
  _FfsPushState( FFS_STATE_ERASEALL ) ;
}


// _StateEraseAll
// 
// State machine implementation of the EraseAll process.
//
// Parameter(s):
//    none
//
// Return:
//    TRUE if complete, FALSE otherwise.
//
static tBoolean _StateEraseAll()
{
  enum
  {
    ERASEALL_START ,
    ERASEALL_ERASE ,
    ERASEALL_END   ,
  } ;

  #if CONSOLE_TEST  // tim_todo TEST 
  const char* DebugStrings[] = 
  {
    "ERASEALL_START ",
    "ERASEALL_ERASE ",
    "ERASEALL_END   ",
  } ;
  #endif // CONSOLE_TEST

  tBoolean   done  = FALSE ;
  static int state = ERASEALL_START ;
  static int idxBlock ;
  
  #if CONSOLE_TEST  // tim_todo TEST 
  printf( "%s\n" , DebugStrings[ state ] ) ;
  #endif // CONSOLE_TEST

  switch( state )
  {
  case ERASEALL_START :
  
    idxBlock = 0 ;
    state = ERASEALL_ERASE ;
    break ;
    
  case ERASEALL_ERASE :
  
    if( idxBlock < NUM_BLOCKS )
    {
      _EraseBlock( idxBlock ) ;
      idxBlock++ ;
    }
    else
    {
      state = ERASEALL_END ;
    }
    break ;
    
  case ERASEALL_END :  
  
    done = TRUE ;
    state = ERASEALL_START ; // prepare for next time 
    
    _ffsOffset = 0 ;
    _ClearFileTable() ;
    _ffsFree = FFS_OFFSET_MAX ;
    
    break ;
  }

  return done ;
}


// FfsWriteFile
// 
// Write a file to the flash file system
//
// Parameter(s):
//    buff - pointer to the data to be written (MUST NOT MODIFY TILL DONE!!!).
//    size - number of bytes to write.
//
// Return:
//    The file ID if successful.  FFS_ERROR otherwise.
//
int FfsWriteFile( tUByte* buff , int size )
{
  // returns fileId if successful, otherwise FFS_ERROR
  int sizeTotal ;

  sizeTotal = size + FFS_WRAPPER_SIZE ;
  if( sizeTotal > _ffsFree )
  {
    _filebuff.head.fileId = FFS_ERROR ;
  }
  else
  {
    _filebuff.head.fileId = _GetNextId() ; // returns FFS_ERROR if out of IDs
  }
  
  // make sure that file can be written
  if( _filebuff.head.fileId != FFS_ERROR )
  {
    _writefileState.buff = buff ;
    _writefileState.size = size ;
    _FfsPushState( FFS_STATE_WRITEFILE ) ;
  }

  return _filebuff.head.fileId ;
}


// _StateWriteFile
// 
// State machine implementation of the WriteFile process.
//
// Parameter(s):
//    none
//
// Return:
//    TRUE if complete, FALSE otherwise.
//
static tBoolean _StateWriteFile() 
{
  enum
  {
    WRITEFILE_START ,
    WRITEFILE_WRITE ,
    WRITEFILE_END   ,
  } ;
  
  #if CONSOLE_TEST // tim_todo TEST 
  const char* DebugStrings[] =
  {
    "WRITEFILE_START" ,
    "WRITEFILE_WRITE" ,
    "WRITEFILE_END  " ,
  } ;
  #endif // CONSOLE_TEST
  
  tBoolean done = FALSE ;
  static int state = WRITEFILE_START ;
  
  #if CONSOLE_TEST // tim_todo TEST 
  printf( "%s\n" , DebugStrings[ state ] ) ;
  #endif // CONSOLE_TEST
  
  switch( state )
  {
  case WRITEFILE_START :
    
    // check if defrag is neccessary (i.e. - enough empty space, but not at end)
    if( ( _ffsOffset + _writefileState.size + FFS_WRAPPER_SIZE ) > FFS_OFFSET_MAX )
    {
      _DefragTotal() ;
    }
    state = WRITEFILE_WRITE ;
    
    break; 
    
  case WRITEFILE_WRITE :
  
    _SetFileOffset( _filebuff.head.fileId , _ffsOffset )  ;

    _filebuff.head.sizeData = _writefileState.size ;
    _filebuff.head.sizeBuff = _writefileState.size ;
    _filebuff.head.filler     = FILLER_VALUE ;
    memcpy( _filebuff.data , _writefileState.buff , _writefileState.size ) ;
    memcpy( _filebuff.data + _writefileState.size , &_filebuff.head , sizeof( _filebuff.head ) ) ;

    _WriteFlashNext( (tUByte*)&(_filebuff) , _writefileState.size + FFS_WRAPPER_SIZE ) ;  // write file

    _ffsFree -= ( _filebuff.head.sizeData + FFS_WRAPPER_SIZE ) ;
    
    state = WRITEFILE_END ;
    
    break ;
    
  case WRITEFILE_END :
    done = TRUE ;
    state = WRITEFILE_START ; // prepare for next time 
    break ;
  }
  
  return done ;
}

// FfsInit
// 
// Initialize the flash file system.
//
// Parameter(s):
//    none
//
// Return:
//    none
//
tVoid FfsInit()
{
  _FfsPushState( FFS_STATE_INIT ) ;
}


// _StateInit
// 
// State machine implementation of the Init process.
//
// Parameter(s):
//    none
//
// Return:
//    TRUE if complete, FALSE otherwise.
//
static tBoolean _StateInit() 
{
  enum
  {
    INIT_START               ,
    INIT_COPY_BLOCK          ,
    INIT_END_FLAG            ,
    INIT_ERASE_FLASHBUFF     , 
    INIT_DEFRAG_PARTIAL      ,
    INIT_CHECK_LAST_BLOCK    ,  
    INIT_COPY_LAST_BLOCK     ,
    INIT_ERASE_FLASHBUFF2    ,
    INIT_CHECK_FILE_SYSTEM   ,
    INIT_RECOVER_FILESYSTEM  ,
    INIT_CHECK_FILE_SYSTEM2  ,    
    INIT_END                 ,
  } ;

  #if CONSOLE_TEST // tim_todo TEST 
  const char* DebugStrings[] =
  {
    "INIT_START             "  ,
    "INIT_COPY_BLOCK        "  ,
    "INIT_END_FLAG          "  ,
    "INIT_ERASE_FLASHBUFF   "  , 
    "INIT_DEFRAG_PARTIAL    "  ,
    "INIT_CHECK_LAST_BLOCK  "  ,  
    "INIT_COPY_LAST_BLOCK   "  ,
    "INIT_ERASE_FLASHBUFF2  "  ,
    "INIT_CHECK_FILE_SYSTEM "  ,
    "INIT_RECOVER_FILESYSTEM"  ,
    "INIT_CHECK_FILE_SYSTEM2"  ,    
    "INIT_END               "  ,
  } ;
  #endif // CONSOLE_TEST
  
  tBoolean done = FALSE ;
  static int state = INIT_START ;

  static int block ;
  static int lastGood ;
  
  #if CONSOLE_TEST // tim_todo TEST 
  printf( "%s\n" , DebugStrings[ state ] ) ;
  #endif // CONSOLE_TEST
  
  switch( state )
  {
  case INIT_START :
  
    // check if defrag process was incomplete during last power-down
    block = _DefragIncomplete() ;
    if( block >= 0 )
    {
      // check if block move was incomplete
      if( !_BlockMoved( block ) )
      {
        // if so, erase destination and recopy
        _EraseBlock( block ) ;
        state = INIT_COPY_BLOCK ;
      }
      else
      {
        // else complete defrag process
        state = INIT_DEFRAG_PARTIAL ;
      }
    }
    else
    {
      state = INIT_CHECK_LAST_BLOCK ;
    }
    break ;
    
  case INIT_COPY_BLOCK :    
  
    // copy the flash buffer to last defrag block
    _CopyBlock( FLASHBUFF_BLOCK , block ) ;
    state = INIT_END_FLAG ;
    break ;
        
  case INIT_END_FLAG :    
  
    // clearing end flag indicates copy complete
    _ClearDefragFlag( block , FALSE ) ;
    state = INIT_ERASE_FLASHBUFF ;
    break ;
    
  case INIT_ERASE_FLASHBUFF :    
  
    // erase the flashbuff, then continue with defrag
    _EraseBlock( FLASHBUFF_BLOCK ) ;
    state = INIT_DEFRAG_PARTIAL ;
    break ;
  
  case INIT_DEFRAG_PARTIAL :    
  
    // complete the defragmentation process beginning at next block
    _DefragPartial( block + 1 ) ;
    state = INIT_CHECK_FILE_SYSTEM ;
    break ;
    
  case INIT_CHECK_LAST_BLOCK : 
     
    // need to handle the special condition where the last block 
    // (which contains the state flags) was erased but FLASHBUFF 
    // may have not yet been copied in
    if( !_IsErased( FLASHBUFF_OFFSET , BLOCK_SIZE ) )
    {
      _EraseBlock( FLASHBUFF_BLOCK - 1 ) ;
      state = INIT_COPY_LAST_BLOCK ;
    }
    else
    {
      state = INIT_CHECK_FILE_SYSTEM ;
    }
    break ;
      
  case INIT_COPY_LAST_BLOCK : 
  
    // copy flashbuff to final block
    _CopyBlock( FLASHBUFF_BLOCK , FLASHBUFF_BLOCK - 1 ) ;
    state = INIT_ERASE_FLASHBUFF2 ;
    break ;
    
  case INIT_ERASE_FLASHBUFF2 : 
  
    // final erase of flashbuff (get ready for next time)
    _EraseBlock( FLASHBUFF_BLOCK ) ;
    state = INIT_CHECK_FILE_SYSTEM ;
    break ;

  case INIT_CHECK_FILE_SYSTEM : 
  
    // check coherency of file system, attempt to recover if bad
    if( _CheckFileSystem( &lastGood ) )
    {
      _RebuildFileTable() ;
      state = INIT_END ;
    }
    else
    {
      state = INIT_RECOVER_FILESYSTEM ;
    }
    break ;
    
  case INIT_RECOVER_FILESYSTEM :    
  
    // attempt to recover file system
    _RecoverFilesystem( lastGood ) ;
    state = INIT_CHECK_FILE_SYSTEM2 ;
    break ;
    
  case INIT_CHECK_FILE_SYSTEM2 :    
  
    // final check, if still bad erase all
    if( !_CheckFileSystem( &lastGood ) )
    {
      FfsEraseAll() ;
    }
    state = INIT_END ;
    break ;

  case INIT_END :    
  
    // all done
    done = TRUE ;
    state = INIT_START ; // prepare for next time 
    break ;
  }
  
  return done ;
}


// _DefragIncomplete
// 
// Checks to see if a defragmentation process has been started but not completed.
// This information is stored in the state.defragFlags[] array at the end of the
// flash data memory (preceding the temporary buffer).
//
// Parameter(s):
//    none
//
// Return:
//    FFS_ERROR if complete.  Otherwise returns index of last block completed.
//
static int _DefragIncomplete()
{
  FFS_STATE state ;
  int       block ;

  _ReadFlash( FFS_OFFSET_MAX , (tUByte*)&state , FFS_STATE_SIZE ) ;

  block = NUM_BLOCKS-1 ;
  do
  {
    block-- ;
  } while( block >= 0 && state.defragFlags[block] == ERASED_BYTE ) ;

  return block ;
}


// _DefragPartial
// 
// Complete a defragmentation process starting at a given block.  The primary 
// function here is to reconstruct the _frag structure so that the _Defrag()
// function can be completed.  This requires walking the file chain from the
// beginning and from the end to reconstruct the state.
//
// Parameter(s):
//    blockStart - the block to start deframenting.
//
// Return:
//    none
//
static tVoid _DefragPartial( int blockStart )
{
  tULong offsetMax ;
  FILE_DESC head ;
  tULong offset ;
  tULong fileId ;
  tUByte byte ;

  _frag.offsetSrc      = 0 ;
  _frag.written        = 0 ;
  _frag.nextEraseBlock = blockStart ;
  _frag.offsetBuff     = FLASHBUFF_OFFSET ;

  // find last file that was partially (or totally) copied
  offsetMax = blockStart * BLOCK_SIZE ;
  
  offset = 0 ;   // prime the pump

  // walk the file chain up to the incomplete block
  do
  {
    _GetFileDescriptor( offset , &head ) ;
    offset += ( head.sizeBuff + FFS_WRAPPER_SIZE ) ;

  } while( offset < offsetMax ) ;  // tim_todo OTHER CONDITIONS ???

  // set up the _frag structure
  _frag.remaining = offset - offsetMax ;
  _frag.offsetDst = offset ;

  fileId = head.fileId ;

  // starting at flash end, find the first unerased byte
  offset = FFS_OFFSET_MAX ;
  do
  {
    offset-- ;
    _ReadFlash( offset , &byte , 1 ) ;
  } while( byte == ERASED_BYTE ) ;

  // find last file  (walk the file chain backwards)
  offset -= (FILE_DESC_SIZE-1) ;
  do
  {
    _GetFileDescriptor( offset , &head ) ;  // read end header
    offset -= ( head.sizeData + FFS_WRAPPER_SIZE ) ;
  } while( ( offset > offsetMax ) && ( head.fileId != fileId ) ) ;

  offset += FILE_DESC_SIZE ;
  _frag.offsetSrc = offset + head.sizeData + FFS_WRAPPER_SIZE ;

  // read the file which was in process of being moved with previous defrag interrupted
  _ReadFlash( offset , (tUByte*)&_filebuff , head.sizeData + FFS_WRAPPER_SIZE ) ;

  _frag.fileptr = (tUByte*)&_filebuff + head.sizeData + FFS_WRAPPER_SIZE - _frag.remaining ;

  _Defrag() ;
}


// _IsErased
// 
// Determine if a given block of flash has been erased.
//
// Parameter(s):
//    offset - the offset into flash to begin checking
//    size   - the size (in bytes) of the region to check.
//
// Return:
//    TRUE if entire region erased.  FALSE otherwise
//
static tBoolean _IsErased( int offset , int size )
{
  tUByte byte ;
  do
  {
    _ReadFlash( offset , &byte , 1 ) ;
    size-- ;
    offset++ ;

  } while( size && ( byte == ERASED_BYTE ) ) ;

  return ( byte == ERASED_BYTE ) ? TRUE : FALSE ;
}


// _BlockMoved
// 
// Determines if a given block has been moved during a defrag process.  This is 
// done by examining the state.defragFlags[] array.
//
// Parameter(s):
//    block - the block number to check.
//
// Return:
//    TRUE if moved.  FALSE otherwise.
//
static tBoolean _BlockMoved( int block )
{
  FFS_STATE state ;
  tBoolean  moved ;

  _ReadFlash( FFS_OFFSET_MAX , (tUByte*)&state , FFS_STATE_SIZE ) ;

  moved = ( state.defragFlags[block] == BLOCK_MOVED ) ;

  return moved ;
}


// _CheckFileSystem
// 
// Check if the file system is coherent.  The entire file system is walked.  
// Agreement between head and tail descriptors is checked and that the size
// of each file is logical.  Once the end file is found a check is made that
// the remaining flash is erased. 
//
// Parameter(s):
//    lastGood - the beginning point to check.
//
// Return:
//    TRUE if good.  FALSE otherwise.
//
static tBoolean _CheckFileSystem( int* lastGood )
{
  FILE_DESC head ;
  FILE_DESC tail ;
  int offset = 0 ;
  tBoolean good = TRUE ;
  tULong size ;

  *lastGood = 0 ;
  do
  {
    _GetFileDescriptor( offset , &head ) ;

    if( head.sizeData != FFS_ERROR )
    {
      size = head.sizeBuff ;

      offset += ( head.sizeBuff + FILE_DESC_SIZE ) ;
      _GetFileDescriptor( offset , &tail ) ;
      offset += FILE_DESC_SIZE ;

      if(  ( tail.fileId   != head.fileId ) 
        || ( tail.sizeBuff != head.sizeBuff )
        || ( tail.filler   != head.filler ) )
      {
        good = FALSE ;
      }
      else if( head.sizeData != 0 )
      {
        if( head.sizeData != tail.sizeData )
        {
          good = FALSE ;
        }
        else if( size > head.sizeData )
        {
          good = FALSE ;
        }
      }

      if( good )
      {
        *lastGood = offset ;
      }
    }
  } while( ( head.sizeData != FFS_ERROR ) && good ) ;

  // make sure all remaining flash is erased
  if( good )
  {
    if( !_IsErased( offset , FFS_TOTAL_SIZE - offset ) )
    {
      good = FALSE ;
    }
  }

  return good ;
}


// _RecoverFilesystem
// 
// Attempt to recover a damaged filesystem.  The last written (which is assumed
// damaged due to a power-down during write) is zeroed out.  Then the resultant
// filesystem is re-checked.
//
// Parameter(s):
//    lastGood - starting point in flash which is known to be good.
//
// Return:
//    TRUE if successful.  FALSE otherwise.
//
static tBoolean _RecoverFilesystem( tULong lastGood )
{
//  FILE_DESC head ;
  tULong offsetTail ;
  tBoolean success = FALSE ;

  _GetFileDescriptor( lastGood , &_filebuff.head ) ;

  offsetTail = lastGood  + _filebuff.head.sizeBuff + FILE_DESC_SIZE ;
  if(  ( offsetTail >= FFS_OFFSET_MAX - FILE_DESC_SIZE ) 
    || ( offsetTail < lastGood + FILE_DESC_SIZE ) )
  {
    offsetTail = lastGood + FILE_DESC_SIZE ;
    _filebuff.head.sizeBuff = 0 ;
  }
  
  _filebuff.head.fileId   = 0 ;
  _filebuff.head.sizeData = 0 ;
  _filebuff.head.filler   = FILLER_VALUE ;
  
  memcpy( &_filebuff.data[ _filebuff.head.sizeBuff ] , &_filebuff.head , FILE_DESC_SIZE ) ;

  _WriteFlash( lastGood , (tUByte*)&_filebuff , _filebuff.head.sizeBuff + FFS_WRAPPER_SIZE ) ;
  
//  _WriteFlash( lastGood   , (tUByte*)&_filebuff , FILE_DESC_SIZE ) ;
//  _WriteFlash( offsetTail , (tUByte*)&head , FILE_DESC_SIZE ) ;

//  success = _CheckFileSystem( &lastGood ) ;
  
  return success ;
}


// _ReadFlash
// 
// Read a block of data from flash.
//
// Parameter(s):
//    offset - offset of start of flash to read.
//    dst    - pointer to destination of data.
//    size   - number of bytes to read.
//
// Return:
//    none
//
static tVoid _ReadFlash( int offset , tUByte* dst , int size )
{
#if FFS_EMBEDDED
  // tim_todo IMPLEMENT FOR ACTUAL FLASH
#else // FFS_EMBEDDED
  while( size )
  {
    *dst++ = _flash[ offset++ ] ;
    size-- ;
  }
#endif // FFS_EMBEDDED
}


// _WriteFlash
// 
// Write data to flash.
//
// Parameter(s):
//    offset - offset into flash to begin writing
//    buff   - pointer to buffer of data to write (must not modify till done!)
//    size   - number of bytes to write
//
// Return:
//    number of bytes actually written (will not write past end of flash)
//
static int _WriteFlash( int offset , tUByte* buff , int size )
{
  _FfsPushState( FFS_STATE_WRITING ) ; 

  _writeState.written = 0 ;
  _writeState.buff    = buff ;
  _writeState.offset  = offset ;

  offset += size ;
  
  // check if end of flash being exceeded. 
  // If so, only write amount that can be written.
  if( offset > FFS_TOTAL_SIZE )
  {
    size = FFS_TOTAL_SIZE - _writeState.offset ;
  }
  
  _writeState.size = size ;
  
  return size ;
}


// _StateWriting
// 
// State machine implementation of the Writing process.
//
// Parameter(s):
//    none
//
// Return:
//    TRUE if complete, FALSE otherwise.
//
static tBoolean _StateWriting()
{
#if FFS_EMBEDDED
  // tim_todo IMPLEMENT FOR ACTUAL FLASH
#else // FFS_EMBEDDED

  while( _writeState.size && ( _writeState.offset < FFS_TOTAL_SIZE ) )
  {
    // tim_todo for testing
    if( gTestCount > 0 )
    {
      _flash[ _writeState.offset ] = *_writeState.buff++ ;
      
      if( _writeState.offset == 100 )
      {
        volatile static int count = 0 ;
        count++ ;
      }
    }
    else
    {
       volatile static int count = 0 ;
       count++ ;
    }
    gTestCount-- ;

    _writeState.size-- ;
    _writeState.offset++ ;
    _writeState.written++ ;
  }

  return TRUE ;
#endif // FFS_EMBEDDED
}


// _GetFileOffset
// 
// Get the offset into flash of a file.  Note that these offsets are initially 
// determined in function FfsInit() and are updated in calls to FfsDeleteFile(),
// FfsWriteFile(), _Defrag(), etc.  They are stored in the array _fileTable[].
//
// Parameter(s):
//    fileId - the file ID (i.e - it's "handle") of the file.
//
// Return:
//    FFS_ERROR if no file.  The offset othewise.
//
static int _GetFileOffset( int fileId )
{
  return _fileTable[ fileId ] ;
}


// _SetFileOffset
// 
// Set the file offset for a given file.
//
// Parameter(s):
//    fileId - the ID of the file.
//    offset - the offset of the file.
//
// Return:
//    none
//
static tVoid _SetFileOffset( int fileId , int offset )
{
  _fileTable[ fileId ] = offset ;
}


// _ClearFileTable
// 
// Clear the file table (i.e. - set all entries to FFS_ERROR).
//
// Parameter(s):
//    none
//
// Return:
//    none
//
static tVoid _ClearFileTable()
{
  int fileId ;

  for( fileId = 0 ; fileId < MAX_FILES ; fileId++ )
  {
    _SetFileOffset( fileId , FFS_ERROR ) ;
  }
}


// _RebuildFileTable
// 
// Rebuild the file table.  Walks the flash file system to determine location
// in flash of each file and stores offsets in file table.
//
// Parameter(s):
//    none
//
// Return:
//    none
//
static tVoid _RebuildFileTable()
{
  FILE_DESC head ;
  int offset = 0 ;

  _ClearFileTable() ;

  do
  {
    _GetFileDescriptor( offset , &head ) ;
    if( head.sizeData && ( head.sizeData != FFS_ERROR ) )
    {
      _SetFileOffset( head.fileId , offset )  ;
    }

    if( head.sizeData != FFS_ERROR )
    {
      offset += ( head.sizeBuff + FFS_WRAPPER_SIZE ) ;
    }

  } while( head.sizeData != FFS_ERROR ) ;

  _ffsOffset = offset ;
}


// _CopyBlock
// 
// Copy data from one block to another (assumes destination has been erased).
//
// Parameter(s):
//    src - index of source block
//    dst - index of destination block
//
// Return:
//    none
//
static tUByte _blockBuffer[ BLOCK_SIZE ] ;
static tVoid _CopyBlock( int src , int dst )
{
  // assumes destination block is erased 

  _ReadFlash( src * BLOCK_SIZE , _blockBuffer , BLOCK_SIZE ) ;
  _WriteFlash( dst * BLOCK_SIZE , _blockBuffer , BLOCK_SIZE ) ;
}


// _GetFileDescriptor
// 
// Reads a file descriptor from flash.
//
// Parameter(s):
//    offset - offset into flash of the descriptor
//    pDesc  - pointer to location to put the descriptor
//
// Return:
//    none
//
static tVoid _GetFileDescriptor( int offset , FILE_DESC* pDesc )
{
  _ReadFlash( offset , (tUByte*)pDesc , sizeof( FILE_DESC ) ) ;
}


// _DefragTotal
// 
// Perform a total defragmentation of the file system.  Initializes the _frag structure
// and calls _Defrag() ;
//
// Parameter(s):
//    none
//
// Return:
//    none
//
tVoid _DefragTotal() // tim_todo TEST
//static tVoid _DefragTotal()
{
  _frag.offsetSrc  = 0 ;
  _frag.offsetDst  = 0 ;
  _frag.written    = 0 ;
  _frag.remaining  = 0 ;
  _frag.fileptr    = (tUByte*)&_filebuff ;
  _frag.nextEraseBlock = 0 ;
  _frag.offsetBuff = FLASHBUFF_OFFSET ;

  _Defrag() ;
}


// _ClearDefragFlag
// 
// Clear the defrag flag.  For each block of flash flags are cleared during the
// defrag process.  The start flag is cleared before a block is erased and the
// end flag is cleared when the block has been reprogrammed.  These flags are 
// themselves stored in flash.  Thus if a power fail occurs during the defrag
// process the state of the system can be re-constructed.
//
// Parameter(s):
//    block - the index of the block to erase.
//    start - TRUE for start, FALSE for end.
//
// Return:
//    none
//
static tVoid _ClearDefragFlag( int block , tBoolean start )
{
  FFS_STATE state ;
  tUByte    value ;

  value = start ? BLOCK_ERASED : BLOCK_MOVED ;  // one bit low for start, two for end

  if( block < FLAGS_BLOCK )
  {
    _ReadFlash( FFS_OFFSET_MAX , (tUByte*)&state , FFS_STATE_SIZE ) ;

    state.defragFlags[ block ] = value ;

    _WriteFlash( FFS_OFFSET_MAX , (tUByte*)&state , FFS_STATE_SIZE ) ;
  }
}


// _GetNextId
// 
// Get next available file ID
//
// Parameter(s):
//    none
//
// Return:
//    FFS_ERROR if none available, file ID otherwise.
//
static int _GetNextId()
{
  int fileId = 0 ;

  while( ( fileId < MAX_FILES ) && ( _GetFileOffset( fileId ) != FFS_ERROR ) )
  {
    fileId++ ;
  }

  if( fileId < MAX_FILES )
  {
    _SetFileOffset( fileId , _ffsOffset ) ;
  }
  else
  {
    fileId = FFS_ERROR ;
  }

  return fileId ;
}


// _WriteFlashNext
// 
// Write next available free space in flash (sequentially fills file space).
// Caller should be certain that sufficient free space is available
//
// Parameter(s):
//    buff - pointer to buffer of data to write
//    size - number of bytes to write
//
// Return:
//    none
//
static tVoid _WriteFlashNext( tUByte* buff , int size )
{
  _WriteFlash( _ffsOffset , buff , size ) ;

  _ffsOffset += size ;
}




// _FfsPushState
// 
// Pushes current state (an index) onto state stack.
//
// Parameter(s):
//    state - index of current state.
//
// Return:
//    none
//
static tVoid _FfsPushState( int state )
{
  if( _FfsStateIndex < FFS_MAX_STATES )
  {
    _FfsStates[ _FfsStateIndex ] = state ;
    _FfsStateIndex++ ;
  }
}


// _FfsPopState
// 
// Pops last pushed state from state stack.  Reduces stack size by one.
//
// Parameter(s):
//    none
//
// Return:
//    last pushed state
//
static int _FfsPopState()
{
  if( _FfsStateIndex > 0 )
  {
    _FfsStateIndex-- ;
  }
  return _FfsStates[ _FfsStateIndex ] ;
}


// _FfsGetCurrentState
// 
// Gets current state (last pushed) from state stack.  Does not effect stack size.
//
// Parameter(s):
//    none
//
// Return:
//    last pushed state
//
static int _FfsGetCurrentState() 
{
  if( _FfsStateIndex == 0 )  // this will initialize 
  {
    _FfsStates[ 0 ] = FFS_STATE_DORMANT ;
    _FfsStateIndex++ ;
  }

  return _FfsStates[ _FfsStateIndex - 1 ] ;
}


// _TimeOk
// 
// Called both for initializing FFS timer and checking if time remains.  The define
// FFS_MAX_MILLISECONDS establishes the amount of time that the FFS is allowed to
// utilize.  Maximum time of operation - 50 hours.
//
// Parameter(s):
//    init - TRUE to initialize timer, FALSE to check timer.
//
// Return:
//    TRUE if time remaining, FALSE otherwise.
//
static tBoolean _TimeOk( tBoolean init )
{
  // init = TRUE  => initialize count
  // init = FALSE => check count

  return TRUE ;  
//  // tULong 2^32ms = 4,294,967,296ms ~ 4,294,000 sec ~ 71,582 min ~ 1,193 hours ~ 50 days
//  static tULong _startTime ;
//  tBoolean timeOk ;
//  
//  if( init )
//  {
//    _startTime = GetTime() ;
//    timeOk = TRUE ;
//  }
//  else
//  {
//    timeOk = ( ( GetTime() - _startTime ) < FFS_MAX_MICROSECONDS ) ;
//  }
//  return timeOk ;  
}


// _EraseBlock
// 
// Erase a block of flash.
//
// Parameter(s):
//    blockNumber - the number of the block to erase.
//
// Return:
//    none
//
static tVoid _EraseBlock( int blockNumber )
{
  _erasingState.block = blockNumber ;
  _FfsPushState( FFS_STATE_ERASING ) ;
}


// _StateErasing
// 
// State machine implementation of the erasing process.
//
// Parameter(s):
//    none
//
// Return:
//    TRUE if complete, FALSE otherwise.
//
static tBoolean _StateErasing()
{
#if FFS_EMBEDDED
  // tim_todo IMPLEMENT FOR ACTUAL FLASH
#else // FFS_EMBEDDED
  int idx ;
  int idxStart = _erasingState.block * BLOCK_SIZE ;
  int idxEnd   = idxStart + BLOCK_SIZE    ;

  for( idx = idxStart ; idx < idxEnd ; idx++ )
  {
    _flash[ idx ] = ERASED_BYTE ;
  }

  return TRUE ;
#endif // FFS_EMBEDDED
}


// _Defrag
// 
// Perform the defrag process.  The _frag structure must be initialized before
// a call to this function.
//
// Parameter(s):
//    none
//
// Return:
//    none
//
static tVoid _Defrag()
{
  _FfsPushState( FFS_STATE_DEFRAG ) ;
}

  
// _StateDefrag
// 
// State machine implementation of the defrag process.
//
// Parameter(s):
//    none
//
// Return:
//    TRUE if complete, FALSE otherwise.
//
static tBoolean _StateDefrag()
{
  enum {
    DEFRAG_START             ,
    DEFRAG_CHECK_BLOCK_DONE ,
    DEFRAG_ERASE_BLOCK       ,
    DEFRAG_COPY_BLOCK        ,
    DEFRAG_END_FLAG          ,
    DEFRAG_ERASE_FLASHBUFF   ,
    DEFRAG_CHECK_MORE_FILES  ,
    DEFRAG_ERASE_REMAINING   ,
    DEFRAG_ERASE_LAST        ,
    DEFRAG_END 
  } ;  

  #if CONSOLE_TEST // tim_todo TEST 
  const char* DebugStrings[] =
  {
    "DEFRAG_START             " ,
    "DEFRAG_CHECK_BLOCK_DONE" ,
    "DEFRAG_ERASE_BLOCK      " ,
    "DEFRAG_COPY_BLOCK       " ,
    "DEFRAG_END_FLAG         " ,
    "DEFRAG_ERASE_FLASHBUFF  " ,
    "DEFRAG_CHECK_MORE_FILES " ,
    "DEFRAG_ERASE_REMAINING  " ,
    "DEFRAG_ERASE_LAST       " ,
    "DEFRAG_END              "
  } ;  
  #endif // CONSOLE_TEST
  
  tBoolean done = FALSE ;
  static int state = DEFRAG_START ;

  #if CONSOLE_TEST // tim_todo TEST
  printf( "%s\n" , DebugStrings[ state ] ) ;
  #endif // CONSOLE_TEST

  switch( state )
  {
  case DEFRAG_START :
  
    // if current buffer (_filebuff) empty, then read next file
    if( !_frag.remaining )
    {
      _GetFileDescriptor( _frag.offsetSrc , &(_filebuff.head) ) ;
      
      // check if end of file chain.
      if( _filebuff.head.sizeBuff == FFS_ERROR )
      {
        _frag.remaining = 0 ;
      }
      else 
      {
        // initialize source of data in flash
        _frag.offsetSrc += FILE_DESC_SIZE ;
        
        // this file may have been deleted, if so, skip over it
        if( _filebuff.head.sizeData )
        {
          _frag.remaining = _filebuff.head.sizeData + FFS_WRAPPER_SIZE ;
          _ReadFlash( _frag.offsetSrc , _filebuff.data , 
                      _filebuff.head.sizeData + FILE_DESC_SIZE ) ;
          _frag.fileptr = (tUByte*)&_filebuff ;
          _frag.offsetDst += _frag.remaining ;
        }
        
        // increment past end of file for next
        _frag.offsetSrc += _filebuff.head.sizeBuff + FILE_DESC_SIZE ;
      }
    }
    
    // now, if we have data in the file buffer, then write it
    if( _frag.remaining )
    {
      _frag.written = _WriteFlash( _frag.offsetBuff , _frag.fileptr , _frag.remaining ) ;
      _frag.remaining  -= _frag.written ;
      _frag.offsetBuff += _frag.written ;
      _frag.fileptr    += _frag.written ;
    }
    
    state = DEFRAG_CHECK_BLOCK_DONE ;

    break ;
    
  case DEFRAG_CHECK_BLOCK_DONE :
  
    // check if time to start new block
    if( _frag.remaining || ( ( _filebuff.head.sizeBuff == FFS_ERROR ) && _frag.written ) )
    {
      // clear start flag before erase/copy
      _ClearDefragFlag( _frag.nextEraseBlock , TRUE ) ;
      state = DEFRAG_ERASE_BLOCK ;
    }
    else
    {
      state = DEFRAG_CHECK_MORE_FILES ; 
    }
    break ;

  case DEFRAG_ERASE_BLOCK :
  
    // erase current block and copy flash buffer into it
    _EraseBlock( _frag.nextEraseBlock ) ;
    state = DEFRAG_COPY_BLOCK ; 
    
    break ;

  case DEFRAG_COPY_BLOCK :
  
    // copy flash buffer to current block
    _CopyBlock( FLASHBUFF_BLOCK , _frag.nextEraseBlock ) ;
    state = DEFRAG_END_FLAG ; 

    break ;
    
  case DEFRAG_END_FLAG :

    // clear end flag after erase/copy
    _ClearDefragFlag( _frag.nextEraseBlock , FALSE ) ;
    state = DEFRAG_ERASE_FLASHBUFF ; 
      
    break ;

  case DEFRAG_ERASE_FLASHBUFF :
  
    // prepare for next
    _EraseBlock( FLASHBUFF_BLOCK ) ;

    _frag.nextEraseBlock++ ;
    _frag.offsetBuff = FLASHBUFF_OFFSET ;
    state = DEFRAG_CHECK_MORE_FILES ; 
    
    break ;
    
  case DEFRAG_CHECK_MORE_FILES :

    // continue till no more files  
    if( _filebuff.head.sizeBuff != FFS_ERROR ) 
    {
      state = DEFRAG_START ; // back to start
    }
    else
    {
      state = DEFRAG_ERASE_REMAINING ;
    }

    break ;

  case DEFRAG_ERASE_REMAINING :
  
    // erase remaining blocks with data
    if( _frag.nextEraseBlock * BLOCK_SIZE < _frag.offsetSrc )
    {
      _EraseBlock( _frag.nextEraseBlock ) ;
      _frag.nextEraseBlock++ ;
      // stay in this state till done
    }
    else
    {
      state = DEFRAG_ERASE_LAST ;
    }
  
    break ;

  case DEFRAG_ERASE_LAST :
  
    // erase last data block if not erased (contains flags)
    if( _frag.nextEraseBlock < FLASHBUFF_BLOCK )
    {
      _EraseBlock( FLAGS_BLOCK ) ;
    }
    
    state = DEFRAG_END ;
  
    break ;
  
  case DEFRAG_END :
  
    // final step in reconstruction
    _RebuildFileTable() ;
    done = TRUE ;
    state = DEFRAG_START ; // prepare for next
  
    break ;
  }

  return done ;
}
