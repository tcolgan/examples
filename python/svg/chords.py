from svg.svgDWG import svgDwg
from svg.svgELLIPSE import svgEllipse
from svg.svgRECT import svgRect
from svg.svgTEXT import svgText
from svgConstellation import svgConstellation
from svgFretboard import svgFretboard
from svgKey import svgKey
from finger import finger


PIXELS_PER_INCH = 100
HBORDER = 0
VBORDER = 0

TOP_OFFSET = 0

FONT_TO_PIXELS = 1.3
HEIGHT_FONT_12 = 12 * FONT_TO_PIXELS

VERTICAL_OFFSET = 1.2 * PIXELS_PER_INCH

NUMBER_FRETS = 14

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


'''
  [
    ( "D"  , "D7"     , [ 5,5,4,5] ),
    ( "G"  , "Gmaj7"  , [ 3,5,4,4] ),
    ( "C"  , "Cmaj7"  , [ 3,3,2,4] ),
    ( "F#" , "F#m7b5" , [ 2,3,2,2] ),
    ( "B"  , "Bm7"    , [ 5,5,4,4] ),
    ( "E"  , "Em7"    , [ 0,5,5,4] ),
    ( "A"  , "Am7"    , [ 3,3,2,2] ),
  ],
  [
    ( "G"  , "G7"     , [ 3,5,3,4] ),
    ( "C"  , "Cmaj7"  , [ 3,3,2,4] ),
    ( "F"  , "Fmaj7"  , [ 1,3,2,2] ),
    ( "B"  , "Bm7b5"  , [ 5,5,3,4] ),
    ( "E"  , "Em7"    , [ 0,5,5,4] ),
    ( "A"  , "Am7"    , [ 3,3,2,2] ),
    ( "D"  , "Dm7"    , [ 5,5,3,5] ),
  ],
'''

fret_arrays_all = [
    ( "Em7"    , 1 ) ,
    ( "Am7"    , 0 ) ,
    ( "D7"     , 1 ) ,
    ( "Gmaj7"  , 1 ) ,
    ( "Cmaj7"  , 0 ) ,
    ( "F#m7b5" , 0 ) ,
    ( "B7"     , 1 ) ,
  ],


suffix = ["vi7" , "ii7" , "V7" , "Imaj7" , "IVmaj7" , "vii7b5" , "iii7" ]
chord_pitches = [ CHORD_MIN7 , CHORD_MIN7 , CHORD_7 , CHORD_MAJ7 ,  CHORD_MAJ7 , CHORD_MIN7B5 , CHORD_MIN7 ]

def parse(val):
  if val[1] == "#" or val[1] == "b" :
     key = val[0:2]
     chord = val[2:]
  else:
     key = val[0]
     chord = val[1:]
  return key,"X"+chord

for idx in range(len(fret_arrays_all)) :
  array_idx = 0
  
  yloc = .75 * PIXELS_PER_INCH
  fret_arrays = fret_arrays_all[idx]
  for text,chord_idx in fret_arrays:
    
    key_idx,text = parse(text)
    key = svgKey( key_idx )
#    pitches = chord_pitches[ array_idx ]

    pitches,frets = finger( key_idx ).getFingering( text , chord_idx )
    
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
                          
    text = key_idx + text[1:] + " (" + suffix[ array_idx ] +")"
    dwg.add( svgText( xloc - text_offset , yloc , text , rotate=270.0 , fontSize = 15 ) )
    yloc += VERTICAL_OFFSET
    array_idx += 1
  xloc += HORIZONTAL_OFFSET
  
dwg.draw()


      
