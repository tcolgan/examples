import optparse

def testFunc(option, opt, value, parser):
	print( "test selected")

version = "1.0"
parser = optparse.OptionParser( version="%prog "+version )

parser.add_option( '--test' ,  action="callback", callback=testFunc ,
                   help = "test of callback function"  )

parser.add_option("-f", "--file", dest="filename",
                  help="write report to filename")


# A simple option, with no arguments
parser.add_option("-t", action="store_true", dest="tracing")

# An option that accepts a string argument
parser.add_option("-o", "--outfile", action="store", type="string", dest="outfile")

# An option requires an integer argument
parser.add_option("-d", "--debuglevel", action="store", type="int", dest="debug")

# An option with a few choices
parser.add_option("--speed", action="store", type="choice", dest="speed",
             choices=["slow","fast","ludicrous"])

# An option taking multiple arguments
parser.add_option("--coord", action="store", type="int", dest="coord", nargs=2)

# A set of options that control a common destination
parser.add_option("--novice", action="store_const", const="novice", dest="mode")
parser.add_option("--guru", action="store_const", const="guru", dest="mode")

# Set default values for the various option destinations
parser.set_defaults(tracing=False,
debug=0,
speed="fast",
coord=(0,0),
mode="novice")

(opt, args) = parser.parse_args()

print( (opt, args) )

# Print option values
print( "tracing :", opt.tracing  )
print( "outfile :", opt.outfile )
print( "debug :", opt.debug )
print( "speed :", opt.speed )
print( "coord :", opt.coord )
print( "mode :", opt.mode )

# Print remaining arguments
print( "args :", args )

