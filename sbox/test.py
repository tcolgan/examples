def firstn(n):
   num = 0
   while num < n:
       yield num
       num += 1

for idx in firstn(4):
    print(idx)