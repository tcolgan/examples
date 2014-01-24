#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> /* NULL */

typedef enum {false, true}  boolean;

char str[] = "W 1073742336 512\r\n" ;
//char str[] = "W1073742336 512\r\n" ;
//char str[] = "W 1073742336\r\n" ;
//char str[] = "W 1073742336 512\n" ;

char* strchrX( char* str , int ch )
{
  while( *str )
  {
    if( *str == ch )
    {
      return str ;
    }
    str++ ;
  }
  return NULL ;
}

int atoiX( char* str ) ;
int atoiX( char* str ) 
{
  int val = 0 ;
  while( *str )
  {
   val = 10 * val + *str - '0' ;
   str++ ;
  }
  return val ;
}

boolean getAddressAndSize( char* str , uint32_t* addr , uint32_t* size ) ;
boolean getAddressAndSize( char* str , uint32_t* addr , uint32_t* size )
{
  char* end ;
  char* addrstr ;
  char* sizestr ;
  
  addrstr = strchrX( str , ' ' ) ;
  if( !addrstr )
  {
    return false ;
  }
  addrstr++ ;

  sizestr = strchrX( addrstr , ' ' ) ;
  if( !sizestr )
  {
    return false ;
  }
  sizestr++ ;

  *( sizestr - 1 ) = 0 ;
  end = strchrX( sizestr , '\r' ) ;
  if( !end )
  {
    return false ;
  }
  *end = 0 ;

  *addr = atoiX( addrstr ) ;
  *size = atoiX( sizestr ) ;

  return true ;
}

int main (int argc, char *argv[])
{
  uint32_t addr ;
  uint32_t size ;

  if( !getAddressAndSize( str , &addr , &size ) )
  {
    printf( "FAILED\n" ) ;
  }
  else
  {
    printf( "address %d = 0x%8.8x\n" , addr , addr ) ;
    printf( "size    %d\n" , size ) ;
  }

  return(0);
}

