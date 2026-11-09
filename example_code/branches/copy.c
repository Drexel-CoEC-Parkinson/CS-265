#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
    if( argc != 3 )
    {
        fprintf( stderr, "usage: %s src targ\n", argv[0] ) ;
        return 1 ;
    }
    FILE *fin = fopen( argv[1], "rb" ) ;
    if( fin == NULL ) { perror( argv[1] ) ; return 1 ; }
    FILE *fout = fopen( argv[2], "wb" ) ;
    if( fout == NULL ) { perror( argv[2] ) ; fclose( fin ) ; return 1 ; }

    int c ;
    while( (c = getc( fin )) != EOF )
        putc( c, fout ) ;

    fclose( fin ) ;
    fclose( fout ) ;
    return 0 ;
}
