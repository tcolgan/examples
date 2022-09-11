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

NUMBER_FRETS = 9

width  =  8.5 * PIXELS_PER_INCH - 2 * HBORDER
height = 11.0 * PIXELS_PER_INCH - 2 * VBORDER

HORIZONTAL_OFFSET = width/2

dwg = svgDwg( width , height )

  
  
  
diameter = .4 * PIXELS_PER_INCH
xloc = .5 * PIXELS_PER_INCH

text_offset = .25 * PIXELS_PER_INCH

FRETBOARD_OFFSET = 1.0 * PIXELS_PER_INCH
CONSTELLATION_OFFSET = 0.4 * PIXELS_PER_INCH

CIRCLE_SCALE = .8


CHORD_7      = [0,4,7,10]
CHORD_MAJ7   = [0,4,7,11]
CHORD_MIN7B5 = [0,3,6,10]
CHORD_MIN7   = [0,3,7,10]



fret_arrays_all = [
  [
    ( "D"  , "Dm7"    , [ 5,5,3,5] ),
    ( "G"  , "G7"     , [ 3,5,3,4] ),
    ( "C"  , "Cmaj7"  , [ 3,3,2,4] ),
    ( "F"  , "Fmaj7"  , [ 1,3,2,2] ),
    ( "B"  , "Bm7b5"  , [ 5,5,3,4] ),
    ( "E"  , "E7"     , [ 0,5,6,4] ),
    ( "A"  , "Am7"    , [ 3,3,2,2] ),
  ],
  [
    ( "E"  , "Em7"    , [ 7,7,5,7] ),
    ( "A"  , "A7"     , [ 5,7,5,6] ),
    ( "D"  , "Dmaj7"  , [ 5,5,4,6] ),
    ( "G"  , "Gmaj7"  , [ 3,5,4,4] ),
    ( "C#" , "C#m7b5" , [ 7,7,5,6] ),
    ( "F#" , "F#7"    , [ 2,7,8,6] ),
    ( "B"  , "Bm7"    , [ 5,5,4,4] ),
  ],
  ]

suffix = ["iv7" , "VII7" , "III7" , "VII7" , "ii7b5" , "V7" , "i7"]
chord_pitches = [ CHORD_MIN7 , CHORD_7 ,  CHORD_MAJ7 , CHORD_MAJ7 , CHORD_MIN7B5 , CHORD_7 , CHORD_MIN7 ]


for idx in range(len(fret_arrays_all)) :
  array_idx = 0
  
  yloc = .75 * PIXELS_PER_INCH
  fret_arrays = fret_arrays_all[idx]
  for key_idx,text,frets in fret_arrays:
    
    key = svgKey( key_idx )
    pitches = chord_pitches[ array_idx ]
    
    dwg.add( svgConstellation( CIRCLE_SCALE * diameter ,
                               xloc + CONSTELLATION_OFFSET ,
                               yloc ,
                               pitches ,
                               key_text = key_idx ))
    
    dwg.add( svgFretboard( xloc + FRETBOARD_OFFSET ,
                           yloc - diameter ,
                           NUMBER_FRETS ,
                           key.makeChordMatrix( frets ) ,
                          ))
                          
    text += " (" + suffix[ array_idx ] +")"
    dwg.add( svgText( xloc - text_offset , yloc , text , rotate=270.0 , fontSize = 15 ) )
    yloc += VERTICAL_OFFSET
    array_idx += 1
  xloc += HORIZONTAL_OFFSET
  
dwg.draw()


      