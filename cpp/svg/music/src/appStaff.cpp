// appStaff.cpp

#include "appStaff.h"
#include "utility.h"
#include "musSymbols.h"
#include "xyzFeature.h"

#include "xml.h"

#define STAFF_LINE_SPACING   ( 2 * BASE_UNIT )
#define STAFF_NUM_LINES 5

#define STAFF_LINE_Y_F 0
#define STAFF_LINE_Y_D ( STAFF_LINE_Y_F + STAFF_LINE_SPACING )
#define STAFF_LINE_Y_B ( STAFF_LINE_Y_D + STAFF_LINE_SPACING )
#define STAFF_LINE_Y_G ( STAFF_LINE_Y_B + STAFF_LINE_SPACING )
#define STAFF_LINE_Y_E ( STAFF_LINE_Y_G + STAFF_LINE_SPACING )

#define STAFF_SPACE_Y_G ( -STAFF_LINE_SPACING / 2 )
#define STAFF_SPACE_Y_E ( STAFF_SPACE_Y_G + STAFF_LINE_SPACING )
#define STAFF_SPACE_Y_C ( STAFF_SPACE_Y_E + STAFF_LINE_SPACING )
#define STAFF_SPACE_Y_A ( STAFF_SPACE_Y_C + STAFF_LINE_SPACING )
#define STAFF_SPACE_Y_F ( STAFF_SPACE_Y_A + STAFF_LINE_SPACING )

#define STAFF_LINE_Y_CENTER   STAFF_LINE_Y_B

#define STAFF_Y_MIDDLE_C ( STAFF_LINE_Y_E + STAFF_LINE_SPACING )

#define FLAG2_SCALE 0.8

#define STAFF_DISTANCE_PER_OCTAVE ( STAFF_SPACE_Y_F - STAFF_LINE_Y_F )

#define DEFAULT_LENGTH 3200

#define HEAD_WIDTH    ( 4 * BASE_UNIT / 2 + 2 )
#define STEM_WIDTH    3
#define STEM_Y_0FFSET 5
#define STEM_LENGTH   ( 13 * STAFF_LINE_SPACING / 4 )

#define SEMITONES_FROM_C0_TO_F5 ( 5 * SEMITONES_PER_OCTAVE + 5 )

#define ACCIDENTAL_SPACE 5

#define LIGATURE_WIDTH ( STAFF_LINE_SPACING / 2 )
#define SHORT_LIGATURE ( 2 * BASE_UNIT )

#define CLEF_OFFSET_X  BASE_UNIT  // amount for symbol to appear to right
#define LINE_PLUS  ( 3 * BASE_UNIT )
#define LINE_MINUS ( BASE_UNIT ) 
class featureTrebleClef : public featurePath
{
public:
  featureTrebleClef( int xpos = CLEF_OFFSET_X , int ypos = STAFF_LINE_Y_G ) 
  : featurePath( xpos , ypos , FEATURE_TREBLE_CLEF ) {} ;
};


void featureNote::addStem( int length , bool flip )
{
  int y1 = _yhead ;

  if( !flip ) // stems up below this point
  {
    y1 -= STEM_Y_0FFSET ;
    _ystem = y1 - length ;
    if( _ystem > STAFF_LINE_Y_CENTER )
    {
      _ystem = STAFF_LINE_Y_CENTER ;
    }
    _xstem = _xhead + HEAD_WIDTH ;
  }
  else
  {
    y1 += STEM_Y_0FFSET ;
    _ystem = y1 + length ;
    if( _ystem < STAFF_LINE_Y_CENTER )
    {
      _ystem = STAFF_LINE_Y_CENTER ;
    }
    _xstem = _xhead + STEM_WIDTH / 2 ;
    flip = true ;
  }
  addElement( new svgLine( _xstem , y1 , _xstem , _ystem , "black" , STEM_WIDTH ) ) ;
}

