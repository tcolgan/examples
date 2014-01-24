/* cli.c */

#include "Config.h"
#include "Serial.h"
#include "Monitor.h"
#include "Cli.h"
#include "IssMemory.h"
#include "String.h"
#include "PciLib.h"

#define BUFFER_LINES  10
#define LINE_BUF_SIZE 100 
#define MAX_PARAMETERS 10

tByte sLineCurrent[ LINE_BUF_SIZE ] ;
tByte sLineBuf[ BUFFER_LINES ][ LINE_BUF_SIZE ] ;
CliTable* sCliTable ;
int       sTableSize ;
tBoolean  sContinue = TRUE ;

int argc ;
char* argv[ MAX_PARAMETERS ] ;

#define BACKSPACE_KEY  0x08
#define ENTER_KEY      0x0d
#define ESCAPE_KEY     0x1b
#define ESCAPE2_KEY    0x5b

#define MAP_UP         0x80
#define MAP_DOWN       0x81
#define MAP_RIGHT      0x82
#define MAP_LEFT       0x83

/* preceded by 1b 5b */
#define UP_KEY         0x41
#define DOWN_KEY       0x42
#define RIGHT_KEY      0x43
#define LEFT_KEY       0x44

const tUByte UpString[]    = { ESCAPE_KEY , ESCAPE2_KEY , UP_KEY     } ;
const tUByte DownString[]  = { ESCAPE_KEY , ESCAPE2_KEY , DOWN_KEY   } ;
const tUByte RightString[] = { ESCAPE_KEY , ESCAPE2_KEY , RIGHT_KEY  } ;
const tUByte LeftString[]  = { ESCAPE_KEY , ESCAPE2_KEY , LEFT_KEY   } ;

static tBoolean MemDump( int argc , char** argv ) ;
static tBoolean Test( int argc , char** argv ) ;
static tBoolean RegConfigDump( int argc , char** argv ) ;
static tBoolean PciDump( int argc , char** argv ) ;


static tVoid CliInit() ;
static tVoid ReplaceLine( int* curr , int* last , char* str ) ;

static tVoid ReplaceLine( int* curr , int* last , char* str ) 
{
   int idx ;
   
   for( idx = 0 ; idx < *curr ; idx++ )
   {
      SerialWrite( SERIAL_PORT_MONITOR , (tUByte*)LeftString , sizeof( LeftString ) ) ;
   }
   
   for( idx = 0 ; idx < *last ; idx++ )
   {
      OutString( " " ) ;
   }
   
   for( idx = 0 ; idx < *last ; idx++ )
   {
      SerialWrite( SERIAL_PORT_MONITOR , (tUByte*)LeftString , sizeof( LeftString ) ) ;
   }
   
   OutString( str ) ;
   *curr = strlen( str ) ;
   *last = *curr ;
}


