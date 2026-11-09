#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void usage( void )
{
    fprintf( stderr, "usage: opts [-c] [-o file] [-h]\n" ) ;
}

int main( int argc, char* argv[] )
{
    int opt ;            /* int, not char -- getopt returns -1 at the end */
    bool bChocolate = false, bStdout = true ;
    char *fn = NULL ;

    while( (opt = getopt( argc, argv, "co:hH" )) != -1 )
    {
        switch( opt )
        {
            case 'c' :
                bChocolate = true ;
                break ;
            case 'o' :
                bStdout = false ;
                fn = strdup( optarg ) ;
                break ;
            case 'H' : /* fall through */
            case 'h' : /* fall through */
            case '?' :
                usage() ;
                break ;
            default :
                fprintf( stderr, "Bad option: %c . Exiting.\n", opt ) ;
                usage() ;
                exit( 1 ) ;
        }
    }
    printf( "chocolate=%d stdout=%d file=%s\n", bChocolate, bStdout, fn ? fn : "(none)" ) ;
    free( fn ) ;
    return 0 ;
}

