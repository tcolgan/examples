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
{
}


void svgGroup::draw( void ) 
{
  char buff[100] ;

  sprintf( buff , "g transform=\"translate(%d,%d) rotate(%.1f) scale( %.2f , %.2f )\"" , 
           (int)_xloc , (int)_yloc , _rotate , _scaleX , _scaleY ) ;

  xmlStartTag( buff ) ;

  for( int idx = 0; idx < _vector.size(); idx++ ) 
  {
     (*_vector[ idx ]).draw() ;
  }

  xmlEndTag( "g" ) ;
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


