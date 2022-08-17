from svg.svgDWG import svgDwg
from svg.svgELLIPSE import svgEllipse
from svg.svgRECT import svgRect
from svg.svgTEXT import svgText
from svgConstellation import svgConstellation
from svgFretboard import svgFretboard
from svgKey import svgKey


PIXELS_PER_INCH = 100
HBORDER = 0
VBORDER = 0

TOP_OFFSET = 0

FONT_TO_PIXELS = 1.3
HEIGHT_FONT_12 = 12 * FONT_TO_PIXELS

VERTICAL_OFFSET = 1.2 * PIXELS_PER_INCH

NUMBER_FRETS = 12

width  =  8.5 * PIXELS_PER_INCH - 2 * HBORDER
height = 11.0 * PIXELS_PER_INCH - 2 * VBORDER

HORIZONTAL_OFFSET = width/2

dwg = svgDwg( width , height )

# dwg.add( svgRect( width , height , 0 , 0 , colorStroke="blue"))


diameter = .4 * PIXELS_PER_INCH
xloc = .5 * PIXELS_PER_INCH

text_offset = .25 * PIXELS_PER_INCH

fret_arrays_all = [
  [
    ( "D"  , "D7"     , [ 5,5,4,5] ),
    ( "G"  , "Gmaj7"  , [ 3,5,4,4] ),
    ( "C"  , "Cmaj7"  , [ 3,3,2,4] ),
    ( "F#" , "F#m7b5" , [ 2,3,2,2] ),
    ( "B"  , "Bmin7"  , [ 5,5,4,4] ),
    ( "E"  , "Emin7"  , [ 0,5,5,4] ),
    ( "A"  , "Amin7"  , [ 3,3,2,2] ),
  ],
  [
    ( "G"  , "G7"     , [ 3,5,3,4] ),
    ( "C"  , "Cmaj7"  , [ 3,3,2,4] ),
    ( "F"  , "Fmaj7"  , [ 3,3,2,4] ),
    ( "B"  , "Bm7b5"  , [ 5,5,3,4] ),
    ( "E"  , "Emin7"  , [ 0,5,5,4] ),
    ( "A"  , "Amin7"  , [ 3,3,2,2] ),
    ( "D"  , "Dmin7"  , [ 5,5,3,5] ),
  ],
  ]


for idx in range(len(fret_arrays_all)) :
  yloc = .75 * PIXELS_PER_INCH
  fret_arrays = fret_arrays_all[idx]
  for key_idx,text,frets in fret_arrays:
    
    key = svgKey( key_idx )
  #  dwg.add( svgConstellation( diameter , xloc , yloc , pitches  ))
    dwg.add( svgFretboard( xloc ,
                           yloc - diameter ,
                           NUMBER_FRETS ,
                           key.makeChordMatrix( frets ) ,
                          ))
    dwg.add( svgText( xloc - text_offset , yloc , text , rotate=270.0) )
    yloc += VERTICAL_OFFSET
  xloc += HORIZONTAL_OFFSET
  
dwg.draw()


      
