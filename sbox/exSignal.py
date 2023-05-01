import signal
import time

def handler(signum, frame):
	if signum == signal.SIGALRM:
		print( "SIGALRM")

	if signum == signal.SIGINT:
		print( "SIGINT" )
		exit()


signal.signal(signal.SIGINT, handler)

signal.signal(signal.SIGALRM, handler)

signal.setitimer( signal.ITIMER_REAL , 2 , 2 )

while True:
  time.sleep(1)