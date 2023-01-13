import math

class Circle(object):
    def __init__(self,radius):
    	self.radius = radius
    @property
    def area(self):
    	return math.pi*self.radius**2
    @area.setter
    def area(self,val):
        self.radius = math.sqrt( val / math.pi )
    @property
    def perimeter(self):
    	return 2*math.pi*self.radius
    @perimeter.setter
    def perimeter(self,val):
    	self.radius = val / (2 * math.pi)
    	
circle = Circle(3)
    	
print( "radius     = " , circle.radius )
print( "area       = " , circle.area )
print( "perimeter  = " , circle.perimeter )

circle.area = 4

print( "radius     = " , circle.radius )
print( "area       = " , circle.area )
print( "perimeter  = " , circle.perimeter )

circle.perimeter = 6

print( "radius     = " , circle.radius )
print( "area       = " , circle.area )
print( "perimeter  = " , circle.perimeter )
   