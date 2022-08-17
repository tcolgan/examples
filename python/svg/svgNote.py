
class svgNote():
  
  key_offsets = {
    "G"  : 0  ,
    "G#" : 11 ,
    "Ab" : 11 ,
    "A"  : 10 ,
    "A#" : 9  ,
    "Bb" : 9  ,
    "B"  : 8  ,
    "C"  : 7  ,
    "C#" : 6  ,
    "Db" : 6  ,
    "D"  : 5  ,
    "D#" : 4  ,
    "Eb" : 4  ,
    "E"  : 3  ,
    "F"  : 2  ,
    "F#" : 1  ,
    "Gb" : 1  ,
  }
  
  NUMBER_NOTES = 12
  NUMBER_STRINGS = 4
  NUMBER_FRETS = 20


  
  def __init__(self,key="G"):
    self._key = key

  def incr( self , start , increment = 1 ) :
    value = start + increment
    if value >= self.NUMBER_NOTES :
      value = value - self.NUMBER_NOTES
    return value

  def makeMatrix( self , pitches ) :
    matrix = []

    pitch_string_base = [9,2,7,0]
    pitch_offset = self.key_offsets[ self._key ]
    pitch_string = []
    for pitch in pitch_string_base :
      pitch_string.append( self.incr( pitch , pitch_offset ) )
  
    for string in range( self.NUMBER_STRINGS ) :
      array = []
      pitch = pitch_string[ string ]
      for fret in range( self.NUMBER_FRETS ) :
        if pitch in pitches:
          val = pitch
        else:
          val = -1
        array.append( val )
        pitch = self.incr( pitch )
      matrix.append( array )
    return matrix
