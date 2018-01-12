// xyzFeature.h

#ifndef XYZFEATURE_H
#define XYZFEATURE_H

#include "utility.h"
#include "svgGroup.h"
#include "musSymbols.h"
#include "xyzMelody.h"

class featureBase : public svgGroup
{
public:
  featureBase( int xpos = 0 ) 
  : _width( 0 )
  , _xpos( xpos )
  {} ;

  virtual int width( void ) { return _width ; } ;

  int addDots( int xpos , int ypos , DURATION_T dur )
  {
  }

  void addDot( int xpos , int ypos , int size = DOT_RADIUS )
  {
    addElement( new svgEllipse( xpos , ypos , size , size , "black" ) ) ;
  }

  void addFeature( featureBase* feature ) 
  {
    addElement( feature ) ;
    _width += feature->width() ;
    _xpos += feature->width() ;
  }

  int    _width ;
  int    _xpos ;
};


class featureBar : public featureBase
{
public:
  featureBar( int xpos , int height , xyzBar& bar ) ;

private:
  static const int THICK_BAR_WIDTH = BASE_UNIT ;
  int _height ;
  void drawThinLine( int xpos )  ;
  void drawThickLine( int xpos ) ;
  void drawTwoDots( int xpos )   ;
};


class featureRest : public featureBase
{
public:
  featureRest( int xpos , xyzRest& rest ) ;

private:
};

class featureGuitarChord : public featureBase
{
public:
  featureGuitarChord( int xpos , xyzGuitarChord& chord ) 
  : _width( 0 )
  {
    addElement( new svgText( xpos , GUITAR_CHORD_OFFSET , chord._str , GUITAR_CHORD_FONT_SIZE ) ) ;
  }

  int width( void )
  {
    return _width ;
  }

private:
  int _width ;
};


class featurePath : public featureBase
{
public:
  featurePath( int xpos = 0 , int ypos = 0 , FEATURE_T type = FEATURE_WHOLE ) 
  {
    int idx = (int)type ;
    const char* def = g_featureDefs[ idx ].path ;
    _width  = g_featureDefs[ idx ].width ;

    addElement( new symBase( def ) ) ;
    transform( xpos , ypos , 0 ) ; 
  }

  int width( void )
  {
    return _width ;
  }

private:
  int _width ;
};


#endif // XYZFEATURE_H

