/*********************************************************
 *
 *  File Name:       Monitor.c
 *
 *
 *  Copyright 2003(c): Innovative Solutions & Support, Inc. as an unpublished work
 *
 *
 *  The information contained herein is confidential property of Innovative Solutions & Support, Inc.
 *  The use, copying, transfer or disclosure of such information is prohibited except by express
 *  written agreement.
 *
 *
 *  MODULE PURPOSE:  
 *      Provides a menu driven monitor on a serial port.
 *
 *********************************************************/


/*********************************************************
 * Includes :                                             
 *********************************************************/

#define EXCEED_REPORT      1

#include "Monitor.h"

#include "Structs.h"
#include "Config.h"
#include "AddressMap.h"
#include "Serial.h"
#include "nvram.h"
#include "PolInput.h"
#include "Version.h"
#include "size_t.h"
#include "MemoryTest.h"

#if EXCEED_REPORT
#include "NvramLocations.h" /* tim_todo ELIMINATE THIS DEPENDENCY */
#include "ExceedanceRecording.h"
#endif /* EXCEED_REPORT */

#ifdef CONFIG_PERFTIMER
#include "PerfTimer.h"
#include "cli.h"
#endif /* CONFIG_PERFTIMER */

#ifdef CONFIG_ERROR_DUMP
#include "Errors.h"
#include "labelMatrix.h"
#include "BitErrorRecording.h"
#endif /* CONFIG_ERROR_DUMP */


/*********************************************************
 * Local Defines:
 *********************************************************/

enum 
{
   WORD_BYTE0 ,
   WORD_BYTE1 
} ;
enum 
{
   LONG_BYTE0 ,
   LONG_BYTE1 ,
   LONG_BYTE2 ,
   LONG_BYTE3 
} ;


#define BYTES_PER_WORD sizeof( tWord )
#define BYTES_PER_LONG sizeof( tLong )



/*********************************************************
 * Local Typedefs :  
 *********************************************************/

typedef tBoolean (*pfunc)( tULong param ) ;

typedef struct menu_struct {

   char* text ;
   pfunc function ;
   tULong   param ;
} menu_struct ;


/*********************************************************
 * Local Macros : 
 *********************************************************/

#define offsetof(type,memb) ((size_t)&((type *)0)->memb)


/********************************************************* 
 * Static Function Prototypes :  
 *********************************************************/

#if EXCEED_REPORT
static tBoolean ExceedReport( tExceedanceFifoRecord* rec , tBoolean headers  ) ;
static tBoolean ExceedanceReport( tULong param ) ; 
#endif /* EXCEED_REPORT */


#ifdef CONFIG_PERFTIMER
static tBoolean DumpPerftimer( tULong param ) ;
static tBoolean CommandLine( tULong param ) ;
#endif /* CONFIG_PERFTIMER */

#ifdef CONFIG_ERROR_DUMP
static tBoolean DumpErrors( tULong param ) ;
static tBoolean EraseErrors( tULong param ) ;
#endif /* CONFIG_ERROR_DUMP */

static tBoolean DumpParameters(  tULong param  ) ;

static tVoid PrintMenu( menu_struct menu[] , tUWord size ) ;


/*********************************************************
 * Local Static Variables :  
 *********************************************************/

tBoolean inhibit_menu = FALSE ;

/*********************************************************
 * Global Variables :  
 *********************************************************/

static tUByte nvbuff[ NVRAM_SIZE ] ; 

/* The following array of structures defines the menu to display over
 * the serial port.  The first parameter is the text.  The second parameter
 * is a pointer to a function to call if the item is selected.  The third
 * parameter is a value to pass to the function.
 */

menu_struct Menu[] =
{ 
#if EXCEED_REPORT
   { "Exceedance dump with headers." , ExceedanceReport  , 1 } ,
   { "Exceedance dump raw."          , ExceedanceReport  , 0 } ,
#endif   

   { "System parameters dump"        , DumpParameters    , 1 } ,

#ifdef CONFIG_PERFTIMER
   { "Dump Perftimer"                , DumpPerftimer     , 0 } ,
   { "Command Line"                  , CommandLine       , 0 } ,
#endif  /* CONFIG_PERFTIMER */

#ifdef CONFIG_ERROR_DUMP
   { "Dump Errors"                   , DumpErrors        , 0 } ,
   { "Erase Errors"                  , EraseErrors       , 0 } ,
#endif /* CONFIG_ERROR_DUMP */
} ;


