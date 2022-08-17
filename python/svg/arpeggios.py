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

NUMBER_FRETS = 20

NUMBER_STRINGS = 4
NUMBER_FRETS = 20

NUMBER_NOTES = 12


width  =  8.5 * PIXELS_PER_INCH - 2 * HBORDER
height = 11.0 * PIXELS_PER_INCH - 2 * VBORDER

dwg = svgDwg( width , height )

# dwg.add( svgRect( width , height , 0 , 0 , colorStroke="blue"))


diameter = .4 * PIXELS_PER_INCH
xloc = 1.2 * PIXELS_PER_INCH
yloc = .75 * PIXELS_PER_INCH

text_offset = 1.4 * diameter

pitch_arrays = [
    ( "chromatic scale" , [0,1,2,3,4,5,6,7,8,9,10,11] ) ,
    ( "major scale"     , [0,2,4,5,7,9,11]            ) ,
    ( "minor scale"     , [0,2,3,5,7,8,10]            ),
    ( "X7"              , [0,4,7,10] ),
    ( "Xmaj7"           , [0,4,7,11] ),
    ( "Xmin7"           , [0,3,7,10] ),
    ( "Xmin7b5"         , [0,3,6,10] ),
    ( "Xsus2"           , [0,2,7]    ),
    ( "Xsus4"           , [0,5,7]    ),
  ]
  
note_matrix = [
    [ -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ] ,
    [ -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ] ,
    [ -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ] ,
    [ -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ] ,
  ]
  
  
def incr( start ) :
  value = start + 1
  if value >= NUMBER_NOTES :
    value = value - NUMBER_NOTES
  return value


def makeNoteMatrix( pitches ) :
  matrix = []

  pitch_string = [9,2,7,0]
  for string in range( NUMBER_STRINGS ) :
    array = []
    pitch = pitch_string[ string ]
    for fret in range( NUMBER_FRETS ) :
      if pitch in pitches:
        val = pitch
      else:
        val = -1
      array.append( val )
      pitch = incr( pitch )
    matrix.append( array )
  return matrix
  

for text,pitches in pitch_arrays:
  
  dwg.add( svgConstellation( diameter , xloc , yloc , pitches  ))
  dwg.add( svgFretboard( xloc + 2*diameter , yloc - diameter , NUMBER_FRETS , makeNoteMatrix( pitches ) ))
  dwg.add( svgText( xloc - text_offset , yloc , text , rotate=270.0) )
  yloc += VERTICAL_OFFSET
  
dwg.draw()


      
