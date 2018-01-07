// svgConstellation.h


#ifndef SVGCONSTELLATION_H
#define SVGCONSTELLATION_H

#include "svgGroup.h"
#include "svgEllipse.h" 
#include "svgLine.h" 
#include "svgText.h" 

#include <string>

using namespace std;

#define RADIUS 100
#define NUM_TICKS 12
#define TICK_LENGTH 10
#define TEXT_OFFSET 30
#define NUM_OFFSET  10
#define TEXT_NUDGE  (5)   // needed since text not centered vertically
#define TITLE_FONT_SIZE 20

class svgConstellation : public svgGroup
{
public:
  svgConstellation() ;

  void setText( string text ) ;
  void setVector( vector<int>values ) ;

private:
} ;

#endif // SVGCONSTELLATION_H

