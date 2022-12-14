#! /usr/bin/python3

import math

width = 160
height = 36
fill = '.'


def make_line( width ) :
  line = []
  for idx in range( width ) :
    line.append( fill )
  return line

def make_array( width , height ):
  array = []
  for idx in range( height ) :
    array.append( make_line( width ) )
  return array
  
def set_point( array , xloc , yloc , val ):
  if( xloc >= 0 and xloc < width and yloc >= 0 and yloc < height ) :
    array[ int( yloc ) ][ int( xloc ) ] = val


def print_array( array ):
  for line in array:
    for char in line:
      print(char,end='')
    print()
  print()
  

myarray = make_array( width , height )

for idx in range( width ):
  set_point( myarray , idx , height/2 , '=')
set_point( myarray , width/2 , height/2 , '+' )

for xidx in range( width ):
  xval = 2 * math.pi * xidx / width
  amp = height / 2
  yval = amp * math.sin( xval )
  yidx = amp - yval
  set_point( myarray , xidx , yidx , "*")

print_array( myarray )


