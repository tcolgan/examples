// xml.cpp

#include <cstdio>
#include <iostream>
#include <iomanip> 
using namespace std;

#define INDENT_SIZE 2 

int _indent ;
string _blank ;

void xmlIndentPlus( void )
{
  _indent += INDENT_SIZE ;
  _blank = string( _indent , ' ' ) ;
}


void xmlIndentMinus( void )
{
  _indent -= INDENT_SIZE ;

  if( _indent < 0 )
  {
    _indent = 0 ;
  }
  _blank = string( _indent , ' ' ) ;
}


void xmlWrite( const char* text )
{
  cout << _blank << text << endl ;
}


void xmlStartTag( const char* tag )
{
  cout << _blank << "<" << tag << ">" << endl ;
  xmlIndentPlus() ;
}


void xmlEndTag( const char* tag )
{
  xmlIndentMinus() ;
  cout << _blank << "</" << tag << ">" << endl ;
}


void xmlStartMultitag( const char* tag )
{
  cout << _blank << "<" << tag << endl ;
  xmlIndentPlus() ;
}


void xmlEndMultitag()
{
  cout << _blank << "/>" << endl ;
  xmlIndentMinus() ;
}


void xmlPartialendMultitag()
{
  cout << _blank << ">" << endl ;
}


void xmlStartQuote( const char* label )
{
  cout << _blank << label << "=\"" << endl ;
  xmlIndentPlus() ;
}


void xmlEndQuote()
{
  cout << _blank << "\"" << endl ;
  xmlIndentMinus() ;
}


void xmlWriteColon( const char* strLabel , const char* strValue )
{
  cout << _blank << strLabel << ":" << strValue << ";" << endl ;
}


void xmlWriteColon( const char* strLabel , int intValue , const char* units )
{
  cout << _blank << strLabel << ":" << intValue << units << ";" << endl ;
}


void xmlWriteColon( const char* strLabel , float floatValue )
{
  cout << _blank << strLabel << ":" << fixed << setprecision(2) << floatValue << ";" << endl ;
}


void xmlWriteColon( const char* strLabel , int intValue )
{
  cout << _blank << strLabel << ":" << intValue << ";" << endl ;
}


void xmlWritePar( const char* text , float val )
{
  cout << _blank << text << "=\"" << (int)val << "\"" << endl ;
}


void xmlWritePar( const char* text , float val , const char* units )
{
  cout << _blank << text << "=\"" << fixed << setprecision(1) << val << units << "\"" << endl ;
}


void xmlWritePar( const char* text , const char* str )
{
  cout << _blank << text << "=\"" << str << "\"" << endl ;
}





