// appTab.h

#ifndef APPTAB_H
#define APPTAB_H

#include "appUtility.h"

#include "svgRect.h"
#include "svgLine.h"
#include "svgText.h"
#include "svgGroup.h"
#include "xyzFeature.h"
#include "xyzMelody.h"

using namespace std;

#define TAB_LENGTH 3200

#define TAB_LINE_SPACE ( 4 * BASE_UNIT )
#define TAB_NUM_LINES  4

#define TAB_HEIGHT ( TAB_LINE_SPACE * ( TAB_NUM_LINES - 1 ) )

#define TAB_FONT_SIZE   ( TAB_LINE_SPACE )
#define TAB_TEXT_OFFSET ( 5 * TAB_FONT_SIZE / 16 )

#define SEMITONE_START_G ( 3 * SEMITONES_PER_OCTAVE + 7 )
#define SEMITONE_START_D ( 4 * SEMITONES_PER_OCTAVE + 2 )
#define SEMITONE_START_A ( 4 * SEMITONES_PER_OCTAVE + 9 )
#define SEMITONE_START_E ( 5 * SEMITONES_PER_OCTAVE + 4 )

// tmctodo - this may change
#define FRETS_USED 6

class tabPos
{
public:
  tabPos( STRING_T str , FRET_T fret )
  : str( str )
  , fret( fret )
  {
  }
  STRING_T str ;
  FRET_T   fret ;
} ;

class appTab : public xyzMelodyConsumer , public svgGroup 
{
public:
  appTab( xyzMelody& melody  ) ;

  void getPositionFromNote( tabPos& pos , xyzNote& note ) ;

  void addNumber( xyzNote& note ) ;

  void addMeasures( int first , int last ) ;

  void addMelodicElement( xyzNote* note ) ;
  void addMelodicElement( xyzBar* bar   )   ;
  void addMelodicElement( xyzRest* rest ) ;
  void addMelodicElement( xyzMelodyGroup* group ) ;

  void end( void ) ;

private:
  xyzMelody& _melody ;
  int        _xpos ;
};

void testTab( xyzMelody& melody ) ;

#endif // APPTAB_H


