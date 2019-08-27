class svgBase(object):

  def __init__(self):
    pass

  def draw(self):
    print( "ERROR: Class \"" + self.__class__.__name__  + "\" must define draw method!" )
        