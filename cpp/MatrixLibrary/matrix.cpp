// matrix.cpp
//
// based in part on Template Numerical Toolkit (TNT) - http://math.nist.gov/tnt/

#include "matrix.h"

#include "memory.h"
#include <iomanip>
#include <fstream>

using namespace std; 


// Copy constructor
CVector::CVector( const CVector& vec ) 
{
   copy( vec ) ;
}

// Copy constructor
CMatrix::CMatrix( const CMatrix& mat ) 
: m_vecs( 0 )
{ 
   copy( mat ) ;
}

// ========================

CVector::CVector()
: m_dat( 0 )
{
}

CMatrix::CMatrix() 
: m_rows( 0 )
, m_vecs( 0 )
{ 
}

// ========================

CVector::CVector( int cols )
: m_cols( cols )
{
   m_dat = new double[ cols ] ;
}

CMatrix::CMatrix( int rows , int cols )
: m_vecs( 0 )
{
   SetSize( rows , cols ) ;
}

// ========================

CVector::CVector( int cols , double* const data ) 
: m_cols( cols )
{
   m_dat = new double[ cols ] ;
   AddData( data ) ;
}

CMatrix::CMatrix( int rows , int cols , double* const data )
: m_rows( rows )
, m_vecs( 0 )
{
   double* ptr = data ;
   m_vecs = new CVector[rows] ;
   for( int row = 0 ; row < rows ; row++ )
   {
      m_vecs[row].SetCols( cols ) ;
      m_vecs[row].AddData( ptr ) ;
      ptr += cols ;
   }
}

// ========================

CMatrix::CMatrix( char* filename ) 
: m_vecs( 0 )
{ 
   // tim_todo error handling
   CMatrix mat ;

   ifstream infile( filename ) ;

   infile >> mat ;
   infile.close();

   copy( mat ) ;
}

// ========================

CVector::~CVector()
{
   remove() ;
}

CMatrix::~CMatrix()
{
   remove() ;
}

// ========================

void CVector::copy( const CVector& vec ) 
{
   m_cols = vec.m_cols ;
   m_dat = new double[ m_cols ] ;
   for( int col = 0 ; col < m_cols ; col++ )
   {
      m_dat[ col ] = vec.m_dat[ col ] ;
   }
}

void CMatrix::copy( const CMatrix& mat ) 
{
   m_rows = mat.m_rows ;
   m_vecs = new CVector[ m_rows ] ;
   for( int row = 0 ; row < m_rows ; row++ )
   {
      m_vecs[ row ] = mat.m_vecs[ row ] ;
   }
}

// ========================

void CVector::remove()
{
   if( m_dat )
   {
      delete [] m_dat ;
      m_dat = 0 ;
   }
}

void CMatrix::remove()
{
   if( m_vecs )
   {
      delete [] m_vecs ;
      m_vecs = 0 ;
   }
}

// ========================

CVector& CVector::operator=( const CVector& rhs )
{
   if( this != &rhs ) 
   {
      remove() ;
      copy( rhs ) ;
   }
   return *this ;
}

CMatrix& CMatrix::operator=( const CMatrix& rhs ) 
{
   if( this != &rhs ) 
   {
      remove() ;
      copy( rhs ) ;
   }
   return *this ;
}

// ========================

const bool operator!=( const CVector& vec1 , const CVector& vec2 ) 
{
   return !( vec1 == vec2 ) ;
}

const double DOUBLE_EPS = 1.0e-14 ;
#define ABS(x) ((x)>0.0?(x):(-(x)))
const bool operator==( const CVector& vec1 , const CVector& vec2 ) 
{
   bool done = false ;
   bool equal = true ;
   
   int col = 0 ;
   int cols = vec1.GetCols() ;
   
   if( cols != vec2.GetCols() )
   {
      done = true ;
      equal = false ;
   }
   
   while( !done )
   {
      // tim_todo - set tolerance?
      if( ABS( vec1[ col ] - vec2[ col ] ) > DOUBLE_EPS )
      {
         done = true ;
         equal = false ;
      }
      col++ ;
      if( col >= cols )
      {
         done = true ;
      }
   }
   return equal ;
}

