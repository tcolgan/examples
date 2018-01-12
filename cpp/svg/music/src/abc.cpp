// abc.cpp

#include <cstdio>
#include <cstdlib>

#include "abc.h"


abcFile::abcFile( char* filename , xyzMelody& melody )
: _filename( filename )
, _melody( melody )
, _durationDefault( DURATION_EIGTH )
{
  getMelody() ;
} ;


// Removes from <CR> and/or <LF> to end of string
void abcFile::eraseLineends( string& str )
{
  size_t startpos = str.find_first_of( LINEENDS ) ; 

  str.erase( startpos ) ;
}


// Removes whitespace from beginning and end of string
void abcFile::trimSpaces( string& str )
{
  size_t startpos = str.find_first_not_of( WHITE_SPACE ) ; 
  size_t endpos = str.find_last_not_of( WHITE_SPACE ) ;

  if(( string::npos == startpos ) || ( string::npos == endpos ))
  {
      str = "" ;
  }
  else
  {  
      str = str.substr( startpos , endpos-startpos+1 ) ;
  }
}


PITCH_CLASS_T abcFile::getPitchClass( char ch )
{
  PITCH_CLASS_T pitch = PITCH_CLASS_C ;  // default

  ch = toupper( ch ) ;

  PITCH_CLASS_T arr[] =
  {
    PITCH_CLASS_A ,
    PITCH_CLASS_B ,
    PITCH_CLASS_C ,
    PITCH_CLASS_D ,
    PITCH_CLASS_E ,
    PITCH_CLASS_F ,
    PITCH_CLASS_G ,
  } ;

  if( ch >= 'A' && ( ch <= 'G' ) )
  {
    pitch = arr [ ch - 'A' ] ;
  }

  return pitch ;
}

void abcFile::handleKey( string& line )
{
  ACCIDENTAL_T acc = ACCIDENTAL_NATURAL ;
  acc = ( line[1] == '#' ) ? ACCIDENTAL_SHARP : acc ;
  acc = ( line[1] == 'b' ) ? ACCIDENTAL_FLAT  : acc ;

  PITCH_CLASS_T pitch = getPitchClass( line[ 0 ] ) ;

  _melody.setKey( xyzNote( pitch , acc ) ) ;

  // tmctodo HANDLE MODES AND OTHER SPECIAL FEATURES
}


void abcFile::handleSignature( string& line )
{
  xyzTimeSignature sig ;

  if( toupper( line[0] ) == 'C' )
  {
    if( line[1] == '|' )
    {
      sig.setValues( CUT_TIMESIG_NUM , CUT_TIMESIG_DEN , SIGNATURE_SPECIAL_CUT ) ;
    }
    else
    {
      sig.setValues( COMMON_TIMESIG_NUM , COMMON_TIMESIG_DEN , SIGNATURE_SPECIAL_COMMON ) ;
    }
  }
  else
  {
    int idx = line.find_first_of( "/" ) ;
  
    if( idx )
    {
      int num = atoi( line.substr( 0 , idx ).c_str() ) ;
      int den = atoi( line.substr( idx + 1 ).c_str() ) ;
  
      sig.setValues( num , den ) ;
    }
  }
  _melody.setSignature( sig ) ;

  // if time < .75 (see abc notation spec)
  if( ( 4 * sig.num ) < ( 3 * sig.den ) )
  {
    _durationDefault = DURATION_SIXTEENTH ;
  }
}


void abcFile::handleNoteLength( string& line )
{
  
  int idx = line.find_first_of( "/" ) ;
  
  if( idx )
  {
    int num = atoi( line.substr( 0 , idx ).c_str() ) ;
    int den = atoi( line.substr( idx + 1 ).c_str() ) ;

    int ratio = den / num ;  

    // handle ratios which are accepted, otherwise leave default alone.
    switch( ratio )
    {
    case 1 :
      _durationDefault = DURATION_WHOLE ; 
      break ;

    case 2 :
      _durationDefault = DURATION_HALF ;        
      break ;

    case 4 :
      _durationDefault = DURATION_QUARTER ;    
      break ;

    case 8 :
      _durationDefault = DURATION_EIGTH ;  
      break ;

    case 16 :
      _durationDefault = DURATION_SIXTEENTH ;  
      break ;

    case 32 :
      _durationDefault = DURATION_THIRTYSECOND ;
      break ;
    }
  }

  printf( "TEST: _durationDefault : %d\n" , _durationDefault ) ;
}


void abcFile::handleTitle( string& line )
{
  _melody.setTitle( line ) ;
}


void abcFile::handleNot( string& line )
{
  // tmctodo TEMPORARY FOR UNHANDLED FIELD TYPES
}

bool abcFile::isNote( char ch )
{
  ch = toupper( ch ) ;

  return ( ( ch >= 'A' ) && ( ch <= 'G' ) || ( ch == '^' ) || ( ch == '_' ) ) ;
}


