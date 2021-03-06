// svgText.cpp

#include <sstream>

#include "svgText.h"

#include "xml.h"

svgText::svgText( float x , float y , string text , 
                  float  fontSize , string fontFamily ,
                  string colorFill ,
                  string anchor )
: _x( x )                       
, _y( y )                       
, _text( text )
, _fontSize( fontSize )         
, _fontFamily( fontFamily )     
, _colorFill( colorFill )       
, _anchor( anchor )             
{
}


void svgText::setText( string text ) 
{
  _text = text ;
}

void svgText::setFontColor( string colorFill ) 
{
  _colorFill = colorFill ;
}

void svgText::setFontSize( float fontSize ) 
{
  _fontSize = fontSize ;
}

void svgText::setLocation( float x , float y ) 
{
  _x = x ;
  _y = y ;
}

// anchor: start | middle | end | inherit
void svgText::setAnchor( string anchor )
{
   _anchor = anchor ;
}


void svgText::draw( void ) 
{
  xmlStartMultitag( "text" ) ;
  xmlWritePar( "x" , _x ) ;
  xmlWritePar( "y" , _y ) ;

  xmlStartQuote( "style" ) ;

  ostringstream fontSize ;
  fontSize << _fontSize << "px" ;
  xmlWriteColon( "font-family" , _fontFamily.c_str() ) ;
  xmlWriteColon( "font-size" , fontSize.str().c_str() ) ;
  xmlWriteColon( "fill" , _colorFill.c_str() ) ;
  xmlWriteColon( "text-anchor" , _anchor.c_str() ) ;

  xmlEndQuote() ;

  xmlPartialendMultitag() ;
  xmlWrite( _text.c_str() ) ;

  xmlEndTag( "text" ) ;
}

