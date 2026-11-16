#include <stdio.h>

void print( float a[], int n, FILE *ofile )
{
    for( int i=0; i<n; ++i )
        fprintf( ofile, "%f ", a[i] ) ;
    fprintf( ofile, "\n" ) ;
}

void addPhi( float *a, int n )
{
    for( int i=0; i<n; ++i, ++a )
        *a += 1.61803398 ;
}

int main( void )
{
    float vals[3] = { 1.0, 2.0, 3.0 } ;

    print( vals, 3, stdout ) ;
    addPhi( vals, 3 ) ;
    print( vals, 3, stdout ) ;
    print( vals, 3, stderr ) ;
    return 0 ;
}
