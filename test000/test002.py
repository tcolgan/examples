#! /usr/bin/python3

import math

width = 161
height = 37

#width = 11
#height = 7
char_fill = '·'
char_origin = '+'
char_xaxis = '='
char_yaxis = '|'
char_point = '©'


def make_line( width ) :
  line = []
  for idx in range( width ) :
    line.append( char_fill )
  return line

def make_array( width , height ):
  array = []
  for idx in range( height ) :
    array.append( make_line( width ) )
  return array
  
def set_point( array , xloc , yloc , val ):
  xloc = round( xloc )
  yloc = round( yloc )
  if( xloc >= 0 and xloc < width and yloc >= 0 and yloc < height ) :
    array[ yloc ][ xloc ] = val


def print_array( array ):
  for line in array:
    for char in line:
      print(char,end='')
    print()
  print()
  

myarray = make_array( width , height )

ymid = (height-1)/2
for xidx in range( width ):
  set_point( myarray , xidx , ymid , char_xaxis )

xmid = (width-1)/2
for yidx in range( height ):
  set_point( myarray , xmid , yidx , char_yaxis )

set_point( myarray , xmid , ymid , char_origin )

for xidx in range( width ):
  xval = 2 * math.pi * ( xidx - xmid ) / ( width - 1 )
  amp = ( height - 1 ) / 2
  yval = amp * math.sin( xval )
  yidx = amp - yval
  set_point( myarray , xidx , yidx , char_point )

print_array( myarray )


