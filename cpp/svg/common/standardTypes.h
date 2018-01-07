#ifndef STANDARDTYPES_H
#define STANDARDTYPES_H
/* =============================================================================
**
**     Copyright (c) 2004-2006 InterDigital Communications Corporation
**
**                      All rights reserved
** 
**  This software embodies materials and concepts that are confidential
**  to InterDigital Communications Corporation.  This information is made
**  available solely pursuant to the terms of a written license agreement
**  with InterDigital Communications Corporation.
**
** =============================================================================
** =============================================================================
**
** Revision Information :
**    File name: standardTypes.h
**    Version:   3.0
**    Date:      
**
** =============================================================================
**
** Project: 
** Block:   
** =============================================================================
** Contents:  standard types
**
** =============================================================================
** References:  C/C++ coding guidelines
**
** Notes: 
** 
** =============================================================================
** History:
**
** Date       Author  Comment
** ---------- ------- ----------------------------------------------------------
** -          -       Managed via ClearCase
** =============================================================================
*/


/*******************************************************************************
 *   Constant Definition
 *******************************************************************************/

#ifndef NULL
#define NULL 0
#endif


/*
 * Use STATIC for static functions.  During debug, this definition may be changed to
 * #define STATIC (null definition)to permit increased visibility in the debugger
 */

#ifndef STATIC
#define STATIC static
#endif


/*******************************************************************************
 *   Type Definition
 *******************************************************************************/

#ifdef __arm
typedef signed char    Int8;
typedef signed short   Int16;
typedef signed int     Int32;
#else
typedef char           Int8;
typedef short          Int16;
typedef int            Int32;
#endif
typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef float   Float32;
typedef double  Float64;

#ifdef FALSE
#undef FALSE
#endif

#ifdef TRUE
#undef TRUE
#endif

typedef enum
{
    FALSE = 0,
    TRUE
} Bool;

/* If using MICROSOFT C (predefined macro by MSC++ V6.0 compiler.) */
#ifdef _MSC_VER
typedef unsigned __int64 Uint64;
typedef __int64 Int64;
#else
typedef unsigned long long Uint64;
typedef long long Int64;
#endif

/*******************************************************************************
 *   Macro Definitions
 *******************************************************************************/

#define STRING_MATCH            0
#define SIZEOF_ARRAY_ELEMENT(a) sizeof( a[0] )
#define NUM_ARRAY_ELEMENTS(a)   ( sizeof( a ) / SIZEOF_ARRAY_ELEMENT(a) )
#define MAX_ARRAY_INDEX(a)      ( NUM_ARRAY_ELEMENTS( a ) - 1 )


/*******************************************************************************
 *   External Variable Definition
 *******************************************************************************/


/*******************************************************************************
 *   Function Prototype Definition
 *******************************************************************************/


/****************************** End of File ************************************/
#endif /* STANDARDTYPES_H */
