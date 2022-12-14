#! /usr/bin/python3

import math

width = 161
height = 37

#width = 11
#height = 7
#char_fill = '·'
char_fill = ' '
char_origin = '+'
char_xaxis = '='
char_yaxis = '|'
char_point = '©'
char_div   = '·'

num_hor_div = 8
num_vert_div   = 8

cycles = 3


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
    
  def draw_horizontal( self , yloc , char ) :
    for xidx in range( self._width ):
      self.set_point( xidx , yloc , char )
    
  def draw_vertical( self , xloc , char ) :
    for yidx in range( self._height ):
      self.set_point( xloc , yidx , char )
  

def mytest():

  myarray = plot_array( width , height )

  vert_sep = ( width - 1 ) / num_vert_div
  for idx in range( num_vert_div + 1 ) :
    myarray.draw_vertical( idx * vert_sep , char_div )
  
  hor_sep = ( height - 1 ) / num_hor_div
  for idx in range( num_hor_div + 1 ) :
    myarray.draw_horizontal( idx * hor_sep , char_div )
  
  ymid = (height-1)/2
  myarray.draw_horizontal( ymid , char_xaxis)

  xmid = (width-1)/2
  myarray.draw_vertical( xmid , char_yaxis)

  myarray.set_point( xmid , ymid , char_origin )
    
  
  for xidx in range( width ):
    xval = 2 * math.pi * ( xidx - xmid ) * cycles / ( width - 1 )
    amp = ( height - 1 ) / 2
    yval = amp * math.sin( xval )
    yidx = amp - yval
    myarray.set_point( xidx , yidx , char_point )
  
  myarray.print()


mytest()