const bool operator!=( const CMatrix& mat1 , const CMatrix& mat2 ) 
{
   return !( mat1 == mat2 ) ;
}

const bool operator==( const CMatrix& mat1 , const CMatrix& mat2 ) 
{
   bool done = false ;
   bool equal = true ;
   
   int row = 0 ;
   int rows = mat1.GetRows() ;
   
   if( rows != mat2.GetRows() )
   {
      done = true ;
      equal = false ;
   }
   
   while( !done )
   {
      if( mat1[ row ] != mat2[ row ] )
      {
         done = true ;
         equal = false ;
      }
      row++ ;
      if( row >= rows )
      {
         done = true ;
      }
   }
   return equal ;
}

// ========================

CVector CVector::operator-()
{
   CVector vec( *this ) ;

   int cols = vec.GetCols() ;
   for( int col = 0 ; col < cols ; col++ )
   {
      vec[ col ] = -vec[ col ] ;
   }

   return vec ;
}

CMatrix CMatrix::operator-()
{
   CMatrix mat( *this ) ;
   int rows = mat.GetRows() ;

   for( int row = 0 ; row < rows ; row++ )
   {
      mat[ row ] = -mat[ row ] ;
   }

   return mat ;
}

// ========================

CVector& CVector::operator*=( double mult )
{
   for( int col = 0 ; col < m_cols ; col++ )
   {
      m_dat[ col ] *= mult ;
   }
   return *this ;
}

CMatrix& CMatrix::operator*=( double mult )
{
   for( int row = 0 ; row < m_rows ; row++ )
   {
      m_vecs[ row ] *= mult ;
   }
   return *this ;
}

// ========================

CVector& CVector::operator/=( double div )
{
   for( int col = 0 ; col < m_cols ; col++ )
   {
      m_dat[ col ] /= div ;
   }
   return *this ;
}

CMatrix& CMatrix::operator/=( double div )
{
   for( int row = 0 ; row < m_rows ; row++ )
   {
      m_vecs[ row ] /= div ;
   }
   return *this ;
}

// ========================

CVector& CVector::operator+=( const CVector& vec )
{
   // tim_todo check dimensions
   for( int col = 0 ; col < m_cols ; col++ )
   {
      m_dat[ col ] += vec[ col ] ;
   }
   return *this ;
}

//CMatrix& operator+=(CMatrix& left, const CMatrix& right)
//{
//   // tim_todo check dimensions
//   for( int row = 0 ; row < right.GetRows() ; row++ )
//   {
//      left.m_vecs[ row ] += right.m_vecs[ row ] ;
//   }
//   return left ;
//}

CMatrix& CMatrix::operator+=( const CMatrix& mat )
{
   // tim_todo check dimensions
   for( int row = 0 ; row < m_rows ; row++ )
   {
      m_vecs[ row ] += mat.m_vecs[ row ] ;
   }
   return *this ;
}

// ========================

CVector& CVector::operator-=( const CVector& vec )
{
   // tim_todo check dimensions
   for( int col = 0 ; col < m_cols ; col++ )
   {
      m_dat[ col ] -= vec[ col ] ;
   }
   return *this ;
}

CMatrix& CMatrix::operator-=( const CMatrix& mat )
{
   // tim_todo check dimensions
   for( int row = 0 ; row < m_rows ; row++ )
   {
      m_vecs[ row ] -= mat.m_vecs[ row ] ;
   }
   return *this ;
}

// ========================

double& CVector::operator[](int col) const
{
	return m_dat[col];
}

CVector& CMatrix::operator[](int row) const
{ 
   return m_vecs[row]; 
}

// ========================

double CVector::Min()
{
   int cols = m_cols ;
   double min = m_dat[ 0 ] ;

   for( int col = 0 ; col < cols ; col++ )
   {
      if( (*this)[ col ] < min  )
      {
         min = m_dat[ col ] ;
      }
   }
   return min ;
}

double CMatrix::Min()
{
   int rows = m_rows ;
   double min = (*this)[ 0 ][ 0 ] ;

   for( int row = 0 ; row < rows ; row++ )
   {
      double rowmin = (*this)[ row ].Min() ;
      if( rowmin < min )
      {
         min = rowmin ;
      }
   }
   return min ;
}

