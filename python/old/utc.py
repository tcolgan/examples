import datetime
import time

nowutc = datetime.datetime.utcnow()
nowetc = datetime.datetime.now()

isdst = bool(time.localtime( ).tm_isdst)

header = "EDT :" if isdst else "EST :"
tail   = "Daylight Savings Time" if isdst else "Standard Time"

print "UTC :" , nowutc.ctime()
print header , nowetc.ctime() , tail

