// ffstest.c
//
// Test program for ffs.c - flash file system functions

#include "ffs.h"

#include <stdio.h>
#include <conio.h>
#include <stddef.h>

tUByte buffer[ MAX_FILE_SIZE ] ;
extern tUByte _flash[ FFS_TOTAL_SIZE ] ;  // for testing only

tVoid TstFillMemory( tUByte* buff , int size , tUByte val ) ;
tVoid TstPrintData( tUByte* data , int size , int offset ) ;
tVoid TstPrintFileInfo( tBoolean data );
tVoid TstPrintFlash() ;

extern tVoid _DefragTotal() ; // exposed for testing

tVoid TstFillMemory( tUByte* buff , int size , tUByte val )
{
  int idx ;

  for( idx = 0 ; idx < size ; idx++ )
  {
    buff[ idx ] = val ;
  }
}


#define INDENT  "  "
#define LINELENGTH 16
tVoid TstPrintData( tUByte* data , int size , int offset )
{
  int idx ;
  int linecount = 0 ;

  for( idx = 0 ; idx < size ; idx++ )
  {
    if( !linecount )
    {
      printf( INDENT ) ;
      printf( "%4.4x : " , offset ) ;
    }

    printf( "%2.2x " , *data ) ;
    linecount++ ;
    data++ ;
    offset++ ;

    if( linecount >= LINELENGTH )
    {
      printf( "\n" ) ;
      linecount = 0 ;
    }
    else if( !( linecount % 4 ) )
    {
      printf( "  " ) ;
    }
  }
}


#define FORMFEED 0x0c
tVoid TstPrintFlash( tUByte* flash )
{
  int idxBlock;
  int offset ;

  for( idxBlock = 0 ; idxBlock < NUM_BLOCKS ; idxBlock++ )
  {
    printf( "Block : 0x%2.2x\n" , idxBlock ) ;

    offset = idxBlock * BLOCK_SIZE ;
    TstPrintData( &flash[ offset ] , BLOCK_SIZE , offset ) ;
  }

  printf( "%c" , FORMFEED ) ;
}


tVoid TstPrintFileInfo( tBoolean data )
{
  int fileId ;

  printf( "Remaining = 0x%4.4x\n" , FfsGetFreeSpace() ) ;

  fileId = FfsGetNextFileId( TRUE ) ;
  do
  {
    int size ;
    printf( "File ID : %d , size = 0x%4.4x\n" , fileId , FfsGetFileSize( fileId ) ) ;
    if( data )
    {
      size = FfsReadFile( fileId , buffer , MAX_FILE_SIZE ) ;
      TstPrintData( buffer , size , 0 ) ;
    }
    fileId = FfsGetNextFileId( FALSE ) ;

  } while( fileId != FFS_ERROR ) ;
}


typedef enum {
  OP_WRITE ,
    OP_ERASE
} OP_TYPE ;


typedef struct TESTDATA
{
  OP_TYPE  type ;
  int      size ;
  tUByte   val  ;
} TESTDATA ;


TESTDATA data[] =
{
   OP_WRITE , 0x80 , 0xf0 ,                            // 1    00
   OP_WRITE , 0x40 , 0xf1 ,                            // 2    01
   OP_WRITE , 0x60 , 0xf2 ,                            // 3    02
   OP_WRITE , 0x40 , 0xf3 ,                            // 4    03
   OP_WRITE , 0x90 , 0xf4 ,                            // 5    04
   OP_WRITE , 0x40 , 0xf5 , // this one overflows      // 6    05
   OP_ERASE , 0x02 , 0x00 ,                            // 7    06
   OP_WRITE , 0x20 , 0xaa ,                            // 8    07
} ;


#define NUM_OPER  ( sizeof( data ) / sizeof( *data ) )


tVoid TstClearScreen()
{
  int idx ;
  for( idx = 0 ; idx < 100 ; idx++ )
  {
    printf( "\n" ) ;
  }
}


typedef struct SNAPSHOT
{
  tUByte before[FFS_TOTAL_SIZE] ;
  tUByte after [FFS_TOTAL_SIZE] ;
} SNAPSHOT ;


