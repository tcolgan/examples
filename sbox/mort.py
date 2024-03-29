data = [
	( 1,4,3529,22.7,3816,25.0 ) ,
	( 5,14,5623,13.7,5975,14.3 ) ,
	( 15,24,35816,84.2,38307,88.9 ) ,
	( 25,34,73486,159.5,82274,180.8 ) ,
	( 35,44,104490,248.0,124939,287.9 ) ,
	( 45,54,191142,473.5,216037,531.0 ) ,
	( 55,64,440549,1038.9,478171,1117.1 ) ,
	( 65,74,674507,2072.3,724266,2151.3 ) ,
	( 75,84,822084,4997.0,829653,5119.4 ) ,
	( 85,100,1012805,15210.9,940780,15743.3 ) ,
]

remaining = 100.0
for (min_age,max_age,number_2020,rate_2020,number_2021,rate_2021) in data:
	for age in range( min_age , max_age + 1 ) :
		rate = rate_2021
		remaining = remaining - remaining * rate / 100000
		print( f"age = {age:>4}  |  rate (%) = {rate/1000:>6.3f}  |  remaining = {remaining:>5.2f}" )
	
	