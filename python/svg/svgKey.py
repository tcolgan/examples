
class svgKey():
  
  key_offsets = {
    "A"  : 0 ,
    "A#" : 1  ,
    "Bb" : 1  ,
    "B"  : 2  ,
    "C"  : 3  ,
    "C#" : 4  ,
    "Db" : 4  ,
    "D"  : 5  ,
    "D#" : 6  ,
    "Eb" : 6  ,
    "E"  : 7  ,
    "F"  : 8  ,
    "F#" : 9  ,
    "Gb" : 9  ,
    "G"  : 10 ,
    "G#" : 11 ,
    "Ab" : 11 ,
  }
  
  NUMBER_NOTES = 12
  NUMBER_STRINGS = 4
  NUMBER_FRETS = 20


  
  def __init__( self , key="A" , number_frets = NUMBER_FRETS ) :
    self._key = key
    self.number_frets = number_frets
  
    pitch_string_base = [7,0,5,10]
    pitch_offset = self.NUMBER_NOTES - self.key_offsets[ self._key ]
    self.pitch_string = []
    for pitch in pitch_string_base :
      self.pitch_string.append( self.incr( pitch , pitch_offset ) )


  def incr( self , start , increment = 1 ) :
    value = start + increment
    if value >= self.NUMBER_NOTES :
      value = value - self.NUMBER_NOTES
    if value < 0 :
      value += self.NUMBER_NOTES
    return value

  def makeMatrix( self , pitches ) :
    matrix = []

    for string in range( self.NUMBER_STRINGS ) :
      array = []
      pitch = self.pitch_string[ string ]
      for fret in range( self.number_frets ) :
        if pitch in pitches:
          val = pitch
        else:
          val = -1
        array.append( val )
        pitch = self.incr( pitch )
      matrix.append( array )
    return matrix
    

  def makeChordMatrix( self , frets ) :
    matrix = []

    for string in range( self.NUMBER_STRINGS ) :
      array = []
      pitch = self.pitch_string[ string ]
      fret_idx = frets[ string ]
      for fret in range( self.number_frets ) :
        if fret_idx == fret :
          val = pitch
        else:
          val = -1
        array.append( val )
        pitch = self.incr( pitch )
      matrix.append( array )
    return matrix
    
  def getNote( self , interval ) :
    offset_base = self.incr( self.key_offsets[ self._key ] , interval )
    return( self.getNoteFromOffset( offset_base ) )
    
  def getNoteFromOffset( self , offset ) :
    for key in self.key_offsets:
      if self.key_offsets[key] == offset :
        return( key )
    return( "G" )