/*********************************************************
 *
 *  NAME:         GetWord()
 *
 *  DESCRIPTION:    Get a word to output.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tUByte* pdata - Pointer to value
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Resultant value
 *
 *  NOTES:
 *
 *********************************************************/

tWord GetWord( tUByte* pdata )
{
   union {
      tWord  word ;
      tUByte byte[2] ;
   } data ;

   data.byte[ WORD_BYTE0 ] = pdata[0] ; 
   data.byte[ WORD_BYTE1 ] = pdata[1] ; 

   return data.word ;
}

/*********************************************************
 *
 *  NAME:         GetUWord()
 *
 *  DESCRIPTION:    Get a uword to output.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tUByte* pdata - Pointer to value
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Resultant value
 *
 *  NOTES:
 *
 *********************************************************/

tUWord GetUWord( tUByte* pdata )
{
   union {
      tUWord uword ;
      tUByte byte[2] ;
   } data ;

   data.byte[ WORD_BYTE0 ] = pdata[0] ; 
   data.byte[ WORD_BYTE1 ] = pdata[1] ; 

   return data.uword ;
}


/*********************************************************
 *
 *  NAME:         GetULong()
 *
 *  DESCRIPTION:    Get a ulong to output.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tUByte* pdata - Pointer to value
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Resultant value
 *
 *  NOTES:
 *
 *********************************************************/

tULong GetULong( tUByte* pdata )
{
   union {
      tULong ulong ;
      tUByte byte[4] ;
   } data ;

   data.byte[ LONG_BYTE0 ] = pdata[0] ; 
   data.byte[ LONG_BYTE1 ] = pdata[1] ; 
   data.byte[ LONG_BYTE2 ] = pdata[2] ; 
   data.byte[ LONG_BYTE3 ] = pdata[3] ; 

   return data.ulong ;
}


/*********************************************************
 *
 *  NAME:         OutLinefeed()
 *
 *  DESCRIPTION:    Output a linefeed.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              None
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes output
 *
 *  NOTES:
 *
 *********************************************************/

tULong OutLinefeed()
{
   return OutString( "\r\n" ) ;
}


/*********************************************************
 *
 *  NAME:         OutString()
 *
 *  DESCRIPTION:    Output a string.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tByte* str - Pointer to string to ouput.
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes output
 *
 *  NOTES:
 *
 *********************************************************/

tULong OutString( tByte* str )
{
   tULong size = 0 ;
   tByte* strTemp ;

   strTemp = str ;
   
   while( *str )
   {
      str++ ;
      size++ ;
   }
   
   SerialWrite(SERIAL_PORT_MONITOR, (tUByte*)strTemp , (tLong)size ) ;
   
   return size ;
}


/*********************************************************
 *
 *  NAME:         OutInt()
 *
 *  DESCRIPTION:    Output a long.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tLong val    - The value to output
 *              tULong len   - Length (in characters) to be printed
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes output
 *
 *  NOTES:
 *
 *********************************************************/

#define MAX_LINE_LEN 200
tULong OutInt( tLong val , tULong len )
{
   tUByte str[ MAX_LINE_LEN ] ;
   tLong div = 10 ;
   tUByte cur ;
   tULong    idx = 0 ;

   if( val < 0 )
   {
      val = -val ;
      str[ idx++ ] = '-' ;
   }

   while( div > 1 )
   {
      while( val / div )
      {
         div *= 10 ;
      }
      div /= 10 ;
      cur = (tUByte)( val / div ) ;
      val = val - cur * div ;
      str[ idx++ ] = (tUByte)( cur + '0' ) ;
   }

   if( !idx )
   {
      str[ idx++ ] = '0' ;
   }

   while( idx < len )
   {
      str[ idx++ ] = ' ' ;
   }

   str[ idx ] = 0 ; /* null terminate */

   OutString( (tByte*)str ) ;

   return idx ;
}


/*********************************************************
 *
 *  NAME:         OutHex()
 *
 *  DESCRIPTION:    Output a hex value.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tULong val      - The value to output
 *              tULong bytes    - Number of bytes in value
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes output
 *
 *  NOTES:
 *
 *********************************************************/

