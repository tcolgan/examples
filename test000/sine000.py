#! /usr/bin/python3

import math

width = 161
height = 37

#width = 11
#height = 7
char_fill = '·'
#char_fill = ' '
char_origin = '+'
char_xaxis = '='
char_yaxis = '|'
char_point = '©'


class plot_array :
  """create an x/y array for plotting"""
  
  def __init__(self, width, height):
    self._array = []
    self._width = width
    self._height = height
    for idx in range( self._height ) :
      self._array.append( self._make_line( self._width ) )

  def _make_line( self ,width ) :
    line = []
    for idx in range( width ) :
      line.append( char_fill )
    return line
    
  def set_point( self , xloc , yloc , val ):
    xloc = round( xloc )
    yloc = round( yloc )
    if( xloc >= 0 and xloc < self._width and yloc >= 0 and yloc < self._height ) :
      self._array[ yloc ][ xloc ] = val

  def print( self ):
    for line in self._array:
      for char in line:
        print(char,end='')
      print()
    print()
  

def mytest():
  myarray = plot_array( width , height )
  
  ymid = (height-1)/2
  for xidx in range( width ):
    myarray.set_point( xidx , ymid , char_xaxis )
  
  xmid = (width-1)/2
  for yidx in range( height ):
    myarray.set_point( xmid , yidx , char_yaxis )
  
  myarray.set_point( xmid , ymid , char_origin )
  
  for xidx in range( width ):
    xval = 2 * math.pi * ( xidx - xmid ) / ( width - 1 )
    amp = ( height - 1 ) / 2
    yval = amp * math.sin( xval )
    yidx = amp - yval
    myarray.set_point( xidx , yidx , char_point )
  
  myarray.print()


mytest()