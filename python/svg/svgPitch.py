
import math

from svg.svgGROUP import svgGroup
from svg.svgELLIPSE import svgEllipse
from svg.svgLINE import svgLine
from svg.svgRECT import svgRect
from svg.svgPolygon import svgPolygon

ICON_SIZE = 10
ICON_SIZE_HALF = ICON_SIZE / 2


class svgPitch(svgGroup):
  
  def __init__(self,xloc,yloc,pitch,scale=1.0):

    super().__init__()
        
    self._pitch = pitch
    self._xloc = xloc
    self._yloc = yloc
    self._pitchIcon = svgGroup(scaleX=scale,scaleY=scale)


    if self._pitch == 0 :
      self.addSquare(xloc , yloc, ICON_SIZE)
        
    elif self._pitch == 1 :
      self.addX( xloc , yloc )
      self.addCircle(xloc,yloc,radius=ICON_SIZE_HALF/2,colorFill="black")

    elif self._pitch == 2 :
      self.addX( xloc , yloc )

    elif self._pitch == 3 :
      self.addTriangle(xloc,yloc,colorFill="black")
        
    elif self._pitch == 4 :
      self.addTriangle(xloc,yloc,colorFill="white")

    elif self._pitch == 5 :
      self.addDiamond(xloc,yloc)

    elif self._pitch == 6 :
      self.addCircle(xloc,yloc,radius=ICON_SIZE_HALF,colorFill="black")

    elif self._pitch == 7 :
      self.addCircle(xloc,yloc,radius=ICON_SIZE_HALF,colorFill="white")

    elif self._pitch == 8 :
      self.add6( xloc , yloc )
      self.addCircle(xloc,yloc,radius=ICON_SIZE_HALF/2,colorFill="black")

    elif self._pitch == 9 :
      self.add6( xloc , yloc )

    elif self._pitch == 10 :
      self.addCircle(xloc,yloc,radius=ICON_SIZE_HALF,colorFill="black")

    elif self._pitch == 11 :
      self.addCircle(xloc,yloc,radius=ICON_SIZE_HALF,colorFill="grey")

        
  def draw(self):
    self._pitchIcon.draw()
        
        
  def addX( self , xloc , yloc ):
    self._pitchIcon.add( svgLine( xloc + ICON_SIZE_HALF , yloc + ICON_SIZE_HALF , xloc - ICON_SIZE_HALF , yloc - ICON_SIZE_HALF) )
    self._pitchIcon.add( svgLine( xloc - ICON_SIZE_HALF , yloc + ICON_SIZE_HALF , xloc + ICON_SIZE_HALF , yloc - ICON_SIZE_HALF) )
    
    
  def add6( self , xloc , yloc ):
    x_delta = ICON_SIZE_HALF * math.cos( 2 * math.pi * 30 / 360 )
    y_delta = ICON_SIZE_HALF * math.sin( 2 * math.pi * 30 / 360 )

    self._pitchIcon = svgGroup()
    self._pitchIcon.add( svgLine( xloc , yloc + ICON_SIZE_HALF , xloc , yloc - ICON_SIZE_HALF ) )
    self._pitchIcon.add( svgLine( xloc + x_delta , yloc + y_delta , xloc - x_delta , yloc - y_delta ) )
    self._pitchIcon.add( svgLine( xloc - x_delta , yloc + y_delta , xloc + x_delta , yloc -   y_delta ) )


  def addLittleCircle(self,xloc,yloc):
    
    radius = ICON_SIZE_HALF / 2
    self._pitchIcon.add( svgEllipse( xloc , yloc , radius , radius , colorFill="black") )


  def addDiamond(self,xloc,yloc):
    
    self._pitchIcon.add( svgLine( xloc + ICON_SIZE_HALF , yloc , xloc , yloc + ICON_SIZE_HALF) )
    self._pitchIcon.add( svgLine( xloc - ICON_SIZE_HALF , yloc , xloc , yloc + ICON_SIZE_HALF) )
    self._pitchIcon.add( svgLine( xloc - ICON_SIZE_HALF , yloc , xloc , yloc - ICON_SIZE_HALF) )
    self._pitchIcon.add( svgLine( xloc + ICON_SIZE_HALF , yloc , xloc , yloc - ICON_SIZE_HALF) )


  def addTriangle(self,xloc,yloc,colorFill="white"):

    x_delta = ICON_SIZE_HALF + math.cos( 2 * math.pi * 30 / 360 )
    y_delta = ICON_SIZE_HALF + math.sin( 2 * math.pi * 30 / 360 )

    x1 = xloc
    y1 = yloc - ICON_SIZE_HALF
    x2 = xloc + x_delta
    y2 = yloc + y_delta
    x3 = xloc - x_delta
    y3 = yloc + y_delta
    
    points = [(x1,y1),(x2,y2),(x3,y3)]
    self._pitchIcon.add( svgPolygon( points , colorFill ) )
    

  def addSquare(self,xloc,yloc,size):
    self._pitchIcon.add( svgRect( size , size , xloc - size / 2 , yloc - size / 2 ) )


  def addCircle(self,xloc,yloc,radius,colorFill="white"):
    self._pitchIcon.add( svgEllipse( xloc , yloc , radius , radius, colorFill=colorFill ) )
