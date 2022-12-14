#! /usr/bin/python3

def test(val):
  if val > 3 :
    return "greater than"
  elif val < 3 :
    return "less than"
  else :
    return "equal to"

for idx in range(5):
  print( str(idx) + " is " + test(idx) + " three")
  
  