// appStaff.h

#ifndef APPSTAFF_H
#define APPSTAFF_H

#include "svgRect.h"
#include "svgLine.h"
#include "svgEllipse.h"
#include "svgText.h"
#include "svgPoly.h"
#include "svgGroup.h"
#include "utility.h"
#include "xyzFeature.h"
#include "xyzMelody.h"

using namespace std;

#define STAFF_TITLE_OFFSET ( - 8 * BASE_UNIT )
#define STAFF_TITLE_HEIGHT ( 4 * BASE_UNIT )
#define STAFF_TITLE_FONT "Courier Bold" 


class featureNote : public featureBase
{
public:
  
  featureNote( int xpos , xyzNote& note , bool drawFlags = true ) ;
  void addFlag( void ) ;
  void addStem( int length , bool flip ) ;

  int _flag ;
  int _xhead ;
  int _yhead ;
  int _xstem ;
  int _ystem ;
  int _stemLength ;
};



class appStaff : public xyzMelodyConsumer , public featureBase
{
public:
  appStaff( xyzMelody& melody ) ;
  ~appStaff() ;

  void addMeasures( int first , int last , bool sig = true ) ;

  void addMelodicElement( xyzNote* note ) ;
  void addMelodicElement( xyzBar* bar   )   ;
  void addMelodicElement( xyzRest* rest ) ;
  void addMelodicElement( xyzMelodyGroup* group ) ;
  void addMelodicElement( xyzGuitarChord* chord ) ;

  void addLigatures( vector<featureNote*>& features ) ;
  void addLigaturesSub0( vector<featureNote*>& features ) ;
  void addLigaturesSub1( vector<featureNote*>& features ) ;
  void drawLigature( int x0 , int y0 , int x1 , int y1 , bool flip ) ;
  float calcSlope( vector<featureNote*>& features ) ;
  
  void end( void ) ;

private:
  xyzMelody&       _melody ;
  int              _length ;
  xyzNote          _key ;
  xyzTimeSignature _sig ;
} ;

void testStaff( xyzMelody& melody ) ;

#endif // APPSTAFF_H



