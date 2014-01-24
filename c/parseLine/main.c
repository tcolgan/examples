#include <stdio.h>
#include <stdlib.h> /* NULL */

#define MAX_ARGS 10

static char* _args[ MAX_ARGS ] ;
static int   _numargs ;


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


// Parse a line into substrings.
//
// Uses spaces as delimitters.
// Places pointers to substrings in _args[] array.
// Sets _numargs to the number of arguments.
// Allows quoted strings (counts as one substring).
//
// Parameters:
//   str - pointer to string to parse 
//
// NOTE - str will be over-written (nulls are added) and thus must not point
//   to const data. 
void ParseLine( char* str )
{
  int quote = 0 ;
  _numargs = 0 ;


  while( str && *str )  
  {
    if( quote )
    {
      if( *str == '\"' )  // see if beginning of quote
      {
        quote = 0 ;
        *str = 0 ;
      }
      str++ ;
      continue ;
    }

    if( *str == '\"' )    // see if end of quote
    {
      quote = 1 ;
      str++ ;
      if( *str )
      {
        _args[ _numargs ] = str ;
        _numargs++ ;
        str++ ;
      }
      continue ;
    }

    if( ( *str == ' ' ) || ( *str == '\t') ) // skip whitespace
    {
      *str = 0 ;
      str++ ;
      continue ;
    }

    _args[ _numargs ] = str ;
    _numargs++ ;

    str = strchrX( str , ' ' ) ;  // returns null if nothing found
  }
}


void Test( char* str )
{
  int idx = 0 ;
  char buff[ 100 ] ;

  while( *str )
  {
    buff[idx++] = *str++ ;  
  }
  buff[idx] = 0 ;

  printf( "Line : %s\n" , buff ) ; 

  ParseLine( buff ) ;

  for( idx = 0 ; idx < _numargs ; idx++ )
  {
    printf( "  idx : %d  ; parameter : [%s]\n" , idx , _args[idx] ) ;
  }
}


int main (int argc, char *argv[])
{
  Test( "this is a test" ) ;


  Test( "another\t test" ) ;

  Test( "one \"and two\" three" ) ;

  Test( "one \"and two\" \"and three\"" ) ;

  Test( "\"and one\" \"and two\" \"and three\"" ) ;

  Test( "\" and one\" \"and two \" \" and three \"" ) ;

  // handle tabs

  // handle quoted strings

  return(0);
}

