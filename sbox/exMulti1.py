"""example that shows how to define this process as a class that inherits from
	Process"""

import multiprocessing
import time

class ClockProcess(multiprocessing.Process):
	def __init__(self,interval):
		multiprocessing.Process.__init__(self)
		self.interval = interval
	def run(self):
		while True:
			print("The time is %s" % time.ctime())
			time.sleep(self.interval)

if __name__ == '__main__':
	p = ClockProcess(3)
	p.start()