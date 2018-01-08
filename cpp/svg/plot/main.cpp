#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* strtof */
#include <stdio.h>
#include <string.h>

#include "utility.h"
#include "svgPlot.h"
#include "svgDwg.h"

using namespace std;



#define MAX_STRING_SIZE 200  // max size for configurable strings

typedef struct
{
   string text ;
   int points[13] ;
} PITCH_DEF_S ;

#define CONFIG_FILE "config.txt"

#define DEFAULT_WIDTH  650
#define DEFAULT_HEIGHT 300
#define DEFAULT_XMIN   0
#define DEFAULT_XMAX   72
#define DEFAULT_YMIN   0
#define DEFAULT_YMAX   1.0
#define DEFAULT_XDIV   4
#define DEFAULT_YDIV   10
#define DEFAULT_NUM_BOARDS 12 
#define DEFAULT_ITERATIONS 10000

// Configuration parameters BEGIN
// May be overwritten by values in config.txt

char _Title[ MAX_STRING_SIZE ]  = "" ;
char _xTitle[ MAX_STRING_SIZE ] = "Average Ports per Board Connected" ;
char _yTitle[ MAX_STRING_SIZE ] = "Probability of Blocking"           ;

char _xFormat[ MAX_STRING_SIZE ] = "%3.0f" ;
char _yFormat[ MAX_STRING_SIZE ] = "%5.2f" ;

float _width      = DEFAULT_WIDTH  ;
float _height     = DEFAULT_HEIGHT ;
float _xmin       = DEFAULT_XMIN   ;
float _xmax       = DEFAULT_XMAX   ;
float _ymin       = DEFAULT_YMIN   ;
float _ymax       = DEFAULT_YMAX   ;
float _xdiv       = DEFAULT_XDIV   ;
float _ydiv       = DEFAULT_YDIV   ;
int   _iterations = DEFAULT_ITERATIONS ;

// Configuration parameters END

#define PLOT_OFFSET_X 100
#define PLOT_OFFSET_Y 100

#define TEXT_FONT 12


#define XTEXT 100 
#define YTEXT_OFFSET 25 

#define TEXT_LINE_SPACING 100 // spaces between text lines below plot

int   _numboards = DEFAULT_NUM_BOARDS ;

typedef enum
{
   TYPE_FLOAT ,
   TYPE_INT ,
   TYPE_STRING ,
   TYPE_FILE ,
} TYPE_E ;


std::vector<string> files ;


bool addDataFile( svgPlot& plot , const char* filename )
{
 	ifstream file;
   string line ;
   string lineFirst ;
   std::vector<Point> data ;
   bool first ;
   static float yText = ( PLOT_OFFSET_Y + _height + TEXT_LINE_SPACING ) ;

	file.open( filename, std::fstream::in );
	if (file.is_open())
	{
      first = true ;
      while( getline( file , line ) ) 
      {
         if( first )
         {
            lineFirst = line ;
            first = false ;
         }

         // lines containing data are space indented
         if( line.at(0) == ' ' )
         {
            size_t pos = 0 ;  
            string first ;

            // comma separates values (first value - number of connections, second value - number of blocks)
            if( ( pos = line.find( "," ) ) != std::string::npos) 
            {
               first = line.substr(0, pos);
               line.erase(0, pos + 1 );

               float val1 = strtof( first.c_str() , NULL ) ;
               float val2 = strtof( line.c_str()  , NULL ) ;

               data.push_back( Point( val1 , val2 ) ) ;
            }
         }
      }

      // normalize data and integrate
      float integral = 0 ;
      for( std::vector<Point>::iterator it = data.begin(); it != data.end(); ++it) 
      {
         integral += (*it).yVal ;
         (*it).yVal = integral / _iterations ;
         // average ports connected per board.  factor of 2 since two ports per connection
         (*it).xVal = (*it).xVal * 2 / _numboards ;  
      }

      const char* color = plot.addData( data ) ;

      // add text below plot
      string desc = filename ;
      desc.append( " - " ) ;
      desc.append( lineFirst ) ;
      svgText text( XTEXT , yText , desc ) ;
      yText += YTEXT_OFFSET ;
      text.setFontColor( color ) ;
      text.setAnchor( "start" ) ;
      text.setFontSize( TEXT_FONT ) ;
      text.draw() ;

		file.close();
      return true ;
	}
   else
   {
      return false ;
   }
}

