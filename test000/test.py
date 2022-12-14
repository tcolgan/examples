#! /usr/bin/python3

'''this is a test program'''


if __name__ == '__main__':
  print( "Running main." )


for item in dir():
  print( item , "->" , eval( item ) )
  
import sys

if __name__ == "__main__":
    print(f"Arguments count: {len(sys.argv)}")
    for i, arg in enumerate(sys.argv):
        print(f"Argument {i}: {arg}")