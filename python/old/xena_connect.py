#!/usr/bin/python
import pexpect
import sys
import time

def connect_xena ():
    ip='172.23.28.116'
    logon='xena'
    owner='COLGANT'
    telnet_port=22611
    module=2
    port=0
    stream=0

    telnet_string='telnet '+ip+' '+str(telnet_port)
    print telnet_string

    xena = pexpect.spawn ( telnet_string  )
    fout = file('xenalog.txt','a')
    xena.logfile_read = fout
    time.sleep(1)

    logon_string='C_LOGON \"%s\"' % (logon)
    xena.sendline( logon_string )
    xena.expect('>')

    owner_string='C_OWNER \"%s\"' % (owner)
    xena.sendline( owner_string )
    xena.expect('>')

    xena.sendline( 'C_TIMEOUT 99999' )
    xena.expect('>')

    module_port_string = '%d/%d' %(module,port)
    xena.sendline( module_port_string )

    xena.sendline( 'P_RESERVATION RELINQUISH' )
    xena.expect('>')

    xena.sendline( 'P_RESERVATION RESERVE' )
    xena.expect('>')

    return xena


xena = connect_xena()
xena.interact() 