void makeDwg( void )
{
   svgPlot plot( _xmin , _xmax , _ymin , _ymax , _width , _height ) ;
   plot.xDiv( _xdiv , _xFormat ) ;
   plot.yDiv( _ydiv , _yFormat ) ;

   plot.Title( _Title ) ;
   plot.xTitle( _xTitle ) ;
   plot.yTitle( _yTitle ) ;

   for( vector<string>::const_iterator it = files.begin(); it != files.end(); ++it ) 
   {  
      addDataFile( plot , (*it).c_str() ) ;
   }

   plot.transform( PLOT_OFFSET_X , PLOT_OFFSET_Y ) ;
   plot.draw() ;
}

#include <fstream>

typedef struct 
{
   const char*  name ;
   TYPE_E type ;
   void*  ptr ;
} ConfigTypeS ;

ConfigTypeS ConfigTypes[] =
{
   { "WIDTH"      , TYPE_FLOAT  , (void*)&_width      } ,
   { "HEIGHT"     , TYPE_FLOAT  , (void*)&_height     } ,
   { "XMIN"       , TYPE_FLOAT  , (void*)&_xmin       } ,
   { "XMAX"       , TYPE_FLOAT  , (void*)&_xmax       } ,
   { "YMIN"       , TYPE_FLOAT  , (void*)&_ymin       } ,
   { "YMAX"       , TYPE_FLOAT  , (void*)&_ymax       } ,
   { "XDIV"       , TYPE_FLOAT  , (void*)&_xdiv       } ,
   { "YDIV"       , TYPE_FLOAT  , (void*)&_ydiv       } ,
   { "NUM_BOARDS" , TYPE_INT    , (void*)&_numboards  } ,
   { "ITERATIONS" , TYPE_INT    , (void*)&_iterations } ,
   { "TITLE"      , TYPE_STRING , (void*)_Title       } ,
   { "XTITLE"     , TYPE_STRING , (void*)_xTitle      } ,
   { "YTITLE"     , TYPE_STRING , (void*)_yTitle      } ,
   { "XFORMAT"    , TYPE_STRING , (void*)_xFormat     } ,
   { "YFORMAT"    , TYPE_STRING , (void*)_yFormat     } ,
   { "FILE"       , TYPE_FILE   , (void*)0            } ,
} ;
             
#define NUM_CONFIG_TYPES ARRAYSIZE( ConfigTypes )


void SetParameter( string label , string value )
{
   for (int idx = 0 ; idx < NUM_CONFIG_TYPES ; idx++ )
   {
      if (strcmp( label.c_str(), ConfigTypes[ idx ].name ) == 0 )
      {
         switch( ConfigTypes[ idx ].type )
         {
         case TYPE_FLOAT :
            {
               float val = atof( value.c_str() ) ;
               *((float*)ConfigTypes[ idx ].ptr) = val ;
            }
            break ;
         case TYPE_INT :
            {
               float val = atoi( value.c_str() ) ;
               *((int*)ConfigTypes[ idx ].ptr) = val ;
            }
            break ;
         case TYPE_STRING :
            {
               char* str = (char*)ConfigTypes[ idx ].ptr ;
               strncpy( str , value.c_str() , MAX_STRING_SIZE ) ;
            }
            break ;

         case TYPE_FILE :
            if (!value.empty() && value[value.size() - 1] == '\r') 
            {
               value.erase(value.size() - 1);
            }
            files.push_back( value ) ;
            break ;

         }
      }
   }
}

void ReadConfig()
{
 	ifstream file;
   string line ;

   file.open( CONFIG_FILE , std::fstream::in );

	if (file.is_open())
	{
      size_t pos = 0 ;  
      string first ;
      while( getline( file , line ) ) 
      {
         if( line.at(0) == '%' )
         {
            continue ;
         }

         if( ( pos = line.find( " " ) ) != std::string::npos)         
         {
            first = line.substr(0, pos); 
            line.erase(0, pos + 1 );
            SetParameter( first , line ) ;
         }
      }

		file.close();
   }
}


int main( int argc , char** argv ) 
{
  int width  =  8 ;
  int height = 10 ;

  ReadConfig() ;

  svgDwg dwg( width , height ) ; 

  dwg.start() ;

  makeDwg() ;
                                                             
  dwg.end() ;
}
