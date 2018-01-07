// common.h

using namespace std;

#include <string>
#include <vector>

#ifndef COMMON_H
#define COMMON_H


#define STAFF_OFFSET_X 50
#define STAFF_OFFSET_Y 75

#define TAB_OFFSET_X 50
#define TAB_OFFSET_Y 150

#define STAFF_DELTA_Y  200
#define MEASURES_PER_STAFF 4

#define COLOR_A "rgb( 255 ,  80 ,  80 )"  // light red
#define COLOR_B "rgb( 252 , 128 ,  64 )"  // light orange
#define COLOR_C "rgb( 255 , 255 , 157 )"  // light yellow
#define COLOR_D "rgb( 128 , 255 , 128 )"  // light green
#define COLOR_E "rgb( 125 , 184 , 255 )"  // light blue
#define COLOR_F "rgb( 255 ,  72 , 255 )"  // light purple
#define COLOR_G "rgb( 255 , 202 , 255 )"  // light pink

#define COLOR_PERFECT_FIRST   "rgb( 255 ,  73 ,  73 )"  // light red
#define COLOR_MINOR_SECOND    "rgb( 255 , 244 , 132 )"  // light orange
#define COLOR_MAJOR_SECOND    "rgb( 255 , 192 ,   0 )"  // medium orange
#define COLOR_MINOR_THIRD     "rgb( 255 , 255 , 147 )"  // light yellow
#define COLOR_MAJOR_THIRD     "rgb( 255 , 255 ,   0 )"  // medium yellow
#define COLOR_PERFECT_FORTH   "rgb( 146 , 208 ,  80 )"  // light green
#define COLOR_TRITONE         "rgb( 166 , 166 , 166 )"  // light grey
#define COLOR_PERFECT_FIFTH   "rgb(   0 , 176 , 240 )"  // light blue
#define COLOR_MINOR_SIXTH     "rgb( 179 , 203 , 255 )"  // light indigo
#define COLOR_MAJOR_SIXTH     "rgb(  17 ,  95 , 255 )"  // medium indigo
#define COLOR_MINOR_SEVENTH   "rgb( 214 , 186 , 235 )"  // light violet
#define COLOR_MAJOR_SEVENTH   "rgb( 162 ,  98 , 208 )"  // medium violet


#define COLOR_HIGHLIGHT "rgb( 255 , 0 , 0 )"  
#define WIDTH_HIGHLIGHT 20
#define OPACITY_HIGHLIGHT .5

#define SEMITONES_PER_OCTAVE 12
#define NOTES_IN_OCTAVE 8

#define GUITAR_CHORD_OFFSET    ( -4 * BASE_UNIT )
#define GUITAR_CHORD_FONT_SIZE ( 4 * BASE_UNIT )

#define BASE_UNIT             15
#define DEFAULT_RADIUS        BASE_UNIT
#define HIGHLIGHT_SQUARE_SIZE ( DEFAULT_RADIUS * 2.2 )

#define HORIZONTAL_BASE_DISTANCE  ( BASE_UNIT / 2 )
#define HORIZONTAL_START_MELODY   ( BASE_UNIT * 32 )

#define STAFF_SCALE_FACTOR (0.15)

#define DEFAULT_TIMESIG_NUM  4
#define DEFAULT_TIMESIG_DEN  4

#define COMMON_TIMESIG_NUM  4
#define COMMON_TIMESIG_DEN  4

#define CUT_TIMESIG_NUM     2
#define CUT_TIMESIG_DEN     2

#define REST_WIDTH ( 2 * BASE_UNIT )

#define NOTESPACE_FROM_DEN(x)  ( HORIZONTAL_BASE_DISTANCE * x )

#define DOT_RADIUS ( BASE_UNIT / 5 )


typedef enum
{
  MODE_IONIAN ,
  MODE_DORIAN ,
  MODE_PHYGIAN ,
  MODE_LYDIAN ,
  MODE_MIXOLYDIAN ,
  MODE_AEOLIAN ,
  MODE_LOCRIAN ,
  MODE_MAJOR = MODE_IONIAN ,
  MODE_MINOR = MODE_AEOLIAN ,

} MODE_T ;


typedef enum
{
  DURATION_THIRTYSECOND  = 1  ,
  DURATION_SIXTEENTH     = 2  ,
  DURATION_SIXTEENTH_DOT = 3  ,
  DURATION_EIGTH         = 4  ,
  DURATION_EIGTH_DOT     = 6  ,
  DURATION_EIGTH_DOT2    = 7  ,
  DURATION_QUARTER       = 8  ,
  DURATION_QUARTER_DOT   = 12 ,
  DURATION_QUARTER_DOT2  = 14 ,
  DURATION_QUARTER_DOT3  = 15 ,
  DURATION_HALF          = 16 ,
  DURATION_HALF_DOT      = 24 ,
  DURATION_HALF_DOT2     = 28 ,
  DURATION_HALF_DOT3     = 30 ,
  DURATION_WHOLE         = 32 ,
  DURATION_WHOLE_DOT     = 48 ,
  DURATION_WHOLE_DOT2    = 56 ,
  DURATION_WHOLE_DOT3    = 60 ,

  DURATION_DEFAULT   = DURATION_QUARTER ,
//  DURATION_DEFAULT   = DURATION_EIGTH ,
//  DURATION_DEFAULT   = DURATION_SIXTEENTH ,

} DURATION_T;


