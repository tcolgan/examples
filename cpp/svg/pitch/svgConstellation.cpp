// svgConstellation.cpp

#include "svgConstellation.h"
#include "utility.h"
#include "stdio.h"

svgConstellation::svgConstellation()
{
   svgEllipse* ellipse = new svgEllipse( 0 , 0 , RADIUS , RADIUS ) ;

   addElement( ellipse ) ;

   for( int idx = 0 ; idx < 12 ; idx++ )
   {
      float x1 ;
      float y1 ;
      float x2 ;
      float y2 ;
      float x3 ;
      float y3 ;
      float angle = 30 * idx ; // in degrees

      polarToRect( RADIUS                   , angle , &x1 , &y1 ) ;
      polarToRect( ( RADIUS - TICK_LENGTH ) , angle , &x2 , &y2 ) ;

      svgLine* tick = new svgLine( x1 , y1 , x2 , y2 ) ;
      addElement( tick ) ;

      polarToRect( ( RADIUS + NUM_OFFSET  ) , angle , &x3 , &y3 ) ;

      char buff[3] ;
      sprintf( buff , "%d" , idx ) ;

      svgText* txt = new svgText() ;
      txt->setText( buff ) ;
      txt->setLocation( x3 , y3 + TEXT_NUDGE ) ;

      addElement( txt ) ;
   }
}

void svgConstellation::setText( string text )
{
   svgText* txt = new svgText() ;
   txt->setText( text ) ;
   txt->setLocation( 0 , -RADIUS - TEXT_OFFSET ) ;
   txt->setFontSize( TITLE_FONT_SIZE ) ;

   addElement( txt ) ;
}


void svgConstellation::setVector( vector<int>values )
{
   vector<int>::iterator iter ;

   for (iter = values.begin(); iter != values.end(); ++iter )
   {
      int idx = *iter ;

      float x1 ;
      float y1 ;
      float x2 ;
      float y2 ;
//      float angle = 30 * ( idx + 1 ) ; // in degrees
      float angle = 30 * idx ; // in degrees

      polarToRect( 0      , angle , &x1 , &y1 ) ;
      polarToRect( RADIUS , angle , &x2 , &y2 ) ;

      svgLine* line = new svgLine( x1,y1,x2,y2,"red",2) ;
      addElement( line ) ;
   }
}


