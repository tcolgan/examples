from svg.svgDWG import svgDwg
from svg.svgELLIPSE import svgEllipse
from svg.svgRECT import svgRect
from svg.svgTEXT import svgText


# from svgGROUP import svgGroup
# from svgLINE import svgLine
PIXELS_PER_INCH = 100
HBORDER = 30
VBORDER = 40

TOP_OFFSET = 30

FONT_TO_PIXELS = 1.3
HEIGHT_FONT_12 = 12 * FONT_TO_PIXELS

width  = 11.0 * PIXELS_PER_INCH - 2 * HBORDER
height =  8.5 * PIXELS_PER_INCH - 2 * VBORDER

dwg = svgDwg( width , height ) 

dwg.add( svgText( width / 2 , TOP_OFFSET * 2 / 3 , "Test Text" , fontSize=20 ) )

dwg.add( svgRect( width , height , 0 , 0 ) )   

width  = 2 * PIXELS_PER_INCH 
height = 3 * PIXELS_PER_INCH 
xloc   = 2 * PIXELS_PER_INCH 
yloc   = 3 * PIXELS_PER_INCH 
dwg.add( svgEllipse( width , height , xloc , yloc ) ) 
  
dwg.draw()
