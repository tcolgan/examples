// svgGroup.cpp
//
// todo
// . add destructor and call deleteAll()

#include "svgGroup.h"

#include "xml.h"
#include <stdio.h>

svgGroup::svgGroup( float xloc , float yloc , float rotate , float scaleX , float scaleY ) 
: _xloc( xloc )
, _yloc( yloc )
, _rotate( rotate )
, _scaleX( scaleX )
, _scaleY( scaleY )
, _viewport( false )
{
}


void svgGroup::draw( void ) 
{
  char buff[100] ;

  if( _viewport )
  {
     sprintf( buff , "svg x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"" , 
              _viewport_x , _viewport_y , _viewport_width , _viewport_height ) ;

     xmlStartTag( buff ) ;
  }

  sprintf( buff , "g transform=\"translate(%d,%d) rotate(%.1f) scale( %.2f , %.2f )\"" , 
           (int)_xloc , (int)_yloc , _rotate , _scaleX , _scaleY ) ;

  xmlStartTag( buff ) ;

  for( int idx = 0; idx < _vector.size(); idx++ ) 
  {
     (*_vector[ idx ]).draw() ;
  }

  xmlEndTag( "g" ) ;

  if( _viewport )
  {
     xmlEndTag( "svg" ) ;
  }
}


void svgGroup::scale( float scale )
{
  _scaleX *= scale ;
  _scaleY *= scale ;
}

void svgGroup::scale( float scaleX , float scaleY )
{
  _scaleX *= scaleX ;
  _scaleY *= scaleY ;
}


void svgGroup::transform( float xloc , float yloc , float rotate )
{
  _xloc   += xloc   ;
  _yloc   += yloc   ;
  _rotate += rotate ;
}


void svgGroup::addElement( svgBase* element )
{
  _vector.push_back( element ) ;
}


void svgGroup::deleteAll( void )
{
  int numitems = _vector.size() ;

  for( int idx = 0 ; idx < numitems ; idx++ )
  {
    delete _vector[ idx ] ;
    _vector[ idx ] = 0 ;
  }
  _vector.clear() ;
}


void svgGroup::setViewport( float x , float y , float width , float height )
{
   _viewport = true ;

   _viewport_x      = x      ;
   _viewport_y      = y      ;
   _viewport_width  = width  ;
   _viewport_height = height ;
}                            

