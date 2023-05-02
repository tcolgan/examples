import time


cmds = [ "time()" ,
         "timezone" ,
         "altzone" ,
         "tzname" ,
         "asctime()" ,
         "ctime()" ,
         "gmtime()" ,
         "localtime()" ,
#         "" ,
       ]


for cmd in cmds :
   cmd_str = f"time.{cmd}"
   result = eval( cmd_str )
   print( f"{cmd_str} = {result}" )