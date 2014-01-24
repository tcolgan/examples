#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> /* NULL */

typedef enum {false, true}  boolean;

// :10000000 18F09FE518F09FE518F09FE518F09FE5 C0
//           18f09fe518f09fe518f09fe518f09fe5
// 
// :10001000 18F09FE50000A0E118F09FE518F09FE5 BB
//           18f09fe5586fa0b818f09fe518f09fe5
//                   ^^^^^^^^ valid user program key!!!
// :10002000 44000000D00000000801000040010000 72
//           44000000d00000000801000040010000
// 
// :10003000 78010000286E20B94003000040000000 55
//           78010000286e20b94003000040000000
// 
// :10004000 FEFFFFEA64019FE5DBF021E300D0A0E1 C1
//           feffffea64019fe5dbf021e300d0a0e1
// 
// :10005000 800040E2D7F021E300D0A0E1800040E2 40
//           800040e2d7f021e300d0     





//char teststr[] = "M&/\"?Y1CPG^48\\)_E&/\"?Y1CPG^58;Z\"X&/\"?Y1CPG^5$````T`````@!``!`\r\n" ;


// 01000078010000286e20b94003000040000000feffffea64019fe5dbf021e300d0a0e1800040e2d7f021e300d0
// uint8_t teststr[] = "M`0``>`$``\"AN(+E``P``0````/[__^ID`9_EV_`AXP#0H.&``$#BU_`AXP#0\r\n" ;
// 
// 
// uint8_t testbytes[] = {
//   0x01, 0x00, 0x00, 0x78, 0x01, 0x00, 0x00, 0x28, 
//   0x6e, 0x20, 0xb9, 0x40, 0x03, 0x00, 0x00, 0x40, 
//   0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xea, 0x64, 
//   0x01, 0x9f, 0xe5, 0xdb, 0xf0, 0x21, 0xe3, 0x00, 
//   0xd0, 0xa0, 0xe1, 0x80, 0x00, 0x40, 0xe2, 0xd7, 
// //  0xf1, 0x21, 0xe3, 0x00, 0xd0
//   0xf0, 0x21, 0xe3, 0x00, 0xd0
// } ;

//uint8_t teststr[] = "M`0``>`$``\"AN(+E``P``0````/[__^ID`9_EV_`AXP#0H.&``$#BU_`AXP#0\r\n" ;
uint8_t teststr[] = "M&/\"?Y1CPG^48\\)_E&/\"?Y1CPG^58;Z\"X&/\"?Y1CPG^5$````T`````@!``!`\r\n" ;



uint8_t testbytes[] = {
  0x18, 0xF0, 0x9F, 0xE5, 0x18, 0xF0, 0x9F, 0xE5, 
  0x18, 0xF0, 0x9F, 0xE5, 0x18, 0xF0, 0x9F, 0xE5,  
  0x18, 0xF0, 0x9F, 0xE5, 0x00, 0x00, 0xA0, 0xE1, 
  0x18, 0xF0, 0x9F, 0xE5, 0x18, 0xF0, 0x9F, 0xE5,  
  0x44, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00, 
  0x08, 0x01, 0x00, 0x00, 0x40
} ;


 

int uudecode( uint8_t* str , uint8_t* buff )
{
  // tmctodo CHECK FOR VALID FORMAT (MULTPLE OF 4 PLUS \r\n")
  int idx ;
  uint8_t temp[100] ;
  int size ;
  int idxin ;
  uint8_t* ptr ;

  idx = 0 ;
  ptr = str ;
  while( ( *ptr != '\n' ) && ( *ptr != '\r' ) )
  {
    temp[ idx ] = *ptr++ - 0x20 ;
    if( temp[ idx ] == 0x40 )
    {
      temp[ idx ] = 0 ;
    }
    idx++ ;
  }

  size = temp[0] ;
  idx-- ;

  // note size = idx * 3/4, example: size = 45, idx = 60

  idxin = 1 ;  // first byte is size, skip over that
  while( idx )
  {
    *buff++ = temp[ idxin + 0 ] << 2 | temp[ idxin + 1 ] >> 4 ;
    *buff++ = temp[ idxin + 1 ] << 4 | temp[ idxin + 2 ] >> 2 ;
    *buff++ = temp[ idxin + 2 ] << 6 | temp[ idxin + 3 ] >> 0 ;

    idxin += 4 ;
    idx -= 4 ;  // process four characters (to three) per pass
  }

  return size ;
}


int main (int argc, char *argv[])
{
  uint32_t size ;
  int idx ;

  uint8_t buff[ 1000 ] ;

  for(idx = 0 ; idx < 1000 ; idx++)
  {
    buff[idx] = 0 ;
  }

  size = uudecode( teststr , buff ) ;

  for( idx = 0 ; idx < size ; idx++ )
  {
    printf( "%2.2x" , buff[ idx ] ) ;
  }
  printf( "\n" ) ;

  printf( "%s\n" , teststr ) ;

  for( idx = 0 ; idx < size ; idx++ )
  {
    if( buff[idx] != testbytes[idx] )
    {
      printf( "Error byte #%d , expected 0x%2.2x, found 0x%2.2x\n" , idx , testbytes[idx], buff[idx] ) ;
    }
  }

  return(0);
}


 

