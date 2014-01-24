`// clc.cpp  xxx
//
// source.h must contain at least:
//
// char srcbuff[] = "" ;


#include <string>
#include <istream>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <complex>

#include "source.h"

#define TRUE  1
#define FALSE 0

#define NAN ((double)(0x7ff8000000000000))

using namespace std;

#define MAX_LINE_LENGTH 200

#define MAX_TOKENS        20
#define MAX_TOKEN_LENGTH  100

char _tokens[ MAX_TOKENS ][ MAX_TOKEN_LENGTH ] ;

typedef double (*pftn)( double input ) ;

enum 
{
   MODE_INT8
,  MODE_UINT8
,  MODE_INT16
,  MODE_UINT16
,  MODE_INT32
,  MODE_UINT32
,  MODE_FLOAT
,  MODE_DOUBLE
,  MODE_CHAR
,  NUM_MODES
} ;


enum
{
  BASE_DEC
, BASE_HEX
, BASE_OCT
, BASE_BIN
, NUM_BASES
} ;

int _mode = MODE_DOUBLE ;
int _base = BASE_DEC ;
int _precision = 6 ; // default always 6?
bool _engineering = FALSE ;
//bool _ieee = TRUE ;
bool _ieee = FALSE ;

char _helpTop[] =
"\n"
"CLC - Command-line Calculator\n"
"  2006 (c) Tim Colgan.\n"
"\n"
"for help type \"help <category>\"\n"
"where <category> is \"general\", \"commands\", or \"functions\".\n"
"\n" ;

char _helpGeneral[] =
"\n"
"CLC - Command-line Calculator\n"
"\n"
"\n"
"The command-line calculator is a simple mathematical tool for solving\n"
"mathematical equations such as:\n"
"  x=3*sin(2*pi)+e^5\n"
"\n"
"Input may be typed in directly after invoking clc, or may be piped in\n"
"from a file (and output to a file) as in:\n"
"  clc<input.txt>output.txt\n"
"\n"
"Multiline equations can be formed as in\n"
"  a=sin(2)\n"
"  b=cos(3)\n"
"  c=a+b\n"
"\n"
"Many common mathematical functions are supported (type \"help functions\"\n"
"for a list) and a useful set of commands are provided (type \"help commands\"\n"
"for another list).\n"
"\n" 
"Several bases are supported: decimal, hexadecimal, octal, binary.  Both for\n"
"input and output.  For input, type the proper characters (0x for hex,\n"
"O for octal, embedded underline for binary).  Examples:\n" 
" 0x1ff\n" 
" O777\n" 
" 0001_1010\n" 
"\n" 
"For output, issue the command (dec, hex, oct, bin) to set the output base.\n" 
"\n" 
"Several modes are supported (int8, int16, int32, uint8, uint16, uint32,\n"
"float, double).  Choosing a mode causes the output to be converted to the\n" 
"chosen internal representation before being output.  (Note - internally\n" 
"all intermediate calculations are done as doubles).\n" 
"\n" 
"A command exists, \"source\", for generating the source code to create\n" 
"this program.\n" 
"\n" 
"Another command, \"mksrc\", takes a source file and generates an include\n" 
"file for the next compile if changes are made.\n" 
"\n" 
"The \"vars\" command displays all variables and their values.\n" 
"\n" 
"The echo [on|off] command effects echoing of commands (useful for file input).\n" 
"\n" 
"Experiment!  Enjoy!\n" 
"\n" 
;


struct
{
   char name[ MAX_TOKEN_LENGTH ] ;
   pftn function ;
   char* help ;
} _functions[] =
{
   { "acos"   , acos , "Calculates the arccosine (argument in radians)."                       }
,  { "asin"   , asin , "Calculates the arcsine (argument in radians)"                          }
,  { "atan"   , atan , "Calculates the arctangent (argument in radians)"                       }
,  { "ceil"   , ceil , "Calculates the ceiling (smallest integer greater than argument)."      }
,  { "cos"    , cos  , "Calculates the cosine (argument in radians)"                           }
,  { "cosh"   , cosh , "Calculates the hyperbolic cosine (argument in radians)"                }
,  { "exp"    , exp  , "Calculates the exponential."                                           }
,  { "fabs"   , fabs , "Calculates the absolute value of the argument."                        }
,  { "floor"  , floor, "Calculates the floor of a value (largest integer less than argument)." }
,  { "log"    , log  , "Calculates the natural logarithm."                                      }
,  { "log10"  , log10, "Calculates the logarithm, base 10."                                     }
,  { "sin"    , sin  , "Calculates the sine (argument in radians)"                             }
,  { "sinh"   , sinh , "Calculates the hyperbolic sine (argument in radians)"                  }
,  { "sqrt"   , sqrt , "Calculates the square root."                                           }
,  { "tan"    , tan  , "Calculates the tangent (argument in radians)"                          }
,  { "tanh"   , tanh , "Calculates the hyperbolic tangent (argument in radians)"               }
} ;

struct
{
   char* name ;
   char* help ;
} _commands[] =
{
  { "bin"         , "sets base to binary mode."                                        }
, { "char"        , "sets output to character mode."                                   }
, { "dec"         , "sets base to decimal."                                            }
, { "double"      , "sets output to double mode."                                      }
, { "echo"        , "echos input (echo [on|off])."                                     } 
, { "engineering" , "sets output to double mode."                                      } 
, { "fixed"       , "sets output stream to fixed"                                      } 
, { "float"       , "sets output to double mode."                                      } 
, { "hex"         , "sets base to hexadecimal."                                        } 
, { "ieee"        , "sets output to ieee (binary format with sign/exponent/fraction)." } 
, { "int16"       , "sets output to int16 mode."                                       } 
, { "int32"       , "sets output to int32 mode."                                       } 
, { "int8"        , "sets output to int8 mode."                                        } 
, { "mksrc"       , "make source for include file (usually type command line: \"clc mksrc>source.h\"" } 
, { "oct"         , "sets base to octal."                                              } 
, { "precision"   , "set the precision of the output (number of significant digits)."  }
, { "source"      , "output source code (usually type command line: \"clc source>clc.cpp\""           } 
, { "uint16"      , "sets output to uint16 mode."                                      } 
, { "uint32"      , "sets output to uint32 mode."                                      } 
, { "uint8"       , "sets output to uint8 mode."                                       } 
, { "vars"        , "display defined variables with values."                           } 
} ;

ostream& output = cout ;
istream& input  = cin  ;

bool echoOn = FALSE ;

#define STR_LEN 100

enum
{
   PRECEDENCE_NONE
   , PRECEDENCE_LOWEST
   , PRECEDENCE_1 = PRECEDENCE_LOWEST
   , PRECEDENCE_2
   , PRECEDENCE_3
   , PRECEDENCE_NUM
} ;

void Output( double val ) ;


void DisplayHelp( char* str )
{
   if( !*str )
   {
      output << _helpTop ;
      return ;
   }

   if( !strcmp( str , "general" ) )
   {
      output << _helpGeneral ;
      return ;
   }

   if( !strcmp( str , "functions" ) )
   {
      output << "type \"help <function>\" for help on following functions:" << endl ;
      for( int idx = 0 ; idx < sizeof( _functions ) / sizeof( *_functions ) ; idx++ )
      {
         output << "  " << _functions[ idx ].name << endl ;
      }
      output << endl ;
      return ;
   }

   if( !strcmp( str , "commands" ) )
   {
      output << "type \"help <command>\" for help on following commands:" << endl ;
      for( int idx = 0 ; idx < sizeof( _commands ) / sizeof( *_commands ) ; idx++ )
      {
         output << "  " << _commands[ idx ].name << endl ;
      }
      output << endl ;
      return ;
   }

   for( int idx = 0 ; idx < sizeof( _functions ) / sizeof( *_functions ) ; idx++ )
   {
      if( !strcmp( _functions[ idx ].name , str ) )
      {
         output << _functions[ idx ].help << endl ;
         return ;
      }
   }

   for( idx = 0 ; idx < sizeof( _commands ) / sizeof( *_commands ) ; idx++ )
   {
      if( !strcmp( _commands[ idx ].name , str ) )
      {
         output << _commands[ idx ].help << endl ;
         return ;
      }
   }


   output << "No help for : " << str << endl ;
   output << _helpTop ;
}




void FindAndReplace( string& str , const string& before , const string& after )
{
   int size0 = before.size() ;
   int size1 = after.size() ;
   int pos = 0 ;
   while( ( pos = str.find( before , pos ) ) != string::npos )
   {
      str.replace( pos , size0 , after ) ;
      pos += size1 ;
   }
}

void MakeSource()
{
   const int BUFF_SIZE = 1000 ;
   char buff[ BUFF_SIZE + 1 ] ;
   fstream file ;
   file.open( "clc.cpp" , fstream::in ) ;


   output << "char srcbuff[] =" << endl ;

   while( !file.eof() )
   {
      file.getline( buff , BUFF_SIZE ) ;

      string str( buff ) ;

      FindAndReplace( str , "\\" , "\\\\" ) ;
      FindAndReplace( str , "\"" , "\\\"" ) ;

      output << "\"" << str << "\\n" << "\"" << endl ;
   }

   output << ";" << endl ;
}


int FindCommand( char* command )
{
   int size = sizeof( _functions ) / sizeof( *_functions ) ;

   for( int idx = 0 ; idx < size ; idx++ )
   {
      if( strcmp( _functions[ idx ].name , command ) == 0 )
      {
         return idx ;
      }
   }

   return -1 ;
}

int FindToken( char* str , int first , int last )
{
   for( int idx = first ; idx <= last ; idx++ )
   {
      if( strcmp( str , _tokens[ idx ] ) == 0 )
      {
         return idx ;
      }
   }

   return -1 ;
}

#define MAX_VARIABLES 100 
struct 
{
   char   name[ MAX_TOKEN_LENGTH ] ;
   double value ;

} _variables[ MAX_VARIABLES ] ;


int GetVariableIdx( char* token ) 
{
   for( int idx = 0 ; idx < MAX_VARIABLES ; idx++ )
   {
      if( strcmp( _variables[ idx ].name , token ) == 0 )
      {
         return idx ;
      }
   }

   return -1 ;
}

int GetNewVariableIdx( char* token ) 
{
   int idx = GetVariableIdx( token ) ;
   if( idx >= 0 )
   {
      return idx ;
   }

   for( idx = 0 ; idx < MAX_VARIABLES ; idx++ )
   {
      if( _variables[ idx ].name[0] == 0 )
      {
         strcpy( _variables[idx].name ,  token ) ;

         return idx ;
      }
   }

   return -1 ;
}

void SetVariable( int varidx , double val )
{
   _variables[ varidx ].value = val ;
}

int CheckAssignment( int& first , int& last )
{
   if( strcmp(  _tokens[ first+1 ] , "=" ) != 0 )
   {
      return -1 ;
   }

   int idx = GetNewVariableIdx( _tokens[ first ] ) ; // tim_todo check for failure (idx<0)

   first += 2 ;

   return idx ;
}

int GetPrecedence( char ch )
{
   int prec = PRECEDENCE_NONE ;

   switch( ch )
   {
   case '+' :
   case '-' :
      prec = PRECEDENCE_1 ;
      break ;

   case '*' :
   case '/' :
      prec = PRECEDENCE_2 ;
      break ;

   case '^' :
      prec = PRECEDENCE_3 ;
      break ;
   }

   return prec ;
}


double eval( double val1 , double val2 , char oper )
{
   double result = 0 ;

   switch( oper )
   {
   case '+':
      result = val1 + val2 ;
      break ;

   case '-':
      result = val1 - val2 ;
      break ;

   case '*':
      result = val1 * val2 ;
      break ;

   case '/':
      result = val1 / val2 ;
      break ;

   case '^':
      result = pow( val1 , val2 ) ;
      break ;


   default:
      output << "invalid operator : " << oper << endl ;
   }

   return result ;
}


bool IsChar( char ch , char* list )
{
   while( *list )
   {
      if( ch == *list )
      {
         return TRUE ;
      }
      list++ ;
   }

   return FALSE ;
}


char* GetNextToken( char* str , char* token )
{
   char* start = str ;

   // skip space
   while( *str == ' ' )
   {
      str++ ;
   }

   if( IsChar( *str , "+-/*()^=" ) )
   {
      *token = *str ;
      token++ ;
      str++ ;
   }
   else
   {
      do
      {
         if( !*str || ( *str == ' ' ) )
         {
            break ;
         }
         *token = *str ;
         token++ ;
         str++ ;
      }
      while( !IsChar( *str , "+-/*()^= " ) ) ;
   }

   *token = 0 ;

   // strip space from end
   char* end = str + strlen( str ) - 1 ;
   while( ( *end == ' ' ) && ( end != str ) )
   {
      *end = 0 ;
      end-- ;
   }

   return str ;
}


int parse( char* str )
{
   int size = 0 ;

   memset( _tokens , 0 , sizeof( _tokens ) ) ;

   while( *str )
   {
      str = GetNextToken( str , _tokens[ size ] ) ;
      size++ ;
   }

   return size ;
}


int ProcessModes()
{
   if( !strcmp( _tokens[0] , "precision" ) )
   {
      _precision = atoi( _tokens[1] ) ;

      output.precision( _precision ) ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "fixed" ) )
   {
      output << setiosflags( ios::fixed );

      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "dec" ) )
   {
      _base = BASE_DEC ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "hex" ) )
   {
      _base = BASE_HEX ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "oct" ) )
   {
      _base = BASE_OCT ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "bin" ) )
   {
      _base = BASE_BIN ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "char" ) )
   {
      _mode = MODE_CHAR ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "int8" ) )
   {
      _mode = MODE_INT8 ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "int16" ) )
   {
      _mode = MODE_INT16 ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "int32" ) )
   {
      _mode = MODE_INT32 ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "uint8" ) )
   {
      _mode = MODE_UINT8 ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "uint16" ) )
   {
      _mode = MODE_UINT16 ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "uint32" ) )
   {
      _mode = MODE_UINT32 ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "float" ) )
   {
      _mode = MODE_FLOAT ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "double" ) )
   {
      _mode = MODE_DOUBLE ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "echo" ) )
   {
      if( !strcmp( _tokens[1] , "off" ) )
      {
         echoOn = FALSE ;
      }
      else
      {
         echoOn = TRUE ;
      }
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "engineering" ) )
   {
      if( !strcmp( _tokens[1] , "off" ) )
      {
         _engineering = FALSE ;
      }
      else
      {
         _engineering = TRUE ;
      }
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "ieee" ) )
   {
      if( !strcmp( _tokens[1] , "off" ) )
      {
         _ieee = FALSE ;
      }
      else
      {
         _ieee = TRUE ;
      }
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "vars" ) )
   {
      int idx = 0 ;
      while( _variables[ idx ].name[0] != 0 )
      {
         output << _variables[ idx ].name << " = " ;
         Output( _variables[ idx ].value  ) ;
         output << endl ;
         idx++ ;
      }
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "source" ) )
   {
      output << srcbuff ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "mksrc" ) )
   {
      MakeSource() ;
      return TRUE ;
   }
   else if( !strcmp( _tokens[0] , "help" ) )
   {
      DisplayHelp( _tokens[1] ) ;
      return TRUE ;
   }



   return FALSE ;
}


int FindOperator( int first , int last )
{
   int level = 0 ;
   int ch ;
   int found = -1 ;
   int precCurr ;
   int precLast = PRECEDENCE_NUM ;


   for( int idx = first ; idx < last ; idx++ )
   {
      ch = _tokens[ idx ][ 0 ]  ;
      if( ch == '(' )
      {
         level++ ;
         continue ;
      }

      if( ch == ')' )
      {
         level-- ;
         continue ;
      }

      if( level )
      {
         continue ;
      }

      precCurr = GetPrecedence( ch ) ;
      if( precCurr )
      {
         if( precCurr <= precLast )
         {
            precLast = precCurr ;
            found = idx ;
         }
      }
   }

   return found ;
}


void StripParenthesis( int& first , int& last ) 
{
   if( ( _tokens[ first ][ 0 ] != '(' ) || ( _tokens[ last ][ 0 ] != ')' ) )
   {
      return ;
   }

   int level = 0 ;

   for( int idx = first ; idx < last ; idx++ )
   {
      char ch = _tokens[ idx ][ 0 ] ;
      if( ch == '(' )
      {
         level++ ;
         continue ;
      }
      if( ch == ')' )
      {
         level-- ;
         if( !level )
         {
            return ;
         }
         continue ;
      }
   }

   (first)++ ;
   (last)-- ;
}


double ProcessCommand( int cmdidx , double input ) 
{
   double val = NAN ;

   val = _functions[ cmdidx ].function( input ) ;

   return val ;
}


double btof( char* token )
{
   int size = strlen( token ) ;
   unsigned long val = 0 ;

   for( int idx = 0 ; idx < size ; idx++ )
   {
      if( token[ idx ] == '1' )
      {
         val = ( val << 1 ) + 1 ;
      }
      else if( token[ idx ] == '0' )
      {
         val = ( val << 1 ) ;
      }
   }

   return(double)val ;
}


double htof( char* token )
{
   int len = strlen( token ) ;
   unsigned long val = 0 ;

   for( int idx = 2 ; idx < len ; idx++ )
   {
      char ch = token[ idx ] ;
      if( ch <= '9' )
      {
         ch -= '0' ;
      }
      else
      {
         ch &= ~(0x20) ; // to upper, just in case
         ch -= 'A' ;
         ch += 10 ;
      }
      val = ( val << 4 ) + ch ;
   }

   return(double)val ;
}


double otof( char* token )
{
   int len = strlen( token ) ;
   unsigned long val = 0 ;

   for( int idx = 1 ; idx < len ; idx++ )
   {
      char ch = token[ idx ] ;
      ch -= '0' ;
      val = ( val << 3 ) + ch ;
   }

   return(double)val ;
}


double Process( int first , int last )
{
   double val = NAN ;
   double val1 ;
   double val2 ;
   char   oper ;
   int    pos ;
   double neg = 1.0 ;

   StripParenthesis( first , last ) ;

   if( strcmp( _tokens[ first ] , "-" ) == 0 )
   {
      neg = -1.0 ;
      first++ ;
   }

   if( first == last )
   {
      char* token = _tokens[first] ;
      int idx = GetVariableIdx( token ) ;
      if( idx < 0 )
      {
         if( token[0] == '\'' )
         {
            return(double)token[1] ;
         }

         int len = strlen( token ) ;
         for( int idx = 0 ; idx < len ; idx++ )
         {
            if( token[idx] == '_' )
            {
               return neg * btof( token ) ;
            }
         }

         if( ( token[0] == 'o' ) || ( token[0] == 'O' ) )
         {
            return neg * otof( token ) ;  // octal input
         }
         if( ( token[0] == '0' ) && ( token[1] == 'x' ) )
         {
            return neg * htof( token ) ;  // hex input
         }
         else
         {
            return neg * atof( token ) ;
         }
      }
      else
      {
         return neg * _variables[ idx ].value ;
      }
   }

   pos = FindOperator( first , last ) ;
   if( pos < 0 )
   {
      int cmdidx = FindCommand( _tokens[ first ] ) ;
      if( cmdidx >= 0 )
      {
         return ProcessCommand( cmdidx , Process( first + 1 , last ) ) ;
      }

      output << "error finding operator between " << first << " and " << last << endl ;
      return 0 ;
   }

   oper = _tokens[ pos ][ 0 ] ;

   val1 = Process( first , pos - 1 ) ;
   val2 = Process( pos + 1 , last ) ;

   val = eval( val1 , val2 , oper ) ;

   return neg * val ;
}


void OutputBinary( double val ) 
{
   int bytes ;
   _int64 llval ;

   switch( _mode )
   {
   case MODE_INT8 :
      bytes = 1 ;
      llval = (char)val ;
      break ;

   case MODE_UINT8 :
      bytes = 1 ;
      llval = (unsigned char)val ;
      break ;

   case MODE_INT16 : 
      bytes = 2 ;
      llval = (short)val ;
      break ;

   case MODE_UINT16 : 
      llval = (unsigned short)val ;
      bytes = 2 ;
      break ;

   case MODE_INT32 :
      llval = (long)val ;
      bytes = 4 ;
      break ;

   case MODE_UINT32 :
      llval = (unsigned long)val ;
      bytes = 4 ;
      break ;

   case MODE_FLOAT :
      {
         float fval = (float)val ;
         llval = *(_int64*)&fval ;
         bytes = 4 ;
      }
      break ;

   case MODE_DOUBLE :
      llval = *(_int64*)&val ;
      bytes = 8 ;
      break ;
   }

   char* bits[] = 
   {
      "0000"
      ,  "0001"
      ,  "0010"
      ,  "0011"
      ,  "0100"
      ,  "0101"
      ,  "0110"
      ,  "0111"
      ,  "1000"
      ,  "1001"
      ,  "1010"
      ,  "1011"
      ,  "1100"
      ,  "1101"
      ,  "1110"
      ,  "1111"
   } ;

   int numnibs = ( bytes * 2 ) ;
   int nibbles[ sizeof( llval ) * 2 ] ;
   for( int idx = 0 ; idx < numnibs ; idx++ )
   {
      nibbles[ idx ] = llval & 0x0f ;
      llval = llval >> 4 ;
   }

   // tim_todo CHECK ENDIANNESS HERE
   for( idx = numnibs-1 ; idx >= 0 ; idx-- )
   {
      output << bits[ nibbles[ idx ] ] ;
      if( idx )
      {
         output << "_" ;
      }
   }
}

#define BITS_PER_BYTE 8
void OutputIeee( double val )
{
   // endian issues?

   _int64 llval = *( (_int64*)(&val) ) ;
   unsigned int lvals[2] ;

   lvals[0] = *(unsigned long*)&llval ;
   lvals[1] = *( (unsigned long*)&llval + 1 ) ;

   int part = 1 ;
   for( int idx = 0 ; idx < sizeof( double ) * BITS_PER_BYTE ; idx++ )
   {
      if( idx == sizeof( long ) * BITS_PER_BYTE )
      {
         part = 0 ;
      }
      if( lvals[part] & 0x80000000 )
      {
         output << "1" ;
      }
      else
      {
         output << "0" ;
      }
      lvals[part] <<= 1 ;
      if( ( idx == 0 ) || ( idx == 11 ) )
      {
         output << "_" ;
      }

   }
}

void OutputEngineering( double val ) 
{
   bool neg = FALSE ;

   if( val < 0 )
   {
      val = -val ;
      neg = TRUE ;
   }

   int exp = (int)floor( log10( val ) ) ;
   float mantissa ;

   if( exp < 0 ) 
   {
     exp -= 2 ;
   }

   exp = exp / 3 * 3 ;


   mantissa = val / pow( 10 , exp ) ;

   if( neg )
   {
      output << "-" ;
   }

   output.precision( _precision ) ;

   output << mantissa ;

   output << "e" ;

   if( exp < 0 )
   {
      output << "-" ;
      exp = -exp ;
   }

   output.fill( '0' ) ;
   output.width( 3 ) ;

   output << exp ;
}


void Output( double val )
{
   if( _base == BASE_BIN )
   {
      OutputBinary( val ) ;
      return ;
   }


   if( _mode != MODE_CHAR )
   {
      switch( _base )
      {
      case BASE_DEC :
         output << dec ;
         break ;

      case BASE_HEX :
         output << hex << "0x" ;
         break ;

      case BASE_OCT :
         output << oct << "O" ;
         break ;
      }
   }

   switch( _mode )
   {
   case MODE_CHAR :
      output << "'" << (char)(val) << "'" ;
      break ;

   case MODE_INT8 :
      output << ( ( (short)(val) ) & 0xff ) ;
      break ;

   case MODE_INT16 : 
      output << (short)val ;
      break ;

   case MODE_INT32 :
      output << (long)val ;
      break ;

   case MODE_UINT8 :
      output << (unsigned short)(unsigned char)val  ;
      break ;

   case MODE_UINT16 : 
      output << (unsigned short)val ;
      break ;

   case MODE_UINT32 :
      output << (unsigned long)val ;
      break ;

   case MODE_FLOAT :

      if( _base != BASE_DEC )
      {
         float fval = val ;
         unsigned long *plval = (unsigned long*)&fval ;
         output << *plval ;
      }
      else
      {
         if( _engineering )
         {
            OutputEngineering( val ) ;
         }
         else if( _ieee )
         {
            OutputIeee( val ) ;
         }
         else
         {
            output << (float)val ;
         }
      }
      break ;

   case MODE_DOUBLE :
      if( _base != BASE_DEC )
      {
         unsigned long *plval = (unsigned long *)&val ;
         plval++ ;
         output << *plval ;
         plval-- ;
         output << *plval ;
      }
      else
      {
         if( _engineering )
         {
            OutputEngineering( val ) ;
         }
         else if( _ieee )
         {
            OutputIeee( val ) ;
         }
         else
         {
            output << val ;
         }
      }
      break ;
   }
}


int main( int argc , char** argv )
{
   char buff[ MAX_LINE_LENGTH ] ;
   int size ;
   bool skip = FALSE ;
   ifstream finput ; 

   if( argc > 1 )
   {
      strcpy( buff , argv[1] ) ;
      skip = true ;
   }

#if 0 // set to 1 for file input in debugger
   else
   {
      finput.open( "test.txt", ios::in );

      if( !finput.is_open() )
      {
         cout << "Failed to open file";
         exit( EXIT_FAILURE ) ;
      }

      input = finput ;
   }
#endif

   int varidx = GetNewVariableIdx( "pi" ) ;
   SetVariable( varidx , asin(1)*2 ) ;
   varidx = GetNewVariableIdx( "e" ) ;
   SetVariable( varidx , exp(1) ) ;

   while( !input.eof() || skip )
   {
      double val ;

      if( !skip )
      {
         input.getline( buff , sizeof(buff) );
      }

      if( !strcmp( buff , "." ) | !strlen( buff ) )
      {
         exit( EXIT_SUCCESS ) ;
      }

      if( echoOn )
      {
         output << buff << endl ;
      }

      size = parse( buff ) ;

      int first = 0 ;
      int last = size-1 ;

      int varidx = 
      CheckAssignment( first , last ) ;

      if( !ProcessModes() )
      {
         val = Process( first , last ) ;

         output << "=" ;

         Output( val ) ;

         output << endl ;

         if( varidx >= 0 )
         {
            SetVariable( varidx , val ) ;
         }
      }

      if( skip )
      {
         exit(0) ;
      }
   }

   output << flush ;

   return EXIT_SUCCESS ;
}                      