// ========================

double CVector::Max()
{
   int cols = m_cols ;
   double max = m_dat[ 0 ] ;

   for( int col = 0 ; col < cols ; col++ )
   {
      if( (*this)[ col ] > max  )
      {
         max = m_dat[ col ] ;
      }
   }
   return max ;
}

double CMatrix::Max()
{
   int rows = m_rows ;
   double max = (*this)[ 0 ][ 0 ] ;

   for( int row = 0 ; row < rows ; row++ )
   {
      double rowmax = (*this)[ row ].Max() ;
      if( rowmax > max )
      {
         max = rowmax ;
      }
   }
   return max ;
}

// ========================

CVector CVector::Sub( int col1 , int col2 )
{
   // tim_todo check dimensions
   CVector vec( col2 - col1 + 1 ) ;
   vec.AddData( &m_dat[ col1 ] ) ;

   return vec ;
}

CMatrix CMatrix::Sub( int row1 , int row2 , int col1 , int col2 )
{
   int numrows = row2 - row1 + 1 ;
   int numcols = col2 - col1 + 1 ;

   CMatrix mat( numrows , numcols ) ;

   for( int row = 0 ; row < numrows ; row++ )
   {
      mat.m_vecs[ row ] = m_vecs[ row1 ].Sub( col1 , col2 ) ;
      row1++ ;
   }

   return mat ;
}

// ========================

int CVector::GetCols() const
{
   return m_cols ;
}

int CMatrix::GetCols() const
{
   int cols = 0 ;
   if( m_vecs )
   {
      cols = m_vecs[0].GetCols() ;
   }
   return cols ;
}

int CMatrix::GetRows() const 
{
   return m_rows ;
}

// ========================

void CVector::Print( char* str ) 
{
   cout << str << " = [" ;
   cout << *this ;
   cout << "]" << endl << endl ;
}

void CMatrix::Print( char* str ) 
{
   cout << str << endl << "[" << endl ;
   cout << *this ;
   cout << "]" << endl << endl ;
}

// ========================

void CVector::SetCols( int cols )
{
   remove() ;
   m_cols = cols ;
   m_dat = new double[ cols ] ;
}

void CMatrix::SetSize( int rows , int cols )
{
   remove() ;
   m_rows = rows ;
   m_vecs = new CVector[rows] ;

   for( int row = 0 ; row < rows ; row++ )
   {
      m_vecs[row].SetCols( cols ) ;
   }
}

// ========================

void CVector::AddData( double* data )
{
   double* dst    = m_dat ;
   double* dstEnd = m_dat + m_cols ;

   while( dst < dstEnd )
   {
      *dst++ = *data++ ;
   }
}

// ====================================================

CMatrix Transpose( const CMatrix& mat )
{
   int rows = mat.GetRows() ;
   int cols = mat.GetCols() ;

   CMatrix matT( cols , rows ) ;

   for( int row = 0 ; row < rows ; row++ )
   {
      for( int col = 0 ; col < cols ; col++ )
      {
         matT[ col ][ row ] = mat[ row ][ col ] ;
      }
   }

   return matT ;
}

void CMatrix::SwapRows( int row1 , int row2 )
{ 
   CVector temp   = m_vecs[ row1 ] ;
   m_vecs[ row1 ] = m_vecs[ row2 ] ;
   m_vecs[ row2 ] = temp ;
}

// ======================================================================

ostream& operator<<( ostream& os, const CVector& vec )
{
   const int prec = 16 ;    // -X.XXXXXXXXXXXXXXXXe-XXX
	os << setiosflags( ios::right ) ;
   os << setprecision( prec ) ;
   os << setiosflags( ios::scientific ) ;
   os << setw( prec + 8 ) ; 

   int cols = vec.GetCols() ;
   for( int col = 0 ; col < cols ; col++ )
   {
      if( col ) // no space before first column
      {
         os << "  " ;
      }

      os << vec[ col ] ;
   }

   return os ;
}

ostream& operator<<( ostream& os, const CMatrix& mat )
{
   int rows = mat.GetRows() ;
   for( int row = 0 ; row < rows ; row++ )
   {
      os << mat[ row ] ;
      os << endl ;
   }

   return os ;
}

