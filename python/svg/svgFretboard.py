
import math

from svg.svgGROUP import svgGroup
from svg.svgLINE import svgLine
from svg.svgRECT import svgRect
from svgPitch import svgPitch

DEFAULT_STRING_SEPARATION = 25
DEFAULT_FRET_SEPARATION = DEFAULT_STRING_SEPARATION

NUMBER_STRINGS = 4
NUMBER_FRETS = 18

class svgFretboard(svgGroup):
  
  def __init__(self,xloc,yloc,pitches=[]):

    super().__init__()

    self._xloc = xloc
    self._yloc = yloc

    
    width  = NUMBER_FRETS * DEFAULT_FRET_SEPARATION
    height = ( NUMBER_STRINGS - 1 ) * DEFAULT_STRING_SEPARATION
    self.add( svgRect( width , height , 0 , 0 , colorStroke="blue" ) )

    yloc = 0
    for string in range( NUMBER_STRINGS ):
      self.add( svgLine(  0 , yloc , width , yloc ) )
      yloc += DEFAULT_STRING_SEPARATION
      xloc = DEFAULT_FRET_SEPARATION
      for fret in range( NUMBER_FRETS - 1 ) :
        self.add( svgLine(  xloc , 0 , xloc , height ) )
        xloc += DEFAULT_FRET_SEPARATION
        
        
#  for pitch in pitches:

#    self.add( svgPitch( xpitch , ypitch , pitch ) )
