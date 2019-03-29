#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv[] ) {

    //the two intervals extrema
    const double a = 0.0;
    const double b = 1.0;

    //granularity of partition of the interval
    const int N = 100000;
    
    //the height of the sub-interval, also the step size of the summation
    const double height = (b-a)/N;

    
    //variable to store our proxy of pi
    double pi_approx = 0;

    int i;
    for(i=0; i<N; i++){
        //the midpoint of the subinterval
        double midpoint = (a + i*height + height/2.0);
        //approximation of f at the midpoint
        double f_approx = 1.0 / (1.0 + midpoint*midpoint);
        //add area of rectangle
        pi_approx += height*f_approx;
    }

    pi_approx *= 4;
    fprintf( stdout, "pi approx: %.6f\n", pi_approx );

    return 0;
}