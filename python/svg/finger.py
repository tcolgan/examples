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
      "Xm"  : [ [ 8,7,7,9] ]  ,
      "Xm7" : [ [ 3,3,2,2] ]  ,
  }
  
  MIN_FRET = 2

  
  def __init__( self , key ) :
    self._key = key
      
    self._svgKey = svgKey( key )
      
      
  def getOffset( self ):
    return self._svgKey.getOffset()
      
  def getFingering( self , chord , version = 0 ):
    
    num_notes = svgKey.NUMBER_NOTES
    max_fret = num_notes + self.MIN_FRET
    
    offset = self.getOffset()
    
    fingering = (self.fingerings[ chord ])[ version ]
    
    fingering = [ x + offset for x in fingering ]
    
    if min(fingering) >= max_fret :
      fingering = [ x - num_notes for x in fingering ]
    
    return fingering
