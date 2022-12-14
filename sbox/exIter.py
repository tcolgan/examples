def exIter(n):
   num = 0
   while num < n:
       yield num
       num += 1

# basic example
print( "First example:")
for idx in exIter(4):
    print(idx)


# alternate use
print( "Second example:")
it = exIter(5)

while( True ):
    try:
        val = it.__next__()
        print( val )
    except:
        break