void featureNote::addFlag( void )
{
  int stemLength = STEM_LENGTH ;  
  bool flip = false ;

  if( _flag == 3 )
  {
    stemLength += STAFF_LINE_SPACING ;
  }

  flip = ( _yhead <= STAFF_LINE_Y_B ) ;
  addStem( stemLength , flip ) ;

  featurePath* pathFlag = 0 ;
  featurePath* pathFlag2 = 0 ;
  if( _flag )
  {
    if( _flag == 3 )
    {  
      pathFlag = new  featurePath( _xstem , _ystem , FEATURE_FLAG ) ;
      addElement( pathFlag ) ;
      if( flip && pathFlag )
      {
        pathFlag->scale( 1.0 , -1.0 ) ;
      }
      _ystem = flip ? ( _ystem - STAFF_LINE_SPACING ) : ( _ystem + STAFF_LINE_SPACING ) ;
    }

    pathFlag = new  featurePath( _xstem , _ystem , FEATURE_FLAG ) ;
    addElement( pathFlag ) ;
    if( flip && pathFlag )
    {
      pathFlag->scale( 1.0 , -1.0 ) ;
    }

    if( _flag >= 2 )
    {
      int offset = flip ? -STAFF_LINE_SPACING : STAFF_LINE_SPACING ;

      pathFlag = new  featurePath( _xstem , _ystem + offset , FEATURE_FLAG ) ;
      addElement( pathFlag ) ;
      if( flip && pathFlag )
      {
        pathFlag->scale( FLAG2_SCALE , -FLAG2_SCALE ) ;
      }
      else
      {
        pathFlag->scale( FLAG2_SCALE , FLAG2_SCALE ) ;
      }
    }
  }
}


featureNote::featureNote( int xpos , xyzNote& note , bool drawFlags )
: _flag( 0 ) 
{
  int lineIdx = note.pitch() + ( note.octave() - OCTAVE_4 ) * ( NOTES_IN_OCTAVE - 1 ) ;
  int ypos = STAFF_Y_MIDDLE_C - lineIdx * STAFF_LINE_SPACING / 2  ;
  bool onLine = !( lineIdx % 2 ) ;
  int dots = 0 ;

  _xpos = xpos ;

  if( note.isSharp() )
  {
    addFeature( new featurePath( _xpos , ypos , FEATURE_SHARP ) ) ;
  }

  if( note.isFlat() )
  {
    addFeature( new featurePath( _xpos , ypos , FEATURE_FLAT ) ) ;
  }
  _xpos += ACCIDENTAL_SPACE ;

  FEATURE_T head ;
  bool stem = true ;
  switch( note.duration() )
  {
  case DURATION_WHOLE :
  case DURATION_WHOLE_DOT :
  case DURATION_WHOLE_DOT2 :
  case DURATION_WHOLE_DOT3 :
    head = FEATURE_WHOLE ;
    stem = false ;
    break ;

  case DURATION_HALF :
  case DURATION_HALF_DOT :
  case DURATION_HALF_DOT2 :
  case DURATION_HALF_DOT3 :
    head = FEATURE_HEAD_EMPTY ;
    break ;

  case DURATION_QUARTER :
  case DURATION_QUARTER_DOT :
  case DURATION_QUARTER_DOT2 :
  case DURATION_QUARTER_DOT3 :
    head = FEATURE_HEAD_FILLED ;
    break ;

  case DURATION_EIGTH :
  case DURATION_EIGTH_DOT :
  case DURATION_EIGTH_DOT2 :
    head = FEATURE_HEAD_FILLED ;
    _flag = 1 ;
    break ;

  case DURATION_SIXTEENTH :
  case DURATION_SIXTEENTH_DOT :
    head = FEATURE_HEAD_FILLED ;
    _flag = 2 ;
    break ;

  case DURATION_THIRTYSECOND :
    head = FEATURE_HEAD_FILLED ;
    _flag = 3 ;
    break ;
  }

  switch( note.duration() )
  {
  case DURATION_SIXTEENTH_DOT :
  case DURATION_EIGTH_DOT     :
  case DURATION_QUARTER_DOT   :
  case DURATION_HALF_DOT      :
  case DURATION_WHOLE_DOT     :
    dots = 1 ;
    break ;

  case DURATION_EIGTH_DOT2    :
  case DURATION_QUARTER_DOT2  :
  case DURATION_HALF_DOT2     :
  case DURATION_WHOLE_DOT2    :
    dots = 2 ;
    break ;

  case DURATION_QUARTER_DOT3  :
  case DURATION_HALF_DOT3     :
  case DURATION_WHOLE_DOT3    :
    dots = 3 ;
    break ;
  }


  xpos = _xpos ;
  _xhead = _xpos ;
  _yhead = ypos ;
  addFeature( new featurePath( _xpos , ypos , head ) ) ;

  if( ypos > STAFF_LINE_Y_E )
  {
      int ypos2 = STAFF_LINE_Y_E + STAFF_LINE_SPACING ;
      while( ypos2 <= ypos )
      {
        addElement( new svgLine( xpos - LINE_MINUS , ypos2 , xpos + LINE_PLUS , ypos2 ) ) ;
        ypos2 += STAFF_LINE_SPACING ;
      }
  }
  if( ypos < STAFF_LINE_Y_F )
  {
      int ypos2 = STAFF_LINE_Y_F - STAFF_LINE_SPACING ;
      while( ypos2 >= ypos )
      {
        addElement( new svgLine( xpos - LINE_MINUS , ypos2 , xpos + LINE_PLUS , ypos2 ) ) ;
        ypos2 -= STAFF_LINE_SPACING ;
      }
  }

  if( stem && ( drawFlags || !_flag ) )
  {
    addFlag() ;
  }

  if( dots )
  {
    int yoff = onLine ?  -STAFF_LINE_SPACING/2 : 0 ;
    _xpos -= ( 3 * BASE_UNIT / 2 ) ;
    while( dots )
    {
      addDot( _xpos , ypos + yoff ) ;
      _xpos += BASE_UNIT ;
      dots-- ;
    }
    _width += ( 3 * DOT_RADIUS ) ;
  }

//  int widthDots ;
//  widthDots = addDots( _xpos , ypos + yoff , note.duration() ) ;
//  _width +=  widthDots ;
//  _xpos += widthDots ;
}

