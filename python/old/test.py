#!/usr/bin/env python3
"""
test documentation

line 1
line 2
"""

class myClass(object):
  
  def __init__(self,val):
    self.val = val
  
  def getVal(self):
    return self.val


def add(a,b):
  'add two numbers and return result'
  return a+b


def countdown(n):
  while n > 0:
    yield n
    n -= 1


def tst_input():
  a = int( input("input a :") )
  b = int( input("input b :") )
  print( add(a,b) )


def tst_countdown():
  for idx in countdown(5):
    print( idx )

def tst_inverse(x):
  return 1/x
  
def tst_class():
  clss= myClass( 30 )
  print( clss.getVal() )
    
def main():
  tst_class()


if __name__ == "__main__":
  main()