tBoolean CliGet()
{
   static int idx = 0 ;
   static int idxMax = 0 ;
   static tBoolean esc = FALSE ; 
   tUByte inbyte ;
   tBoolean enterHit = FALSE ;
   tUByte* ptr ;
   int size ;
   static int lineCurrent = 0 ;
   static int lineBuffer  = 0 ;
   static int lineMax = 0 ;
   static tBoolean prompt = FALSE ;
   int echo = FALSE ;
   
   ptr = &inbyte ;
   size = 1 ;
   
   if( !prompt )
   {
      OutString( ">" ) ;
      prompt = TRUE ;
   }

   if( SerialRead( SERIAL_PORT_MONITOR , &inbyte , 1 ) )
   {
      if( inbyte == ESCAPE_KEY )
      {
         esc = TRUE ;
      }
      else if( esc )
      {
         if( inbyte == ESCAPE2_KEY ) /* ignore after escape */
         {
            inbyte = 0 ;
         }
         else {
            switch( inbyte )
            {
            case UP_KEY :
               inbyte = 0 ;
               lineBuffer-- ;
               if( lineBuffer < 0 )
               {
                  lineBuffer = lineMax-1 ;
               }
               memcpy( sLineCurrent , (char*)sLineBuf[ lineBuffer ] , sizeof( sLineCurrent ) ) ;
               ReplaceLine( &idx , &idxMax , (char*)sLineCurrent ) ;
               break ;
            case DOWN_KEY : 
               inbyte = 0 ;
               lineBuffer++ ;
               if( lineBuffer >= lineMax )
               {
                  lineBuffer = 0 ;
               }
               memcpy( sLineCurrent , (char*)sLineBuf[ lineBuffer ] , sizeof( sLineCurrent ) ) ;
               ReplaceLine( &idx , &idxMax , (char*)sLineCurrent ) ;
               break ;
            case RIGHT_KEY :
               inbyte = MAP_RIGHT ;
               ptr = (tUByte*)RightString ;
               size = sizeof( RightString ) ;
               break ;
            case LEFT_KEY :
               inbyte = MAP_LEFT ;
               ptr = (tUByte*)LeftString ;
               size = sizeof( LeftString ) ;
               break ;
            default :                
               inbyte = 0 ;
               break ;
            }
            esc = FALSE ;
         }
      }
   
      if(   ( inbyte == BACKSPACE_KEY ) 
         || ( inbyte == ENTER_KEY ) 
         || ( inbyte == MAP_LEFT ) 
         || ( inbyte == MAP_RIGHT ) 
         || ( ( inbyte >= ' ' ) && ( inbyte <= '~' ) ) )
      {

         if( inbyte == ENTER_KEY )
         {
            sLineCurrent[ idxMax ] = 0 ; /* null terminate string */
            idx = 0 ;
            idxMax = 0 ;
            enterHit = TRUE ;
            memcpy( sLineBuf[ lineCurrent ] , sLineCurrent , sizeof( sLineCurrent ) ) ;
            lineCurrent++ ;
            if( lineCurrent >= BUFFER_LINES )
            {
               lineCurrent = 0 ; 
            }
            lineBuffer = lineCurrent ;
            if( lineCurrent > lineMax )
            {
               lineMax = lineCurrent ;
            }
            prompt = FALSE ;
            echo = TRUE ;
         }
         else if( inbyte == BACKSPACE_KEY )
         {
            if( idx )
            {
               SerialWrite( SERIAL_PORT_MONITOR , (tUByte*)LeftString , sizeof( LeftString ) ) ;
               OutString( " " ) ;
               SerialWrite( SERIAL_PORT_MONITOR , (tUByte*)LeftString , sizeof( LeftString ) ) ;
               idx-- ;
            }
         }
         else if( inbyte == MAP_LEFT )
         {
            if( idx )
            {
               idx-- ;
               echo = TRUE ;
            }
         }
         else if( ( inbyte == MAP_RIGHT ) )
         {
            if( idx < idxMax )
            {
               idx++ ;
               echo = TRUE ;
            }
         }
         else if( idx < ( LINE_BUF_SIZE - 1 ) ) 
         {
            sLineCurrent[ idx++ ] = inbyte ;
            echo = TRUE ;
         }
      }         
   }
   
   if( echo ) 
   {
      SerialWrite( SERIAL_PORT_MONITOR , ptr , size ) ;
   }
   
   if( idx > idxMax )
   {
      idxMax = idx ;
   }

   return enterHit ;
}


int ParseLine( tByte* buff )
{
   /* line must be null terminated, space separated */

   tBoolean found = FALSE ;

   argc = 0 ;

   while( *buff )
   {
      if( !found )
      {
         if( *buff != ' ' )
         {
            argv[argc] = buff ;
            argc++ ;
            found = TRUE ;
         }
      }
      else
      {
         if( *buff == ' ' )
         {
            *buff = 0 ; /* null terminate substring */
            found = FALSE ; /* get ready for next */
         }
      }
      buff++ ;
   }

   return argc ;
}


tBoolean StrMatch( char* str1 , char* str2 )
{
   tBoolean match = TRUE ;
   tBoolean done  = FALSE ;

   do {
      if( *str1 != *str2 )
      {
         done = TRUE ;
         match = FALSE ;
      }
      else if ( *str1 == 0 )
      {
         done = TRUE ;
      }
      str1++ ;
      str2++ ;

   } while( !done ) ;

   return match ;
}


