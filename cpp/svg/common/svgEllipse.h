// svgEllipse.h

#ifndef SVGELLIPSE_H
#define SVGELLIPSE_H

#include "svgBase.h"
#include <string>

using namespace std;


class svgEllipse : public svgBase
{
public:
  svgEllipse( float cx = 0 , float cy = 0 , 
              float rx = 100 , float ry = 100 , 
              string colorFill = "white" , string colorStroke = "black" ,
              float widthStroke = 1 , float opacityFill = 0.0 ) ;

  void draw( void ) ;

  void setFill( string color ) ;
  void setStroke( string color ) ;

private:
  float  _cx ;
  float  _cy ;
  float  _rx ;
  float  _ry ;
  string _colorFill ;
  string _colorStroke ;
  float  _widthStroke ;
  float  _opacityFill ;
} ;

#endif // SVGELLIPSE_H

