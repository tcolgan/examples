'''
list comprehension examples
'''

lstList = [
            "[ idx for idx in range(5)]" ,
            "[ idx ** 2 for idx in range(5)]" ,
            "[ idx ** 2 for idx in range(5) if (idx % 2) == 0]" ,
            "[ x * y for x,y in [ (1,2) , (3,4) , (5,6)] ]" ,
            "[ (x,y) for x in [1,2,3] for y in [4,5,6]]"
          ]


print( __doc__ )

for lst in lstList:
    print( "%50s = %s"  %  ( lst , eval(lst) ) )
