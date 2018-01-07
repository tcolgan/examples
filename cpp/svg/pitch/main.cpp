#include <cstdio>
#include <string>
#include <iostream>

#include "utility.h"
#include "svgGroup.h"
#include "svgDwg.h"
#include "svgConstellation.h"

using namespace std;

typedef struct
{
   string text ;
   int points[13] ;
} PITCH_DEF_S ;


PITCH_DEF_S pitchDef[] =
{
   { "Acoustic scale"                           , {  0 , 2 , 4 , 6 , 7 , 9 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Adonai malakh scale"                      , {  0 , 2 , 4 , 5 , 7 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Aeolian mode or natural minor scale"      , {  0 , 2 , 3 , 5 , 7 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Algerian scale"                           , {  0 , 2 , 3 , 6 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Altered scale"                            , {  0 , 1 , 3 , 4 , 6 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Augmented scale"                          , {  0 , 3 , 4 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Bebop dominant scale"                     , {  0 , 2 , 4 , 5 , 7 , 9 ,10 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Blues scale"                              , {  0 , 3 , 5 , 6 , 7 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Chromatic scale"                          , {  0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 ,10 ,11 ,-1 } } ,
   { "Dorian mode"                              , {  0 , 2 , 3 , 5 , 7 , 9 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Double harmonic scale"                    , {  0 , 1 , 4 , 5 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Enigmatic scale"                          , {  0 , 1 , 4 , 6 , 8 ,10 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Flamenco mode"                            , {  0 , 1 , 4 , 5 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Gypsy scale"                              , {  0 , 2 , 3 , 6 , 7 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Half diminished scale"                    , {  0 , 2 , 3 , 5 , 6 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Harmonic major scale"                     , {  0 , 2 , 4 , 5 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Harmonic minor scale"                     , {  0 , 2 , 3 , 5 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Hirajoshi scale"                          , {  0 , 2 , 3 , 7 , 8 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Hungarian gypsy scale"                    , {  0 , 2 , 3 , 6 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Hungarian minor scale"                    , {  0 , 2 , 3 , 6 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Insen scale"                              , {  0 , 1 , 5 , 7 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Ionian mode or major scale"               , {  0 , 2 , 4 , 5 , 7 , 9 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Istrian scale"                            , {  0 , 1 , 3 , 4 , 6 , 7 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Iwato scale"                              , {  0 , 1 , 5 , 6 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Locrian mode"                             , {  0 , 1 , 3 , 5 , 6 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Lydian augmented scale"                   , {  0 , 2 , 4 , 6 , 8 , 9 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Lydian mode"                              , {  0 , 2 , 4 , 6 , 7 , 9 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Major bepop scale"                        , {  0 , 2 , 4 , 5 , 7 , 8 , 9 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Major locran scale"                       , {  0 , 2 , 4 , 5 , 6 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Major pentatonic scale"                   , {  0 , 2 , 4 , 7 , 9 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Melodic minor scale"                      , {  0 , 2 , 3 , 5 , 7 , 8 , 9 ,10 ,11 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Melodic minor scale (ascending)"          , {  0 , 2 , 3 , 5 , 7 , 9 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Minor pentatonic scale"                   , {  0 , 3 , 5 , 7 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Mixolydian scale"                         , {  0 , 2 , 4 , 5 , 7 , 9 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Neapolitan major scale"                   , {  0 , 1 , 3 , 5 , 7 , 9 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Neapolitan minor scale"                   , {  0 , 1 , 3 , 5 , 7 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Octatonic scale"                          , {  0 , 2 , 3 , 5 , 6 , 8 , 9 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Persian scale"                            , {  0 , 1 , 4 , 5 , 6 , 8 ,11 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Phrygian dominant scale"                  , {  0 , 1 , 4 , 5 , 7 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Phrygian mode"                            , {  0 , 1 , 3 , 5 , 7 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Prometheus scale"                         , {  0 , 2 , 4 , 6 , 9 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Tritone scale"                            , {  0 , 1 , 4 , 6 , 7 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Ukranian Dorian scale"                    , {  0 , 2 , 3 , 6 , 7 , 9 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
   { "Whole tone scale"                         , {  0 , 2 , 4 , 6 , 8 ,10 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 } } ,
} ;

#define NUM_CONST  ARRAYSIZE( pitchDef )

#define OFFSET_X_MIN     150
#define OFFSET_Y_MIN     200
#define OFFSET_X_DELTA   300
#define OFFSET_Y_DELTA   300

#define CONST_PER_ROW  7



void addConst( PITCH_DEF_S& def , int offsetX , int offsetY )
{
   svgConstellation constellation ;

   constellation.transform( offsetX , offsetY ) ;
   constellation.setText( def.text ) ;
   int idx = 0 ;
   vector<int> vect ;
   while( def.points[ idx ] != -1 )
   {
      vect.push_back( def.points[ idx ] ) ;
      idx++ ;
   }
   constellation.setVector( vect ) ;
   constellation.draw() ;
}


int main( int argc , char** argv ) 
{
  int numrows = ( NUM_CONST + CONST_PER_ROW - 1 ) / CONST_PER_ROW ;
  int width  = (  ( CONST_PER_ROW ) * OFFSET_X_DELTA ) / PIXELS_PER_INCH ;
  int height = ( ( OFFSET_Y_MIN / 2 ) + ( numrows * OFFSET_Y_DELTA ) ) / PIXELS_PER_INCH ;

  svgDwg dwg( width , height ) ; 
  svgGroup group ;

  dwg.start() ;

  int offsetX = OFFSET_X_MIN ;
  int offsetY = OFFSET_Y_MIN ;  
  int rowCount = 0 ;

  for( int idx = 0 ; idx < NUM_CONST ; idx++ )
  {
     rowCount++ ;
     if( rowCount > CONST_PER_ROW )
     {
        rowCount = 1 ;
        offsetX = OFFSET_X_MIN ;
        offsetY += OFFSET_Y_DELTA ;
     }

     addConst( pitchDef[ idx ] , offsetX , offsetY ) ;
     offsetX += OFFSET_X_DELTA ;
  }

  dwg.end() ;
}
