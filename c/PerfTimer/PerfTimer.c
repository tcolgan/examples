/* PerfTimer.c */


#include "Clock.h" /* for CLOCK_FREQUENCY */

#define FREQUENCY_MHZ (CLOCK_FREQUENCY/1000000)
#define MAX_TIMES 5000

#include "PerfTimer.h"

struct 
{
  char*  str ;  
  tULong TimeUs ;
} Timers[ MAX_TIMES ] ;

typedef unsigned long long tInt64 ;

static tInt64 sStartTicks ;
static int idxTimer = 0 ;
static tBoolean record = TRUE ;
static tBoolean full = FALSE ;

#define MAX_STACK 30 
static int idxStack = 0 ;
char* PerftimerStack[ MAX_STACK ] ;

static tVoid GetTbrTicks(tULong* pTbrUpper, tULong* pTbrLower) ;
static tInt64 GetTicks() ;


asm tVoid GetTbrTicks(tULong* pTbrUpper, tULong* pTbrLower)
{
#pragma unused (pTbrUpper, pTbrLower)
    /********************************************************* 
      r3 is addr for storing TBR Upper
      r4 is addr for storing TBR Lower
    **********************************************************/
    nofralloc

    issGetTbrTicks:  

    /********************************************************* 
      Get time base register values in r5 (tbu) and r6 (tbl).
      Value read from tbl is valid only if value in tbu does
      not change during time period when reading timer data.
      To avoid sel-inconsistent data, tbr and tbl must be read
      as shown below:
          read tbu
          read tbl
          read tbu again
          if tbu has changed, read tbl again
    **********************************************************/
    mftbu  r7
    mftb   r6
    mftbu  r5
    cmplw  cr1,r7,r5
    beq    cr1,issGetTbr01
    mftb   r6

    issGetTbr01:
    stw    r5,0(r3)
    stw    r6,0(r4)

    blr
}

tInt64 GetTicks()
{
  tULong TbrUpper ; 
  tULong TbrLower ;
 
  GetTbrTicks( &TbrUpper , &TbrLower ) ;
  
  return ( (tInt64)TbrUpper ) * 0x100000000 + TbrLower ;
}

tBoolean GetNextPerftime( tULong* timeUs , char** string )
{
   static int idx = 0 ;
   tBoolean data_available = TRUE ;

   if( record )
   {
      record = FALSE ;
      idx = full ? idxTimer : 0 ;
   }

   if( ( full && idx < MAX_TIMES ) || idxTimer > idx )
   {
      *timeUs = Timers[ idx ].TimeUs  ;
      *string = Timers[ idx ].str     ;  

      idx++ ;

      if( full && ( idx == MAX_TIMES ) )
      {
         full = FALSE ;
         idx = 0 ;
      }

   }
   else
   {
      idxTimer = 0 ;      
      idx = 0 ;
      data_available = FALSE ;
      record = TRUE ;
   }

   return data_available ;
}

void PerfTimerClear()
{
  sStartTicks = GetTicks() ;
}

void PerfTimerStart()
{
  for( idxTimer = 0 ; idxTimer < MAX_TIMES ; idxTimer++ )
  {
      Timers[ idxTimer ].TimeUs = 0 ;
      Timers[ idxTimer ].str    = 0 ;  
  }
  idxTimer = 0 ;
  sStartTicks = GetTicks() ;
}

tULong PerfTimerGetUsec()
{
  tInt64 Ticks ;
  
  Ticks = GetTicks() - sStartTicks ;
  
  return (tULong)( ( 4 * Ticks ) / FREQUENCY_MHZ ) ;
}

tBoolean PerfTimerCapture( char* str )
{
   if( !record  )
   {
      return FALSE ;
   }

   Timers[ idxTimer ].TimeUs = PerfTimerGetUsec() ;
   Timers[ idxTimer ].str    = str ;

   idxTimer++ ;

   if( idxTimer >=  MAX_TIMES )
   {
      idxTimer = 0 ;
      full = TRUE ;
   }

   return TRUE ;
}

tBoolean PerfTimerPop()
{
   tBoolean success = FALSE ;

   if( idxStack )
   {
      idxStack-- ;
   }

   return PerfTimerCapture( PerftimerStack[ idxStack - 1 ] ) ;
}

tBoolean PerfTimerPush( char* str )
{
   if( idxStack < MAX_STACK-1 )
   {
      PerftimerStack[ idxStack ] = str ;
      idxStack++ ;
   }

   return PerfTimerCapture( str ) ;
}