int GetIndex( char* command )
{
   int idx ;
   int idxFound = -1 ;

   for( idx = 0 ; idx < sTableSize ; idx++ )
   {
      if( StrMatch( sCliTable[idx].command , command ) )
      {
         idxFound = idx ;
         break ;
      }
   }

   return idxFound ;
}


tBoolean CliProcess()
{
   /* returns TRUE if still processing */
   tBoolean processing = FALSE ;
   int argc ;
   int idx ;

   argc = ParseLine( sLineCurrent ) ;

   if( argc >= 1 && ( idx = GetIndex( argv[ 0 ] ) ) >= 0 )
   {
      sContinue = sCliTable[idx].pfunc( argc-1 , &argv[1] ) ;
   }
   else
   {
      OutLinefeed() ;
      OutString( "Unrecognized command (enter ? for command list)" ) ;
      OutLinefeed() ;
   }

   return processing ;
}


tBoolean CliQuit( int argc , char** argv ) 
{
   return FALSE ;
}

tBoolean CliHelp( int argc , char** argv ) 
{
   int idx ;
   int idxMin ;
   int idxMax ;

   OutLinefeed() ;

   if( argc > 0 )
   {
      idxMin = GetIndex( argv[0] ) ;
      idxMax = idxMin+1 ;
   }
   else
   {
      idxMin = 0 ;
      idxMax = sTableSize ;
   }

   for( idx = idxMin ; idx < idxMax ; idx++ )
   {
      OutString( sCliTable[idx].help ) ;
      OutLinefeed() ;
      OutLinefeed() ;
   }
   OutLinefeed() ;

   return TRUE ;
}


tVoid CliSetTable( CliTable* table , int size ) 
{
   sCliTable  = table ; 
   sTableSize = size ;
}


tBoolean CliCheck() 
{
   static tBoolean processing = FALSE ;
   static tBoolean bContinue ;
   static tBoolean primed = FALSE ;

   if( !primed )
   {
      CliInit() ;
      primed = TRUE ;
   }

   if( !processing )
   {
      processing = CliGet() ;
   }

   if( processing )
   {
      processing = CliProcess() ;
   }

   bContinue = sContinue ;
   sContinue = TRUE ; /* get ready for next time */

   return bContinue ;
}

tVoid PrintArgs( int argc , char** argv )
{
   int idx ;

   for( idx = 0 ; idx < argc ; idx++ )
   {
      OutInt( idx , sizeof( idx ) ) ;
      OutString( " : " ) ;
      OutString( argv[ idx ] ) ;
      OutLinefeed() ;
   }
}


int CharToInt( char ch )
{
   int val ;

   if( ch >= 'a' )
   {
      val = ch - 'a' + 10 ;
   }
   else if( ch >= 'A' )
   {
      val = ch - 'A' + 10 ;
   }
   else
   {
      val = ch - '0' ;
   }

   return val ;
}


int StringToInt( char* str )
{
   int val = 0 ;
   int mult = 10 ;

   if( ( str[0] == '0' ) && ( str[1] == 'x' ) )
   {
      str += 2 ;
      mult = 16 ;
   }

   while( *str )
   {
      val *= mult ;
      val += CharToInt( *str ) ;
      str++ ;
   }

   return val ;
}


