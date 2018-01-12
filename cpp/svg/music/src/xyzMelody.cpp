// xyzMelody.cpp

#include "xyzMelody.h"

// ==============================================================================
// xyzNote start
// ==============================================================================

xyzNote::xyzNote( PITCH_CLASS_T pitch 
                , ACCIDENTAL_T  accidental 
                , OCTAVE_T      octave     
                , DURATION_T    duration   )
: _pitch     ( pitch      )
, _accidental( accidental )
, _octave    ( octave     )
, _duration  ( duration   )
, xyzMelodicElement( MELODIC_ELEMENT_NOTE )
{
}


bool xyzNote::operator>(const xyzNote& other) const
{
  return ( semitonesFromC0() > other.semitonesFromC0() ) ;
}


bool xyzNote::operator<(const xyzNote& other) const
{
  return ( semitonesFromC0() < other.semitonesFromC0() ) ;
}


bool xyzNote::operator==(const xyzNote& other) const
{
  return ( semitonesFromC0() == other.semitonesFromC0() ) ;
}


bool xyzNote::operator!=(const xyzNote& other) const
{
  return !( *this == other ) ;
}


INTERVAL_T xyzNote::interval(const xyzNote& key) const
{
  int semi = semitonesFromC0() - key.semitonesFromC0() ;

  while( semi < 0 )
  {
    semi += SEMITONES_PER_OCTAVE ;
  }

  while( semi >= SEMITONES_PER_OCTAVE )
  {
    semi -= SEMITONES_PER_OCTAVE ;
  }

  return (INTERVAL_T)semi ;
}


void xyzNote::nextPitch( xyzNote& key , MODE_T mode )
{
  bool useFlat = key.isFlat() ;

  do
  {
    nextSemitone( !useFlat ) ;
  } while( !checkNote( semitonesFromC() - key.semitonesFromC() , mode ) ) ;

}


void xyzNote::prevPitch( xyzNote& key , MODE_T mode )
{
  bool useFlat = key.isFlat() ;

  do
  {
    prevSemitone( !useFlat ) ;
  } while( !checkNote( semitonesFromC() - key.semitonesFromC() , mode ) ) ;
}


void xyzNote::nextSemitone( bool useSharp )
{
  int idx = g_semitoneFromC[ (int)_pitch ][ (int)_accidental ] ;
  idx++ ;
  if( idx == SEMITONES_PER_OCTAVE )
  {
    idx = 0 ;
    _octave = (OCTAVE_T)( (int)_octave + 1 ) ;
  }
  _pitch      = g_noteSequence[ idx ].pitch ;
  _accidental = g_noteSequence[ idx ].accidental ;

  if( !useSharp )
  {
    sharpToFlat() ;
  }
}


void xyzNote::prevSemitone( bool useSharp  )
{
  int idx = g_semitoneFromC[ (int)_pitch ][ (int)_accidental ] ;
  idx-- ;
  if( idx < 0 )
  {
    idx = SEMITONES_PER_OCTAVE - 1 ;
    _octave = (OCTAVE_T)( (int)_octave - 1 ) ;
  }
  _pitch      = g_noteSequence[ idx ].pitch ;
  _accidental = g_noteSequence[ idx ].accidental ;

  if( !useSharp )
  {
    sharpToFlat() ;
  }
}


void xyzNote::sharpToFlat( void )
{
  if( _accidental == ACCIDENTAL_SHARP )
  {
    _pitch = (PITCH_CLASS_T)( ((int)_pitch) + 1 ) ;
    _accidental = ACCIDENTAL_FLAT ;
  }
}


bool xyzNote::isNatural( void )
{
  return _accidental == ACCIDENTAL_NATURAL ;
}


bool xyzNote::isSharp( void )
{
  return _accidental == ACCIDENTAL_SHARP ;
}


bool xyzNote::isFlat( void )
{
  return _accidental == ACCIDENTAL_FLAT ;
}


// from C0
int xyzNote::semitonesFromC0( void ) const
{
  return semitonesFromC() + SEMITONES_PER_OCTAVE * _octave ;
}


int xyzNote::semitonesFromC( void ) const
{
  return g_semitoneFromC[ (int)_pitch ][ (int)_accidental ] ;
}


