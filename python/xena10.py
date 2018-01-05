#!/usr/bin/python

import pexpect
import time
import sys

ip='172.23.28.116'
logon='xena'
owner='COLGANT'
telnet_port=22611
module=2
port=0
stream=0

def expect_response ():
    child.expect('>')

def set_rate ( percent ):
    print '%s percent' % (percent)
    child.sendline( "P_TRAFFIC OFF" )
    expect_response() ;
    rate_string = 'PS_RATEFRACTION [%d] %d' % (stream,percent*10000)
    child.sendline( rate_string )
    expect_response() ;
    child.sendline( "P_TRAFFIC ON" )
    expect_response() ;
    return percent
    

telnet_string='telnet '+ip+' '+str(telnet_port)
print telnet_string

child = pexpect.spawn ( telnet_string  )
time.sleep(1)
# fout = file('log.txt','w')
# child.logfile_read = fout 

logon_string='C_LOGON \"%s\"' % (logon)
child.sendline( logon_string )
expect_response() ;

owner_string='C_OWNER \"%s\"' % (owner)
child.sendline( owner_string )
expect_response() ;

child.sendline( 'C_TIMEOUT 99999' )
expect_response() ;

module_port_string = '%d/%d' %(module,port)
child.sendline( module_port_string )

child.sendline( 'P_RESERVATION RELINQUISH' )
expect_response() ;

child.sendline( 'P_RESERVATION RESERVE' )
expect_response() ;


while True:
    for percent in range(5,105,5) :
        set_rate( percent)
        time.sleep(90)

child.sendcontrol( ']' )

