
import math

from svg.svgGROUP import svgGroup
from svg.svgELLIPSE import svgEllipse
from svg.svgLINE import svgLine
from svgPitch import svgPitch
from svgKey import svgKey
from svg.svgTEXT import svgText


TICK_FRACTION = .9
PITCH_LOCATION_SCALE = .2
TEXT_OFFSET = 6

class svgConstellation(svgGroup):
  
  def __init__(self,dia,xloc,yloc,pitches=[] , key_text = "G"):

    super().__init__()
    self.add( svgEllipse( xloc , yloc , dia , dia))
    for idx in range(12):
      ang = idx * 30 - 90

      x1 = xloc + TICK_FRACTION * dia * math.cos( 2 * math.pi * ang / 360 )
      y1 = yloc + TICK_FRACTION * dia * math.sin( 2 * math.pi * ang / 360 )

      x2 = xloc + dia * math.cos( 2 * math.pi * ang / 360 )
      y2 = yloc + dia * math.sin( 2 * math.pi * ang / 360 )
      self. add( svgLine( x1 , y1 , x2 , y2 ) )
  

    key = svgKey( key_text )
    for pitch in pitches:
      ang = pitch * 30 - 90
      
      cos_ang = math.cos( 2 * math.pi * ang / 360 )
      sin_ang = math.sin( 2 * math.pi * ang / 360 )

      x1 = xloc
      y1 = yloc

      x2 = xloc + dia * cos_ang
      y2 = yloc + dia * sin_ang
      
      self.add( svgLine( x1 , y1 , x2 , y2 ) )
      
      xpitch = xloc + ( 1 + PITCH_LOCATION_SCALE ) * dia * cos_ang
      ypitch = yloc + ( 1 + PITCH_LOCATION_SCALE ) * dia * sin_ang
  
      self.add( svgPitch( xpitch , ypitch , pitch ) )

      xtext = xloc + ( 1 + 3 * PITCH_LOCATION_SCALE ) * dia * cos_ang
      ytext = yloc + ( 1 + 3 * PITCH_LOCATION_SCALE ) * dia * sin_ang + TEXT_OFFSET

      self.add( svgText( xtext , ytext , key.getNote( pitch ) ) )