class featureKeySignature : public featureBase
{
public:
  featureKeySignature( xyzNote key , int xpos = 0 ) 
  : _key( key ) 
  , featureBase( xpos )
  {
    //                   C  , Db , D  , Eb , E  , F  , Fs , G  , Ab , A  , Bb , B 
    int sharps[] = {  0  ,  0 , 2  , 0  , 4  , 0  , 6  , 1  , 0  , 3  , 0  , 5 } ;
    int flats[]  = {  0  ,  5 , 0  , 3  , 0  , 1  , 0  , 0  , 4  , 0  , 2  , 0 } ;

    int ySharp[] =
    {
      STAFF_LINE_Y_F , 
      STAFF_SPACE_Y_C ,
      STAFF_SPACE_Y_G ,
      STAFF_LINE_Y_D  ,
      STAFF_SPACE_Y_A ,
      STAFF_SPACE_Y_E ,
      STAFF_LINE_Y_B  ,
    } ;

    int yFlat[] =
    {
      STAFF_LINE_Y_B  ,
      STAFF_SPACE_Y_E ,
      STAFF_SPACE_Y_A ,
      STAFF_LINE_Y_D  ,
      STAFF_LINE_Y_G  ,
      STAFF_SPACE_Y_C ,
      STAFF_SPACE_Y_F ,
    } ;


    int idx ;
    int semitone = key.semitonesFromC() ;
    int numSharps = sharps[ semitone ] ;
    for( idx = 0 ; idx < numSharps ; idx++ )
    {
      addFeature( new featurePath( _xpos , ySharp[ idx ], FEATURE_SHARP ) ) ;
    }

    int numFlats = flats[ semitone ] ;
    for( idx = 0 ; idx < numFlats ; idx++ )
    {
      addFeature( new featurePath( _xpos , yFlat[ idx ], FEATURE_FLAT ) ) ;
    }

    _width += BASE_UNIT ;

  }

  int width( void )
  {
    return _width ;
  }

private:
  xyzNote _key ;
};