DURATION_T abcFile::getDuration( string& str )
{
  int duration = (int)_durationDefault ;
  bool more = true ;
  int mult = 0 ;
  int div = 0 ;
  bool divide = false ;

  while( more && str.size() )
  {
    char ch = str[0] ;
    if( ( ch >= '0' ) && ( ch <= '9' ) )
    {
      if( mult )
      {
        mult *= 10 ;
      }
      mult += ( ch - '0' ) ;
      str.erase( 0 , 1 ) ;
    }
    else
    {
      more = false ;
      if( ch == '/' )
      {
        divide = true ;
        str.erase( 0 , 1 ) ;
      }
    }
  }

  if( divide )
  {
    more = true ;
    while( more && str.size() )
    {
      char ch = str[0] ;
      if( ( ch >= '0' ) && ( ch <= '9' ) )
      {
        if( div )
        {
          div *= 10 ;
        }
        div += ( ch - '0' ) ;
        str.erase( 0 , 1 ) ;
      }
      else
      {
        more = false ;
      }
    }
  }

  div = div ? div : 1 ;
  mult = mult ? mult : 1 ;

  duration = ( duration * mult ) / div ;

  return (DURATION_T)duration ;
}


xyzNote* abcFile::getNote( string& group )
{
  int octave = 4 ;
  DURATION_T dur = _durationDefault ;
  ACCIDENTAL_T acc = ACCIDENTAL_NATURAL ;
  
  char chTemp = group[0] ;

  if( chTemp == '^' )
  {
    acc = ACCIDENTAL_SHARP ;
    group.erase( 0 , 1 ) ;
    chTemp = group[0] ;
  }
  if( chTemp == '_' )
  {
    acc = ACCIDENTAL_FLAT ;
    group.erase( 0 , 1 ) ;
    chTemp = group[0] ;
  }


  char ch = toupper( chTemp ) ;
  if( ch != chTemp )
  {
    octave++ ;
  }

  PITCH_CLASS_T pitch = getPitchClass( ch ) ;

  group.erase( 0 , 1 ) ;

  bool more = true ;

  while( more )
  {
    if( !group.size() )
    {
      more = false ;
    }
    else
    {
      ch = group[0] ;
      if( ch == '\'' )
      {
        octave++ ;
        group.erase( 0 , 1 ) ;
      }
      else if( ch == ',' )
      {
        octave-- ;
        group.erase( 0 , 1 ) ;
      }
      else 
      {
        dur = getDuration( group ) ;
        more = false ;
      }
    }
  }

  xyzNote* note = new xyzNote( pitch , acc , (OCTAVE_T)octave , dur ) ;
  return note ;
}



bool abcFile::processGuitarChord( string& str , xyzMelodyGroup& group )
{
  bool isChord = false ;
  string strChord ;

  if( str[0] == '\"' )
  {
    isChord = true ;

    str.erase( 0 , 1 ) ;

    while( !str.empty() && str[0] != '\"' )
    {
        strChord += str[0] ;
        str.erase( 0 , 1 ) ;
    }
    if( str[0] == '\"' )
    {
      str.erase( 0 , 1 ) ;
    }

    group.addElement( new xyzGuitarChord( strChord ) ) ;

  }

  return isChord ;
}


bool abcFile::processRest( void )
{
  bool isRest = false ;

  if( _notes[0] == 'z' )
  {
    _notes.erase( 0 , 1 ) ;
    isRest = true ;

    DURATION_T dur = getDuration( _notes ) ;

    _melody.addElement( new xyzRest( dur ) ) ;
  }

  return isRest ;
}


bool abcFile::processBar( void )
{
  //   |   bar line                         BAR_STANDARD                       
  //   |]  thin-thick double bar line       BAR_END              
  //   ||  thin-thin double bar line        BAR_DOUBLE               
  //   [|  thick-thin double bar line       BAR_BEGIN                 
  //   :|  left repeat                      BAR_END_REPEAT        
  //   |:  right repeat                     BAR_BEGIN_REPEAT           
  //   ::  left-right repeat                BAR_BEGIN_AND_END_REPEAT
   
  bool isBar = false ;
  BAR_T type = BAR_STANDARD ;                      
  char ch ;

  ch = _notes[0] ;
  if( ch == '|' )
  {
    isBar = true ;
    _notes.erase( 0 , 1 ) ;

    ch = _notes[0] ;
    if( ch == ']'  )
    {
      type = BAR_END ;
      _notes.erase( 0 , 1 ) ;
    }
    else if( ch == '|'  )
    {
      type = BAR_DOUBLE ;
      _notes.erase( 0 , 1 ) ;
    }
    else if( ch == ':'  )
    {
      type = BAR_BEGIN_REPEAT ;
      _notes.erase( 0 , 1 ) ;
    }
    else
    {
      type = BAR_STANDARD ;
    }
  }
  else if(  ch == ':' )
  {
    isBar = true ;
    _notes.erase( 0 , 1 ) ;
    
    ch = _notes[0] ;
    if( ch == ':'  )
    {
      type = BAR_BEGIN_AND_END_REPEAT ;
      _notes.erase( 0 , 1 ) ;
    }
    else if( ch == '|'  )
    {
      type = BAR_END_REPEAT ;
      _notes.erase( 0 , 1 ) ;
    }
  }
  else if(  ch == '[' )
  {
    isBar = true ;
    _notes.erase( 0 , 1 ) ;
    
    ch = _notes[0] ;
    if( ch == '|'  )
    {
      type = BAR_BEGIN ;
      _notes.erase( 0 , 1 ) ;
    }
  }

  if( isBar )
  {
    _melody.addElement( new xyzBar( type ) ) ;
  }

  return isBar ;
}