// ========================

const CVector operator+( const CVector& vec1 , const CVector& vec2 ) 
{
   // tim_todo check dimensions
   CVector vec = vec1 ;
   vec += vec2 ;
   return vec ;
}

const CMatrix operator+( const CMatrix& mat1 , const CMatrix& mat2 ) 
{
   // tim_todo check dimensions
   CMatrix mat = mat1 ;
   mat += mat2 ;
   return mat ;
}

// ========================

const CVector operator-( const CVector& vec1 , const CVector& vec2 ) 
{
   // tim_todo check dimensions
   
   CVector vec = vec1 ;

   vec -= vec2 ;

   return vec ;
}

const CMatrix operator-( const CMatrix& mat1 , const CMatrix& mat2 )
{
   CMatrix mat = mat1 ;

   mat -= mat2 ;

   return mat ;
}

// ========================

const CVector operator*( const CVector& vec , double mult ) 
{
   // tim_todo check dimensions
   CVector vec1( vec ) ;
   vec1 *= mult ;
   return vec1 ;
}

const CVector operator*( double mult , const CVector& vec ) 
{
   // tim_todo check dimensions
   CVector vec1( vec ) ;
   vec1 *= mult ;
   return vec1 ;
}

const CMatrix operator*( double mult , const CMatrix& mat ) 
{
   // tim_todo check dimensions
   CMatrix mat1( mat ) ;
   mat1 *= mult ;
   return mat1 ;
}

const CMatrix operator*( const CMatrix& mat , double mult )
{
   // tim_todo check dimensions
   CMatrix mat1( mat ) ;
   mat1 *= mult ;
   return mat1 ;
}

// ========================
                
const CVector operator/( const CVector& vec , double div ) 
{
   CVector vec1( vec ) ;
   vec1 /= div ;

   return vec1 ;
}

const CMatrix operator/( const CMatrix& mat , double div ) 
{
   CMatrix mat1( mat ) ;
   mat1 /= div ;

   return mat1 ;
}

// ========================

const CMatrix operator*( const CMatrix& mat1 , const CMatrix& mat2 )
{
   // tim_todo check dimensions

   CMatrix mat2t = Transpose( mat2 ) ;

   int rows1 = mat1.GetRows() ;
   int rows2 = mat2t.GetRows() ;

   CMatrix mat( rows1 , rows2 ) ;

   for( int row1 = 0 ; row1 < rows1 ; row1++ )
   {
      for( int row2 = 0 ; row2 < rows2 ; row2++ )
      {
         mat[ row1 ][ row2 ] = mat1[ row1 ] * mat2t[ row2 ] ;
      }
   }

   return mat ;
}

// ========================

const double operator*( const CVector& vec1 , const CVector& vec2 )
{
   // tim_todo check dimensions

   double sum = 0 ;

   int cols = vec1.GetCols() ;
   for( int col = 0 ; col < cols ; col++ )
   {
      sum += vec1[ col ] * vec2[ col ] ;
   }

   return sum ;
}

const CVector operator*( const CMatrix& mat , const CVector& vec )
{
   // tim_todo check dimensions

   int rows = mat.GetRows() ;
   CVector vec1( rows ) ;

   for( int row = 0 ; row < rows ; row++ )
   {
      vec1[ rows ] = mat[ row ] * vec ;
   }

   return vec1 ;
}

// ========================

// tim_todo eliminate need for consts
const int MAX_SIZE = 200 ;
const int MAX_LEN  = 2000 ;
istream& operator>>( istream &is , CVector &vec )
{
   // reads a line from stream and creates a vector from it.
   // assumes space delimitted

   char str[ MAX_LEN + 1 ] ;
   int idxs[ MAX_SIZE ] ;

   int count = 0 ;
   int idx = 0 ;

   is.getline( str , MAX_LEN ) ;
   int len = strlen( str ) ;

   while( idx < len ) 
   {
      // skip whitespace
      if( ( str[ idx ] == ' ' ) || ( str[ idx ] == '\t' ) )
      {
         idx++ ;
         continue ;
      }

      idxs[ count ] = idx ;

      // find end of non-whitespace
      while( ( str[ idx ] != ' ' ) && ( str[ idx ] != '\t' ) && str[ idx ] )
      {
         idx++ ;
      }

      str[ idx ] = 0 ;

      count++ ;      
      idx++ ;
   }

   vec.SetCols( count ) ;

   for( int elem = 0 ; elem < count ; elem++ )
   {
      vec[ elem ] = atof( &str[ idxs[ elem ] ] ) ;
   }

   return is ;
}

