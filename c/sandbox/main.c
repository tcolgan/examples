#include <stdio.h>

//typedef unsigned char uint8_t ;
//typedef          char  int8_t ;

int main (int argc, char *argv[])
{
  uint8_t val1 ;
  uint8_t val2 ;
  int8_t val0 ;

  val1 = 5 ;
  val2 = 250 ;
  
  val0 = val1 - val2 ;

  printf( "val0 %d , 0x%2.2x\n" , val0 , val0 ) ;

  val1 = 0 ;

  do {

    val2 = 0 ;

    do {

      val0 = val1 - val2 ;
      printf( "%4.4d ", val0 ) ;
      val2++ ;
    } while( val2 ) ;

    printf( "\n" ) ;

    val1++ ;
  } while( val1 ) ;

  return(0);
}

