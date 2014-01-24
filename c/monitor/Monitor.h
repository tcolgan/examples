/*********************************************************
 *
 *  FILE NAME:         Monitor.h
 *
 *
 *  Copyright 2003(c): Innovative Solutions & Support, Inc. as an unpublished work
 *
 *
 * The information contained herein is confidential property of
 * Innovative Solutions & Support, Inc. The use, copying, transfer or
 * disclosure of such information is prohibited except by express
 * written agreement.
 *
 *
 *  HEADER PURPOSE:    
 *      Public information for callers of functions defined in Monitor.c
 *
 *********************************************************/

#ifndef MONITOR_H
#define MONITOR_H


/*********************************************************
 * Includes:
 *********************************************************/

#include "IssTypes.h"


/*********************************************************
 * Global Defines: 
 *********************************************************/


/*********************************************************
 * Global Declarations:
 *********************************************************/


/*********************************************************
 * Global Typedefs:
 *********************************************************/


/*********************************************************
 * Global Macros:  
 *********************************************************/


/*********************************************************
 * Global Function Prototypes:
 *********************************************************/

tVoid CheckMonitor( tVoid ) ;

tWord  GetWord( tUByte* pdata ) ;
tUWord GetUWord( tUByte* pdata ) ;
tULong GetULong( tUByte* pdata ) ;
tULong OutString( tByte* str ) ;  
tULong OutInt( tLong val , tULong len ) ;
tULong OutHex( tULong val , tULong bytes ) ;
tULong OutLinefeed() ;
tULong OutFloat( tLong val , tULong scale , tULong len ) ;


/*********************************************************
 * Global Variables:
 *********************************************************/


#endif /* MONITOR_H */
