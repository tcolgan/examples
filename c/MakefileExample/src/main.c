// main.c - sandbox program

#include <stdio.h>

#include "file1.h"
#include "file2.h"

int main( int argc , char** argv )
{
   int idx ;

   for( idx = 0 ; idx < 5 ; idx++ )
   {
      printf( "idx = %d\n" , idx ) ;
   }

   function1() ;
   function2() ;
}

