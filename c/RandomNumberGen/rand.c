#include <stdio.h>


typedef unsigned int Uint32 ;

Uint32 rand0()
{
  static Uint32 x = 102 ;
  Uint32 val = 0 ;
  int idx ;

  x ^= 0x64139f93 ;


  for( idx = 0 ; idx < 32 ; idx++ )
  {
    x = (x << 1) | (((x >> 31) & 1) ^ ((x >> 15) & 1) ^ ((x >> 4) & 1));

    val <<= 1 ;
    val |= ( x & 1 ) ;
  }

  return val ;
}


int main(int argc , char** argv)
{
  int idx ;
  Uint32 val ;

  FILE* file ;

  file = fopen( "c:\\temp\\data.txt" , "wb" ) ;

  for( idx = 0 ; idx < 1000000 ; idx++ )
  {
    val = rand0() ;

    fwrite( &val , sizeof( val ) , 1 , file ) ;
  }

  fclose( file ) ;

   return 0;
}


