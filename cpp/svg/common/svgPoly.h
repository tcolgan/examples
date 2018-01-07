// svgPoly.h

#ifndef SVGPOLY_H
#define SVGPOLY_H

#include "svgBase.h"
#include <string>
#include <vector>

using namespace std;

class svgPoly : public svgBase
{
public:
  svgPoly( vector<svgPoint> points ,
           string colorFill = "black" , string colorStroke = "black" ,
           float widthStroke = 1 ) ;

  void draw( void ) ;

private:
  string           _colorFill ;
  string           _colorStroke ;
  float            _widthStroke ;
  vector<svgPoint> _points ;
} ;

#endif // SVGPOLY_H


