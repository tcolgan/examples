#include <iostream>
#include <iomanip>
#include <bitset>

using namespace std ; 

string uchar2hex(unsigned char inchar)
{
  ostringstream oss (ostringstream::out);
  oss << setw(2) << setfill('0') << hex << (int)(inchar);
  return oss.str();
}

void out_bytes( void* buf , int size )
{
  unsigned char* ptr = (unsigned char*)buf + size - 1 ;
  for( int idx = 0 ; idx < size ; idx++ )
  {
     cout << uchar2hex( *ptr-- ) ;
  }

  cout << "  " ;

  ptr = (unsigned char*)buf + size - 1 ;
  for( int idx = 0 ; idx < size ; idx++ )
  {
    cout << bitset<8> ( +*ptr-- ) ;
    if( idx != size - 1)
    {
      cout << "_" ;
    }
  }
}

void out_float( float val )
{
  cout << setprecision( 20 ) << std::scientific <<  setw( 30 ) << left ;
  cout << val ;
  out_bytes( (void *)&val , sizeof( float ) ) ;
  cout << endl ;
}

void out_double( double val )
{
  cout << setprecision( 20 ) << std::scientific <<  setw( 30 ) << left ;
  cout << val ;
  out_bytes( (void *)&val , sizeof( double ) ) ;
  cout << endl ;
}


int main() 
{ 
  cout << "char        : " << sizeof( char        ) << endl ; 
  cout << "short       : " << sizeof( short       ) << endl ; 
  cout << "int         : " << sizeof( int         ) << endl ; 
  cout << "long        : " << sizeof( long        ) << endl ; 
  cout << "bool        : " << sizeof( bool        ) << endl ; 
  cout << "float       : " << sizeof( float       ) << endl ; 
  cout << "double      : " << sizeof( double      ) << endl ; 
  cout << "long double : " << sizeof( long double ) << endl ; 
  cout << "wchar_t     : " << sizeof( wchar_t     ) << endl ; 

  cout << endl ;

  cout << "char" << endl ;
  char ch = 0xff ;
  cout << ch << endl ;
  cout << +ch << endl ;
  unsigned char ch_unsigned = 0xff ;
  cout << ch_unsigned << endl ;
  cout << +ch_unsigned << endl ;
  signed char ch_signed = 0xff ;
  cout << ch_signed << endl ;
  cout << +ch_signed << endl ;

  cout << endl ;

  float val_float ;
  int size_float = sizeof ( float ) ;
  unsigned char* ptr = (unsigned char *)( &val_float ) ;
  for (int idx = 0 ; idx < size_float ; idx++ )
  {
    *ptr++ = 0xff ;
  }

                                                        
  // note - these are ordered for little-endian machines.  Need to reverse for big-endian.
  unsigned char val[][4] ={
                             { 0xff , 0xff , 0xff , 0xff  } ,
                             { 0x00 , 0xff , 0xff , 0xff  } ,
                             { 0xff , 0xff , 0xff , 0x3f  } ,
                             { 0x00 , 0x00 , 0x00 , 0x30  } ,
                          } ;

  cout << endl << "floats" << endl ;

  for( int idx = 0 ; idx < sizeof( val ) / sizeof( val[0] ) ; idx++ )
  {
    out_float( *((float*)&val[ idx ]) ) ;
  }
  out_float( 100 ) ;
  out_float( 1 ) ;
  out_float( 2 ) ;
  out_float( 4 ) ;
  out_float( -1 ) ;
  out_float( -2 ) ;
  out_float( -4 ) ;

  cout << endl << "doubles" << endl ;

  out_double( 1 ) ;
  out_double( 2 ) ;
  out_double( 4 ) ;

  return 0 ; 
} 











