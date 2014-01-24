/* PerfTimer.h */

#ifndef PERFTIMER_H
#define PERFTIMER_H

#include "IssDefs.h"

void     PerfTimerClear() ;
void     PerfTimerStart() ;
tULong   PerfTimerGetUsec() ;
tBoolean PerfTimerCapture( char* str ) ;
tBoolean GetNextPerftime( tULong* timeUs , char** string ) ;

tBoolean PerfTimerPop() ;
tBoolean PerfTimerPush( char* str ) ;

#endif /* PERFTIMER_H */