#define LINE_LENGTH 16
tBoolean MemDump( int argc , char** argv )
{
   tByte* ptr ;
   tByte* ptrEnd ;
   int    size ;
   int    linecount = 0 ;
   char   ascii[LINE_LENGTH+1] ;

   ascii[ LINE_LENGTH ] = 0 ; /* Null terminate */
      
   if( argc != 2 )
   {
      return FALSE ;
   }

   size = StringToInt( argv[1] ) ;

   ptr  = (char*)StringToInt( argv[0] ) ;

   ptrEnd = ptr + size ;

   OutLinefeed() ;

   while( ptr < ptrEnd )
   {
      if( linecount == 0 )
      {
         OutHex( (tULong)ptr , 4 ) ;
         OutString( " : " ) ;
      }

      OutHex( *ptr , 1 ) ;

      /* printable characters */
      if( *ptr >= ' ' && *ptr <= '~' )
      {
         ascii[ linecount ] = *ptr ;
      }
      else
      {
         ascii[ linecount ] = '.' ;
      }

      OutString( " " ) ;
      ptr++ ;
      linecount++ ;
      if( linecount == 8 )
      {
         OutString( "  " ) ;
      }
      else if( linecount == 16 ) 
      {
         OutString( "  " ) ;
         OutString( (char*)ascii ) ;

         OutLinefeed() ;
         linecount = 0 ;
      }
   }

   ascii[ linecount ] = 0 ;
   OutString( "  " ) ;
   OutString( (char*)ascii ) ;

   OutLinefeed() ;
   
   return TRUE ;
}

typedef struct tPortParam
{
   tULong addr ;
   tByte* name ;
   tULong size ;
} tPortParam ;

