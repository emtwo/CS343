#include <stdio.h>

int main() {
    int frameno = 1;
    void h( int p ) {            // nest routine
        int v1 = 10;

        void g( int p ) {            // nest routine
            int v2 = 100;

            void f( int p ) {            // nest routine
                if ( p > 0 ) f( p - 1 );
                v2 += 1;
                printf( "%d\t%d\t%p\t%d\t%p\tf(%d)\t___\t___\n", frameno, v1, &v1, v2, &v2, p );
                frameno += 1;
            }

            if ( p % 2 == 0 ) f( p - 1 );
            v1 += 1;
            if ( p != 0 ) g( p - 1 );
            printf( "%d\t%d\t%p\t%d\t%p\tg(%d)\t___\n", frameno, v1, &v1, v2, &v2, p );
            frameno += 1;
        }

        if ( p % 2 == 0 ) g( 2 );
        if ( p != 0 ) h( p - 1 );
        printf( "%d\t%d\t%p\t\t\t\th(%d)\t\t\n", frameno, v1, &v1, p );
        frameno += 1;
    }

    printf( "frame#\tv1\t&v1\t\tv2\t&v2\t\trtn(p)\tfrm:v1\tfrm:v2\n"
            "==============================================================\n" );
    h( 3 );
}

