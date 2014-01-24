#include <stdio.h>
#include <stdlib.h> /* NULL */


#define RECEIVE_STRING_BUFFER_SIZE 100

typedef enum {false, true}  boolean;

static char tmpbuff[ RECEIVE_STRING_BUFFER_SIZE+1 ] ;


// utility function (move?)
char* strchrX( char* str , int ch ) ;
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


char* strncpyX( char* dst , const char* src , size_t num ) ;
char* strncpyX( char* dst , const char* src , size_t num )
{
  char *dscan;
  _CONST char *sscan;

  dscan = dst;
  sscan = src;
  while (num > 0)
  {
    --num;
    if ((*dscan++ = *sscan++) == '\0')
	  break;
  }
  while (num-- > 0)
  {  
    *dscan++ = '\0';
  }

  return dst;
}


// utility function (move?)
int atoiX( char* str ) ;
int atoiX( char* str ) 
{
  int val = 0 ;
  while( *str && ( *str != '\r' ) && ( *str != '\n' ) && ( *str != ' ' ) )
  {
   val = 10 * val + *str - '0' ;
   str++ ;
  }
  return val ;
}


boolean getThreeParams( char* str , uint32_t* par0 , uint32_t* par1 , uint32_t* par2 ) ;
boolean getThreeParams( char* str , uint32_t* par0 , uint32_t* par1 , uint32_t* par2 )
{
  if( !( str = strchrX( str , ' ' ) ) )
  {
    return false ;
  }
  str++ ;

  *par0 = atoiX( str ) ;

  if( !( str = strchrX( str , ' ' ) ) )
  {
    return false ;
  }
  str++ ;

  *par1 = atoiX( str ) ;

  if( !( str = strchrX( str , ' ' ) ) )
  {
    return false ;
  }
  str++ ;

  *par2 = atoiX( str ) ;

  return true ;
}


boolean getTwoParams( char* str , uint32_t* par0 , uint32_t* par1 ) ;
boolean getTwoParams( char* str , uint32_t* par0 , uint32_t* par1 )
{
  if( !( str = strchrX( str , ' ' ) ) )
  {
    return false ;
  }
  str++ ;

  *par0 = atoiX( str ) ;

  if( !( str = strchrX( str , ' ' ) ) )
  {
    return false ;
  }
  str++ ;

  *par1 = atoiX( str ) ;

  return true ;
}

int main (int argc, char *argv[])
{
  char tststr2[] = "C 2\r\n" ;
  char tststr3[] = "C 2 5\r\n" ;
//  char tststr2[] = "C 2 5\r\n" ;
//  char tststr3[] = "C 2 5 7\r\n" ;
  uint32_t par0 ;
  uint32_t par1 ;
  uint32_t par2 ;

  if( getTwoParams( tststr2 , &par0 , &par1 ) )
  {
    printf( "%s\n  par1 = %d\n  par2 = %d\n" , tststr2 , par0 , par1 ) ;
  }
  else
  {
    printf( "Error: %s\n" , tststr2 ) ;
  }


  if( getThreeParams( tststr3 , &par0 , &par1 , &par2 ) )
  {
    printf( "%s\n  par1 = %d\n  par2 = %d\n  par3 = %d\n" , 
            tststr2 , par0 , par1 , par2 ) ;
  }
  else
  {
    printf( "Error: %s\n" , tststr3 ) ;
  }


  return(0);
}

