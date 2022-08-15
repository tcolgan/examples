import math

import svg.XML as xml
from svg.svgBASE import svgBase


class svgEqTri(svgBase):
  
  def __init__(self,radius,x,y,colorFill="white",colorStroke="black",strokeWidth=1,opacityFill=0.0):
    self._radius = radius
    self._x = x
    self._y = y
    self._colorFill = colorFill
    self._colorStroke = colorStroke
    self._strokeWidth = strokeWidth
    self._opacityFill = opacityFill
  
  def draw(self):
    xml.StartMultitag( "polygon" )
    
    x_delta = self._radius + math.cos( 2 * math.pi * 30 / 360 )
    y_delta = self._radius + math.sin( 2 * math.pi * 30 / 360 )

    xloc = self._x
    yloc = self._y
    
    x1 = xloc
    y1 = yloc - self._radius
    x2 = xloc + x_delta
    y2 = yloc + y_delta
    x3 = xloc - x_delta
    y3 = yloc + y_delta
    
    points = [(x1,y1),(x2,y2),(x3,y3)]
    outstr = ""
    for px,py in points:
      outstr += repr(px) + " , " + repr(py) + "  "
    xml.WritePar( "points" , outstr )
    xml.EndMultitag()