typedef enum
{
  STRING_G ,
  STRING_D ,
  STRING_A ,
  STRING_E ,

} STRING_T ;


typedef enum
{
  FRET_00 , 
  FRET_01 , 
  FRET_02 , 
  FRET_03 , 
  FRET_04 , 
  FRET_05 , 
  FRET_06 , 
  FRET_07 , 
  FRET_08 , 
  FRET_09 , 
  FRET_10 , 
  FRET_11 , 
  FRET_12 , 

} FRET_T ;


typedef enum
{
  INTERVAL_TONIC          ,
  INTERVAL_MINOR_SECOND   ,
  INTERVAL_MAJOR_SECOND   ,
  INTERVAL_MINOR_THIRD    ,
  INTERVAL_MAJOR_THIRD    ,
  INTERVAL_PERFECT_FOURTH ,
  INTERVAL_TRITONE        ,
  INTERVAL_PERFECT_FIFTH  ,
  INTERVAL_MINOR_SIXTH    ,
  INTERVAL_MAJOR_SIXTH    ,
  INTERVAL_MINOR_SEVENTH  ,
  INTERVAL_MAJOR_SEVENTH  ,
  INTERVAL_OCTAVE         ,

} INTERVAL_T ;


// note - 88 key piano keyboard runs from A0 to C8
//   7 * 12 + 4 (7 octaves plus A/A#/B/C)

typedef enum
{
  OCTAVE_0 ,
  OCTAVE_1 ,
  OCTAVE_2 ,
  OCTAVE_3 ,
  OCTAVE_4 ,
  OCTAVE_5 ,
  OCTAVE_6 ,
  OCTAVE_7 ,
  OCTAVE_8 ,

} OCTAVE_T ;


typedef enum
{
  PITCH_CLASS_C ,
  PITCH_CLASS_D ,
  PITCH_CLASS_E ,
  PITCH_CLASS_F ,
  PITCH_CLASS_G ,
  PITCH_CLASS_A ,
  PITCH_CLASS_B ,
  NUM_PITCH_CLASSES ,
  PITCH_CLASS_FIRST = PITCH_CLASS_C ,
  PITCH_CLASS_LAST  = PITCH_CLASS_B ,

} PITCH_CLASS_T ;


typedef enum
{
  ACCIDENTAL_NATURAL ,
  ACCIDENTAL_SHARP   ,
  ACCIDENTAL_FLAT    ,
  NUM_ACCIDENTAL ,
} ACCIDENTAL_T ;


typedef struct 
{
  PITCH_CLASS_T pitch ;
  ACCIDENTAL_T  accidental ;
} NOTEDEF_T ;


typedef struct 
{
  int x ;
  int y ;
} Xy ;

typedef unsigned int uint ;

const NOTEDEF_T g_noteSequence[] =
{
  { PITCH_CLASS_C , ACCIDENTAL_NATURAL } , // 0
  { PITCH_CLASS_C , ACCIDENTAL_SHARP   } , // 1
  { PITCH_CLASS_D , ACCIDENTAL_NATURAL } , // 2
  { PITCH_CLASS_D , ACCIDENTAL_SHARP   } , // 3
  { PITCH_CLASS_E , ACCIDENTAL_NATURAL } , // 4
  { PITCH_CLASS_F , ACCIDENTAL_NATURAL } , // 5
  { PITCH_CLASS_F , ACCIDENTAL_SHARP   } , // 6
  { PITCH_CLASS_G , ACCIDENTAL_NATURAL } , // 7
  { PITCH_CLASS_G , ACCIDENTAL_SHARP   } , // 8
  { PITCH_CLASS_A , ACCIDENTAL_NATURAL } , // 9
  { PITCH_CLASS_A , ACCIDENTAL_SHARP   } , // 10
  { PITCH_CLASS_B , ACCIDENTAL_NATURAL } , // 11
} ;

const int g_semitoneFromC[][ NUM_ACCIDENTAL ] =
{
  { 0  ,  1 , 11 } ,   // PITCH_CLASS_C
  { 2  ,  3 ,  1 } ,   // PITCH_CLASS_D
  { 4  ,  5 ,  3 } ,   // PITCH_CLASS_E
  { 5  ,  6 ,  4 } ,   // PITCH_CLASS_F
  { 7  ,  8 ,  6 } ,   // PITCH_CLASS_G
  { 9  , 10 ,  8 } ,   // PITCH_CLASS_A
  { 11 ,  0 , 10 } ,   // PITCH_CLASS_B
} ;


