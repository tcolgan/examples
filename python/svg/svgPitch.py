
import math

from svg.svgGROUP import svgGroup
from svg.svgELLIPSE import svgEllipse
from svg.svgLINE import svgLine
from svg.svgRECT import svgRect
from svg.svgEqTri import svgEqTri

ICON_SIZE = 10
ICON_SIZE_HALF = ICON_SIZE / 2

class svgPitch(svgGroup):
  
  def __init__(self,xloc,yloc,pitch,scale=1.0):

    super().__init__()
        
    self._pitch = pitch
    self._xloc = xloc
    self._yloc = yloc
    self._scale = scale


    if self._pitch == 0 :
      self._pitchIcon = svgRect( ICON_SIZE , ICON_SIZE , self._xloc - ICON_SIZE / 2 , self._yloc - ICON_SIZE / 2 )
        
    elif self._pitch == 1 :
      
      pass
        
    elif self._pitch == 2 :
      pass
        
    elif self._pitch == 3 :
      self._pitchIcon = svgEqTri(ICON_SIZE_HALF,xloc,yloc)
      pass
        
    elif self._pitch == 4 :
      x_delta = ICON_SIZE_HALF + math.cos( 2 * math.pi * 30 / 360 )
      y_delta = ICON_SIZE_HALF + math.sin( 2 * math.pi * 30 / 360 )
      self._pitchIcon = svgGroup()
      x1 = xloc
      y1 = yloc - ICON_SIZE_HALF
      x2 = xloc + x_delta
      y2 = yloc + y_delta
      x3 = xloc - x_delta
      y3 = yloc + y_delta
      self._pitchIcon.add( svgLine( x1 , y1 , x2 , y2 ) )
      self._pitchIcon.add( svgLine( x2 , y2 , x3 , y3 ) )
      self._pitchIcon.add( svgLine( x3 , y3 , x1 , y1 ) )
      pass
        
    elif self._pitch == 5 :
      pass
        
    elif self._pitch == 6 :
      pass
        
    elif self._pitch == 7 :
      pass
        
    elif self._pitch == 8 :
      pass
        
    elif self._pitch == 9 :
      pass
        
    elif self._pitch == 10 :
      pass
        
    elif self._pitch == 11 :
      pass

        
  def draw(self):

    if hasattr( self , '_pitchIcon' ):
      self._pitchIcon.draw()
        
        


