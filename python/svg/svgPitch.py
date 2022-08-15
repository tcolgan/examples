
import math

from svg.svgGROUP import svgGroup
from svg.svgELLIPSE import svgEllipse
from svg.svgLINE import svgLine
from svg.svgRECT import svgRect

ICON_SIZE = 10

class svgPitch(svgGroup):
  
  def __init__(self,xloc,yloc,pitch,scale=1.0):

    super().__init__()
        
    self._pitch = pitch
    self._xloc = xloc
    self._yloc = yloc
    self._scale = scale
        
  def draw(self):
        
    if self._pitch == 0 :
      rect = svgRect( ICON_SIZE , ICON_SIZE , self._xloc - ICON_SIZE / 2 , self._yloc - ICON_SIZE / 2 )
      rect.draw()
        
        
        
