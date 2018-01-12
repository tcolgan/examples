#include <cstdio>

#include "xml.h"
#include "abc.h"
#include "svgDwg.h"
#include "svgRect.h"
#include "svgLine.h"
#include "svgEllipse.h"
#include "svgText.h"
#include "svgGroup.h"
#include "appStaff.h"
#include "appTab.h"
#include "xyzMelody.h"

#define APP_DWG_WIDTH  8.5
#define APP_DWG_HEIGHT 11.0
#define PIXEL_EDGE    ( 0.25 * PIXELS_PER_INCH )
#define PIXEL_WIDTH   ( APP_DWG_WIDTH  * PIXELS_PER_INCH - 2 * PIXEL_EDGE )
#define PIXEL_HEIGHT  ( APP_DWG_HEIGHT * PIXELS_PER_INCH - 2 * PIXEL_EDGE )

int main( int argc , char** argv ) 
{
  svgDwg dwg( APP_DWG_WIDTH , APP_DWG_HEIGHT ) ;

  dwg.start() ;

  svgRect rect( PIXEL_WIDTH , PIXEL_HEIGHT , PIXEL_EDGE , PIXEL_EDGE ) ;
  rect.draw() ;

  xyzMelody melody ;
  abcFile abc( (char*)"test.abc" , melody ) ;

  xyzNote key = melody.getKey() ;

  testStaff( melody ) ;
  testTab( melody ) ;

  dwg.end() ;
}

