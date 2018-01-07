#include <cstdio>
#include <string>
#include <iostream>

#include "utility.h"
#include "svgGroup.h"
#include "svgDwg.h"
#include "svgRect.h"

using namespace std;

typedef struct
{
   string text ;
   int points[13] ;
} PITCH_DEF_S ;


#define OFFSET_X_MIN     150
#define OFFSET_Y_MIN     200
#define OFFSET_X_DELTA   300
#define OFFSET_Y_DELTA   300

#define CONST_PER_ROW  7


void makeDwg( void )
{
   svgRect rect( 200 , 200 , 100 , 100 ) ;
   rect.draw() ;

   svgEllipse ellipse( 100 , 100 , 100 , 100 ) ;
   ellipse.draw() ;
}

#include <fstream>

int main( int argc , char** argv ) 
{
  int width  =  8.5 * PIXELS_PER_INCH ;
  int height = 11.0 * PIXELS_PER_INCH ;

  svgDwg dwg( width , height ) ; 
  svgGroup group ;

  dwg.start() ;

  makeDwg() ;
                                                             
  dwg.end() ;
}
