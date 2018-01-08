// svgLine.cpp

#include "svgLine.h"

#include "xml.h"

svgLine::svgLine( float x1 , float y1 , 
                  float x2 , float y2 , 
                  string colorStroke , float widthStroke ,
                  float opacity ) 
: _x1( x1 )                
, _y1( y1 )              
, _x2( x2 )                  
, _y2( y2 )                  
, _colorStroke( colorStroke )        
, _widthStroke( widthStroke )    
, _opacity( opacity )    
{
}

svgLine::svgLine( Point& point1 , 
                  Point& point2 , 
                  string colorStroke , float widthStroke ,
                  float opacity ) 
: _x1( point1.xVal )                
, _y1( point1.yVal )              
, _x2( point2.xVal )                  
, _y2( point2.yVal )                  
, _colorStroke( colorStroke )        
, _widthStroke( widthStroke )    
, _opacity( opacity )    
{
}

void svgLine::setEndpoints( float x1 , float y1 , float x2 , float y2 )
{
   _x1 = x1 ;                
   _y1 = y1 ;              
   _x2 = x2 ;                  
   _y2 = y2 ;                  
}

void svgLine::draw( void ) 
{
  xmlStartMultitag( "line" ) ;
  xmlWritePar( "x1" , _x1 ) ;
  xmlWritePar( "x2" , _x2 ) ;
  xmlWritePar( "y1" , _y1 ) ;
  xmlWritePar( "y2" , _y2 ) ;

  xmlStartQuote( "style" ) ;

  xmlWriteColon( "stroke" , _colorStroke.c_str() ) ;
  xmlWriteColon( "stroke-width" , (int)_widthStroke ) ;
  xmlWriteColon( "stroke-opacity" , _opacity ) ;

  xmlEndQuote() ;

  xmlEndMultitag() ;
}

