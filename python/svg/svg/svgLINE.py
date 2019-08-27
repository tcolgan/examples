import XML as xml
from svgBASE import svgBase

class svgLine(svgBase):

  def __init__( self , x1=0 , y1=0 , x2=100 , y2=100 , colorStroke="black" , widthStroke=1 , opacity=1.0 ):
    self._x1           = x1
    self._y1           = y1
    self._x2           = x2
    self._y2           = y2
    self._colorStroke  = colorStroke
    self._widthStroke  = widthStroke
    self._opacity      = opacity    

  def setEndpoints( self , x1 , y1 , x2 , y2 ):
    self._x1 = x1
    self._y1 = y1
    self._x2 = x2
    self._y2 = y2

  def draw( self ):
    xml.StartMultitag( "line" ) ;
    xml.WritePar( "x1" , self._x1 )
    xml.WritePar( "x2" , self._x2 )
    xml.WritePar( "y1" , self._y1 )
    xml.WritePar( "y2" , self._y2 )
    xml.StartQuote( "style" )
    xml.WriteColon( "stroke" , self._colorStroke )
    xml.WriteColon( "stroke-width" , self._widthStroke )
    xml.WriteColon( "stroke-opacity" , self._opacity ) 
    xml.EndQuote() ;
    xml.EndMultitag() ;

