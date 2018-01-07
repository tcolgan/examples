// svgBase.h

#ifndef SVGBASE_H
#define SVGBASE_H

using namespace std;

class svgPoint
{
public:
  svgPoint( int x = 0 , int y = 0 )
  : x( x ) 
  , y( y )
  {
  } ;

  int x ;
  int y ;

private:
};

class svgBase
{
public:
  svgBase() ;

  virtual void draw( void ) ;

private:
} ;

#endif // SVGBASE_H