const bool g_modePattern[][ SEMITONES_PER_OCTAVE + 1 ] =
{
  //C , C#, D , D#, E , F , F#, G , G#, A , A#, B , C  (example key of c)
  { 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 } ,  // MODE_IONIAN = MODE_MAJOR
  { 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 } ,  // MODE_DORIAN                
  { 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 } ,  // MODE_PHYGIAN               
  { 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 1 } ,  // MODE_LYDIAN                
  { 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 } ,  // MODE_MIXOLYDIAN            
  { 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 } ,  // MODE_AEOLIAN = MODE_MINOR
  { 1 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 } ,  // MODE_LOCRIAN               
} ;


const string NoteColors[] =
{
  COLOR_C ,
  COLOR_D ,
  COLOR_E ,
  COLOR_F ,
  COLOR_G ,
  COLOR_A ,
  COLOR_B ,
} ;

const string intervalColors[] =
{
  COLOR_PERFECT_FIRST ,
  COLOR_MINOR_SECOND  ,
  COLOR_MAJOR_SECOND  ,
  COLOR_MINOR_THIRD   ,
  COLOR_MAJOR_THIRD   ,
  COLOR_PERFECT_FORTH ,
  COLOR_TRITONE       ,
  COLOR_PERFECT_FIFTH ,
  COLOR_MINOR_SIXTH   ,
  COLOR_MAJOR_SIXTH   ,
  COLOR_MINOR_SEVENTH ,
  COLOR_MAJOR_SEVENTH ,
} ;



const string NoteText[][4] =
{
  "C" , "C#" , "B"  , "C#/Db" , 
  "D" , "D#" , "Db" , "D#/Eb" , 
  "E" , "G"  , "Eb" , "F"     , 
  "F" , "F#" , "E"  , "F#/Gb" , 
  "G" , "G#" , "Gb" , "G#/Ab" , 
  "A" , "A#" , "Ab" , "A#/Bb" , 
  "B" , "C"  , "Bb" , "C"     , 
} ;

const struct
{
  string key ;
  int    semitone ;
  bool   sharp ;  // true if notes sharpened,  false if flattened.
} keyTable[] =
{
  "C"  , 0  , true  , 

  "C#" , 1  , true  , 
  "Db" , 1  , false ,  

  "D"  , 2  , true  , 

  "D#" , 3  , true  , 
  "Eb" , 3  , false ,  

  "E"  , 4  , true  , 

  "F"  , 5  , false ,  

  "F#" , 6  , true  , 
  "Gb" , 6  , false ,  

  "G"  , 7  , true  , 

  "G#" , 8  , true  , 
  "Ab" , 8  , false ,  

  "A"  , 9  , true  , 

  "A#" , 10 , true  , 
  "Bb" , 10 , false ,  

  "B"  , 11 , true  , 
} ;

const int semiMando[][4] =
{
   7 ,  2 ,  9 ,  4 , 
   8 ,  3 , 10 ,  5 ,
   9 ,  4 , 11 ,  6 ,
  10 ,  5 ,  0 ,  7 ,
  11 ,  6 ,  1 ,  8 ,
   0 ,  7 ,  2 ,  9 ,
   1 ,  8 ,  3 , 10 ,
   2 ,  9 ,  4 , 11 ,
   3 , 10 ,  5 ,  0 ,
   4 , 11 ,  6 ,  1 ,
   5 ,  0 ,  7 ,  2 ,
   6 ,  1 ,  8 ,  3 ,
   7 ,  2 ,  9 ,  4 , 
} ;

const string noteText[][2] =
{
  "C"  ,  "C"  ,
  "Db" ,  "C#" , 
  "D"  ,  "D"  ,
  "Eb" ,  "D#" , 
  "E"  ,  "E"  ,
  "F"  ,  "F"  , 
  "Gb" ,  "F#" , 
  "G"  ,  "G"  ,
  "Ab" ,  "G#" , 
  "A"  ,  "A"  ,
  "Bb" ,  "A#" , 
  "B"  ,  "B"  ,
} ;

const string intervalText[] =
{
  "1"  ,
  "b2" ,
  "2"  ,
  "b3" ,
  "3"  ,
  "4"  ,
  "b5" ,
  "5"  ,
  "b6" ,
  "6"  ,
  "b7" ,
  "7"  ,
} ;    


typedef enum
{
  BAR_STANDARD             ,
  BAR_DOUBLE               ,
  BAR_BEGIN                ,
  BAR_END                  ,
  BAR_BEGIN_REPEAT         ,
  BAR_END_REPEAT           ,
  BAR_BEGIN_AND_END_REPEAT ,
} BAR_T;



#define BAR_SPACE_LINE_THIN_TO_THIN  ( 2 * BASE_UNIT / 2 )
#define BAR_SPACE_LINE_THICK_TO_THIN ( 3 * BASE_UNIT / 2 )
#define BAR_SPACE_LINE_THIN_TO_DOT   ( BASE_UNIT )
#define BAR_SPACE_AFTER              ( 4 * BASE_UNIT )
#define BAR_SPACE_XTRA               ( BAR_SPACE_LINE_THICK_TO_THIN - BAR_SPACE_LINE_THIN_TO_THIN )



#endif // COMMON_H

