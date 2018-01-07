// svgEllipse.cpp

#include "svgEllipse.h"

#include "xml.h"

svgEllipse::svgEllipse( float cx , float cy , 
                        float rx , float ry , 
                        string colorFill , string colorStroke , 
                        float widthStroke , float opacityFill ) 
: _cx( cx )                
, _cy( cy )              
, _rx( rx )                  
, _ry( ry )                  
, _colorFill( colorFill )        
, _colorStroke( colorStroke )        
, _widthStroke( widthStroke )    
, _opacityFill( opacityFill )    
{
}

void svgEllipse::draw( void ) 
{
  xmlStartMultitag( "ellipse" ) ;
  xmlWritePar( "cx" , _cx ) ;
  xmlWritePar( "cy" ,_cy  ) ;
  xmlWritePar( "rx" , _rx ) ;
  xmlWritePar( "ry" , _ry ) ;

  xmlStartQuote( "style" ) ;

  xmlWriteColon( "fill" , _colorFill.c_str() ) ;
  xmlWriteColon( "stroke" , _colorStroke.c_str() ) ;
  xmlWriteColon( "stroke-width" , (int)_widthStroke ) ;
  xmlWriteColon( "fill-opacity" , _opacityFill ) ;

  xmlEndQuote() ;

  xmlEndMultitag() ;
}


void svgEllipse::setStroke( string color ) 
{
  _colorStroke = color ;
}

void svgEllipse::setFill( string color ) 
{
  _colorFill = color ;
}

