from svg.svgDWG import svgDwg
from svg.svgELLIPSE import svgEllipse
from svg.svgRECT import svgRect
from svg.svgTEXT import svgText


# from svgGROUP import svgGroup
# from svgLINE import svgLine
PIXELS_PER_INCH = 100
HBORDER = 0
VBORDER = 0

TOP_OFFSET = 0

FONT_TO_PIXELS = 1.3
HEIGHT_FONT_12 = 12 * FONT_TO_PIXELS

width  = 11.0 * PIXELS_PER_INCH - 2 * HBORDER
height =  8.5 * PIXELS_PER_INCH - 2 * VBORDER

dwg = svgDwg( width , height )


diameter = 1 * PIXELS_PER_INCH
xloc = 2 * PIXELS_PER_INCH
yloc = 2 * PIXELS_PER_INCH

dwg.add( svgEllipse( xloc , yloc , diameter , diameter ) )
  
dwg.draw()
