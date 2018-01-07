// utility.h

#ifndef UTILITY_H
#define UTILITY_H

#include <string> 
#include <vector>

#include "svgGroup.h"
#include "svgEllipse.h"
#include "svgText.h"
#include "xml.h"

using namespace std;

#define ARRAYSIZE(a) sizeof(a)/sizeof(a[0])
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define PI 3.14159265
#define DWG_WIDTH  11.0 
#define DWG_HEIGHT  8.5
#define PIXELS_PER_INCH 100

void split( vector<string> &tokens , const string &text , char sep ) ;
const std::string trimNondigits( const std::string& pString ) ;
void trim( std::string& str ) ;
void polarToRect( float radius , float angle , float* x , float* y ) ;

class symBase : public svgBase
{
public:
  symBase( const char* def ) 
  : _def( def )
  {
  } ;

  void draw( void )
  {
    xmlStartMultitag( "path" ) ;
    xmlWritePar( "d" , _def ) ;
    xmlEndMultitag() ;
  } ;

private:
  const char* _def ;
};


#endif // UTILITY_H




