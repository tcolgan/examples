#include <stdio.h>

typedef unsigned long uint32_t;

#define _BIT(x)       ((1UL)<<(x))                // set bit x high, others low
#define _HIBITS(x)    (0xffffffffUL >> (31-(x)))  // set bits 0 .. x high, others low
#define _LOBITS(x)    (0x7fffffffUL >> (31-(x)))  // set bits x .. 31 low, others high  
#define _BITMASK(b,e) ( _HIBITS(e) - _LOBITS(b) ) // set bits b .. e high, others low

char* bitstr( uint32_t val )
{
  static char str[33] ;  
  int idx ;
  uint32_t mask = 0x80000000 ;

  for( idx = 0 ; idx < 32 ; idx++ )
  {
    str[ idx ] = ( val & mask ) ? 'X' : '.' ;
    mask >>= 1 ;
  }
  str[ idx ] = 0 ; // null terminate
  return str ;
}

int main (int argc, char *argv[])
{
  int beg ;
  int end ;

  for( beg = 0 ; beg < 32 ; beg++ )
  {
      printf( "_BIT(%2d) : %8.8x %s\n" , beg ,  _BIT( beg ) , bitstr( _BIT( beg ) ) ) ;
  }

  for( beg = 0 ; beg < 32 ; beg++ )
  {
      printf( "_LOBITS(%2d) : %8.8x %s\n" , beg ,  _LOBITS( beg ) , bitstr( _LOBITS( beg ) ) ) ;
  }

  for( end = 0 ; end < 32 ; end++ )
  {
    printf( "_HIBITS(%2d) : %8.8x %s\n" , end , _HIBITS( end ) , bitstr( _HIBITS( end ) ) ) ;
  }

  for( beg = 0 ; beg < 32 ; beg++ )
  {
    for( end = beg ; end < 32 ; end++ )
    {
      printf( "_BITMASK(%2d,%2d) : %8.8x %s\n" , beg , end , _BITMASK( beg , end ), bitstr( _BITMASK ( beg , end ) ) ) ;
    }
  }


  return(0);
}

