// matrix.h

#include <iostream>

class CVector
{
public:
   CVector( const CVector& vec ) ;
   CVector();
   CVector( int cols );
   CVector( int cols , double* const data ) ;
   
   virtual ~CVector();

	double& operator[](int col) const ;

   CVector& operator=(const CVector& rhs) ;

   CVector& operator*=( const double mult ) ;
   CVector& operator/=( const double div ) ;
   
   CVector& operator+=( const CVector& vec ) ;
   CVector& operator-=( const CVector& vec ) ;

   CVector operator-() ;

   friend const bool operator!=( const CVector& vec1 , const CVector& vec2 ) ;
   friend const bool operator==( const CVector& vec1 , const CVector& vec2 ) ;

   friend const CVector operator+( const CVector& vec1 , const CVector& vec2 ) ;
   friend const CVector operator-( const CVector& vec1 , const CVector& vec2 ) ;

   friend const CVector operator*( const CVector& vec , double mult ) ;
   friend const CVector operator*( double mult , const CVector& vec ) ;
   friend const CVector operator/( const CVector& vec , double div ) ;

   friend const double operator*( const CVector& vec1 , const CVector& vec2 ) ;

   friend std::ostream& operator<<( std::ostream& os, const CVector& vec ) ;
   friend std::istream& operator>>( std::istream& is , CVector& vec ) ;

   void AddData( double* data ) ;
   void SetCols( int cols ) ;
   int  GetCols() const ;

   CVector Sub( int col1 , int col2 ) ;
   double Max() ;
   double Min() ;

   void Print( char* str ) ;

//   Doesn't work with vc6.0
//   static const int MAX_SIZE = 200 ;
//   static const int MAX_LEN  = 2000 ;

private:
   void copy( const CVector& vec ) ;
   void remove() ;

   int m_cols ;
   double* m_dat ;
} ;


class CMatrix 
{
public:
   CMatrix() ;
   CMatrix( const CMatrix& mat ) ;
   CMatrix( int rows , int cols );
   CMatrix( int rows , int cols , double* const data ) ;
   CMatrix( char* filename )  ;

   virtual ~CMatrix();

   CVector& operator[](int row) const ;
   
   CMatrix& operator=(const CMatrix& rhs) ;
   
   CMatrix& operator*=( const double mult ) ;
   CMatrix& operator/=( const double div ) ;
   
   CMatrix& operator+=( const CMatrix& mat ) ;
   CMatrix& operator-=( const CMatrix& mat ) ;

   CMatrix operator-() ;

   friend const bool operator==( const CMatrix& mat1 , const CMatrix& mat2 ) ;
   friend const bool operator!=( const CMatrix& mat1 , const CMatrix& mat2 ) ;
   
   friend const CMatrix operator+( const CMatrix& mat1 , const CMatrix& mat2 ) ;
   friend const CMatrix operator-( const CMatrix& mat1 , const CMatrix& mat2 ) ;

   friend const CMatrix operator*( const CMatrix& mat , double mult ) ;
   friend const CMatrix operator*( double mult , const CMatrix& mat ) ;
   friend const CMatrix operator/( const CMatrix& mat , double div ) ;

   friend const CMatrix operator*( const CMatrix& mat1 , const CMatrix& mat2 ) ;

   friend std::ostream& operator<<( std::ostream& os,  const CMatrix& mat ) ;
   friend std::istream& operator>>( std::istream& is , CMatrix& mat ) ;

   void SetSize( int rows , int cols ) ;
   int  GetCols() const ;
   int  GetRows() const ;
        
   void    SwapRows( int row1 , int row2 ) ;

   CMatrix Sub( int row1 , int row2 , int col1 , int col2 ) ;
   double  Max() ;
   double  Min() ;

   void    Print( char* str ) ;

private:
   void copy( const CMatrix& mat ) ;
   void remove() ;

   int m_rows ;
   CVector* m_vecs ;
} ;



const CVector operator*( const CMatrix& mat , const CVector& vec ) ;

CMatrix Transpose( const CMatrix& mat ) ;

CMatrix Solve( CMatrix mat ) ;
CMatrix Solve( const CMatrix& matA , const CMatrix& matY ) ;

CVector Append( const CVector& vec1 , const CVector& vec2 ) ;
CMatrix Append( const CMatrix& mat1 , const CMatrix& mat2 ) ;
