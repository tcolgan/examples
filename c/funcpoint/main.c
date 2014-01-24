#include <stdio.h>
#include <string.h>

// this is a test

// this is another test

// this is a third test


typedef float (*PFUNC)( float , float ) ;

float FuncAdd( float var1 , float var2 ) 
{
  return var1 + var2 ;
}

float FuncSubtract( float var1 , float var2 ) 
{
  return var1 - var2 ;
}

float FuncMultiply( float var1 , float var2 ) 
{
  return var1 * var2 ;
}

float FuncDivide( float var1 , float var2 ) 
{
  return var1 / var2 ;
}

struct
{
  PFUNC pfunc ;
  char* str ;
}
func[] =
{
  &FuncAdd      , "Add"      ,
  &FuncSubtract , "Subtract" ,
  &FuncMultiply , "Multiply" ,
  &FuncDivide   , "Divide"   ,
} ;

#define NUMELEM (sizeof( func ) / sizeof( func[0] ) )

PFUNC GetFunction( char* str )
{
  PFUNC pfunc ;
  int idx ;

  for( idx = 0 ; idx < NUMELEM ; idx++ )
  {
    if( !strcmp( str , func[ idx ].str ) )
    {
      return func[ idx ].pfunc ;
    }
  }
  return NULL ;
}

int main (int argc, char *argv[])
{
  int idx ;
  char* str = "Multiply" ;
  float var1 = 2 ;
  float var2 = 3 ;

  PFUNC pfunc ;

  pfunc = GetFunction( str ) ;

  if( pfunc )
  {
    printf( "%s %f and %f = %f\n" , str , var1 , var2 , pfunc( var1 , var2 ) ) ;
  }
  else
  {
    printf( "string not found\n" ) ;
  }

  return(0);
}

