import math

import svg.XML as xml
from svg.svgBASE import svgBase


class svgPolygon(svgBase):
  
  def __init__(self,points,colorFill="white",colorStroke="black",strokeWidth=1,opacityFill=1.0):
    self._points = points
    self._colorFill = colorFill
    self._colorStroke = colorStroke
    self._strokeWidth = strokeWidth
    self._opacityFill = opacityFill
  
  def draw(self):
    xml.StartMultitag( "polygon" )
    
    outstr = ""
    for px,py in self._points:
      outstr += repr(px) + " , " + repr(py) + "  "
    xml.WritePar( "points" , outstr )
    
    xml.StartQuote( "style" )
    xml.WriteColon( "fill" , self._colorFill )
    xml.WriteColon( "stroke" , self._colorStroke )
    xml.WriteColon( "stroke-width" , str( self._strokeWidth ) )
    xml.WriteColon( "fill-opacity" , "%.2f" % self._opacityFill )
    xml.EndQuote()
    
    xml.EndMultitag()