#include <stdio.h>

char BigEndian()
{
  short val = 0x0100 ;
  return *( (char*)&val ) ;
}


int main(int argc, char* argv[])
{
  printf( BigEndian() ? "Big endian\n" : "Little endian\n" ) ;

  return 0 ;
}

