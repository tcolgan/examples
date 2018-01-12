// abc.h

#ifndef ABC_H
#define ABC_H

#include <string>

#include "xyzMelody.h"

using namespace std;

#define FILE_BUFF_SIZE 200
#define WHITE_SPACE " \t\n\r"
#define LINEENDS "\n\r"
#define NOTE_CHARS "abcdefgABCDEFG0123456789,\'/^_" 


#define ABCTYPE_AREA                   'A'
#define ABCTYPE_BOOK                   'B'
#define ABCTYPE_COMPOSER               'C'
#define ABCTYPE_DISCOGRAPHY            'D'
#define ABCTYPE_ELEMSKIP               'E'
#define ABCTYPE_FILE_NAME              'F'
#define ABCTYPE_GROUP                  'G'
#define ABCTYPE_HISTORY                'H'
#define ABCTYPE_INFORMATION            'I'
#define ABCTYPE_KEY                    'K'
#define ABCTYPE_DEFAULT_NOTE_LENGTH    'L'
#define ABCTYPE_METER                  'M'
#define ABCTYPE_NOTES                  'N'
#define ABCTYPE_ORIGIN                 'O'
#define ABCTYPE_PARTS                  'P'
#define ABCTYPE_TEMPO                  'Q'
#define ABCTYPE_RHYTHM                 'R'
#define ABCTYPE_SOURCE                 'S'
#define ABCTYPE_TITLE                  'T'
#define ABCTYPE_WORDS                  'W'
#define ABCTYPE_REFERENCE_NUMBER       'X'
#define ABCTYPE_TRANSCRIPTION_NOTE     'Z'



class abcFile
{
public:
  abcFile( char* filename , xyzMelody& melody ) ;

  void getMelody( void ) ;
  void trimSpaces( string& str ) ;
  void eraseLineends( string& str ) ;
  bool isNote( char ch ) ;
  PITCH_CLASS_T getPitchClass( char ch ) ;
  void removeComments( string& str ) ;

  bool processField( string line ) ;
  void processNotes( void ) ;
  bool processGroup( void ) ;
  bool processBar( void ) ;
  bool processRest( void ) ;
  bool processGuitarChord( string& str , xyzMelodyGroup& group ) ;

  xyzNote* getNote( string& group ) ;
  DURATION_T getDuration( string& str ) ;

  void handleNot( string& line ) ;
  void handleKey( string& line ) ;
  void handleTitle( string& line ) ;
  void handleSignature( string& line ) ;
  void handleNoteLength( string& line ) ;

private:
  xyzMelody& _melody ;
  string     _notes ;

  string     _filename ;
  string     _title ;
  DURATION_T _durationDefault ;
} ;

typedef void (abcFile::*handler)( string& line ) ;

#endif // ABC_H
