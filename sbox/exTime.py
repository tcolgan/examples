import time
import timeit

def tstFunc():
  sum = 0
  for idx in range(5):
    sum += idx
  return sum


start_cpu = time.thread_time()
start_real= time.time()

tstFunc()

end_cpu = time.thread_time()
end_real = time.time()

print("%f Real Seconds" % (end_real - start_real))
print("%f Thread seconds" % (end_cpu - start_cpu))

timeitTime = timeit.timeit( "tstFunc()" , number = 100  , setup = "from __main__ import tstFunc" )
print( "%f timeit seconds" % ( timeitTime ))