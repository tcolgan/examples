import svg.XML as xml
from svg.svgBASE import svgBase


class svgRect(svgBase):
  
  def __init__(self,width,height,x,y,colorFill="white",colorStroke="black",strokeWidth=1,opacityFill=0.0):
    self._width = width
    self._height = height
    self._x = x
    self._y = y
    self._colorFill = colorFill
    self._colorStroke = colorStroke
    self._strokeWidth = strokeWidth
    self._opacityFill = opacityFill
  
  def draw(self):
    xml.StartMultitag( "rect" )
    xml.WritePar( "width" , self._width )
    xml.WritePar( "height" , self._height ) 
    xml.WritePar( "x" , self._x )
    xml.WritePar( "y" , self._y )
    xml.StartQuote( "style" )
    xml.WriteColon( "fill" , self._colorFill ) 
    xml.WriteColon( "stroke" , self._colorStroke )
    xml.WriteColon( "stroke-width" , str( self._strokeWidth ) )
    xml.WriteColon( "fill-opacity" , "%.2f" % self._opacityFill )
    xml.EndQuote()
    xml.EndMultitag()