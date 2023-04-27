#def printDict( dict ):
#	for key in dict:
#		print( f'{dict.__name__}[{key}={dict[key]}' )

def printIter( iter ):
	for item in iter:
		print( f'{iter} = {getattr( iter , item )}' )

if __name__ == '__main__':
    printIter( [0,1,2] )