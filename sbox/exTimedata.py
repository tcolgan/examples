from datetime import date
from datetime import datetime
import time


today = date.today()

print( today )

print( today.strftime( "today is %B %d, %Y" ) )
print( today.strftime( "today is %m/%d/%y" ) )
print( today.strftime( "today is %b-%d-%Y" ) )

print( "\n" )

now = datetime.now()

print( now )
print( now.strftime("%d/%m/%Y %H:%M:%S") )

print( "\n" )

timestamp = time.time()
print( "timestamp = " , timestamp )

bday = date( 1955 , 11 , 22 )
print( "bday = " , bday )

