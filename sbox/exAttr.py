import math

class Circle(object):
    def __init__(self,radius):
        self.radius = radius
    def __getattr__(self,name):
        if name == 'area':
            return math.pi*self.radius**2
        elif name == 'perimeter':
            return 2*math.pi*self.radius
        else:
            return object.__getattr__(self,name)
    def __setattr__(self,name,value):
        if name in ['area','perimeter']:
            raise TypeError("%s is readonly" % name)
        object.__setattr__(self,name,value)

cir = Circle(1)

print( "area = " , cir.area )
print( "perimeter = " , cir.perimeter )