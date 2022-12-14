#!/usr/bin/python

import datetime
from datetime import datetime, timedelta

import sys
import datetime

filename = "tmc.bat"

today = datetime.date.today()
hour = 1800

file = open( filename , "w" )

for idx in range( 60 ) :
    year = today.year
    mon  = today.month
    day  = today.day
     
    line = ( "rename image%2.2d.gif %d_%2.2d_%2.2d_%4.4d.gif\n" % (idx+1 , year , mon , day , hour ) )
    file.write( line )
#    print line
    hour -= 600 
    if hour < 0 :
        hour = 1800
        today = today - timedelta( days = 1 )

file.close()

