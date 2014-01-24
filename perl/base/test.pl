#!/usr/local/bin/perl


sub exampleSubroutine
{
  my $maxidx = shift @_ ;

  for (my $idx = 0; $idx < $maxidx ; ++$idx )	
  {
  	print "$idx\n";
  }
}


foreach $idx ( 0 .. $#ARGV )
{
  print "argv[$idx] = $ARGV[ $idx ]\n" ;
}

exampleSubroutine( 5 ) ;


