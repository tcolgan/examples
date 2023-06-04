#!/usr/bin/env python

import datetime as dt 

now = dt.datetime.now()
timeDelta = dt.timedelta(days=1)
numDays = 365
endtime = dt.datetime(2023,12,1)


for idx in range(numDays):
  delta = endtime - now
  days_remaining = delta.days
  print( f'{days_remaining:4}  {now.strftime("%a  %d %b %Y").lower()}' )
  day = now.weekday()
  if ( day == 4 ) or ( day == 6 ) :
    print( "=======================")
  now += timeDelta
