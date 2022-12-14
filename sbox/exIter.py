def exIter(n):
   num = 0
   while num < n:
       yield num
       num += 1

for idx in exIter(4):
    print(idx)