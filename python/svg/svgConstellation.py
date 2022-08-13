
import math

from svg.svgGROUP import svgGroup
from svg.svgELLIPSE import svgEllipse
from svg.svgLINE import svgLine


TICK_FRACTION = .9

class svgConstellation(svgGroup):
  
  def __init__(self,dia,xloc,yloc,pitches=[]):

    super().__init__()
    self.add( svgEllipse( xloc , yloc , dia , dia))
    for idx in range(12):
      ang = idx * 30 - 90

      x1 = xloc + TICK_FRACTION * dia * math.cos( 2 * math.pi * ang / 360 )
      y1 = yloc + TICK_FRACTION * dia * math.sin( 2 * math.pi * ang / 360 )

      x2 = xloc + dia * math.cos( 2 * math.pi * ang / 360 )
      y2 = yloc + dia * math.sin( 2 * math.pi * ang / 360 )
      self. add( svgLine( x1 , y1 , x2 , y2 ) )
  

    for pitch in pitches:
      ang = pitch * 30 - 90

      x1 = xloc
      y1 = yloc

      x2 = xloc + dia * math.cos( 2 * math.pi * ang / 360 )
      y2 = yloc + dia * math.sin( 2 * math.pi * ang / 360 )
      self. add( svgLine( x1 , y1 , x2 , y2 ) )
