import svg.XML as xml
from svg.svgBASE import svgBase


class svgGroup(svgBase):

  def __init__(self, xloc=0 , yloc=0 , rotate=0 , scaleX=1.0 , scaleY=1.0 ):
    self._xloc = xloc
    self._yloc = yloc
    self._rotate = rotate
    self._scaleX = scaleX
    self._scaleY = scaleY
    self._viewport = False
    self._viewport_x = 0.0
    self._viewport_y = 0.0
    self._viewport_width = 1.0
    self._viewport_height = 1.0
    self._set = []

  def draw(self):

    if self._viewport:
      buff = "svg x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"" % ( self._viewport_x , self._viewport_y , self._viewport_width , self._viewport_height )
      xml.StartTag( buff ) ;

    buff  = "g transform=\"translate(%d,%d) rotate(%.1f) scale( %.2f , %.2f )\"" % (self._xloc , self._yloc , self._rotate , self._scaleX , self._scaleY )
    xml.StartTag( buff )

    for element in self._set:
      element.draw() ;

    xml.EndTag( "g" ) ;

    if self._viewport :
      xml.EndTag( "svg" ) ;
      
  def add( self, element ):
    self._set.append( element )
    
  def scale( self , scaleX , scaleY ):
    self._scaleX = self._scaleX * scaleX
    self._scaleY = self._scaleY * scaleY
    
  def transform( self , xloc = 0 , yloc = 0 , rotate = 0 ) :
    self._xloc   = self._xloc   + xloc
    self._yloc   = self._yloc   + yloc
    self._rotate = self._rotate + rotate
     
  def setViewport( self , x , y , width , height ):
    self._viewport = True ;
    self._viewport_x      = x
    self._viewport_y      = y
    self._viewport_width  = width
    self._viewport_height = height
