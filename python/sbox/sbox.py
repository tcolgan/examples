#!/usr/bin/python

# example - reading a json file

import json


filename = "test.json"

if filename:
  with open( filename , 'r' ) as f :
    datastore = json.load( f )

print datastore['office']['medical'][1]['price']
