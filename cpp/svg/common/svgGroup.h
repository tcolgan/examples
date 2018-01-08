// svgGroup.h

#ifndef SVGGROUP_H
#define SVGGROUP_H

#include "svgBase.h"
#include <string>
#include <vector>

using namespace std;

class svgGroup : public svgBase
{
public:
  svgGroup( float xloc = 0 , float yloc = 0 , float rotate = 0 , float scaleX = 1.0 , float scaleY = 1.0 ) ;

  void draw( void ) ;
  void addElement( svgBase* element ) ;
  void transform( float xloc , float yloc , float rotate = 0 ) ;
  void scale( float scaleX , float scaleyY ) ;
  void scale( float scale ) ;
  void deleteAll( void ) ;
  void setViewport( float x , float y , float width , float height ) ;

private:
  float  _xloc ;
  float  _yloc ;
  float  _rotate ;
  float  _scaleX ;
  float  _scaleY ;
  bool   _viewport ;

  int _viewport_x ; 
  int _viewport_y ;
  int _viewport_width ;
  int _viewport_height ;
  vector<svgBase*> _vector ;
} ;

#endif // SVGGROUP_H



