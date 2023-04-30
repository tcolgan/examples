import optparse

def testFunc(option, opt, value, parser):
	print( "test selected")

parser = optparse.OptionParser()

parser.add_option( '--test' , '-t' ,  action="callback", callback=testFunc ,
                   help = "test of callback function"  )

(options, args) = parser.parse_args()

#print( (options, args) )