tPortParam PortParam[] =
{
   0x00 , "VENDID  " , 2 ,  /* Vendor ID = 0x1057 (not shown) 2 2 Read 0x1057 */
   0x02 , "DEVID   " , 2 ,  /* Device ID = 0x0006(not shown) 2 2 Read 0x0006 */
   0x04 , "PCICR   " , 2 ,  /* PCI command register 2 2 Read/Write mode-dependent */
   0x06 , "PCISR   " , 2 ,  /* PCI status register 2 2 Read/Bit Reset 0x00A0 */
   0x08 , "REVID   " , 1 ,  /* Revision ID (not shown) 1 1 Read 0xnn */
   0x09 , "PIR     " , 1 ,  /* Standard programming interface 1 1 Read mode-dependent */
   0x0A , "PSCCR   " , 1 ,  /* Subclass code (not shown) 1 1 Read 0x00 */
   0x0B , "PBCCR   " , 1 ,  /* Class code 1 1 Read mode-dependent */
   0x0C , "PLTR    " , 1 ,  /* Cache line size 1 1 Read/Write 0x00 */
   0x0D , "LAT_TIM " , 1 ,  /* Latency timer 1 1 Read/Write 0x00 */
   0x0E , "HDR_TYP " , 1 ,  /* Header type (not shown) 1 1 Read 0x00 */
   0x0F , "BISTCR  " , 1 ,  /* BIST control 1 1 Read 0x00 */
   0x10 , "LM_BAR0 " , 4 ,  /* Local memory base address register 0 4 4 Read/Write 0x0000_0008 */
   0x14 , "PCSRBAR " , 4 ,  /* Peripheral control and status register base address register 4 4 Read/Write 0x0000_0000 */
   0x18 , "LM_BAR1 " , 4 ,  /* Local memory base address register 1 4 4 Read/Write 0x0000_0008 */
   0x2C , "SSVENDID" , 2 ,  /* Subsystem Vendor ID 2 2 Read/Write config setting */
   0x2E , "SSID    " , 2 ,  /* Subsystem ID 2 2 Read/Write config setting */
   0x30 , "EROMBA  " , 4 ,  /* Expansion ROM base address 4 4 Read 0x0000_0000 */
   0x3C , "ILR     " , 1 ,  /* Interrupt line 1 1 Read/Write 0x00 */
   0x3D , "IPR     " , 1 ,  /* Interrupt pin (not shown) 1 1 Read 0x01 */
   0x3E , "MIN_GNT " , 1 ,  /* MIN GNT (not shown) 1 1 Read 0x00 */
   0x3F , "MIN_LAT " , 1 ,  /* MAX LAT (not shown) 1 1 Read 0x00 */
   0x40 , "BUSNUM  " , 1 ,  /* Bus number (not shown) 1 1 Read/Write 0x00 */
   0x41 , "SBUSNUM " , 1 ,  /* Subordinate bus number (not shown) 1 1 Read/Write 0x00 */
   0x44 , "PACR    " , 2 ,  /* PCI general control register 2 2 Read/Write config setting */
   0x46 , "PARBCR  " , 2 ,  /* PCI arbiter control register 2 2 Read/Write 0x0000 */
   0x70 , "PMCAR1  " , 2 ,  /* Power management configuration register 1 (PMCR1) 2 1 or 2 Read/Write 0x00 */
   0x72 , "PMCAR2  " , 1 ,  /* Power management configuration register 2 (PMCR2) 1 1 Read/Write 0x00 */
   0x73 , "ODCR    " , 1 ,  /* Output driver control register 1 1 Read/Write 0xFF */
   0x74 , "CDCR    " , 2 ,  /* CLK driver control register 2 1 or 2 Read/Write 0x0300 */
   0x76 , "MDCR1   " , 1 ,  /* Miscellaneous driver control register 1 1 1 Read/Write 0x00 */
   0x77 , "MDCR2   " , 2 ,  /* Miscellaneous driver control register 2 1 1 Read/Write 0x00 */
   0x78 , "EUMBAR  " , 4 ,  /* Embedded utilities memory block base address register 4 4 Read/Write 0x0000_0000 */
   0x80 , "MSAR1   " , 4 ,  /* Memory starting address registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0x84 , "MSAR2   " , 4 ,  /* Memory starting address registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0x88 , "EMSAR1  " , 4 ,  /* Extended memory starting address registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0x8C , "EMSAR2  " , 4 ,  /* Extended memory starting address registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0x90 , "MEAR1   " , 4 ,  /* Memory ending address registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0x94 , "MEAR2   " , 4 ,  /* Memory ending address registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0x98 , "EMEAR1  " , 4 ,  /* Extended memory ending address  registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0x9C , "EMEAR2  " , 4 ,  /* Extended memory ending address  registers 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0xA0 , "MBER    " , 2 ,  /* Memory bank enable register 1 1 Read/Write 0x00 */
   0xA3 , "PMMR    " , 2 ,  /* Page mode counter/timer 1 1 Read/Write 0x00 */
   0xA8 , "PICR1   " , 4 ,  /* Processor interface configuration 1 4 1, 2, or 4 Read/Write 0x00n4_0010 */
   0xAC , "PICR2   " , 4 ,  /* Processor interface configuration 2 4 1, 2, or 4 Read/Write 0x000C_000C */
   0xB8 , "ECCSBECR" , 1 ,  /* ECC single bit error counter 1 1 Read/Bit Reset 0x00 */
   0xB9 , "ECCSBETR" , 1 ,  /* ECC single bit error trigger register 1 1 Read/Write 0x00 */
   0xC0 , "ERRENR1 " , 1 ,  /* Error enabling register 1 1 1 Read/Write 0x01 */
   0xC1 , "ERRDR1  " , 1 ,  /* Error detection register 1 1 1 Read/Bit Reset 0x00 */
   0xC3 , "BESR    " , 1 ,  /* Processor internal bus error status register 1 1 Read/Bit Reset 0x00 */
   0xC4 , "ERRENR1 " , 2 ,  /* Error enabling register 2 1 1 Read/Write 0x00 */
   0xC5 , "ERRENR2 " , 2 ,  /* Error detection register 2 1 1 Read/Bit Reset 0x00 */
   0xC7 , "BESR    " , 1 ,  /* PCI bus error status register 1 1 Read/Bit Reset 0x00 */
   0xC8 , "ERRENR2 " , 4 ,  /* Processor/PCI error address register 4 1, 2, or 4 Read 0x00 */
   0xD0 , "ERRDR1  " , 4 ,  /* Extended ROM configuration register 1 4 4 Read/Write 0xB5FF_8000 */
   0xD4 , "ERRDR2  " , 4 ,  /* Extended ROM configuration register 2 4 4 Read/Write 0xB5FF_8000 */
   0xD8 , "ERRDR3  " , 4 ,  /* Extended ROM configuration register 3 4 4 Read/Write 0x0C00_000E */
   0xDC , "ERRDR4  " , 4 ,  /* Extended ROM configuration register 4 4 4 Read/Write 0x0800_000E */
   0xE0 , "AMBOR   " , 1 ,  /* Address map B options register 1 1 Read/Write 0xC0 */
   0xE2 , "PEAR    " , 1 ,  /* PLL configuration register 1 1 Read config setting */
   0xF0 , "MCCR1   " , 4 ,  /* MCCR1 4 1, 2, or 4 Read/Write 0xFFn2_0000 */
   0xF4 , "MCCR2   " , 4 ,  /* MCCR2 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0xF8 , "MCCR3   " , 4 ,  /* MCCR3 4 1, 2, or 4 Read/Write 0x0000_0000 */
   0xFC , "MCCR4   " , 4    /* MCCR4 4 1, 2, or 4 Read/Write 0x000_0000 */
} ;

