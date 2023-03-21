"""
example of operator overloading
"""

class Complex(object):
  def __init__(self,real,imag=0):
    self.real = float(real)
    self.imag = float(imag)
  def __repr__(self):
    return "Complex(%s,%s)" % (self.real, self.imag)
  def __str__(self):
    return "(%g+%gj)" % (self.real, self.imag)
  # self + other
  def __add__(self,other):
    return Complex(self.real + other.real, self.imag + other.imag)
  # self - other
  def __sub__(self,other):
    return Complex(self.real - other.real, self.imag - other.imag)



a = Complex(1,2)
b = Complex(3,4)

c=a+b 
d=a-b

print( "a = " , a )
print( "b = " , b )

print( "a+b = " , c )
print( "a-b = " , d )
