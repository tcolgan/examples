class classExample:
  def __init__(self,val):
    self.val = val
  def incr(self,inc=1):
    self.val += inc


objExample = classExample( 5 )

objExample.incr( 3 )

print( objExample.val )
