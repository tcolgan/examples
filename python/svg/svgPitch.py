
import math

from svg.svgGROUP import svgGroup
from svg.svgELLIPSE import svgEllipse
from svg.svgLINE import svgLine
from svg.svgRECT import svgRect
from svg.svgPolygon import svgPolygon

ICON_SIZE = 10
ICON_SIZE_HALF = ICON_SIZE / 2

SMALL_CIRCLE_SIZE = 3


class svgPitch(svgGroup):
  
  def __init__(self,xloc,yloc,pitch,scale=1.0):

    super().__init__()
        
    self._xloc = xloc
    self._yloc = yloc
    self._scaleX = scale
    self._scaleY = scale


    if pitch == 0 :
      self.addSquare(ICON_SIZE)
        
    elif pitch == 1 :
      self.addX()
      self.addCircle(radius=SMALL_CIRCLE_SIZE,colorFill="black")

    elif pitch == 2 :
      self.addX()

    elif pitch == 3 :
      self.addTriangle(colorFill="black")
        
    elif pitch == 4 :
      self.addTriangle(colorFill="white")

    elif pitch == 5 :
      self.addDiamond()

    elif pitch == 6 :
      self.addCircle(radius=ICON_SIZE_HALF,colorFill="black")

    elif pitch == 7 :
      self.addCircle(radius=ICON_SIZE_HALF,colorFill="white")

    elif pitch == 8 :
      self.add6()
      self.addCircle(radius=ICON_SIZE_HALF/2,colorFill="black")

    elif pitch == 9 :
      self.add6()

    elif pitch == 10 :
      self.addCircle(radius=SMALL_CIRCLE_SIZE,colorFill="black")

    elif pitch == 11 :
      self.addCircle(radius=SMALL_CIRCLE_SIZE,colorFill="white")

        
  def addX( self ):
    self.add( svgLine( +ICON_SIZE_HALF , +ICON_SIZE_HALF , -ICON_SIZE_HALF , -ICON_SIZE_HALF) )
    self.add( svgLine( -ICON_SIZE_HALF , +ICON_SIZE_HALF , +ICON_SIZE_HALF , -ICON_SIZE_HALF) )
    
    
  def add6( self ):
    x_delta = ICON_SIZE_HALF * math.cos( 2 * math.pi * 30 / 360 )
    y_delta = ICON_SIZE_HALF * math.sin( 2 * math.pi * 30 / 360 )

    self.add( svgLine( 0        , +ICON_SIZE_HALF , 0        , -ICON_SIZE_HALF ) )
    self.add( svgLine( +x_delta , +y_delta        , -x_delta , -y_delta ) )
    self.add( svgLine( -x_delta , +y_delta        , +x_delta , -y_delta ) )


  def addDiamond(self):
    
    x1 = +ICON_SIZE_HALF
    y1 = 0
    
    x2 = 0
    y2 = -ICON_SIZE_HALF

    x3 = -ICON_SIZE_HALF
    y3 = 0

    x4 = 0
    y4 = +ICON_SIZE_HALF
    
    points = [(x1,y1),(x2,y2),(x3,y3),(x4,y4)]
    self.add( svgPolygon( points ) )


  def addTriangle(self,colorFill="white"):

    x_delta = ICON_SIZE_HALF + math.cos( 2 * math.pi * 30 / 360 )
    y_delta = ICON_SIZE_HALF + math.sin( 2 * math.pi * 30 / 360 )

    x1 = 0
    y1 = -ICON_SIZE_HALF
    x2 = x_delta
    y2 = y_delta
    x3 = -x_delta
    y3 = y_delta
    
    points = [(x1,y1),(x2,y2),(x3,y3)]
    self.add( svgPolygon( points , colorFill ) )
    

  def addSquare(self,size):
    self.add( svgRect( size , size , -size / 2 , -size / 2 , colorFill = "white" ) )


  def addCircle(self,radius,colorFill="white"):
    self.add( svgEllipse( 0 , 0 , radius , radius, colorFill=colorFill ) )
