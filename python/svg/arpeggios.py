#!/usr/bin/python3


import sys

from svg.svgDWG import svgDwg
from svg.svgELLIPSE import svgEllipse
from svg.svgRECT import svgRect
from svg.svgTEXT import svgText
from svgConstellation import svgConstellation
from svgFretboard import svgFretboard
from svgKey import svgKey
from pitchArrays import pitch_arrays


PIXELS_PER_INCH = 100
HBORDER = 0
VBORDER = 0

TOP_OFFSET = 0

FONT_TO_PIXELS = 1.3
HEIGHT_FONT_12 = 12 * FONT_TO_PIXELS

VERTICAL_OFFSET = 1.2 * PIXELS_PER_INCH

NUMBER_STRINGS = 4
NUMBER_FRETS = 20

CIRCLE_SCALE = .8



width  =  8.5 * PIXELS_PER_INCH - 2 * HBORDER
height = 11.0 * PIXELS_PER_INCH - 2 * VBORDER

TITLE_OFFSET_X = PIXELS_PER_INCH * .02
TITLE_OFFSET_Y = PIXELS_PER_INCH * .2

dwg = svgDwg( width , height )

# dwg.add( svgRect( width , height , 0 , 0 , colorStroke="blue"))


diameter = .4 * PIXELS_PER_INCH
xloc = 1.2 * PIXELS_PER_INCH
yloc = .75 * PIXELS_PER_INCH

text_offset = 2 * diameter


key_text = "G"
if( len( sys.argv ) > 1 ) :
  key_text = sys.argv[1]
title = "KEY : " + key_text
dwg.add( svgText(TITLE_OFFSET_X,TITLE_OFFSET_Y,title,fontSize=24,anchor="left"))


for dict_key in pitch_arrays:
  
  text = dict_key
  pitches= pitch_arrays[ dict_key ]
  
  key = svgKey( key_text )
  dwg.add( svgConstellation( CIRCLE_SCALE * diameter , xloc , yloc , pitches , key_text = key_text ) )
  dwg.add( svgFretboard( xloc + 2*diameter ,
                         yloc - diameter ,
                         NUMBER_FRETS ,
                         key.makeMatrix( pitches ) ,
                        ))
  dwg.add( svgText( xloc - text_offset , yloc , text , rotate=270.0) )
  yloc += VERTICAL_OFFSET
  
dwg.draw()


      
