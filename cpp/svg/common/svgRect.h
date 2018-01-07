// svgRect.h

#ifndef SVGRECT_H
#define SVGRECT_H

#include "svgBase.h"
#include <string>

using namespace std;

class svgRect : public svgBase
{
public:
  svgRect( float width = 100 , float height = 100 , 
           float xloc = 0 , float yloc = 0 , 
           string colorFill = "white" , string colorStroke = "black" ,
           float widthStroke = 1 , float opacityFill = 0.0 ) ;

  void draw( void ) ;

private:
  float  _width ;
  float  _height ;
  float  _xloc ;
  float  _yloc ;
  string _colorFill ;
  string _colorStroke ;
  float  _widthStroke ;
  float  _opacityFill ;
} ;

#endif // SVGRECT_H

