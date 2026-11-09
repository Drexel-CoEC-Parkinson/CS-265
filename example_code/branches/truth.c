#include <stdio.h>

int main( void )
{
    int vals[] = { 0, 1, -1, 42 } ;
    for( int i = 0 ; i < 4 ; ++i )
    {
        if( vals[i] )
            printf( "%3d is true\n", vals[i] ) ;
        else
            printf( "%3d is false\n", vals[i] ) ;
    }
    printf( "(3 < 5) evaluates to %d\n", 3 < 5 ) ;
    printf( "(3 > 5) evaluates to %d\n", 3 > 5 ) ;
    return 0 ;
}
