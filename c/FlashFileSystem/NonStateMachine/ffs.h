// ffs.h - Flash File System

#ifndef FFS_H
#define FFS_H

#include "types.h"

#define BLOCK_SIZE    256  // smallest erasable unit
#define NUM_BLOCKS    4
#define MAX_FILE_SIZE 0x100
#define MAX_FILES     64

#define FFS_TOTAL_SIZE  ( NUM_BLOCKS * BLOCK_SIZE )


#define FFS_ERROR (-1)
#define FFS_DEBUG 1

tVoid    FfsDeleteFile( int fileId ) ;                               
tVoid    FfsEraseAll() ;                                             
int      FfsGetNextFileId( tBoolean first ) ;                        
int      FfsGetFileSize( int fileId ) ;
int      FfsGetFreeSpace() ;
int      FfsReadFile( int fileId , tUByte* buff , tULong maxsize ) ;    
int      FfsWriteFile( tUByte* buff , int size ) ;                   
tVoid    FfsInit() ;                   

extern int gTestCount ; // tim_todo TEST - remove

#endif // FFS_H