#define TIME_TEXT_WIDTH 80
#define TIME_TEXT_HEIGHT ( 2 * STAFF_LINE_SPACING * 1.5 )
//#define TIME_TEXT_FONT "Times New Roman Bold" 
//#define TIME_TEXT_FONT "Courier" 
#define TIME_TEXT_FONT "Courier Bold" 
class featureTimeSignature : public featureBase
{
public:
  featureTimeSignature( int xpos = 0 , 
                        xyzTimeSignature sig 
                          = xyzTimeSignature(DEFAULT_TIMESIG_NUM , DEFAULT_TIMESIG_DEN ) )
  : _sig( sig ) 
  {
    char buff[4] ;
    sprintf( buff , "%d" , _sig.num ) ;
    addElement( new svgText( 0 , 
                             2 * STAFF_LINE_SPACING ,
                             buff , 
                             TIME_TEXT_HEIGHT , 
                             TIME_TEXT_FONT ,
                             "black" ,
                             "start" ) ) ;

    sprintf( buff , "%d" , _sig.den ) ;
    addElement( new svgText( 0 , 
                             4 * STAFF_LINE_SPACING , 
                             buff , 
                             TIME_TEXT_HEIGHT , 
                             TIME_TEXT_FONT ,
                             "black" ,
                             "start" ) ) ;

    transform( xpos , 0 , 0 ) ; 
  }

  int width( void )
  {
    return WIDTH_TIME_SIGNATURE ;
  }

private:
  xyzTimeSignature _sig ;
};


void appStaff::addMeasures( int first , int last , bool sig )
{
  deleteAll() ;

  addFeature( new featureTrebleClef ) ;

  if( sig )
  {
    addFeature( new featureKeySignature( _melody.getKey() , _xpos ) ) ;
  
    addFeature( new featureTimeSignature( _xpos , _melody.getTimeSignature() ) ) ;
  
    addElement( new svgText( 0 , 
                             STAFF_TITLE_OFFSET ,
                             _melody.getTitle() , 
                             STAFF_TITLE_HEIGHT , 
                             STAFF_TITLE_FONT ,
                             "black" ,
                             "start" ) ) ;
  
  }
  _xpos = HORIZONTAL_START_MELODY ;  // for proper allignment with tabs

  addMelody( _melody , first , last ) ;

  end() ;
}


float appStaff::calcSlope( vector<featureNote*>& features ) 
{
  float sum_x_y ;
  float sum_x ;
  float sum_y ;
  float sum_x2 ;
  int size = features.size() ;

  vector<featureNote*>::iterator iter ;
  for ( iter=features.begin() ; iter < features.end() ; iter++ )
  {
    float x = (float)(*iter)->_xhead ;
    float y = (float)(*iter)->_yhead ;

    sum_x_y += x * y ;
    sum_x   += x ;
    sum_y   += y ;
    sum_x2  += x * x ;
  }
  return ( ( sum_x_y - sum_x * sum_y / size ) / ( sum_x2 - sum_x * sum_x / size ) ) ;
}


void appStaff::drawLigature( int x0 , int y0 , int x1 , int y1 , bool flip )
{
  vector<svgPoint> points ;

  int offset = flip ? -LIGATURE_WIDTH : LIGATURE_WIDTH ;

  points.push_back( svgPoint( x0 , y0 ) ) ;
  points.push_back( svgPoint( x1 , y1 ) ) ;
  points.push_back( svgPoint( x1 , y1 + offset ) ) ;
  points.push_back( svgPoint( x0 , y0 + offset ) ) ;

  addElement( new svgPoly( points ) ) ;
}


