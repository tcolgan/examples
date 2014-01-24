#include <stdio.h>
#include <stdint.h>

typedef enum {false, true}  boolean;

#define COMM_BUFFER_SIZE 100


char* uitoaX( uint32_t val , char* buff ) ;

// Convert a uint32_t to string of decimal digits.
//
// Paramters:
//   val - the value to convert.
//   buff - pointer to char buffer to place result.
//
// Return:
//   pointer to end (null terminator) of string.
char* uitoaX( uint32_t val , char* buff )
{
  // max uint32 4294967295 (10 digits)
  int idx ;
  int digit ;
  boolean primed = false ;
  char* ptr ;
  uint32_t subval[] =
  {
    1000000000 ,
    100000000 ,
    10000000 ,
    1000000 ,
    100000 ,
    10000 ,
    1000 ,
    100 ,
    10 ,
    1 ,
  } ;

  ptr = buff ;

  if( val )
  {
    idx = 0 ;
    do 
    {
      digit = 0 ;
      while( val >= subval[ idx ] )
      {
        val -= subval[ idx ] ;
        digit++ ;
        primed = true ;
      }
  
      idx++ ;
  
      if( primed )
      {
        *ptr++ = '0' + digit ;
      }
    } while( val ) ;
  }
  else // handle zero value
  {
    *ptr++ = '0' ;
  }

  // handle lower digit zeroes
  while( idx < ( sizeof( subval ) / sizeof( subval[0] ) ) )
  {
    *ptr++ = '0' ;
    idx++ ;
  }

  *ptr = 0 ; // null terminate

  return ptr ;
}

char* itoaX( int val , char* buff ) ;
// Convert an int to string of decimal digits.
//
// Paramters:
//   val - the value to convert.
//   buff - pointer to char buffer to place result.
//
// Return:
//   pointer to end (null terminator) of string.
char* itoaX( int val , char* buff )
{
  if( val < 0 )
  {
    *buff++ = '-' ;
    val = -val ;
  }
  return uitoaX( val , buff ) ;
}

int main (int argc, char *argv[])
{
  char buff[ COMM_BUFFER_SIZE ] ;

  itoaX( 100 , buff ) ;
  printf( "%s\n" , buff ) ;

  uitoaX( 123 , buff ) ;
  printf( "%s\n" , buff ) ;

  itoaX( -123 , buff ) ;
  printf( "%s\n" , buff ) ;

  itoaX( 123 , buff ) ;
  printf( "%s\n" , buff ) ;

  itoaX( 0 , buff ) ;
  printf( "%s\n" , buff ) ;

  return(0);
}

