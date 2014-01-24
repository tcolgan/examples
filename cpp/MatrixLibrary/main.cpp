// main.cpp

#include "matrix.h"
#include <iostream>


using namespace std; 

// solves the matrix equation y = A * x for x given y and A.
// for example suppose maty.txt contains:
//   13
//   32
//   21
// and matA.txt contains:
//   2 1 3
//   4 5 6
//   7 4 2
// then running the program:
//   matrix matA.txt maty.txt
// yields
//   1
//   2
//   3 


void OutResult( bool passed , char* str )
{
   cout << str <<  " : " ;
   passed ? ( cout << "Passed" ) : ( cout << "Failed" ) ;
   cout << endl ;
}

void RunTestSuite( CMatrix& matA , CMatrix& maty )
{
   bool passed ;
   bool passedAll = true ;

   CMatrix matx = Solve( matA , maty ) ;

   passed = ( maty == matA * matx ) ;   
   OutResult( passed , "Solve test" ) ;
   passedAll = passedAll && passed ;

   double dat1[] = { 4 , 1 , 2 , 3 } ;
   CMatrix mat1( 2 , 2, dat1 ) ;
   CMatrix mat2 = 2 * mat1 ;
   mat2 += mat1 ;
   
   passed = ( mat1 != mat2 ) ;
   OutResult( passed , "test 1" ) ;
   passedAll = passedAll && passed ;

   mat1 *= 3 ;   
   
   passed = ( mat1 == mat2 ) ;
   OutResult( passed , "test 2" ) ;
   passedAll = passedAll && passed ;
   
   mat2 = -mat1 ;
   passed = ( mat1 != mat2 ) ;
   OutResult( passed , "operator- test1" ) ;
   passedAll = passedAll && passed ;
   
   mat2 = -mat2 ;
   passed = ( mat1 == mat2 ) ;
   OutResult( passed , "operator- test2" ) ;
   passedAll = passedAll && passed ;
   
   OutResult( passedAll , "ALL TESTS PASSED" ) ;
}


int main( int argc , char** argv )
{
   bool passed ;
   bool passedAll = true ;

   CMatrix matA( argv[1] ) ;
   CMatrix maty( argv[2] ) ;
   CMatrix matx = Solve( matA , maty ) ;

   cout << matx ;

   // uncomment following to run test suite
//   RunTestSuite( matA , maty ) ;
   
   return 0 ;
}
