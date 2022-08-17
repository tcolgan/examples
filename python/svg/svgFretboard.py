
import math

from svg.svgGROUP import svgGroup
from svg.svgLINE import svgLine
from svg.svgRECT import svgRect
from svg.svgELLIPSE import svgEllipse
from svgPitch import svgPitch

DEFAULT_STRING_SEPARATION = 25
DEFAULT_FRET_SEPARATION = DEFAULT_STRING_SEPARATION

NUMBER_STRINGS = 4
NUMBER_FRETS = 20

NUMBER_NOTES = 12

DOT_RADIUS = 3

class svgFretboard(svgGroup):
  
  def __init__(self,xloc,yloc , number_frets , note_matrix = [[],[],[],[]] ):

    super().__init__()

    self._xloc = xloc
    self._yloc = yloc

    
    width  = number_frets * DEFAULT_FRET_SEPARATION
    height = ( NUMBER_STRINGS - 1 ) * DEFAULT_STRING_SEPARATION

    yloc = 0
    pitch_start = [9,2,7,0]
    dots = [0,0,0,1,0,1,0,1,0,0,1,0,2,0,0,1,0,1,0,1,0,0]
    for string in range( NUMBER_STRINGS ):
      notes = note_matrix[ string ]
      pitch_idx = pitch_start[ string ]
      self.add( svgLine(  0 , yloc , width , yloc ) )
      xloc = DEFAULT_FRET_SEPARATION
      for fret in range( number_frets ) :
        note = notes[ fret ]
        if fret != number_frets - 1 :
          self.add( svgLine(  xloc , 0 , xloc , height ) )
        if note >= 0 :
          self.add( svgPitch( xloc - DEFAULT_FRET_SEPARATION / 2 , yloc , note ))

        if string == 0 :
          if dots[fret] == 1 :
            self.addCircle( DOT_RADIUS , xloc - DEFAULT_FRET_SEPARATION / 2 , yloc + height + DEFAULT_STRING_SEPARATION * .75 )
          elif dots[fret] == 2 :
            self.addCircle( DOT_RADIUS , xloc - DEFAULT_FRET_SEPARATION / 2 , yloc + height + DEFAULT_STRING_SEPARATION * .5 )
            self.addCircle( DOT_RADIUS , xloc - DEFAULT_FRET_SEPARATION / 2 , yloc + height + DEFAULT_STRING_SEPARATION * 1.0 )
          
        xloc += DEFAULT_FRET_SEPARATION
            
      yloc += DEFAULT_STRING_SEPARATION
        
  def addCircle(self,radius, xloc, yloc , colorFill="grey"):
    self.add( svgEllipse( xloc , yloc , radius , radius, colorFill=colorFill ) )
      
        
  def incr( self, start ) :
    value = start + 1
    if value >= NUMBER_NOTES :
      value = value - NUMBER_NOTES
    return value

