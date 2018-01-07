// svgLine.h

#ifndef SVGLINE_H
#define SVGLINE_H

#include "svgBase.h"
#include <string>

using namespace std;

class svgLine : public svgBase
{
public:
  svgLine( float x1 = 0 , float y1 = 0 , 
           float x2 = 100 , float y2 = 100 , 
           string colorStroke = "black" , float widthStroke = 1 ,
           float opacity = 1.0 ) ;

  void draw( void ) ;

  void setFill( string color ) ;
  void setEndpoints( float x1 , float y1 , float x2 , float y2 ) ;

private:
  float  _x1 ;
  float  _y1 ;
  float  _x2 ;
  float  _y2 ;
  string _colorStroke ;
  float  _widthStroke ;
  float  _opacity ;
} ;

#endif // SVGLINE_H

