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
  
  CHORD_7      = [0,4,7,10]
  CHORD_MAJ7   = [0,4,7,11]
  CHORD_MIN7B5 = [0,3,6,10]
  CHORD_MIN7   = [0,3,7,10]
  CHORD_MAJ    = [0,4,7]
  CHORD_MIN    = [0,3,7]


  fingerings = {
      "Xm"    : ( CHORD_MIN    , [ [ 5,3,2,2] , [ 8,7,7,9] ] )  ,
      "Xm7"   : ( CHORD_MIN7   , [ [ 3,3,2,2] , [ 12,12,10,12]] )  ,
      "Xmaj7" : ( CHORD_MAJ7   , [ [ 4,4,2,2] , [ 5,7,6,6] ,[ 12,12,11,13]] )  ,
      "X7"    : ( CHORD_7      , [ [ 5,7,5,6] , [ 12,12,11,12] , [ 3,4,2,2]] )  ,
      "Xm7b5" : ( CHORD_MIN7B5 , [ [ 5,6,5,5] , [ 11,12,10,12]] )  ,
      "X"     : ( CHORD_MAJ    , [ [ 5,4,2,2] , [ 5,4,7,9] , [ 12,12,11,9]] )  ,
#      "X"    : ( CHORD_  , [ [ ] ]  ,
  }
  
  MIN_FRET = 1

  
  def __init__( self , key ) :
    self._key = key
      
    self._svgKey = svgKey( key )
      
      
  def getOffset( self ):
    return self._svgKey.getOffset()
      
  def getFingering( self , chord , version = 0 ):
    
    num_notes = svgKey.NUMBER_NOTES
    max_fret = num_notes + self.MIN_FRET
    
    offset = self.getOffset()
    
    chord_intervals,fingerings = self.fingerings[ chord ]
    fingering = fingerings[ version ]
    
    fingering = [ x + offset for x in fingering ]
    
    if min(fingering) >= max_fret :
      fingering = [ x - num_notes for x in fingering ]
    
    return chord_intervals,fingering
