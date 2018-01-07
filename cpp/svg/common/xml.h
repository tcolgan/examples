// xml.h

#ifndef XML_H
#define XML_H

void xmlIndentPlus( void ) ;
void xmlIndentMinus( void ) ;
void xmlIndent( void ) ;
void xmlWrite( const char* text ) ;
void xmlStartTag( const char* tag ) ;
void xmlEndTag( const char* tag ) ;
void xmlStartMultitag( const char* tag ) ;
void xmlEndMultitag() ;
void xmlPartialendMultitag() ;
void xmlStartQuote( const char* label ) ;
void xmlEndQuote() ;
void xmlWriteColon( const char* strLabel , const char* strValue ) ;
void xmlWriteColon( const char* strLabel , int intValue , const char* units ) ;
void xmlWriteColon( const char* strLabel , float floatValue ) ;
void xmlWriteColon( const char* strLabel , int intValue ) ;
void xmlWritePar( const char* text , float val ) ;
void xmlWritePar( const char* text , float val , const char* units ) ;
void xmlWritePar( const char* text , const char* str ) ;

#endif // XML_H

