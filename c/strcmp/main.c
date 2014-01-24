#include <stdio.h>
#include <stdlib.h> /* NULL */

typedef enum {false, true}  boolean;


int strcmpX( char* str1 , char* str2 )
{
  while( *str1 == *str2 )
  {
    if( !*str2 )
    {
    }
  }


}


int main (int argc, char *argv[])
{
  printf( "%s ; %s ; %d\n" , "abc" , "cde" ) ;
  printf( "%s ; %s ; %d\n" , "abc" , "abc" ) ;
  printf( "%s ; %s ; %d\n" , "abc" , "abcd" ) ;
  printf( "%s ; %s ; %d\n" , "abcd" , "abc" ) ;
  return(0);
}

