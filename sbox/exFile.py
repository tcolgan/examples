import os

FILE_NAME = "test.txt"

def fileRead():
   file = open( FILE_NAME , "r")
   for line in file:
     print( line )
   file.close()


def fileWrite():
   data = [ "one" , "two" , "three"]
   file = open( FILE_NAME , "w")
   for item in data:
         file.write( item )
         file.write( "\n" )
   file.close()

def fileDelete():
	os.remove( FILE_NAME )

fileWrite()

fileRead()

fileDelete()