import datetime as dt 

now = dt.datetime.now()
timeDelta = dt.timedelta(days=1)
numDays = 20


for idx in range(numDays):
  print( now.strftime("%a  %d %b").lower() )
  if now.weekday() == 6:
    print( "=============")
  now += timeDelta
