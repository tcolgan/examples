// utility.cpp

#include <math.h>

#include "utility.h"
#include "xml.h"


void split( vector<string> &tokens , const string &text , char sep ) 
{
  int start = 0 ;
  int end   = 0 ;

  while( ( end = text.find( sep , start ) ) != string::npos ) 
  {
    tokens.push_back( text.substr( start , end - start ) ) ;
    start = end + 1 ;
  }
  tokens.push_back( text.substr( start ) ) ;
}


void trim( std::string& str )
{
  str.erase( str.find_last_not_of( " \n\r\t" ) + 1 ) ;
//  str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

const std::string trimNondigits( const std::string& pString )
{
  const std::string& digits = "0123456789" ;
  const size_t begin = pString.find_first_of( digits );

  if (begin == std::string::npos)
  {
      return "" ;
  }

  const size_t end = pString.find_last_of( digits ) ;
  const size_t range = end - begin + 1;

  return pString.substr(begin, range);
}

// 0 => 12 o'clock
void polarToRect( float radius , float angle , float* x , float* y )
{
   angle = ( angle - 90 ) * 2 * PI / 360 ;  // convert degrees to radians
   *x = radius * cos( angle ) ;
   *y = radius * sin( angle ) ;
}









                       



