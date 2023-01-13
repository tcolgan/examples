""" 
example python documentaion

this module illustrates the use of python documentation
"""

class exClass(object):
    """
    example class documentation
    """

    def exClassMethod(self):
        """
        example class method documentation
        """
        pass

def exFunc():
    """
    example function documentation
 
    purpose:     TBD 
    parameters:  TBD 
    returns:     TBD   
    """

    print( "esample function")


print( "module documentation:")
print( __doc__)

print( "----------------------" )

print( "function documentation:")
print( exFunc.__doc__)

print( "----------------------" )

print( "class documentation:")
print( exClass.__doc__)

print( "----------------------" )

print( "class method documentation:")
print( exClass.exClassMethod.__doc__)
