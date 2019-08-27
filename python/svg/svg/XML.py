INDENT_SIZE = 2 

_blank = ""
_indent = 0 

def IndentPlus():
  global _blank
  global _indent
  _indent = _indent + INDENT_SIZE
  _blank = _blank + INDENT_SIZE * " " 
  
def IndentMinus():
  global _blank
  global _indent
  if _indent > 0:
    _indent = _indent - INDENT_SIZE
    _blank = _blank[:-INDENT_SIZE] 
  
def Write( text ):
  print( _blank + text )
  
def StartMultitag( tag ):
  print( _blank + "<" + tag )
  IndentPlus()
  
def EndMultitag():
  print( _blank + "/>" ) 
  IndentMinus() ;

def StartTag( tag ):
  print( _blank + "<" + tag + ">" )
  IndentPlus() 
  
def EndTag( tag ):
  IndentMinus()
  print( _blank + "</" + tag + ">" )
  
def PartialendMultitag():
  print( _blank + ">" )

def WriteColon( label , value , units="" ):
  print( _blank + label + ":" + str( value ) + units + ";" )
  
def WritePar( text , val , units="" ):
  print( _blank + text + "=\"" + str(val) + units + "\"" )
  
def StartQuote( label ):
  print( _blank + label + "=\"" )
  IndentPlus()
  
def EndQuote():
  print( _blank + "\"" )
  IndentMinus()