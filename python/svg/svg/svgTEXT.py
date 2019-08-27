import XML as xml
from svgBASE import svgBase

class svgText(svgBase):

  def __init__( self ,  x=0 , y=0 , text="" , fontSize=12 , fontFamily="Arial" , colorFill="black" , anchor="middle" , rotate = 0.0 ):
    self._x          = x
    self._y          = y 
    self._text       = text
    self._fontSize   = fontSize
    self._fontFamily = fontFamily
    self._colorFill  = colorFill
    self._anchor     = anchor
    self._rotate     = rotate

  def setText( self ,  text ):
    self._text = text

  def setFontColor( self ,  colorFill ):
    self._colorFill = colorFill

  def setFontSize( self ,  fontSize ):
    self._fontSize = fontSize

  def setLocation( self ,  x , y ):
    self._x = x 
    self._y = y 


  # anchor: start | middle | end | inherit
  def setAnchor( self ,  anchor ):
    self._anchor = anchor

  def draw(self) :
    
    xml.StartMultitag( "text" ) 
    xml.WritePar( "x" , 0 ) 
    xml.WritePar( "y" , 0 ) 
    translate_string = 'translate(%2.2f,%2.2f) rotate(%2.2f)' % ( self._x , self._y , self._rotate)
    xml.WritePar( "transform" , translate_string )
    xml.StartQuote( "style" ) 
    xml.WriteColon( "font-family" , self._fontFamily ) 
    xml.WriteColon( "font-size" , str(self._fontSize) + "px")
    xml.WriteColon( "fill" , self._colorFill )
    xml.WriteColon( "text-anchor" , self._anchor )
    xml.EndQuote() 
    xml.PartialendMultitag() 
    xml.Write( self._text )
    xml.EndTag( "text" )