void xyzNote::init( PITCH_CLASS_T pitch      , 
                    ACCIDENTAL_T  accidental , 
                    OCTAVE_T      octave     ,
                    DURATION_T    duration   )
{
  _pitch      = pitch      ;
  _accidental = accidental ;
  _octave     = octave     ;
  _duration   = duration   ;
}


string xyzNote::text( void )
{
  string text =  NoteText[ _pitch ][ _accidental ] ;
  return text ;
}


string xyzNote::color( void )
{
  string color = NoteColors[ _pitch ] ;
  return color ;
}


PITCH_CLASS_T xyzNote::pitch()
{
  return _pitch ;
}


ACCIDENTAL_T  xyzNote::accidental()  
{
  return _accidental ;
}


OCTAVE_T xyzNote::octave()          
{
  return _octave ;
}


void xyzNote::duration( DURATION_T duration )
{
  _duration = duration ;
}


DURATION_T xyzNote::duration()
{
  return _duration ;
}


void xyzNote::addInterval( INTERVAL_T interval , bool useSharp )
{
  int idx = (int)interval ;
  while( idx-- )
  {
    nextSemitone( useSharp ) ;
  }
}


void xyzNote::subtractInterval( INTERVAL_T interval , bool useSharp )
{
  int idx = (int)interval ;
  while( idx-- )
  {
    prevSemitone( useSharp ) ;
  }
}

// ==============================================================================
// xyzNote end
// ==============================================================================

// ==============================================================================
// xyzMelody start
// ==============================================================================

xyzMelody::xyzMelody( void )
{
} ;


int xyzMelody::size( void )
{
  return _elements.size() ;
}


int xyzMelody::getNumMeasures( void )
{
  int numMeasures    = _endMeasures.size() ;
  if( numMeasures )
  {
    int idxLastMeasure = _endMeasures.back() ;
    int idxLastElement = _elements.size() - 1 ;
  
    if( idxLastMeasure != idxLastElement )
    {
      numMeasures++ ;
    }
  }

  return numMeasures ;
}


void xyzMelody::addElement( xyzBar* element ) 
{
  int idx = _elements.size() ;
  if( idx )  // don't count bar when first element
  {
    BAR_T type = element->_bartype ;
    if( ( type == BAR_BEGIN ) || ( type == BAR_BEGIN_REPEAT ) )
    {
      idx-- ;

    }

    // don't count if first element of measure
    if( !( _endMeasures.size() && ( _endMeasures.back() == idx ) ) ) 
    {
      _endMeasures.push_back( idx ) ;
    }
  }
  addElement( (xyzMelodicElement*)element ) ;
}


void xyzMelody::addElement( xyzMelodicElement* element )
{
  xyzMelodyGroup::addElement( element ) ;
}


string xyzMelody::getTitle( void ) 
{
  return _title ;
}


void xyzMelody::setTitle( string& title ) 
{
  _title = title ;
}


void xyzMelody::setKey( xyzNote key ) 
{
  _key = key ;
}


void xyzMelody::setSignature( xyzTimeSignature& sig ) 
{
  _sig = sig ;
}


void xyzMelody::addScale( MODE_T mode )
{
  xyzNote note = _key ;
  for( int idx = 0 ; idx < NOTES_IN_OCTAVE ; idx++ )
  {
    addElement( new  xyzNote( note ) ) ;
    note.nextPitch( _key , mode ) ;
  }
} ;


int xyzMelody::getFirstIndex( uint measure ) 
{
  int index ;
  int numMeasures = getNumMeasures() ;

//  measure = MIN( measure , numMeasures - 1 ) ;  

  if( !measure )
  {
    index = 0 ;
  }
  else
  {
    index = _endMeasures[ measure - 1 ] + 1 ;
  }

  return index ;
}


int xyzMelody::getLastIndex( uint measure ) 
{
  int index ;
  int numMeasures = getNumMeasures() ;
//  measure = MIN( measure , numMeasures - 1 ) ;  

  if( measure > ( numMeasures - 1 ) )
  {
    index = _elements.size() - 1 ; // last measure ends with last element
  }
  else
  {
    index = _endMeasures[ measure ] ; 
  }

  return index ;
}


xyzNote xyzMelody::getKey( void )
{
  return _key ;
}


xyzTimeSignature xyzMelody::getTimeSignature( void )
{
  return _sig ;
}


// ==============================================================================
// xyzMelody end
// ==============================================================================