#define MAX_NIBS     8 
#define BITS_PER_NIB 4 
tULong OutHex( tULong val , tULong bytes )
{
   tUByte str[ MAX_NIBS + 1 ] ;
   const tUByte hexdigits[] = "0123456789abcdef" ;
   tULong num_nibs ;

   tULong idx ;
   tULong idxtmp ;

   num_nibs = bytes * 2 ;

   for( idx = 0 ; idx < num_nibs ; idx++ )
   {
      idxtmp = (tULong)(( val >> ( ( num_nibs - idx - 1 ) * BITS_PER_NIB ) ) & 0x0f) ;
      str[ idx ] = hexdigits[ idxtmp ] ;
   }
   str[ idx ] = 0 ;

   OutString( (tByte*)str ) ;

   return idx ;
}


#define OCT_DIGS 3
tULong OutOctal( tULong val )
{
   /* assumes threee octal digits for now */
   tUByte str[ OCT_DIGS + 1 ] ;
   const tUByte octdigits[] = "01234567" ;
   int   shift ;
   int idx ;
   int idxtmp ;

   for( idx = 0 ; idx < OCT_DIGS ; idx++ )
   {
      shift = ( OCT_DIGS - idx - 1 ) * 3 ; /* three bits per octal digit */
      idxtmp = (tULong)( ( val >> shift ) & 0x07 ) ; /* mask off three bits */
      str[ idx ] = octdigits[ idxtmp ] ;
   }
   str[ idx ] = 0 ;

   OutString( (tByte*)str ) ;

   return idx ;
}


/*********************************************************
 *
 *  NAME:         OutFloat()
 *
 *  DESCRIPTION:    Output a float value.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tLong val    - The value to be output
 *              tULong scale - Scale factor
 *              tULong len   - Length (in characters) to be printed
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes output
 *
 *  NOTES:
 *      Only prints two decimal points
 *
 *********************************************************/

tULong OutFloat( tLong val , tULong scale , tULong len ) 
{
  tULong size ;

  tFloat fval = (tFloat)val / scale ;
  tLong  intpart ;
  tLong  decpart ;

  intpart = (tLong)fval ;
  size = OutInt( intpart , 0 ) ;
  size += OutString( "." ) ;
  decpart = (tLong)( ( fval - (tFloat)intpart ) * 100 ) ;
  if( decpart )
  {
      size += OutInt( decpart , 0 ) ;
  }
  else
  {
     size += OutString( "00" ) ;
  }
  while( size < len )
  {
     size += OutString( " " ) ;
  }

  return size ;
}

#if EXCEED_REPORT

/*********************************************************
 *
 *  NAME:         ExceedReport()
 *
 *  DESCRIPTION:    Outputs one record of exeedance report.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tExceedanceFifoRecord* rec - Pointer to the record
 *              tBoolean headers           - TRUE => headers printed
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes written.
 *
 *  NOTES:
 *
 *********************************************************/

