from svg.svgDWG import svgDwg
from svg.svgELLIPSE import svgEllipse
from svg.svgRECT import svgRect
from svg.svgTEXT import svgText
from svgConstellation import svgConstellation



PIXELS_PER_INCH = 100
HBORDER = 0
VBORDER = 0

TOP_OFFSET = 0

FONT_TO_PIXELS = 1.3
HEIGHT_FONT_12 = 12 * FONT_TO_PIXELS

width  =  8.5 * PIXELS_PER_INCH - 2 * HBORDER
height = 11.0 * PIXELS_PER_INCH - 2 * VBORDER

dwg = svgDwg( width , height )

dwg.add( svgRect( width , height , 0 , 0 , colorStroke="blue"))


diameter = .5 * PIXELS_PER_INCH
xloc = 1 * PIXELS_PER_INCH
yloc = 1 * PIXELS_PER_INCH

#dwg.add( svgConstellation( diameter , xloc, yloc , [0,3,7] ))
dwg.add( svgConstellation( diameter , xloc, yloc , [0,1,2,3,4,5,6,7,8,9,10,11] ))
  
dwg.draw()
