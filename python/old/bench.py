#!/usr/bin/python
import pexpect
import sys

child = pexpect.spawn ( 'ssh onpath@10.88.39.154' )
fout = file('benchlog.txt','a')
child.logfile_read = fout

child.expect("assword: ")

child.sendline("onpath")
child.expect('\$ ')

child.sendline("telnet localhost 35000")

child.interact() 

