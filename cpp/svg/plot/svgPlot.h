// svgPlot.h

#ifndef SVGPLOT_H
#define SVGPLOT_H

#include "svgGroup.h"
#include "svgRect.h"
#include "utility.h"
#include <string>
#include <vector>

using namespace std;

#define PLOT_HEIGHT 400
#define PLOT_WIDTH  1000

#define STR_BUFF_SIZE 20
#define TEXT_OFFSET_X 20
#define TEXT_OFFSET_Y -10

#define MARKER_RADIUS 2

class svgPlot : public svgGroup
{
public:
  svgPlot( float xMin , float xMax , float yMin , float yMax , int width , int height ) ;
  void xDiv( int num , const char* format ) ;
  void yDiv( int num , const char* format ) ;
  const char* addData( std::vector<Point>& data ) ;
  Point TranslatePoint( Point& point ) ;
  void Title( string title ) ;
  void xTitle( string title ) ;
  void yTitle( string title ) ;

private:
  svgRect* _rect ;
  float    _width  ;
  float    _height ;
  float    _xMin ;
  float    _xMax ;
  float    _yMin ;
  float    _yMax ;
  int      _xDiv ;
  int      _yDiv ;
  int      _color ;
} ;

#endif // SVGGROUP_H


