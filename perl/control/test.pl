#!/usr/local/bin/perl


sub printFunctionname
{
  my $this_function = (caller(1))[3];

  print "$this_function\n" ;
}

sub forExample
{
  printFunctionname() ;

  for( $idx = 0 ; $idx < 5 ; ++$idx )	
  {
  	print "$idx\n";
  }
}

sub ifExample
{
  printFunctionname() ;

  my $var = shift @_ ;

  if( $var == 0 )
  {
    print "zero\n" ;
  }
  elsif( $var == 1 )
  {
    print "one\n" ;
  }
  else
  {
    print "not zero or one\n" ;
  }

}

sub whileExample0
{
  printFunctionname() ;
  my $var ;

  $var = 0 ;
  while( $var < 4 )
  {
    print "$var\n" ;
    $var++ ;
  }

  print "end value : $var\n" ;
}

sub whileExample
{
  printFunctionname() ;

  my $var ;

  $var = 0 ;
  while( $var < 10 )
  {
    $var++ ;
    if( $var == 3 )
    {
      print "skipped $var\n" ;
      next ;
    }
    print "$var\n" ;
    if( $var == 5 )
    {
      print "reached break\n" ;
      last ;
    }
  }

  print "end value : $var\n" ;
}

sub dowhileExample
{
  printFunctionname() ;

  my $var ;

  $var = 0 ;
  do
  {
    print "$var\n" ;
    $var++ ;
  }
  while( $var < 4 ) ;

  print "end value : $var\n" ;
}

sub untilExample
{
  printFunctionname() ;

  my $var = 0 ;

  until( $var == 4 )
  {
    print "$var\n" ;
    $var++ ;
  }

  print "end value : $var\n" ;
}

sub foreachExample
{
  printFunctionname() ;

  my @words = ( "alpha" , "beta" , "gamma" ) ;

  foreach $word ( @words )
  {
    print "$word\n" ;
  }

  print "end value : $word\n" ;
}


#forExample() ;
#ifExample( 1 ) ;
#whileExample0() ;
#whileExample() ;
#dowhileExample() ;
#untilExample() ;
foreachExample() ;