tBoolean ExceedReport( tExceedanceFifoRecord* rec , tBoolean headers ) 
{
   tLong   sample ;
   tULong  engine ;
   tULong  numitems ;
   tULong  itemidx ;
   tULong  prepostidx ;
   tLong   timeMs ;

   enum {
      TYPE_WORD  ,
      TYPE_UWORD 
   } ;

   enum {
      PRE_IDX  ,
      POST_IDX ,
      POST_POST_MAX 
   } ;

   enum
   {
      SCALE_TORQUE   = 1   ,
      SCALE_TIT      = 1   ,
      SCALE_TACH     = 256 ,
      SCALE_FUELFLOW = 1   
   } ;

   typedef struct tItem {
      char* title ;
      tULong   type ;
      tULong   scale ;
      tULong   offset[ POST_POST_MAX ] ;
   } tItem ;
   
   tItem items[] =
   {
      { "Torque   " , 
        TYPE_WORD  , 
        SCALE_TORQUE ,
        offsetof(  tExceedanceFifoRecord , preBuf  ) + offsetof( tPreExceedanceRecordingEvent , Torque ) ,
        offsetof(  tExceedanceFifoRecord , postBuf ) + offsetof( tExceedanceRecordingEvent    , Torque ) ,
      } , 
      { "Tit      " , 
        TYPE_WORD  ,
        SCALE_TIT ,
        offsetof(  tExceedanceFifoRecord , preBuf  ) + offsetof( tPreExceedanceRecordingEvent , Tit ) ,
        offsetof(  tExceedanceFifoRecord , postBuf ) + offsetof( tExceedanceRecordingEvent    , Tit ) ,
      } , 
      { "Tach     " , 
        TYPE_UWORD ,
        SCALE_TACH ,
        offsetof(  tExceedanceFifoRecord , preBuf  ) + offsetof( tPreExceedanceRecordingEvent , Tach ) ,
        offsetof(  tExceedanceFifoRecord , postBuf ) + offsetof( tExceedanceRecordingEvent    , Tach ) ,
      } , 
      { "FuelFlow " , 
        TYPE_UWORD ,
        SCALE_FUELFLOW ,
        offsetof(  tExceedanceFifoRecord , preBuf  ) + offsetof( tPreExceedanceRecordingEvent , FuelFlow ) ,
        offsetof(  tExceedanceFifoRecord , postBuf ) + offsetof( tExceedanceRecordingEvent    , FuelFlow ) ,
      } , 
   } ;

   tULong samples[] = { PRE_TRIGGER_SAMPLES , POST_TRIGGER_SAMPLES } ;

   if( headers )
   {
      OutString( "  exceedanceDuration   = " ) ;
      OutInt( (tLong)GetUWord( (unsigned char*)&(rec->header.exceedanceDuration ) ) , 0 ) ;
      OutLinefeed() ;

      OutString( "  exceedanceIdentifier = 0x" ) ;
      OutHex( GetUWord( (unsigned char*)&(rec->header.exceedanceIdentifier ) ) , BYTES_PER_WORD ) ;
      OutLinefeed() ;

      OutString( "  exceedanceBeginTime  = " ) ;
      OutInt( (tLong)GetULong( (unsigned char*)&(rec->header.exceedanceBeginTime ) ) , 0 ) ;
      OutLinefeed() ;
      OutLinefeed() ;
   }

   numitems = sizeof( items ) / sizeof( items[0] ) ;

   for( itemidx = 0 ; itemidx < numitems ; itemidx++ )
   {
      tUByte* itemptr ;

      if( headers )
      {
         OutString( "  " ) ;
         OutString( items[ itemidx ].title ) ;
         OutLinefeed() ;

         OutString( "    time(ms)   engine1   engine2   engine3   engine4"  ) ;
         OutLinefeed() ;

         OutString( "    ================================================" ) ;
         OutLinefeed() ;
      }

      for( prepostidx = PRE_IDX ; prepostidx <= POST_IDX ; prepostidx++ )
      {
         itemptr = (tUByte*)rec + items[ itemidx ].offset[ prepostidx ] ;

         for( sample = 0 ; sample < samples[ prepostidx ] ; sample++ )
         {
            timeMs = ( prepostidx == PRE_IDX ) ? ( sample - PRE_TRIGGER_SAMPLES ) : sample ;
            timeMs *= SAMPLE_PERIOD_MS ;


            OutString( "    " ) ;
            OutInt( timeMs , 11 ) ;

            for( engine = 0 ; engine < MAX_ENGINES ; engine++ )
            {
               tUByte* ptr = itemptr + ( sample * MAX_ENGINES + engine ) * sizeof( tWord ) ;
               tLong val = ( items[ itemidx ].type == TYPE_WORD ) ? (tLong)GetWord( ptr ) : (tLong)GetUWord( ptr ) ;

               if( items[ itemidx ].scale == 1 )
               {
                  OutInt( val , 10 ) ;
               }
               else
               {
                  OutFloat( val , items[ itemidx ].scale , 10 ) ;
               }
            }
            OutLinefeed() ;
         }
      }
   }
   
   return FALSE ;
}


/*********************************************************
 *
 *  NAME:         ExceedanceReport()
 *
 *  DESCRIPTION:  Outputs an exeedance report.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tULong param - Converted to Boolean.  TRUE => headers printed
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes written
 *
 *  NOTES:
 *
 *********************************************************/

