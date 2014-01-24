#include <stdio.h>
#include <stdint.h>

typedef enum {false, true}  boolean;

#define INTTOSSTR_BUFF_SIZE 11  // 10 digits (max) plus one for null terminator
char* uintToStrX( uint32_t val )
{
  // max uint32 4294967295 (10 digits)
  static char buf[ INTTOSSTR_BUFF_SIZE ];
  char* ptr ;

  buf[ INTTOSSTR_BUFF_SIZE ] = 0 ; // null terminate
  ptr = &buf[ INTTOSSTR_BUFF_SIZE - 1 ] ; // start at end
  do 
  {
    *ptr-- = (val % 10) + '0';
    val /= 10;
  } while( val ) ;

  return ++ptr ;
}

char* uintToStr( uint32_t val )
{
  // max uint32 4294967295 (10 digits)
  static char buf[ INTTOSSTR_BUFF_SIZE ];
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

  idx = 0 ;
  ptr = buf ;
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

  buf[ idx ] = 0 ; // null terminate

  return buf ;
}

int main (int argc, char *argv[])
{
  printf( "%s\n" , uintToStr( 1234 ) );
  printf( "%s\n" , uintToStr( 0xffffffff ) );
  return(0);
}

