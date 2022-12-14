#!/usr/bin/python

#import getpass
#import sys
import telnetlib

prompt = "=> "

def to_command ( command ):
    command += "\r\n"
    tn.write( command )
    str = tn.read_until( prompt )
    return str[ len( command ) : len( str ) - len( prompt ) ] 


HOST = "10.88.39.154"
PORT = 53058
USER = "administrator"
PW   = "netscout1"

tn = telnetlib.Telnet( HOST , PORT )
tn.read_until( prompt )

to_command( "logon " + USER + " " + PW )

print to_command( "show lic" )

tn.write( "exit\n\r" )
tn.close()



