#!/usr/bin/env python3

class myClass(object):
  
  def __init__(self,val):
    self.val = val
  
  def getVal(self):
    return self.val


def add(a,b):
  return a+b


def countdown(n):
  while n > 0:
    yield n
    n -= 1


def ex_input():
  a = int( input("input a :") )
  b = int( input("input b :") )
  print( add(a,b) )


def ex_countdown():
  for idx in countdown(5):
    print( idx )

def ex_inverse(x):
  return 1/x
  
def ex_class():
  clss= myClass( 30 )
  print( clss.getVal() )
    
def main():
  ex_class()


if __name__ == "__main__":
  main()
