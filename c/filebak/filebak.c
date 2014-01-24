// filebak.c
//
// This moduled defines a function, vpCreateBackup, which can be called to 
// create a backup (i.e. - a copy with extension xxx) of a given file.
//
// Also included is a main() routine for creating a standalone program.
//
// To add to Windows Explorer right-click menu add registry key:
//
// HKEY_CLASSES_ROOT\*\Shell\filebak\Command = c:\bin\filebak.exe "%1"
//
// assumming this exe is in c:\bin directory

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

// define FILEBAK_BUILD_STANDALONE for standalone program (i.e. - generate main() ).
#define FILEBAK_BUILD_STANDALONE

#define FULLNAME_LENGTH 1000


#ifndef WIN32

#define DIR_SLASH '/'
#include <dirent.h>

#else // WIN32

#include <io.h>
#include <windows.h>

#define DIR_SLASH '\\'

#define DIR int 

DIR _dir ;
int primed = 0 ;

char _filespec[ FULLNAME_LENGTH ] ;

char _tmpname[ FULLNAME_LENGTH ] ;

struct dirent
{
  char* d_name ;
} _dirent ;



DIR *opendir(const char *dirname)
{
  sprintf( _filespec , "%s\\*" , dirname ) ;
  _dirent.d_name = _tmpname ;

  return &_dir ;
}

int closedir(DIR *dirp)
{
  primed = 0 ;

  return 0 ;
}

struct dirent *readdir(DIR *dirp)
{
  static long handle ;
  struct dirent *ret = &_dirent ;
  int success = 1 ;
  struct _finddata_t finddata ;


  if( primed )
  {
    success = ( _findnext( handle , &finddata ) != -1L ) ? 1 : 0 ;
  }
  else
  {
    handle = _findfirst( _filespec , &finddata ) ;
    success = ( handle != -1L ) ? 1 : 0 ;
    primed = 1 ;
  }

  if( success )
  {
    strcpy( _tmpname , finddata.name ) ;
  }
  else
  {
    ret = 0 ;
  }

  return ret ;
}

int link(const char *oldname, const char *newname)
{
  CopyFile( oldname , newname , 1 ) ;

  return 0 ;
}

#endif // WIN32

// This routine creates a backup copy of filename with extension .xxx where
// xxx is the next available three digit integer.
// 
// params:
//    dirname - directory where file exists (backup also placed here).
//    filename - name of file to backup.
//
void vpCreateBackup( char* dirname , char* filename )
{
  int len ;
  int ch ;
  int match ;
  char newname[ FULLNAME_LENGTH ] ;
  char oldname[ FULLNAME_LENGTH ] ;
  DIR *dir;
  struct dirent *entry;
  int nextidx = 0 ;
  int curridx ;
  char* currname ;

  len = strlen( filename ) ;

  // loop through files in directory
  dir = opendir( dirname ) ;
  if( dir ) 
  {
    while ( ( entry = readdir( dir ) ) != NULL )
    {
      currname = entry->d_name ;
      
      // check if currname is of form "filename.xxx" (where x's are decimal digits)
      
      // first, check if initial len characters are same
      if( !strncmp( filename , currname , len ) )
      {                                    
        // length must be four more then base (i.e ".xxx")
        if( strlen( currname ) == (unsigned)( len + 4 ) )
        {
          // period "." must be next
          if( currname[ len ] == '.' )
          {
            match = 1 ;
    
            // now check for decimal digits (three of them - xxx)
            for( ch = len+1 ; ch <= len+3 ; ch++ )
            { 
              if( ( currname[ ch ] < '0' ) || ( currname[ ch ] > '9' ) )
              {
                match = 0 ; // no match if not decimal digit
                break ;
              }
            }
            
            if( match )
            {
              curridx = atoi( &( currname[len+1] ) ) ;
              nextidx = ( curridx >= nextidx ) ? curridx + 1 : nextidx ;
            }
          }
        }
      }
    }
    
    closedir( dir ) ;
  }
  
  // get full path name
  sprintf( oldname , "%s/%s" , dirname , filename ) ;
  
  // add next extension number
  sprintf( newname , "%s.%3.3d" , oldname , nextidx ) ;
  
  // link (essentially a copy) oldname to newname
  link( oldname , newname ) ;
}

#ifdef FILEBAK_BUILD_STANDALONE

// takes one parameter (the filename with optional path)
// creates backup of filename with next .xxx extension

int main( int argc , char** argv )
{
  char currdir[] = "." ;
  char* filename ;
  char* dirname ;
  char* ptr ;

//  MessageBox( 0 , argv[1] , "test" , MB_OK ) ;

  if( argc == 2 )
  {
    // extract filename and dirname from string
    filename = argv[1] ;
    dirname  = argv[1] ;
        
    // find last backslash
    while( ptr = strchr( filename , DIR_SLASH ) )
    {
      filename = ptr+1 ;
    }
    
    if( filename == dirname )
    {
      dirname = currdir ; // no backslash found, use currdir
    }
    else
    {
      *(filename-1) = 0 ; // null terminate dirname
    }
      
    vpCreateBackup( dirname , filename ) ;
  }
  else
  {
    printf( "\nFormat:\n\n  %s _filename_\n\n" , argv[0] ) ;
  }    
  
  return 1 ;
}

#endif // FILEBAK_BUILD_STANDALONE