SNAPSHOT snapshots[NUM_OPER+1] ;


tVoid TstCopyFlash( tUByte* dst , tUByte* src )
{
  int idx ;
  
  for( idx = 0 ; idx < FFS_TOTAL_SIZE ; idx++ )
  {
    dst[idx] = src[idx] ;
  }
}

tBoolean TstFlashCompare( tUByte* flash0 , tUByte* flash1 )
{
  int size = FFS_TOTAL_SIZE ;
  tBoolean equal ;

  do {
    equal = ( *flash0 == *flash1 ) ;
    flash0++ ;
    flash1++ ;
    size-- ;
  }
  while( size && equal ) ;

  return equal ;
}

#define BIG_NUMBER 0x7fffffff

int TstRunTest( int operMax , int testCount )
{
  // returns number completed operations
  int idx = 0 ;

  gTestCount = BIG_NUMBER ;
  FfsEraseAll() ;

  gTestCount = testCount ;
  
  while( ( idx < operMax ) && ( gTestCount > 0 ) ) 
  {
     if( data[ idx ].type == OP_WRITE )
     {
        TstFillMemory( buffer , data[idx].size , data[idx].val ) ;
        FfsWriteFile( buffer , data[idx].size ) ;
     }
     else
     {
        FfsDeleteFile( data[idx].size ) ;
     }

     idx++ ;
  }
  
  if( gTestCount < 0 )
  {
    idx-- ;
  }

  return idx ;
}


int main( int argc , char** argv )
{
  int operMax ;
  int operComplete ;
  int totalWrites ;
  SNAPSHOT stapshotCurrent ;
  int testCount ;
  tBoolean passed ;

  int test = NUM_OPER ;

  // store snapshots of successful operations for comparison
  for( operMax = 0 ; operMax <= NUM_OPER ; operMax++ )
  {
    TstRunTest( operMax , BIG_NUMBER ) ;
    totalWrites = BIG_NUMBER - gTestCount ;

    TstCopyFlash( snapshots[operMax].before , _flash ) ;
    _DefragTotal() ;
    TstCopyFlash( snapshots[operMax].after , _flash ) ;
  }

  // print normal flash contents for each operation
//  for( operMax = 0 ; operMax <= NUM_OPER ; operMax++ )
//  {
//    TstPrintFlash( snapshots[operMax].before ) ;
//    TstPrintFlash( snapshots[operMax].after  ) ;
//  }

  // run test of power failure after each write
  testCount = 0 ; 
  do
  {
    operComplete = TstRunTest( NUM_OPER , testCount ) ;
   
    TstCopyFlash( stapshotCurrent.before , _flash ) ;
  
    gTestCount = BIG_NUMBER ;
    FfsInit() ;
    _DefragTotal() ;
    TstCopyFlash( stapshotCurrent.after , _flash  ) ;
  
    passed = TstFlashCompare( stapshotCurrent.after , snapshots[operComplete].after ) ;
    if( !passed )
    {
      // under some circumstances operation may be complete even though interrupted
      if( operComplete < NUM_OPER )
      {
        passed = TstFlashCompare( stapshotCurrent.after , snapshots[operComplete+1].after ) ;
      }
    }
    
    if( !passed )
    {
      // print flash contents for failed test
      printf( "Good before\n" ) ;
      TstPrintFlash( snapshots[operComplete].before ) ;
      printf( "-------------------------------------------------------------\n" ) ;
      printf( "Good after\n" ) ;
      TstPrintFlash( snapshots[operComplete].after ) ;
      printf( "-------------------------------------------------------------\n" ) ;
      printf( "Bad before\n" ) ;
      TstPrintFlash( stapshotCurrent.before ) ;
      printf( "-------------------------------------------------------------\n" ) ;
      printf( "Bad after\n" ) ;
      TstPrintFlash( stapshotCurrent.after ) ;
      printf( "-------------------------------------------------------------\n" ) ;
      printf( "testCount = 0x%4.4x\n" , testCount ) ;
      printf( "=============================================================\n" ) ;
    }

    testCount++ ;

  } while( ( testCount < totalWrites ) && passed ) ;

  return 0 ;
}

