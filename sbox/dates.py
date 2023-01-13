import datetime as dt 

now = dt.datetime.now()
timeDelta = dt.timedelta(days=1)
numDays = 31


for idx in range(numDays):
  print( now.strftime("%a  %d %b").lower() )
  day = now.weekday()
  if ( day == 4 ) or ( day == 6 ) :
    print( "=============")
  now += timeDelta