bool abcFile::processGroup( void )
{
  bool isGroup = false ;
  char ch = toupper( _notes[0] ) ;
  if( isNote( ch ) )
  {
    isGroup = true ;

    xyzMelodyGroup* melodyGroup = new xyzMelodyGroup ;
  
    int idx = 0 ;
    bool loop ;
    do
    {
      loop = false ;
      idx = _notes.find_first_not_of( NOTE_CHARS , idx ) ;
      if( idx == string::npos )
      {
        idx = _notes.size() - 1 ;
      }
      else
      {
        if( _notes[ idx ] == '\"' )
        {
          idx = _notes.find_first_of( "\"" , idx + 1 ) + 1 ;
          loop = true ;
        }
      }
    } while( loop ) ;

    string group = _notes.substr( 0 , idx ) ;

    _notes.erase( 0 , idx ) ;
  
    while( group.size() )
    {
      if( !processGuitarChord( group , *melodyGroup ) )
      {
        melodyGroup->addElement( getNote( group ) ) ;
      }
    }
  
    trimSpaces( _notes ) ;

    _melody.addElement( melodyGroup ) ;
  }

  return isGroup ;
}


void abcFile::processNotes( void )
{
  while( _notes.size() )
  {  
    if( !processGroup() )
    {
      if( !processRest() )
      {
        if( !processBar() )
        {
          if( !processGuitarChord( _notes , _melody ) )
          {
            // if here, then unknown char.  erase it.
            _notes.erase( 0 , 1 ) ;
          }
        }
      }
    }
  }
}


bool abcFile::processField( string line )
{
  if( line[1] != ':' )
  {
    return false ;
  }

  bool found = false ;

  char type = line[0] ;
  line.erase( 0 , 2 ) ;

  trimSpaces( line ) ;

  struct
  {
    char type ;
    handler ftn ;
  } defs[] =
  {
    ABCTYPE_AREA                  , &abcFile::handleNot    ,
    ABCTYPE_BOOK                  , &abcFile::handleNot    ,
    ABCTYPE_COMPOSER              , &abcFile::handleNot    ,
    ABCTYPE_DISCOGRAPHY           , &abcFile::handleNot    ,
    ABCTYPE_ELEMSKIP              , &abcFile::handleNot    ,
    ABCTYPE_FILE_NAME             , &abcFile::handleNot    ,
    ABCTYPE_GROUP                 , &abcFile::handleNot    ,
    ABCTYPE_HISTORY               , &abcFile::handleNot    ,
    ABCTYPE_INFORMATION           , &abcFile::handleNot    ,
    ABCTYPE_KEY                   , &abcFile::handleKey    ,
    ABCTYPE_DEFAULT_NOTE_LENGTH   , &abcFile::handleNoteLength ,
    ABCTYPE_METER                 , &abcFile::handleSignature ,
    ABCTYPE_NOTES                 , &abcFile::handleNot    ,
    ABCTYPE_ORIGIN                , &abcFile::handleNot    ,
    ABCTYPE_PARTS                 , &abcFile::handleNot    ,
    ABCTYPE_TEMPO                 , &abcFile::handleNot    ,
    ABCTYPE_RHYTHM                , &abcFile::handleNot    ,
    ABCTYPE_SOURCE                , &abcFile::handleNot    ,
    ABCTYPE_TITLE                 , &abcFile::handleTitle  ,
    ABCTYPE_WORDS                 , &abcFile::handleNot    ,
    ABCTYPE_REFERENCE_NUMBER      , &abcFile::handleNot    ,
    ABCTYPE_TRANSCRIPTION_NOTE    , &abcFile::handleNot    ,
  } ;

  for( int idx = 0 ; idx < ARRAYSIZE( defs ) ; idx++ )
  {
    if( defs[ idx ].type == type )
    {
      (*this.*(defs[ idx ].ftn))( line ) ;
      found = true ;
      break ;
    }
  }

  return found ;
}


void abcFile::removeComments( string& str )
{
  size_t pos = str.find_first_of( "%" ) ; 

  if( pos != string::npos )
  {
    str.erase( pos ) ;
  }
}


void abcFile::getMelody( void )
{
  FILE*  file ;
  char   buffer[ FILE_BUFF_SIZE ] ;
  string line ;

  file = fopen( _filename.c_str() , "r" ) ;

  if( !file )
  {
    printf( "ERROR: unable to open %s\n" , _filename.c_str() ) ;
    return ;
  }

  while( fgets( buffer , sizeof( buffer ) , file ) )
  {
    line = buffer ;

    removeComments( line ) ;

    if( line.size() )
    {
  
      if( processField( line ) )
      {
        continue ;
      }
  
      eraseLineends( line ) ;
      _notes += line ;

      processNotes() ;
    }
  }

  fclose( file ) ;
}




