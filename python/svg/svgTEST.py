from svgRECT import svgRect
#from svgELLIPSE import svgEllipse
#from svgsvgGROUP import svgGroup
from svgDWG import svgDwg
#from svgsvgTEXT import svgText
from svgLINE import svgLine

import copy

def Transform( obj , x = 0 , y = 0 , rotate = 0 ):
  newobj = copy.copy( obj )
  newobj.transform( x , y , rotate )
  return newobj
  
def Scale( obj , scaleX , scaleY ):
  newobj = copy.copy( obj )
  newobj.scale( scaleX , scaleY )
  return newobj  

PIXELS_PER_INCH = 100

width  =  8.5 * PIXELS_PER_INCH
height = 11.0 * PIXELS_PER_INCH

# group = svgGroup()
# group.setViewport( 100 , 100 , 200 , 200 )
# group.add( svgRect(200,200,100,100,colorFill="green") )
# group.add( svgEllipse( 100,100,100,100 ) )
# 
colors=["black","red","orange","yellow","green","blue","purple","violet","brown","pink"]

dwg = svgDwg( width , height ) 

# for idx in range( 10 ):
#   trans = idx * 100
#   rot   = idx * 36
#   dwg.add( Transform( group , 500 , 500 , rot ) )

# for idx in range( 10 ):
#   scaleX = idx / 2.0
#   scaleY = idx / 4.0
#   rot   = idx * 36
#   dwg.add( Scale( group , scaleX , scaleY ) ) 

# svgtext = svgText( text="ABCdef" )
# for idx in range( 1,11 ):
#   newobj = copy.copy( svgtext )
#   newobj.setFontSize( 12 + idx )
#   newobj.setFontColor( colors[idx-1] )
#   newobj.setText( colors[idx-1] )
#   newobj.setLocation( idx * 100 , idx * 40 )
#   dwg.add( newobj )
  
dwg.add( svgRect( 850 , 1100 , 0 , 0 ) )
for idx in range( 1 , 11 ):
  dwg.add( svgLine( 70*idx , 10*idx, 70*idx , 20*idx , colors[idx-1] ) )
    
dwg.draw()


