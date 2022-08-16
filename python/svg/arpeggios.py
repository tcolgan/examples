from svg.svgDWG import svgDwg
from svg.svgELLIPSE import svgEllipse
from svg.svgRECT import svgRect
from svg.svgTEXT import svgText
from svgConstellation import svgConstellation
from svgFretboard import svgFretboard



PIXELS_PER_INCH = 100
HBORDER = 0
VBORDER = 0

TOP_OFFSET = 0

FONT_TO_PIXELS = 1.3
HEIGHT_FONT_12 = 12 * FONT_TO_PIXELS

VERTICAL_OFFSET = 1.2 * PIXELS_PER_INCH

width  =  8.5 * PIXELS_PER_INCH - 2 * HBORDER
height = 11.0 * PIXELS_PER_INCH - 2 * VBORDER

dwg = svgDwg( width , height )

dwg.add( svgRect( width , height , 0 , 0 , colorStroke="blue"))


diameter = .4 * PIXELS_PER_INCH
xloc = 1 * PIXELS_PER_INCH
yloc = 1 * PIXELS_PER_INCH

text_offset = 1.4 * diameter

pitch_arrays = [
    ( "chromatic scale" , [0,1,2,3,4,5,6,7,8,9,10,11] ) ,
    ( "major scale"     , [0,2,4,5,7,9,11]            ) ,
    ( "minor scale"     , [0,2,3,5,7,8,10]            ),
  ]

for text,pitches in pitch_arrays:
  
  dwg.add( svgConstellation( diameter , xloc , yloc , pitches  ))
  dwg.add( svgFretboard( xloc + 2*diameter , yloc - diameter , pitches ))
  dwg.add( svgText( xloc - text_offset , yloc , text , rotate=270.0) )
  yloc += VERTICAL_OFFSET
  
dwg.draw()
