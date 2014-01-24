// ffstest.c
//
// Test program for ffs.c - flash file system functions

extern "C" {
#include "ffs.h"
extern tUByte _flash[ FFS_TOTAL_SIZE ] ;  // for testing only
extern tVoid _DefragTotal() ; // exposed for testing
} ;

#include <stdio.h>
#include <conio.h>
#include <stddef.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


tUByte buffer[ MAX_FILE_SIZE ] ;

tVoid TstFillMemory( tUByte* buff , int size , tUByte val ) ;
tVoid TstPrintData( tUByte* data , int size , int offset ) ;
tVoid TstPrintFlash() ;

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
tVoid TstPrintData( tUByte* data , int size , int offset , ostream& os )
{
  int idx ;
  int linecount = 0 ;

  os.setf( ios_base::hex, ios_base::basefield ) ;
  os << setfill ('0') ;
  for( idx = 0 ; idx < size ; idx++ )
  {
    if( !linecount )
    {
      os << INDENT << setw( 4 ) << offset << "  " ;
    }

    os << setw( 2 ) << (int)*data << " " ;
    linecount++ ;
    data++ ;
    offset++ ;

    if( linecount >= LINELENGTH )
    {
      os << endl ;
      linecount = 0 ;
    }
    else if( !( linecount % 4 ) )
    {
      os << "  " ;
    }
  }
}


#define FORMFEED '\f'
tVoid TstPrintFlash( tUByte* flash , ostream& os ) 
{
  int idxBlock;
  int offset ;

  os.setf( ios_base::hex, ios_base::basefield ) ;
  os << setfill ('0') ;
  for( idxBlock = 0 ; idxBlock < NUM_BLOCKS ; idxBlock++ )
  {
    os << "Block : " << setw( 2 ) << idxBlock << endl ;

    offset = idxBlock * BLOCK_SIZE ;
    TstPrintData( &flash[ offset ] , BLOCK_SIZE , offset , os ) ;
  }
                        
  os << FORMFEED ;
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
  while( FfsCheck() ) ; // tim_todo test

  gTestCount = testCount ;
  
  while( ( idx < operMax ) && ( gTestCount > 0 ) ) 
  {
     if( data[ idx ].type == OP_WRITE )
     {
        TstFillMemory( buffer , data[idx].size , data[idx].val ) ;
        FfsWriteFile( buffer , data[idx].size ) ;
        while( FfsCheck() ) ; // tim_todo test
     }
     else
     {
        FfsDeleteFile( data[idx].size ) ;
        while( FfsCheck() ) ; // tim_todo test
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
  SNAPSHOT snapshotCurrent ;
  int testCount ;
  tBoolean passed ;

  int test = NUM_OPER ;

//  ostream osGoodbase( cout ) ; 
  ofstream osGoodbase( "GoodBase.txt" , ios_base::out | ios_base::trunc ) ; 
  ofstream osTestref ( "Testref.txt"  , ios_base::out | ios_base::trunc ) ; 
  ofstream osTestact ( "Testact.txt"  , ios_base::out | ios_base::trunc ) ; 


  // store snapshots of successful operations for comparison
//  operMax = 3 ;
  for( operMax = 0 ; operMax <= NUM_OPER ; operMax++ )
  {
    TstRunTest( operMax , BIG_NUMBER ) ;
    totalWrites = BIG_NUMBER - gTestCount ;

    TstCopyFlash( snapshots[operMax].before , _flash ) ;
    _DefragTotal() ;
    while( FfsCheck() ) ; // tim_todo test
    TstCopyFlash( snapshots[operMax].after , _flash ) ;
  }

  // print normal flash contents for each operation
  for( operMax = 0 ; operMax <= NUM_OPER ; operMax++ )
  {
    osGoodbase << "Before (operation " << operMax << ")" << endl ;
    TstPrintFlash( snapshots[operMax].before , osGoodbase ) ;
    osGoodbase << "After (operation " << operMax << ")" << endl ;
    TstPrintFlash( snapshots[operMax].after , osGoodbase ) ;
  }

//#if 0
#if 1
  // run test of power failure after each write
  testCount = 0 ; 
//  testCount = 0xa1 ; 
  do
  {
    operComplete = TstRunTest( NUM_OPER , testCount ) ;
   
    TstCopyFlash( snapshotCurrent.before , _flash ) ;
  
    gTestCount = BIG_NUMBER ;

    FfsInit() ;
    while( FfsCheck() ) ; // tim_todo test

    _DefragTotal() ;
    while( FfsCheck() ) ; // tim_todo test

    TstCopyFlash( snapshotCurrent.after , _flash  ) ;
  
    passed = TstFlashCompare( snapshotCurrent.after , snapshots[operComplete].after ) ;
    if( !passed )
    {
      // under some circumstances operation may be complete even though interrupted
      if( operComplete < NUM_OPER )
      {
        passed = TstFlashCompare( snapshotCurrent.after , snapshots[operComplete+1].after ) ;
      }
    }
    
    if( !passed )
    {
      // print flash contents for failed test
      cout.setf( ios_base::hex, ios_base::basefield ) ;
      cout << "testCount = " << setw( 2 ) << setfill ('0') << testCount << endl ;
      cout << "Good before " << endl ;
      TstPrintFlash( snapshots[operComplete].before , cout ) ;
      cout << "-------------------------------------------------------------" << endl ;
      cout << "Good after" << endl ;
      TstPrintFlash( snapshots[operComplete].after , cout ) ;
      cout << "-------------------------------------------------------------" << endl ;
      cout << "Bad before" << endl ;
      TstPrintFlash( snapshotCurrent.before , cout ) ;
      cout << "-------------------------------------------------------------" << endl ;
      cout << "Bad after" << endl ;
      TstPrintFlash( snapshotCurrent.after , cout ) ;
      cout << "=============================================================" << endl ;
    }

    testCount++ ;

    osTestref << "Before" << endl ;
    TstPrintFlash( snapshots[operComplete].before , osTestref ) ;
    osTestref << "After" << endl ;
    TstPrintFlash( snapshots[operComplete].after  , osTestref ) ;

    osTestact << "Before" << endl ;
    TstPrintFlash( snapshotCurrent.before , osTestact ) ;
    osTestact << "After" << endl ;
    TstPrintFlash( snapshotCurrent.after  , osTestact) ;

    cout << "." ;

  } while( ( testCount < totalWrites ) && passed ) ;
  
#endif

  cout << ( passed ? "PASSED" : "FAILED" ) << endl ;

//  while( !_kbhit() ) ;

//  osGoodbaseFile.close() ;
//  osTestrefFile.close() ;

  return 0 ;
}

