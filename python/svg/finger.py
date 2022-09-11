from svgKey import svgKey

'''
  [
    ( "D"  , "D7"     , [ 5,5,4,5] ),
    ( "G"  , "Gmaj7"  , [ 3,5,4,4] ),
    ( "C"  , "Cmaj7"  , [ 3,3,2,4] ),
    ( "F#" , "F#m7b5" , [ 2,3,2,2] ),
    ( "B"  , "Bm7"    , [ 5,5,4,4] ),
    ( "E"  , "Em7"    , [ 0,5,5,4] ),
    ( "A"  , "Am7"    , [ 3,3,2,2] ),
  ],
  [
    ( "G"  , "G7"     , [ 3,5,3,4] ),
    ( "C"  , "Cmaj7"  , [ 3,3,2,4] ),
    ( "F"  , "Fmaj7"  , [ 1,3,2,2] ),
    ( "B"  , "Bm7b5"  , [ 5,5,3,4] ),
    ( "E"  , "Em7"    , [ 0,5,5,4] ),
    ( "A"  , "Am7"    , [ 3,3,2,2] ),
    ( "D"  , "Dm7"    , [ 5,5,3,5] ),
  ],
'''

class finger():

  fingerings = {
      "Xm7" : [ [ 3,3,2,2] ]  ,
  }

  
  def __init__( self , key ) :
    self._key = key
      
    self._svgKey = svgKey( key )
      
      
  def getOffset( self ):
    return self._svgKey.getOffset()
      
  def getFingering( self , chord , version = 0 ):
    return (self.fingerings[ chord ])[ version ]
