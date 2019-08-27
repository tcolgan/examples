import XML as xml
from svgGROUP import svgGroup

class svgDwg( svgGroup ):
  
  def __init__( self , width = 1 , height = 1 ):
    self._width = width
    self._height = height
    super(svgDwg,self).__init__()

  def draw(self):
    self.Start()
    super(svgDwg,self).draw() 
    self.End()
        
    
  def Start(self):
    buff = "0 0 %d %d" % ( self._width ,  self._height )
    xml.Write( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" ) 
    xml.StartMultitag( "svg" ) 
    xml.WritePar( "xmlns:svg" , "http://www.w3.org/2000/svg" ) 
    xml.WritePar( "xmlns" , "http://www.w3.org/2000/svg" ) 
    xml.WritePar( "version" , "1.1" ) 
    xml.WritePar( "width" , self._width   , "px" ) 
    xml.WritePar( "height" , self._height , "px" ) 
    xml.WritePar( "viewBox" , buff ) ;
    xml.PartialendMultitag() ;
  
  def End(self):
    xml.EndTag( "svg" ) ;
    