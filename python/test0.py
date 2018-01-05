#!/usr/bin/python

import pexpect
child = pexpect.spawn ('ftp ftp.openbsd.org')
child.expect ('Name .*: ')
child.sendline ('anonymous')
child.expect ('Password:')
child.sendline ('noah@example.com')
child.expect ('ftp> ')
child.sendline ('cd pub')
child.expect('ftp> ')
child.sendline ('get ls-lR.gz')
child.expect('ftp> ')
child.sendline ('bye')
