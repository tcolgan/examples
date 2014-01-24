/* cli.h */

#ifndef CLI_H
#define CLI_H

#include "IssTypes.h"

typedef tBoolean (*pfCli)( int argc , char** argv ) ;


typedef struct CliTable
{
   char* command ;
   pfCli pfunc ;
   char* help ;
} CliTable ;

tBoolean CliCheck() ;
tVoid    CliSetTable( CliTable* table , int size ) ;
tBoolean CliHelp( int argc , char** argv ) ;
tBoolean CliQuit( int argc , char** argv ) ;

#endif /* CLI_H */