tBoolean ExceedanceReport( tULong param ) 
{
   tLong  num_records ;
   tLong  rec_num ;
   tBoolean headers ;
   
   headers = (tBoolean)param ;

   CopyFromNvRam( 0 , (tVoid*)nvbuff , NVRAM_SIZE ) ;

   num_records = nvbuff[ NVRAM_EXCEEDANCE_NUM ] ;

   if( headers )
   {
      OutString( "num_records = ") ;
      OutInt( num_records , 0 ) ;
      OutLinefeed() ;
   }

   for( rec_num = 0 ; rec_num < num_records ; rec_num++ )
   {
      tULong offset = NVRAM_EXCEEDANCE_SRT + rec_num * (tULong)sizeof( tExceedanceFifoRecord ) ;


      if( headers )
      {
         OutString( "rec_num " ) ;
         OutInt( rec_num , 0 ) ;
         OutLinefeed() ;
      }

      ExceedReport( (tExceedanceFifoRecord*)&nvbuff[ offset ] , headers ) ;
   }
   
   return FALSE ;
}
#endif /* EXCEED_REPORT */


/*********************************************************
 *
 *  NAME:         DumpParameters()
 *
 *  DESCRIPTION:  Dumps systeme parameters.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tULong param -  Not used
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              Number of bytes written
 *
 *  NOTES:
 *
 *********************************************************/

tBoolean DumpParameters( tULong param )
{
    param = param ;  /* not used */
    
    OutLinefeed() ;
    
    OutString( "GRP Part Number = " ) ;
    /* null terminate just in case */
    gCoordination.grpPartNumberString[PART_NUM_LEN-1] = 0 ;
    OutString( gCoordination.grpPartNumberString ) ;
    OutLinefeed() ;
    
    OutString( "GRP Crc         = 0x" ) ;
    OutHex( gCoordination.grpCrcValue , BYTES_PER_LONG ) ;
    OutLinefeed() ;
    
    OutLinefeed() ;
    
    OutString( "ICP Part Number = " ) ;
    OutString( VERSION_STRING ) ;
    OutLinefeed() ;

    OutString( "ICP Crc         = 0x" ) ;
    OutHex( GetProgramCrc() , BYTES_PER_LONG ) ;
    OutLinefeed() ;
    OutLinefeed() ;

   return FALSE ;
}

#ifdef CONFIG_PERFTIMER

/*********************************************************
 *
 *  NAME:         DumpPerftimer()
 *
 *  DESCRIPTION:    Dump performance timer data
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              tULong param  - non used
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              0
 *
 *  NOTES:
 *      This function used for debug
 *
 *********************************************************/

tBoolean DumpPerftimer( tULong param )
{
   tULong  timeUs ;
   char*   string ;

   param = param ;

   while( GetNextPerftime( &timeUs , &string ) )
   {
      OutInt( (tLong)timeUs , 10UL ) ;
      OutString( "   " ) ;
      OutString( string ) ;
      OutLinefeed() ;
   }
   
   OutLinefeed() ;

   inhibit_menu = TRUE ;
   
   return FALSE ;
}

tBoolean CommandLine( tULong param )
{
   return CliCheck() ;
}


#endif /* CONFIG_PERFTIMER */


#ifdef CONFIG_ERROR_DUMP
tBoolean EraseErrors( tULong param )
{
   EraseBitLog() ;
   
   return FALSE ;
}

