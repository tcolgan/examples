from datetime import date
from datetime import time 

cmds = [ "today()" ,
         "min" ,
         "max" ,
         "resolution" ,
         "today().ctime()" ,
         "today().isocalendar()" ,
         "today().isoformat()" ,
         "today().isoweekday()" ,
         "today().timetuple()" ,
         "today().weekday()" ,
       ]

for cmd in cmds:
	cmd_str = f"date.{cmd}"
	result = eval( cmd_str )
	print( f"{cmd_str:30s} = {result} :: type = {type(result)}" )
