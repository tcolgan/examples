// svgRect.cpp

#include "svgRect.h"

#include "xml.h"

svgRect::svgRect( float width , float height , 
                  float xloc , float yloc , 
                  string colorFill , string colorStroke , 
                  float widthStroke , float opacityFill ) 
: _width( width )                
, _height( height )              
, _xloc( xloc )                  
, _yloc( yloc )                  
, _colorFill( colorFill )        
, _colorStroke( colorStroke )        
, _widthStroke( widthStroke )    
, _opacityFill( opacityFill )    
{
}

void svgRect::draw( void ) 
{
  xmlStartMultitag( "rect" ) ;
  xmlWritePar( "width" , _width ) ;
  xmlWritePar( "height" ,_height  ) ;
  xmlWritePar( "x" , _xloc ) ;
  xmlWritePar( "y" , _yloc ) ;

  xmlStartQuote( "style" ) ;

  xmlWriteColon( "fill" , _colorFill.c_str() ) ;
  xmlWriteColon( "stroke" , _colorStroke.c_str() ) ;
  xmlWriteColon( "stroke-width" , (int)_widthStroke ) ;
  xmlWriteColon( "fill-opacity" , _opacityFill ) ;

  xmlEndQuote() ;

  xmlEndMultitag() ;
}