tBoolean DumpErrors( tULong param )
{
   tUByte idx ;
   tUByte size ;
   tUByte iop ;
   tUByte eng ;
   tArincProcParm* ptr ;
   const char divider[] = "| " ;

   param = param ;

   for( idx = 0 ; idx < ICPERR_NUM_ERRORS ; idx++ )
   {
      OutString( (char*)sErrors[idx].msg ) ;
      OutString( "  Hard Error : " ) ;
      OutString( sErrors[idx].hardError ? "TRUE " : "FALSE" ) ;
      OutString( "  Soft Errors : " ) ;
      OutInt( (tLong)(  sErrors[idx].numSoftErrors - sErrors[idx].softErrorCount ) , 1 ) ;
      OutString( " / " ) ;
      OutInt( (tLong)( sErrors[idx].numSoftErrors ) , 1 ) ;
      OutLinefeed() ;
   }
   OutLinefeed() ;
   OutLinefeed() ;
   
   OutString( "ARINC ERRORS :" ) ;
   OutLinefeed() ;
   
   size = sizeof( tProcParmDB ) / sizeof( tArincProcParm ) ;
   
   ptr = (tArincProcParm*)(&gArincProcParm) ;
   
   OutString( "  ENGINE -> " ) ;
   OutString( (char*)divider ) ;
   for( eng = 0 ; eng < MAX_ENGINES ; eng++ )
   {
      for( iop = INP1 ; iop <= INP3 ; iop++ )
      {
         OutInt( eng + 1 , 1 ) ;
         OutString( " " ) ;
      }
      OutString( (char*)divider ) ;
   }
   OutLinefeed() ;
   
   OutString( "  IOP    -> " ) ;
   OutString( (char*)divider ) ;
   for( eng = 0 ; eng < MAX_ENGINES ; eng++ )
   {
      for( iop = INP1 ; iop <= INP3 ; iop++ )
      {
         OutInt( iop + 1 , 1 ) ;
         OutString( " " ) ;
      }
      OutString( (char*)divider ) ;
   }
   OutLinefeed() ;
   
   
   for( idx = 0 ; idx < size ; idx++ )
   {
      OutString( "  Label_" ) ;
      OutOctal( ptr->ucLabel ) ;
      OutString( " " ) ;
      OutString( (char*)divider ) ;
      
      for( eng = 0 ; eng < MAX_ENGINES ; eng++ )
      {
         for( iop = INP1 ; iop <= INP3 ; iop++ )
         {
            GetDcuBitError( iop , eng , idx ) ? OutString( "X" ) : OutString( " " ) ;
            OutString( " " ) ;
         }
         OutString( (char*)divider ) ;
      }
      
      OutLinefeed() ;
      ptr++ ;
   }
   
   OutLinefeed() ;
   
   return FALSE ;
}
#endif /* CONFIG_ERROR_DUMP */

/*********************************************************
 *
 *  NAME:         PrintMenu()
 *
 *  DESCRIPTION:  Outputs a menu over the serial port.
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              menu_struct menu[]  The menu structure
 *              tUWord      size    Number of items in menu
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              None
 *
 *  NOTES:
 *
 *********************************************************/

tVoid PrintMenu( menu_struct menu[] , tUWord size )
{
   /* note: works for max of 9 menu items */
   tLong idx ;

   OutLinefeed() ;
   OutString( "Select one of the following:" ) ;
   OutLinefeed() ;
   OutLinefeed() ;
   for( idx = 0 ; idx < size ; idx++ )
   {
      OutInt( idx + 1 , 1 ) ;
      OutString( ") " ) ;
      OutString( menu[ idx ].text ) ;
      OutLinefeed() ;
   }
   OutLinefeed() ;
}


/*********************************************************
 *
 *  NAME:         CheckMonitor()
 *
 *  DESCRIPTION:  Task to input/output bytes for the serial monitor
 *
 *  INPUTS:
 *              Parameters Passed:
 *              -------------------
 *              None
 *
 *  OUTPUTS:
 *              Value(s) Returned:
 *              -------------------
 *              None
 *
 *  NOTES:
 *      Called periodically to service the serial monitor.
 *
 *********************************************************/

tVoid CheckMonitor( tVoid )
{
   enum {
      STATE_INIT ,
      STATE_INPUT ,
      STATE_OUTPUT ,
      STATE_PROCESS ,
      STATE_MAX
   } ;

   static tULong state = STATE_INIT ;
   static tULong menu  = 0 ;
   static tULong remaining = 0 ;
   static tUByte* ptrout ;
   static tULong idx = 0 ;
   
   tUByte buff ;

   tUWord NumMenuItems = sizeof( Menu ) / sizeof( Menu[0] ) ;

   switch( state )
   {
   case STATE_INIT :

      if( !inhibit_menu )
      {
         PrintMenu( Menu , NumMenuItems ) ;
      }
      inhibit_menu = FALSE ;

      state = STATE_INPUT ;

      break ;

   case STATE_INPUT :

      if( SerialRead( SERIAL_PORT_MONITOR , &buff , 1 ) )
      {
         idx = (tULong)( buff - '1' ) ;
         if( idx < NumMenuItems )
         {
            state = STATE_PROCESS ;
         }
         else
         {
            state = STATE_INIT ;
         }
      }

      break ;

   case STATE_PROCESS :
   
      if( !Menu[ idx ].function( Menu[ idx ].param ) )
      {
         state = STATE_OUTPUT ;
      }
      break ;
      
   
   case STATE_OUTPUT :
   {
      if( SerialOutEmpty( SERIAL_PORT_MONITOR ) )
      {
         state = STATE_INIT ;
      }

      break ;
   }

   default :
      state = STATE_INIT ;
      break ;
   }
}

