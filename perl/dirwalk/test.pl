#!/usr/local/bin/perl

use Cwd; # module for finding the current working directory

sub ScanDirectory
{
  my ($workdir) = shift;
  my ($indent) = shift ; 

  my ($startdir) = &cwd; # keep track of where we began

  chdir($workdir) or die "Unable to enter dir $workdir: $!\n";
  opendir(DIR, ".") or die "Unable to open $workdir: $!\n";
  my @names = readdir(DIR) or die "Unable to read $workdir: $!\n";
  closedir(DIR);

  foreach my $name (@names)
  {
    next if ($name eq "."); 
    next if ($name eq "..");

    print "$indent$name\n" ;

    my $subdir = $workdir."\\".$name ;
    if (-d $subdir)
    {          
      $indent = "$indent.." ;
      &ScanDirectory( $subdir , $indent ) ;
      chop( $indent ) ;
      chop( $indent ) ;
      next;
    }

    chdir($startdir) or 
       die "Unable to change to dir $startdir: $!\n";
  }
}
                       
$indent = "" ;                       
# ScanDirectory( "c:\\xyz" , $indent ) ;  
ScanDirectory( "c:\\work" , $indent ) ;  
