#!/usr/local/bin/perl

# File Read Examples =============================================

sub fileReadExample0()
{
  $filename = "datain.txt" ;

  open( FILE , "< $filename" ) 
    or die "Unable to open $filename for reading.\n" ; 

  @dataarray = <FILE> ;  #read entire file into array

  close FILE ;

  foreach $dataitem ( @dataarray )
  {
    print "$dataitem" ;
  }
}

sub fileReadExample1()
{
  $filename = "datain.txt" ;

  open( FILE , "< $filename" ) 
    or die "Unable to open $filename for reading.\n" ; 

  while( <FILE> ) 
  {
    print $_ ;
  }

  close FILE ;
}

sub fileReadExample2()
{
  my @dataarray ;

  @dataarray = ReadTextFile( "datain.txt" ) ;

  foreach $dataitem ( @dataarray )
  {
    print "$dataitem" ;
  }
}

# Read text file into array
# Parameters:
#   string - filename
# Returns
#   array  - string array of elements read
sub ReadTextFile
{
  my $filename = @_[0] ;
  my @dataarray ;

  open( FILE , "< $filename" ) 
    or die "Unable to open $filename for reading.\n" ; 

  @dataarray = <FILE> ;  #read entire file into array

  close FILE ;

  return @dataarray ;
}

# File Write Examples =============================================

sub fileWriteExample0()
{
  $filename = "dataout.txt" ;

  open( FILE , "> $filename" )  # this will over-write file
#  open( FILE , ">> $filename" )  # this will append to file
    or die "Unable to open $filename for writing.\n" ; 

  print FILE "first\n" ;
  print FILE "second\n" ;
  print FILE "third\n" ;

  close FILE ;
}


sub fileWriteExample1()
{
  my @dataarray = ( "alpha" , "beta" , "gamma" ) ;

  WriteTextFile( "dataout.txt" , @dataarray ) ;
}


# Write text array into file
# Parameters:
#   string - filename
#   array  - array of strings to write to file
sub WriteTextFile
{
  my $filename = shift @_ ;
  my @dataarray = @_ ;

  open( FILE , "> $filename" ) 
    or die "Unable to open $filename for writing.\n" ; 

  print FILE join( "\n" , @dataarray ) ;  #write entire array to file

  close FILE ;
}
 


fileReadExample0() ;
fileReadExample1() ;
fileReadExample2() ;
fileWriteExample0() ;
fileWriteExample1() ;


