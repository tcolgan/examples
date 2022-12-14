#!/usr/bin/python

import pexpect

child = pexpect.spawn ('ssh onpath@10.88.39.154')
child.expect ('password: ')
child.sendline ('onpath')
child.sendline ('telnet localhost 35000')
child.expect ('=> ')

for idx in range(8) :
    line = 'b ace2 mac10 ' + str(idx) + '\r'
    child.sendline( line )
    child.expect ('=> ')
    input = child.before

    for row in input.split('\n') :
        if 'rx_stats_framesok' in row:
            output = "%4.4d %s" % ( idx , row )
            print output


child.sendline ('exit')

