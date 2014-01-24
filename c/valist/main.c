#include <stdio.h>
#include <stdarg.h>

// prints a variable argument list of ints and calculates their sum.
// parameters:
//   numargs - the number of arguments
//   ...     - the argument list of ints
// returns:
//   the sum of the integers
int valistExample( int numargs , ... )
{
  va_list valist ;
  int idx ;
  int sum = 0 ;
  int arg ;
 
  va_start( valist , numargs ) ;

  for ( idx = 0 ; idx < numargs; idx++ )
  {
    arg = va_arg( valist , int ) ;

    printf( "argument %d - %d\n" , idx , arg ) ;

    sum += arg ;
  }

  va_end( valist ) ;

  printf( "sum - %d\n\n" , sum ) ;

  return sum ;
}


#define NUM_ARGS 3
#define ARG0 2
#define ARG1 4
#define ARG2 6

int main( int argc , char *argv[] )
{
  valistExample( NUM_ARGS , ARG0 , ARG1 , ARG2 ) ;

  return(0);
}