#define DELTAY_CUTOFF (0.5)
void appStaff::addLigaturesSub1( vector<featureNote*>& features ) 
{
  int deltaX = features.back()->_xhead - features.front()->_xhead ;
  float deltaY = calcSlope( features ) * deltaX  ;
  int stemOff = 0 ;
  int yhigh = STAFF_LINE_Y_CENTER ;
  int ylow  = STAFF_LINE_Y_CENTER ;
  bool flip ;
  int flags = 0 ;

  // determine wheter beam should slope up, down or be flat.
  if( deltaY > DELTAY_CUTOFF )
  {
    stemOff = STAFF_LINE_SPACING ;
  }
  else if( deltaY < -DELTAY_CUTOFF )
  {
    stemOff = -STAFF_LINE_SPACING ;
  }

  // determine whether stems should point up or down
  vector<featureNote*>::iterator iter ;
  for ( iter = features.begin() ; iter < features.end() ; iter++ )
  {  
    yhigh = MAX( (*iter)->_yhead , yhigh ) ;
    ylow  = MIN( (*iter)->_yhead , ylow  ) ;
    flags = MAX( (*iter)->_flag  , flags ) ;
  }
  flip = ( ( yhigh - STAFF_LINE_Y_CENTER ) < ( STAFF_LINE_Y_CENTER - ylow  ) ) ;

  int yFirst = features.front()->_yhead ;
  int xFirst = features.front()->_xhead ;
  int stemAdder = 0 ;
  int stemBase = STEM_LENGTH ; 

  if( flags > 1 )
  {
    // stem extension if more then one flag
    stemBase += ( flags - 1 ) * STAFF_LINE_SPACING ;
  }

  // calculate stem lengths.  put standard length on first then see
  //   if any are too long.  extend all by this amount.
  for ( iter=features.begin() ; iter < features.end() ; iter++ )
  {  
    int deltaXcurr =  (*iter)->_xhead - xFirst  ;
    int deltaYcurr =  (*iter)->_yhead - yFirst ;

    (*iter)->_stemLength =
      (int)( stemBase + (flip?1:-1)*(( stemOff * deltaXcurr ) / deltaX - deltaYcurr )) ;

    if( (*iter)->_stemLength < stemBase )
    {
      stemAdder = MAX( stemAdder , stemBase - (*iter)->_stemLength ) ;
    }
  }

  // draw the stems
  for ( iter=features.begin() ; iter < features.end() ; iter++ )
  {
    (*iter)->_stemLength += stemAdder ;
    (*iter)->addStem( (*iter)->_stemLength , flip ) ;
  }

  // now add the ligatures
  int offsetDelta = flip ? -STAFF_LINE_SPACING : STAFF_LINE_SPACING ;
  int offset = 0 ;
  int numnotes = features.size() ;
  for( int flagnum = 1 ; flagnum <= flags ; flagnum++ )
  {
    bool drewlast = false ;
    for( int noteidx = 1 ; noteidx < numnotes  ; noteidx++ )
    {
      featureNote& note0 = *features[noteidx-1] ;
      featureNote& note1 = *features[noteidx] ;
      int x0 = note0._xstem ;
      int y0 = note0._ystem + offset ;
      int x1 = note1._xstem ;
      int y1 = note1._ystem + offset ;

      int deltaX = SHORT_LIGATURE ;
      int deltaY = ( y1 - y0 ) * deltaX / ( x1 - x0 );

      if( ( note0._flag >= flagnum ) && ( note1._flag >= flagnum ) )
      {
        // ligature goes between two notes if both have flags
        drawLigature( x0 , y0 , x1 , y1 , flip ) ;
        drewlast = true ;
      }
      // next three else statements handle case where only one note has flag
      else if( ( note0._flag >= flagnum ) && ( noteidx == 1 ) )
      {
        // short ligature goes forward since first in group
        drawLigature( x0 , y0 , x0 + deltaX , y0 + deltaY , flip ) ;
        drewlast = false ;
      }
      else if( ( note0._flag >= flagnum ) && !drewlast )
      {
        // short ligature goes backwards since last not drawn
        drawLigature( x0 - deltaX , y0 - deltaY , x0  , y0 , flip ) ;
      }
      else if( ( note1._flag >= flagnum ) && ( noteidx == ( numnotes - 1 ) ) )
      {
        // short ligature goes backwards since last in group
        drawLigature( x1 - deltaX , y1 - deltaY , x1  , y1 , flip ) ;
      }
      else
      {
        drewlast = false ;
      }
    }

    offset += offsetDelta ;
  }
}

