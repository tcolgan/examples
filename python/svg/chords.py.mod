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

NUMBER_FRETS = 13

width_inches  =  30.0
#width_inches  =  8.5
height_inches =  11.0

width  =  width_inches  * PIXELS_PER_INCH - 2 * HBORDER
height =  height_inches * PIXELS_PER_INCH - 2 * VBORDER

HORIZONTAL_OFFSET = width/6

dwg = svgDwg( width , height )


diameter = .4 * PIXELS_PER_INCH
xloc = .5 * PIXELS_PER_INCH

text_offset = .25 * PIXELS_PER_INCH

FRETBOARD_OFFSET = 1.0 * PIXELS_PER_INCH
CONSTELLATION_OFFSET = 0.4 * PIXELS_PER_INCH

CIRCLE_SCALE = .8


fret_arrays_all = [
   [
     ( "Dm7"    , 0 ) ,
     ( "Gm7"    , 1 ) ,
     ( "C7"     , 0 ) ,
     ( "Fmaj7"  , 2 ) ,
     ( "Bbmaj7" , 1 ) ,
     ( "Em7b5"  , 1 ) ,
     ( "A7"     , 0 ) ,
   ],
   [
     ( "Em7"    , 1 ) ,
     ( "Am7"    , 0 ) ,
     ( "D7"     , 1 ) ,
     ( "Gmaj7"  , 1 ) ,
     ( "Cmaj7"  , 2 ) ,
     ( "F#m7b5" , 0 ) ,
     ( "B7"     , 1 ) ,
   ],
   [
     ( "Am7"    , 0 ) ,
     ( "Dm7"    , 1 ) ,
     ( "G7"     , 0 ) ,
     ( "Cmaj7"  , 2 ) ,
     ( "Fmaj7"  , 1 ) ,
     ( "Bm7b5"  , 1 ) ,
     ( "E7"     , 3 ) ,
   ],
   [
     ( "F#m7"    , 1 ) ,
     ( "Bm7"    , 0 ) ,
     ( "E7"     , 1 ) ,
     ( "Amaj7"  , 1 ) ,
     ( "Dmaj7"  , 2 ) ,
     ( "G#m7b5" , 0 ) ,
     ( "C7"     , 1 ) ,
   ],
   [
     ( "Bm7"    , 0 ) ,
     ( "Em7"    , 1 ) ,
     ( "A7"     , 0 ) ,
     ( "Dmaj7"  , 2 ) ,
     ( "Gmaj7"  , 1 ) ,
     ( "C#m7b5"  , 1 ) ,
     ( "F#7"     , 3 ) ,
   ],
   [
     ( "G#m7"    , 1 ) ,
     ( "C#m7"    , 0 ) ,
     ( "F#7"     , 1 ) ,
     ( "Bmaj7"  , 1 ) ,
     ( "Emaj7"  , 2 ) ,
     ( "A#m7b5" , 0 ) ,
     ( "D7"     , 1 ) ,
   ],
   [
     ( "C#m7"    , 0 ) ,
     ( "F#m7"    , 1 ) ,
     ( "B7"     , 0 ) ,
     ( "Emaj7"  , 2 ) ,
     ( "Amaj7"  , 1 ) ,
     ( "D#m7b5"  , 1 ) ,
     ( "A#7"     , 3 ) ,
   ],
  ]



suffix = ["vi7" , "ii7" , "V7" , "Imaj7" , "IVmaj7" , "vii7b5" , "III7" ]


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
                           key.makeMatrix( pitches ) ,
                           color = "lightgrey"
                          ))
                          
    dwg.add( svgFretboard( xloc + FRETBOARD_OFFSET ,
                           yloc - diameter ,
                           NUMBER_FRETS ,
                           key.makeChordMatrix( frets ) ,
                           showAll = False ,
                          ))

                          
    text = key_idx + text[1:] + " (" + suffix[ array_idx ] +")"
    dwg.add( svgText( xloc - text_offset , yloc , text , rotate=270.0 , fontSize = 15 ) )
    yloc += VERTICAL_OFFSET
    array_idx += 1
  xloc += HORIZONTAL_OFFSET
  
dwg.draw()


      
