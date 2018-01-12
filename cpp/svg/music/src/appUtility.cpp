// utility.cpp

#include "xml.h"
#include "appUtility.h"
#include "musSymbols.h"


bool checkNote( int interval , MODE_T mode )
{
  if( interval < 0 )
  {
    interval += SEMITONES_PER_OCTAVE ;
  }
  return g_modePattern[ (int)mode ][ interval ] ;
}


xyzCircleText::xyzCircleText( string text , int cx , int cy , string color , float opacity , int radius )
: _ellipse( 0 , 0 , radius ,radius , color , "black" , 1 , opacity )
, _text( 0 , 0 , text ) 
{
  addElement( &_ellipse ) ;
  addElement( &_text ) ;

  int size = text.size() ;

  float fontSize ;  // factor determined via experimentation
  if( size <= 2 )
  {
    fontSize = 1.2 * radius ; 
  }
  else
  {
    fontSize = 3.0 * radius / size ;
  }

  _text.setFontSize( fontSize ) ;
  _text.setLocation( 0 , .4 * fontSize ) ;

  transform( cx , cy , 0 ) ;
}










                       