void appStaff::addLigaturesSub0( vector<featureNote*>& features ) 
{
  if( features.size() )
  {
    if( features.size() == 1 )  // handle lone note case
    {
      features[0]->addFlag() ;
    }
    else
    {
      addLigaturesSub1( features ) ;
      features.clear() ;
    }
  }
}


void appStaff::addLigatures( vector<featureNote*>& features ) 
{
  vector<featureNote*>::iterator iter ;
  vector<featureNote*> featuresSub ;

  for ( iter=features.begin() ; iter < features.end() ; iter++ )
  {  
    if( (*iter)->_flag )
    {
      featuresSub.push_back( *iter ) ;
    }
    else
    {
      addLigaturesSub0( featuresSub ) ;
    }
  }

  addLigaturesSub0( featuresSub ) ;  // check at end also
}


#define TEST_LINE ( STAFF_LINE_Y_E + 2 * STAFF_LINE_SPACING )
#define TEST_OFF  BASE_UNIT

void appStaff::addMelodicElement( xyzMelodyGroup* group ) 
{
  xyzMelodicElement* element = group->getFirstElement() ;
  vector<featureNote*> featuresNotes ;

  int xstart = _xpos ;
  while( element )
  {
    int xposTemp = _xpos ;
    featureBase* feature ;
    switch( element->type() )
    {
      case MELODIC_ELEMENT_NOTE :
      {
        featureNote* note = new featureNote( _xpos , *(xyzNote*)element , false ) ; 
        feature = (featureBase*)note ;
        addFeature( feature ) ;
        featuresNotes.push_back( note ) ;
        _xpos = xposTemp +  durationToSpace( ((xyzNote*)element)->duration() ) ;
        break ;
      }

      case MELODIC_ELEMENT_GUITAR_CHORD :
      {
       feature = new featureGuitarChord( _xpos , *(xyzGuitarChord*)element )  ;
       addFeature( feature ) ;
        break ;
      }
    }
    element = group->getNextElement() ;
  }

  addLigatures( featuresNotes ) ;
} 


void appStaff::addMelodicElement( xyzGuitarChord* chord )
{
  addFeature( new featureGuitarChord( _xpos , *chord ) ) ;
}


void appStaff::addMelodicElement( xyzBar* bar )
{
  addFeature( new featureBar( _xpos , 4 * STAFF_LINE_SPACING ,  *bar ) ) ;
}

void appStaff::end( void )
{
  _length = _xpos ;

  int yPos = 0 ;
  _xpos = 0 ;

  for( int line = 0 ; line < STAFF_NUM_LINES ; line++ )
  {
    addElement( new svgLine( 0 , yPos , _length , yPos ) ) ;
    yPos += STAFF_LINE_SPACING ;
  }
}


void appStaff::addMelodicElement( xyzNote* note )
{
  int xposTemp = _xpos ;
  addFeature( new featureNote( _xpos , *note ) ) ;
  _xpos = xposTemp + durationToSpace( note->duration() ) ;
}


void appStaff::addMelodicElement( xyzRest* rest )
{
  int xposTemp = _xpos ;
  addFeature( new featureRest( _xpos , *rest ) ) ;
  _xpos = xposTemp + durationToSpace( rest->duration() ) ;
}


appStaff::appStaff( xyzMelody& melody )
: _sig( DEFAULT_TIMESIG_NUM , DEFAULT_TIMESIG_DEN )
, _melody( melody )
{
}


appStaff::~appStaff()
{
  deleteAll() ;
}


void testStaff( xyzMelody& melody ) 
{
  appStaff staff( melody ) ;

  staff.scale( STAFF_SCALE_FACTOR ) ;

  staff.transform( STAFF_OFFSET_X , STAFF_OFFSET_Y , 0 ) ;

  int numMeasures = melody.getNumMeasures() ;
  bool head = true ;
  for( int first = 0 ; first < numMeasures ; first += MEASURES_PER_STAFF )
  {
    int last = first + MEASURES_PER_STAFF - 1 ;

    last = MIN( last , numMeasures - 1 ) ;
  
    staff.addMeasures( first , last , head ) ;
    head = false ;
    staff.draw() ;
    staff.transform( 0 , STAFF_DELTA_Y , 0 ) ;
  }
}



