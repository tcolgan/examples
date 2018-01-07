// svgPoly.cpp

#include "svgPoly.h"

#include "xml.h"

#include <sstream>

svgPoly::svgPoly( vector<svgPoint> points ,
                  string colorFill , string colorStroke ,
                  float widthStroke ) 
: _points( points )
, _colorFill( colorFill )        
, _colorStroke( colorStroke )        
, _widthStroke( widthStroke )    
{
}

void svgPoly::draw( void ) 
{
  xmlStartMultitag( "polygon" ) ;
  xmlWritePar( "fill" , _colorFill.c_str() ) ;
  xmlWritePar( "stroke" ,_colorStroke.c_str()  ) ;
  xmlWritePar( "stroke-width" , _widthStroke ) ;

  stringstream str ;

  vector<svgPoint>::iterator iter ;
  for ( iter = _points.begin() ; iter < _points.end() ; iter++ )
  {
    if ( str.str().length() )
    {
      str<<" , " ;
    }
    str<<(*iter).x ;
    str<<"," ;
    str<<(*iter).y ;
  }

  xmlWritePar( "points" , str.str().c_str() ) ;
//  xmlWritePar( "points" , "0,0 , 50,50 , 50,150 , 0,100" ) ;

  xmlEndMultitag() ;
}

