import os
from svgKey import svgKey


for key in svgKey.key_offsets :
  callscript = "python3 arpeggios.py " + key + " > arpeggios" + key + ".svg"
#  print( callscript )
  os.system( callscript )