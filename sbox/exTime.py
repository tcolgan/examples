import time


cmds = [ "time()" ,
         "timezone" ,
         "altzone" ,
         "tzname" ,
         "asctime()" ,
         "ctime()" ,
         "gmtime()" ,
         "localtime()" ,
         "perf_counter()" ,
         "process_time()" ,
#         "" ,
       ]

separator = 60*"-"

for cmd in cmds :
   cmd_str = f"time.{cmd}"
   result = eval( cmd_str )
   print( "\n"+separator )
   print( f"{cmd_str} = {result}" )
   print( separator )
   if "()" in cmd_str:
      base = cmd_str.replace("(","").replace(")","")
      print( eval( f"{base}.__doc__") )

fmts = [ "%c" ,
         "%Y %m %d" ,
         "%a %b %d %Y %H:%M:%S" ,
         "%A %B %d %Y %I:%M %p" ,
         "day of year: %j" ,
         "week of year (sun first): %U" ,
         "week of year (mon first): %W" ,
         "weekday (0=sunday): %w" ,
         "local time: %X" , 
         "%Z" ,
       ]

now = time.gmtime()

print( "\nstrftime:" )

for fmt in fmts:
   cmd = f'time.strftime( "{ fmt }" , now )'
   result = eval( cmd )
   print( f'{fmt:30s} :: {result}' )
