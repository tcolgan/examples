// musSymbols.h

#ifndef MUSSYMBOLS_H
#define MUSSYMBOLS_H

#include "appUtility.h"

using namespace std;

#define WIDTH_TIME_SIGNATURE ( 5 * BASE_UNIT )

#define NOTE_WIDTH  ( 5 * BASE_UNIT )

#define WIDTH_TREBLE_CLEF  ( 7 * BASE_UNIT )
#define WIDTH_SHARP        ( 2 * BASE_UNIT )
#define WIDTH_FLAT         ( 2 * BASE_UNIT )
#define WIDTH_WHOLE        NOTE_WIDTH 
#define WIDTH_HEAD_FILLED  NOTE_WIDTH 
#define WIDTH_HEAD_EMPTY   NOTE_WIDTH 
#define WIDTH_FLAG         0
#define WIDTH_NATURAL      NOTE_WIDTH

#define WIDTH_REST_THIRTYSECOND  NOTE_WIDTH
#define WIDTH_REST_SIXTEENTH     NOTE_WIDTH
#define WIDTH_REST_EIGTH         NOTE_WIDTH
#define WIDTH_REST_QUARTER       NOTE_WIDTH
#define WIDTH_REST_HALF          NOTE_WIDTH
#define WIDTH_REST_WHOLE         NOTE_WIDTH


typedef enum
{
  FEATURE_TREBLE_CLEF  ,
  FEATURE_SHARP        ,
  FEATURE_FLAT         ,
  FEATURE_WHOLE        ,
  FEATURE_HEAD_FILLED  ,
  FEATURE_HEAD_EMPTY   ,
  FEATURE_FLAG         ,
  FEATURE_NATURAL      ,

  FEATURE_REST_THIRTYSECOND ,
  FEATURE_REST_SIXTEENTH    ,
  FEATURE_REST_EIGTH        ,
  FEATURE_REST_QUARTER      ,
  FEATURE_REST_HALF         ,
  FEATURE_REST_WHOLE        ,

} FEATURE_T ;


typedef struct
{
  const char* path ;
  int         width ;
} FEATURE_DEF_T ;

extern FEATURE_DEF_T g_featureDefs[] ;

#endif // MUSSYMBOLS_H

