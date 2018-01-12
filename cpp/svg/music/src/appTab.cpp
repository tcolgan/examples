// appTab.cpp

#include "appTab.h"
#include "xyzFeature.h"
#include "xyzMelody.h"


appTab::appTab( xyzMelody& melody ) 
: _xpos( 0 )
, _melody( melody )
{
  _xpos = HORIZONTAL_START_MELODY ;
}


void appTab::end( void )
{
  int ypos = 0 ;
  for( int line = 0 ; line < TAB_NUM_LINES ; line++ )
  {
    addElement( new svgLine( 0 , ypos , _xpos , ypos ) ) ;
    ypos += TAB_LINE_SPACE ;
  }
}


void appTab::addMeasures( int first , int last )
{
  deleteAll() ;

  _xpos = HORIZONTAL_START_MELODY ;

  addMelody( _melody , first , last ) ;

  end() ;
}


void appTab::getPositionFromNote( tabPos& pos , xyzNote& note )
{
  int semitone = note.semitonesFromC0() ;

  if( semitone >= SEMITONE_START_G )
  {
    if( semitone >= SEMITONE_START_D )
    {
      if( semitone >= SEMITONE_START_A )
      {
        if( semitone >= SEMITONE_START_E )
        {
          if( semitone < SEMITONE_START_E + FRETS_USED )
          {
            pos.str  = STRING_E ;
            pos.fret = (FRET_T)(semitone - SEMITONE_START_E) ;
          }
        }
        else
        {
          pos.str  = STRING_A ;
          pos.fret = (FRET_T)(semitone - SEMITONE_START_A) ;
        }
      }
      else
      {
        pos.str  = STRING_D ;
        pos.fret = (FRET_T)(semitone - SEMITONE_START_D) ;
      }
    }
    else
    {
      pos.str  = STRING_G ;
      pos.fret = (FRET_T)(semitone - SEMITONE_START_G) ;
    }
  }
}

void appTab::addNumber( xyzNote& note )
{
  // tmctodo - may want to handle out-of-range differently
  tabPos pos( STRING_G , FRET_00 ) ; 

  getPositionFromNote( pos , note ) ;

  int ypos = ( (int)STRING_E - (int)pos.str ) * TAB_LINE_SPACE + TAB_TEXT_OFFSET ;
  char buff[ 4 ] ;
  sprintf( buff , "%d" , (int)pos.fret ) ;

  addElement( new svgText( _xpos , ypos , buff , TAB_FONT_SIZE ) ) ;
} ;


void appTab::addMelodicElement( xyzMelodyGroup* group )
{
  // tmctodo ADD LIGATURES ???
  xyzMelodicElement* element = group->getFirstElement() ;

  while( element )
  {
    if( element->type() == MELODIC_ELEMENT_NOTE )
    {  
        addMelodicElement( (xyzNote*)element ) ;
    }
    element = group->getNextElement() ;
  }
}


void appTab::addMelodicElement( xyzBar* bar )
{
  featureBar* feature = new featureBar( _xpos , TAB_HEIGHT ,  *bar ) ;
  addElement( feature ) ;
  _xpos += feature->width() ;
}

void appTab::addMelodicElement( xyzNote* note )
{
  addNumber( *note )  ;
  _xpos += durationToSpace( note->duration() ) ;
}

void appTab::addMelodicElement( xyzRest* rest )
{
  featureRest* restFeature = new featureRest( _xpos , *rest ) ;
  addElement( restFeature ) ;
  _xpos += durationToSpace( rest->duration() ) ;
}


void testTab( xyzMelody& melody )
{
  appTab tab( melody ) ;

  tab.scale( STAFF_SCALE_FACTOR ) ;
  tab.transform( TAB_OFFSET_X , TAB_OFFSET_Y , 0 ) ;

  int numMeasures = melody.getNumMeasures() ;
  bool head = true ;
  for( int first = 0 ; first < numMeasures ; first += MEASURES_PER_STAFF )
  {
    int last = first + MEASURES_PER_STAFF - 1 ;

    last = MIN( last , numMeasures - 1 ) ;
  
    tab.addMeasures( first , last ) ;
    head = false ;
    tab.draw() ;
    tab.transform( 0 , STAFF_DELTA_Y , 0 ) ;
  }
}

