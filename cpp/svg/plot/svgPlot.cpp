// svgPlot.cpp
//

#include "svgPlot.h"
#include "svgGroup.h"
#include "svgLine.h"

#include "xml.h"
#include "utility.h"
#include <stdio.h>

const char* colors[] = {"blue", "red", "green", "orange" , "cyan" , "coral" , "darkred" , "darkviolet" , "palegreen" , "orchid" , "aqua" };
#define NUMBER_COLORS (ARRAYSIZE(colors)) 

#define XTITLE_FONTSIZE 16
#define YTITLE_FONTSIZE 16

#define ROTATE_CW  90
#define ROTATE_CCW -90

// note - width/height in pixels, rest are real-world numbers
svgPlot::svgPlot( float xMin , float xMax , float yMin , float yMax , int width , int height ) 
: _xMin( xMin )
, _xMax( xMax ) 
, _yMin( yMin ) 
, _yMax( yMax )
, _width( width )
, _height( height )
, _color(0)
{
   _rect = new svgRect( _width , _height ) ;
   addElement( _rect ) ;
}


void svgPlot::xDiv( int num , const char* format  ) 
{
   for ( int idx = 0 ; idx <= num ; idx++ )
   {
      float xVal = idx * ( _xMax - _xMin ) / num + _xMin ;
      int xPixels = ( idx * _width )/ num ; 
      svgLine* line = new svgLine( xPixels , 0 , xPixels , _height ) ;
      addElement( line ) ;

      char strTemp[ STR_BUFF_SIZE ] ;     
      snprintf( strTemp , STR_BUFF_SIZE , format , xVal ) ;
      svgText* text = new svgText( xPixels , _height + TEXT_OFFSET_X , strTemp ) ;
      addElement( text ) ;
   }
}


void svgPlot::yDiv( int num , const char* format  ) 
{
   for ( int idx = 0 ; idx <= num ; idx++ )
   {
      // note - vertical numbering reversed in real-world vs pixels
      float yVal = _yMax -  idx * ( _yMax - _yMin ) / num ;
      int yPixels = ( idx * _height )/ num ; 
      svgLine* line = new svgLine( 0 , yPixels , _width , yPixels ) ;
      addElement( line ) ;

      char strTemp[ STR_BUFF_SIZE ] ;
      snprintf( strTemp , STR_BUFF_SIZE , format , yVal ) ;
      svgText* text = new svgText( TEXT_OFFSET_Y , yPixels , strTemp ) ;

      text->setAnchor( "end" ) ;

      addElement( text ) ;
   }
}


void svgPlot::Title( string title ) 
{
   svgText* text = new svgText( _width / 2 , - TEXT_OFFSET_X * 2 , title ) ;

   text->setAnchor( "middle" ) ;
   text->setFontSize( XTITLE_FONTSIZE ) ;

   addElement( text ) ;
}


void svgPlot::xTitle( string title ) 
{
   svgText* text = new svgText( _width / 2 , _height + TEXT_OFFSET_X * 2 , title ) ;

   text->setAnchor( "middle" ) ;
   text->setFontSize( XTITLE_FONTSIZE ) ;

   addElement( text ) ;
}


void svgPlot::yTitle( string title ) 
{
   svgText* text = new svgText( 0 , 0 , title ) ;
   svgGroup* group = new svgGroup( TEXT_OFFSET_Y * 8 , _height / 2 , ROTATE_CCW ) ;

   text->setAnchor( "middle" ) ;
   text->setFontSize( YTITLE_FONTSIZE ) ;

   group->addElement( text ) ;

   addElement( group ) ;
}


// translate a point from real-world coordinates to plot-relative coordinates
Point svgPlot::TranslatePoint( Point& point )
{
   Point pointReturn(  ( point.xVal - _xMin ) * _width / ( _xMax - _xMin ) , ( point.yVal - _yMax ) * _height / ( _yMin - _yMax ) ) ;

   return pointReturn ;
}


// add a vector of data to the plot (will use a new color for each call)
const char* svgPlot::addData( std::vector<Point>& data )
{
   bool first = true ;
   std::vector<Point>::iterator itLast ;

   const char* strColor = colors[ _color ] ;
   _color++ ;
   if( _color >= NUMBER_COLORS )
   {
      _color = 0 ;
   }

   svgGroup* group = new svgGroup ;
   group->setViewport( 0 , 0 , _width , _height ) ;

   for( std::vector<Point>::iterator it = data.begin(); it != data.end(); ++it) 
   {
      Point point1 = TranslatePoint( *it ) ;

      svgEllipse* ellipse = new svgEllipse( point1.xVal , point1.yVal , MARKER_RADIUS , MARKER_RADIUS , strColor ) ;
      group->addElement( ellipse ) ;

      if( first )
      {
         first = false ;
         itLast = it ;
         continue ;
      }

      Point point2 = TranslatePoint( *itLast ) ;
      svgLine* line = new svgLine( point1 , point2 , strColor ) ;
      group->addElement( line ) ;

      itLast = it ;
   }

   addElement( group ) ;

   return strColor ;
}