istream& operator>>( istream &is , CMatrix &mat )
{
   CVector* vecs[ MAX_SIZE ] ;
   int rows = 0 ;
   CVector vec ;

   while( is.good() )
   {
      is >> vec ;

      if( vec.GetCols() ) // tim_todo CHECK IF ALL VECTORS SAME SIZE
      {
         vecs[ rows ] = new CVector( vec ) ;
         rows++ ;
      }
   }

   if( rows != 0 )
   {
      int cols = vecs[ 0 ]->GetCols() ;

      mat.SetSize( rows , cols ) ;

      for( int row = 0 ; row < rows ; row++ )
      {
         mat[ row ] = *vecs[ row ] ;
      }
   }
   else
   {
      mat.SetSize( 0 , 0 ) ;
   }

   return is ;
}

// ========================

CVector Append( const CVector& vec1 , const CVector& vec2 ) 
{
   int col ;
   int cols1 = vec1.GetCols() ;
   int cols2 = vec2.GetCols() ;

   CVector vec( cols1 + cols2 ) ;

   for( col = 0 ; col < cols1 ; col++ )
   {
      vec[ col ] = vec1[ col ] ;
   }
   
   for( col = 0 ; col < cols2 ; col++ )
   {
      vec[ col + cols1 ] = vec2[ col ] ;
   }

   return vec ;
}

CMatrix Append( const CMatrix& mat1 , const CMatrix& mat2 ) 
{
   int rows = mat1.GetRows() ;
   int cols =  mat1.GetCols() + mat2.GetCols() ;

   CMatrix mat( rows , cols ) ;

   for( int row = 0 ; row < rows ; row++ )
   {
      mat[ row ] = Append( mat1[ row ] , mat2[ row ] ) ;
   }
   return mat ;
}

// ========================

CMatrix Solve( const CMatrix& matA , const CMatrix& matY )
{
   return Solve( Append( Transpose( matA ) * matA , Transpose( matA ) * matY ) ) ;
}

CMatrix Solve( CMatrix mat )
{
   // tim_todo check dimensions

   // performs gaussian elimination algorithm to solve system of equations y = Ax
   // last column of mat is y.  rest of mat is 'A'.

   int row ;
	int row2 ;
	int col ;

   int dim = mat.GetRows() ;
   CMatrix matOut( dim , 1 ) ;

	for( row = 0 ; row < dim ; row++ )
   {
      // tim_todo RESEARCH OPTIMIZING PIVOTS

      // check for zero at pivot, swap with another row if found
   	if( mat[row][row] == 0 )
      {
      	for( row2 = row ; row2 < dim ; row2++ )
         {
         	if( mat[row2][row] != 0 )
            {
               mat.SwapRows( row , row2 ) ;
            	break ;
            }
         }

      	if( row2 > dim )
         {
         	return matOut ;
         }
      }

    	mat[row] /= mat[row][row] ;      // normalize current row

      // cancel subsequent values in current column
   	for( row2 = row+1 ; row2 < dim ; row2++ )
      {
       	mat[row2] = mat[row2] - mat[row] * mat[row2][row] ;
      }
   }

   // diagonal elements are now all ones, and elements to left of diagonals are zero.
   // now cancel out elemement to right of diagonals
	for( row = dim-1 ; row >= 0 ; row-- )
   {
   	for( col = row+1 ; col < dim ; col++ )
      {
      	if( mat[row][col] != 0 )
         {
         	mat[row][dim] = mat[row][dim] - mat[col][dim] * mat[row][col] ;
         	mat[row][col] = 0 ;
         }
      }
   	matOut[row][0] = mat[row][dim] ;
   }

	return matOut ;
}
