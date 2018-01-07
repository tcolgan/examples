// svgDwg.h

#ifndef SVGDWG_H
#define SVGDWG_H

#include "utility.h"

using namespace std;

class svgDwg
{
public:
  svgDwg( float width = DWG_WIDTH , float height = DWG_HEIGHT ) ;

  void start( void ) ;
  void end( void ) ;

private:
  float _width ;
  float _height ;
} ;

#endif // SVGDWG_H

