
valFloat = 12000.35
valInt = 35
valString = "this is a test"

print()	

print( f'{"string left justified:":30}|{valString:<50}|' )
print( f'{"string right justified:":30}|{valString:>50}|' )
print( f'{"string centered:":30}|{valString:^50}|' )

print()	

print( f'{"float (two decimal)":30}{valFloat:12.2f}' )
print( f'{"float (four decimal)":30}{valFloat:12.4f}' )
print( f'{"float (with comma)":30}{valFloat:12,.4f}' )
print( f'{"float (added sign)":30}{valFloat:+12,.4f}' )
print( f'{"float (w/ exponent)":30}{valFloat:12.2e}' )


print()	
val = .5
print(f"Using {val = }")
print( f'{"Percent : 	":30}{val:.2%}' )


print()	

val = 10
print( "Examples of uning equals sign within brackets (for debug,etc):")
print( f'{val=}')
print( f'{val = }')
print( f'{val+2=}')
print( f'{2*val+3=}')

print()	

print(f"Using Numeric {val = }")
print(f"This prints without formatting {val}")
print(f"This prints with formatting {val:d}")
print(f"This prints also with formatting {val:n}")
print(f"This prints with spacing {val:10d}\n")

print()	

print("Columns example:")
for idx in range(4):
	print( f'{idx:>3}  |   {idx**2:>3}  |   {idx**3:>3}' )