tBoolean RegConfigDump( int argc , char** argv )
{
   int idx ;
   tULong val ;
   tULong addr ;
   tULong diff ;
   
   OutLinefeed() ;
   for( idx = 0 ; idx < sizeof( PortParam ) / sizeof( *PortParam )  ; idx++ )
   {
      OutString( PortParam[idx].name ) ;
      OutString( " : " ) ;
      addr = PortParam[idx].addr & ~0x03 ;
      diff = PortParam[idx].addr - addr ;
      val = PciRegGet( PCIREG_BASE_ADR , addr ) ;
      
      val = ( val >> diff * 8 ) & ( 0xffffffffUL >> ( 4 - PortParam[idx].size ) * 8 ) ;
      
      OutHex( val , PortParam[idx].size ) ;
      OutLinefeed() ;
   }
   
   return TRUE ;
}


tBoolean PciDump( int argc , char** argv )
{
   int idx ;
   tULong devNo ;
   
/*   PciDevProbe() ; */
   
   devNo = StringToInt( argv[0] ) ;
   
   OutLinefeed() ;
   for( idx = 0 ; idx < MAX_PCI_HEADER_REG ; idx++ )
   {
      OutString( GetPciRegname( idx ) ) ;
      OutString( " : " ) ;
      OutHex( ReadAReg( devNo , idx ) , GetPciRegsize( idx ) ) ;
      OutLinefeed() ;
   }
   
   return TRUE ;   
}

char BigEndian();
char BigEndian()
{
  short val = 0x0100 ;
  return *( (char*)&val ) ;
}

tBoolean Test( int argc , char** argv )
{
   OutString( "\nTest\n" ) ;     
   OutLinefeed() ;
   PrintArgs( argc , argv ) ;   

   BigEndian() ? OutString( "BigEndian" ) : OutString( "LittleEndian" ) ;
   OutLinefeed() ;

   return TRUE ;
}


#define PCI_DUMP_HELP            \
   "pci devNo\n\r"               \
   "  pci registers dump\n\r"    \
   "    devNo - device number"
#define RC_HELP                            \
   "rc\n\r"                                \
   "  registers (configuration) dump\n\r"             
#define MEM_DUMP_HELP                   \
   "m location length\n\r"              \
   "  memory dump\n\r"                  \
   "    location - start location\n\r"  \
   "    length   - number of bytes "
#define TEST_HELP                    \
   "t par1 par2\n\r"                 \
   "  test\n\r"                      \
   "    par1 - first parameter\n\r"  \
   "    par2 - second parameter "
#define HELP_HELP    "? <command>\n\r  help"
#define QUIT_HELP    "q\n\r quit"

CliTable tableCli[] =
{
   { "m"   , MemDump       , MEM_DUMP_HELP } ,
   { "rc"  , RegConfigDump , RC_HELP       } ,
   { "pci" , PciDump       , PCI_DUMP_HELP       } ,
   { "t"   , Test          , TEST_HELP     } ,
   { "?"   , CliHelp       , HELP_HELP     } ,
   { "q"   , CliQuit       , QUIT_HELP     } ,
} ;


tVoid CliInit()
{
   int idx ;

   CliSetTable( tableCli , sizeof( tableCli ) / sizeof( *tableCli )  ) ;
}

