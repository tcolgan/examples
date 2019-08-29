import svg.XML as xml
from svg.svgBASE import svgBase


class svgEllipse(svgBase):
  
  def __init__(self,cx,cy,rx,ry,colorFill="white",colorStroke="black",strokeWidth=1,opacityFill=0.0):
    self._cx = cx
    self._cy = cy
    self._rx = rx
    self._ry = ry
    self._colorFill = colorFill
    self._colorStroke = colorStroke
    self._strokeWidth = strokeWidth
    self._opacityFill = opacityFill
  
  
  def draw(self):
    xml.StartMultitag( "ellipse" )
    xml.WritePar( "cx" , self._cx )
    xml.WritePar( "cy" , self._cy ) 
    xml.WritePar( "rx" , self._rx )
    xml.WritePar( "ry" , self._ry )
    xml.StartQuote( "style" )
    xml.WriteColon( "fill" , self._colorFill ) 
    xml.WriteColon( "stroke" , self._colorStroke )
    xml.WriteColon( "stroke-width" , str( self._strokeWidth ) )
    xml.WriteColon( "fill-opacity" , "%.2f" % self._opacityFill )
    
    xml.EndQuote()
    xml.EndMultitag()