#!/usr/bin/python

class tracer:
    def __init__(self, func):
        self.calls = 0
        self.func = func
    def __call__(self, *args):
        self.calls += 1
        print 'call %s to %s' % (self.calls, self.func.__name__)
        self.func(*args)

@tracer
def spam(a, b, c): # Wrap spam in a decorator object
    print a, b, c

@tracer
def spam2(a, b, c): # Wrap spam in a decorator object
    print a, b, c


spam(1, 2, 3) # Really calls the tracer wrapper object
spam('a', 'b', 'c') # Invokes _ _call_ _ in class
spam(4, 5, 6) # _ _call_ _ adds logic and runs original object

spam2(1, 2, 3) # Really calls the tracer wrapper object
spam2('a', 'b', 'c') # Invokes _ _call_ _ in class
spam2(4, 5, 6) # _ _call_ _ adds logic and runs original object

