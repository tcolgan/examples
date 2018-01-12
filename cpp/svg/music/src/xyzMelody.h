// xyzMelody.h

#ifndef XYZMELODY_H
#define XYZMELODY_H

#include "appUtility.h"

typedef enum
{
  SIGNATURE_SPECIAL_NO     ,
  SIGNATURE_SPECIAL_COMMON ,
  SIGNATURE_SPECIAL_CUT    ,
} SIGNATURE_SPECIAL_T ;


typedef enum
{
  MELODIC_ELEMENT_NOTE         ,
  MELODIC_ELEMENT_REST         ,
  MELODIC_ELEMENT_BAR          ,
  MELODIC_ELEMENT_GROUP        ,
  MELODIC_ELEMENT_MELODY       ,
  MELODIC_ELEMENT_GUITAR_CHORD ,

} MELODIC_ELEMENT_T ;


class xyzTimeSignature
{
public:
  xyzTimeSignature( int num = DEFAULT_TIMESIG_NUM , int den = DEFAULT_TIMESIG_DEN 
                  , SIGNATURE_SPECIAL_T special =  SIGNATURE_SPECIAL_NO )
  : num( num )
  , den( den )
  , special( special ) 
  {
  }

  void setValues( int numNew = DEFAULT_TIMESIG_NUM , int denNew = DEFAULT_TIMESIG_DEN
                , SIGNATURE_SPECIAL_T specialNew =  SIGNATURE_SPECIAL_NO )
  {
    num = numNew ;
    den = denNew ;
    special = specialNew ;
  }

  int                 num ;
  int                 den ;
  SIGNATURE_SPECIAL_T special ;

} ;


class xyzMelodicElement
{
public:
  xyzMelodicElement( MELODIC_ELEMENT_T type )
  : _type( type ) {} ;

  MELODIC_ELEMENT_T type() 
  {
    return _type ;
  } ;

private:
  MELODIC_ELEMENT_T _type ;
};


class xyzGuitarChord : public xyzMelodicElement
{
public:
  xyzGuitarChord( string str )
  : _str( str )
  , xyzMelodicElement( MELODIC_ELEMENT_GUITAR_CHORD )
  { 
  } ;

  string _str ;
private:
};


class xyzBar : public xyzMelodicElement
{
public:
  xyzBar( BAR_T bartype )
  : _bartype( bartype )
  , xyzMelodicElement( MELODIC_ELEMENT_BAR )
  { 
  } ;

  BAR_T _bartype ;
private:
};


class xyzRest : public xyzMelodicElement
{
public:
  xyzRest( DURATION_T duration = DURATION_DEFAULT )
  : _duration( duration )
  , xyzMelodicElement( MELODIC_ELEMENT_REST )
  { 
  } ;

  DURATION_T duration()
  {
    return _duration ;
  }

private:
  DURATION_T    _duration   ;
};


class xyzNote : public xyzMelodicElement
{
public:

  xyzNote( PITCH_CLASS_T pitch      = PITCH_CLASS_C 
         , ACCIDENTAL_T  accidental = ACCIDENTAL_NATURAL
         , OCTAVE_T      octave     = OCTAVE_4           
         , DURATION_T    duration   = DURATION_DEFAULT
         ) ;

  bool operator>(const xyzNote& other) const ;
  bool operator<(const xyzNote& other) const ;
  bool operator==(const xyzNote& other) const ;
  bool operator!=(const xyzNote& other) const ;

  INTERVAL_T interval(const xyzNote& key) const ;

  void nextPitch( xyzNote& key , MODE_T mode ) ;
  void prevPitch( xyzNote& key , MODE_T mode ) ;
  void nextSemitone( bool useSharp = true ) ;
  void prevSemitone( bool useSharp = true  ) ;
  void addInterval( INTERVAL_T interval , bool useSharp = true ) ;
  void subtractInterval( INTERVAL_T interval , bool useSharp = true ) ;

  void sharpToFlat( void ) ;

  bool isNatural( void ) ;
  bool isSharp( void ) ;
  bool isFlat( void ) ;

  int semitonesFromC0( void ) const ;
  int semitonesFromC( void ) const ;

  void init( PITCH_CLASS_T pitch      = PITCH_CLASS_C 
           , ACCIDENTAL_T  accidental = ACCIDENTAL_NATURAL
           , OCTAVE_T      octave     = OCTAVE_4           
           , DURATION_T    duration   = DURATION_DEFAULT  ) ;

  string text( void ) ;
  string color( void ) ;

