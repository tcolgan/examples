// svgText.h

#ifndef SVGTEXT_H
#define SVGTEXT_H

#include "svgBase.h"
#include <string>

using namespace std;

class svgText : public svgBase
{
public:
  svgText( float x = 0 , float y = 0 , string text = "" ,
           float  fontSize = 12 , string fontFamily = "Arial" ,
//           float  fontSize = 20 , string fontFamily = "Courier New" ,
           string colorFill = "black"  ,
           string anchor = "middle"
           ) ;

  void draw( void ) ;
  void setText( string text ) ;
  void setFontSize( float fontSize ) ;
  void setLocation( float x , float y ) ;
  void setAnchor( string anchor ) ;
  void setFontColor( string colorFill ) ;

private:
  float  _x ;
  float  _y ;
  string _text ;
  float  _fontSize ;
  string _fontFamily ;
  string _colorFill ;
  string _anchor ;
} ;

#endif // SVGTEXT_H


