#!/usr/bin/python

import os

print "listdir"
print os.listdir('.')

print "\ngetcwd"
print os.getcwd()

rootDir = '.'
for dirName, subdirList, fileList in os.walk(rootDir):
    print('Found directory: %s' % dirName)
    for fname in fileList:
        print('\t%s' % fname)