  PITCH_CLASS_T pitch( void ) ;
  ACCIDENTAL_T  accidental( void ) ;
  OCTAVE_T octave( void ) ;
  DURATION_T duration( void ) ;
  void duration( DURATION_T duration ) ;

private:
  PITCH_CLASS_T _pitch      ;
  ACCIDENTAL_T  _accidental ;
  OCTAVE_T      _octave     ;
  DURATION_T    _duration   ;
};


class xyzMelodyGroup : public xyzMelodicElement
{
public:
  xyzMelodyGroup( void )
  : _idx( 0 )
  , xyzMelodicElement( MELODIC_ELEMENT_GROUP )
  { 
  } ;

  ~xyzMelodyGroup( void )
  {
    deleteAll() ;
  } ;

  void addElement( xyzMelodicElement* element )
  {
    _elements.push_back( element ) ;
  }

  xyzMelodicElement* getElement( int idx )
  {
  //  idx = MAX( 0 , idx ) ;
  //  idx = MIN( idx , _elements.size() - 1 ) ;
  
    return _elements[ idx ] ;
  }

  xyzMelodicElement* getFirstElement( void )
  {
    if( _elements.size() )
    {
      _idx = 0 ;
      return _elements[ 0 ] ;
    }

    return 0 ;
  }


  xyzMelodicElement* getNextElement( void )
  {
    xyzMelodicElement* element = 0 ;

    _idx++ ;
    if( _idx < _elements.size() )
    {
      element = _elements[ _idx ] ;
    }
    return element ;
  }


  void deleteAll( void )
  {
    int numitems = _elements.size() ;
  
    for( int idx = 0 ; idx < numitems ; idx++ )
    {
      delete _elements[ idx ] ;
      _elements[ idx ] = 0 ;
    }
    _idx = 0 ;
  }

  vector <xyzMelodicElement*> _elements ;
  int _idx ;
private:
};


class xyzMelody : public xyzMelodyGroup
{
public:
  xyzMelody( void ) ;
  void setKey( xyzNote key ) ;
  void setSignature( xyzTimeSignature& sig ) ;
  void addElement( xyzMelodicElement* element ) ;
  void addElement( xyzBar* element ) ;
  void addScale( MODE_T mode = MODE_MAJOR ) ;
  int  getFirstIndex( uint measure ) ;
  int  getLastIndex( uint measure ) ;
  xyzNote getKey( void ) ;
  xyzTimeSignature getTimeSignature( void ) ;
  void setTitle( string& title ) ;
  string getTitle( void ) ;
  int  getNumMeasures( void ) ;
  int  size( void ) ;

private:
  vector<int>      _endMeasures ;  // index into _elements of measure ends
  xyzNote          _key ;
  xyzTimeSignature _sig ;
  string           _title ;
};


class xyzMelodyConsumer
{
public:
  void addMelody( xyzMelody& melody , int firstMeasure , int lastMeasure )
  {
    int idxFirst = melody.getFirstIndex( firstMeasure ) ;
    int idxLast  = melody.getLastIndex( lastMeasure ) ;

    _baseNoteSpace = NOTESPACE_FROM_DEN( melody.getTimeSignature().den ) ;
  
    for( int idx = idxFirst ; idx <= idxLast ; idx++ )
    {
      xyzMelodicElement* element = melody.getElement( idx ) ;
      MELODIC_ELEMENT_T type = element->type() ;
      
      switch( type )
      {
      case MELODIC_ELEMENT_NOTE :
        addMelodicElement( (xyzNote*)element ) ;
        break ;
      
      case MELODIC_ELEMENT_GUITAR_CHORD :
        addMelodicElement( (xyzGuitarChord*)element ) ;
        break ;

      case MELODIC_ELEMENT_BAR :
        addMelodicElement( (xyzBar*)element ) ;
        break ;
    
      case MELODIC_ELEMENT_REST :
        addMelodicElement( (xyzRest*)element ) ;
        break ;
  
      case MELODIC_ELEMENT_GROUP :
        addMelodicElement( (xyzMelodyGroup*)element ) ;
        break ;
      }
    }
  }  ;

  // tmctodo MOVE?
  int durationToSpace( DURATION_T dur ) 
  {
    return 4 * _baseNoteSpace ;
//    return dur * _baseNoteSpace ;
  }

  virtual void addMelodicElement( xyzNote* note  ) {} ;
  virtual void addMelodicElement( xyzBar*  bar   ) {} ;
  virtual void addMelodicElement( xyzRest* rest  ) {} ;
  virtual void addMelodicElement( xyzMelodyGroup* group ) {} ;
  virtual void addMelodicElement( xyzGuitarChord* chord ) {} ;

  int _baseNoteSpace ; // tmctodo MOVE?
};

#endif // XYZMELODY_H

