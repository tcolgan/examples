// xyzFeature.cpp

#include "xyzFeature.h"


// ==============================================================================
// featureBar begin
// ==============================================================================

#define BAR_DOT_SIZE ( BASE_UNIT / 3 )
featureBar::featureBar( int xpos , int height , xyzBar& bar )
: _height( height ) 
{
  int xstart = xpos ;
  switch( bar._bartype )
  {
  case BAR_STANDARD :
    drawThinLine( xpos ) ;
    break ;

  case BAR_DOUBLE :
    drawThinLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THIN_TO_THIN ;
    drawThinLine( xpos ) ;
    break ;

  case BAR_BEGIN :
    drawThickLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THICK_TO_THIN ;
    drawThinLine( xpos ) ;
    xpos += BAR_SPACE_XTRA ;
    break ;

  case BAR_END :
    drawThinLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THICK_TO_THIN ;
    drawThickLine( xpos ) ;
    xpos += BAR_SPACE_XTRA ;
    break ;

  case BAR_BEGIN_REPEAT :
    drawThickLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THICK_TO_THIN ;
    drawThinLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THIN_TO_DOT ;
    drawTwoDots( xpos ) ;
    break ;

  case BAR_END_REPEAT :
    drawTwoDots( xpos ) ;
    xpos += BAR_SPACE_LINE_THIN_TO_DOT ;
    drawThinLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THICK_TO_THIN ;
    drawThickLine( xpos ) ;
    xpos += BAR_SPACE_XTRA ;
    break ;

  case BAR_BEGIN_AND_END_REPEAT :
    drawTwoDots( xpos ) ;
    xpos += BAR_SPACE_LINE_THIN_TO_DOT ;
    drawThinLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THICK_TO_THIN ;
    drawThickLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THICK_TO_THIN ;
    drawThinLine( xpos ) ;
    xpos += BAR_SPACE_LINE_THICK_TO_THIN ;
    drawTwoDots( xpos ) ;
    break ;
  }

  _width = xpos - xstart + BAR_SPACE_AFTER ;
}

void featureBar::drawThinLine( int xpos ) 
{
  addElement( new svgLine( xpos , 0 , xpos , _height ) ) ;
}

void featureBar::drawThickLine( int xpos ) 
{
  addElement( new svgLine( xpos , 0 , xpos , _height , "black" , THICK_BAR_WIDTH ) ) ;
}

void featureBar::drawTwoDots( int xpos ) 
{
  addDot( xpos , 3 * _height / 8 , BAR_DOT_SIZE ) ;
  addDot( xpos , 5 * _height / 8 , BAR_DOT_SIZE ) ;
}

// ==============================================================================
// featureBar end
// ==============================================================================


// ==============================================================================
// featureRest begin
// ==============================================================================

featureRest::featureRest( int xpos , xyzRest& rest )
{
  FEATURE_T feature = FEATURE_REST_HALF ;  // default, just in case
  _width = WIDTH_REST_HALF ;

  switch( rest.duration() )
  {
  case DURATION_THIRTYSECOND :
    feature = FEATURE_REST_THIRTYSECOND ;
    _width = WIDTH_REST_THIRTYSECOND ;
    break ;

  case DURATION_SIXTEENTH :
    feature = FEATURE_REST_SIXTEENTH ;
    _width = WIDTH_REST_SIXTEENTH ;
    break ;

  case DURATION_EIGTH :
    feature = FEATURE_REST_EIGTH ;
    _width = WIDTH_REST_EIGTH ;
    break ;

  case DURATION_QUARTER :
    feature = FEATURE_REST_QUARTER ;
    _width = WIDTH_REST_QUARTER ;
    break ;

  case DURATION_HALF :
    feature = FEATURE_REST_HALF ;
    _width = WIDTH_REST_HALF ;
    break ;

  case DURATION_WHOLE :
    feature = FEATURE_REST_WHOLE ;
    _width = WIDTH_REST_WHOLE ;
    break ;
  }

  addFeature( new featurePath( xpos , 0 , feature ) ) ;
}

// ==============================================================================
// featureRest end
// ==============================================================================

