#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main( int argc, char * argv[] ) {
    //the two intervals extrema
    const double a = 0.0;
    const double b = 1.0;

    //granularity of partition of the interval
    const int N = 1e7;
    
    //the height of the sub-interval, also the step size of the summation
    const double height = (b-a)/N;

    //variable to store our proxy of pi
    double pi_approx = 0;

    double tstart = omp_get_wtime();
    
    #pragma omp parallel
    {   
        //print of no. threads is executed single thread w/o barrier
        #pragma omp single nowait
        {
            fprintf(stdout,"Num threads: %d\n", omp_get_num_threads());
        }


        int i;

        //partial pi is accumulator for the infrathread computation of pi
        double partial_pi = 0;

        #pragma omp for schedule(static)
        for(i=0; i<N; i++){
            //the midpoint of the subinterval
            double midpoint = (a + i*height + height/2.0);
            //approximation of f at the midpoint
            double f_approx = 1.0 / (1.0 + midpoint*midpoint);
            //rectangle area for current subinterval
            double rec_area = height*f_approx;
            //add area of rectangle
            partial_pi += rec_area;
        }
        //accumulation with critical
        #pragma omp critical
            pi_approx += partial_pi;
        
    }  
    

    pi_approx *= 4;

    double tend = omp_get_wtime();
    fprintf(stdout, "time: %f\n", tend-tstart);
    fprintf( stdout, "pi approx: %.6f\n", pi_approx );

    return 0;
}