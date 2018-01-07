// svgDwg.cpp

using namespace std;

#include "svgDwg.h"
#include "xml.h"
#include <string> 
#include <stdio.h>
                                    

svgDwg::svgDwg( float width , float height )
: _width( width )
, _height( height )
{
}

void svgDwg::start( void ) 
{
  char buff[100] ;

  sprintf( buff , "0 0 %d %d" , (int)( _width * 100 ) ,(int)( _height * 100 ) ) ;

  xmlWrite( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" ) ;
  xmlStartMultitag( "svg" ) ;
  xmlWritePar( "xmlns:svg" , "http://www.w3.org/2000/svg" ) ;
  xmlWritePar( "xmlns" , "http://www.w3.org/2000/svg" ) ;
  xmlWritePar( "version" , "1.1" ) ;
  xmlWritePar( "width" , _width   , "in" ) ;
  xmlWritePar( "height" , _height , "in" ) ;
  xmlWritePar( "viewBox" , buff ) ;
  xmlPartialendMultitag() ;
}

void svgDwg::end( void )
{
  xmlEndTag( "svg" ) ;
}

