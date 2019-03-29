#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void print_usage( int * a, int N, int nthreads ) {

	int tid, i;
	for( tid = 0; tid < nthreads; ++tid ) {

		fprintf( stdout, "%d: ", tid );

		for( i = 0; i < N; ++i ) {

			if( a[ i ] == tid) fprintf( stdout, "*" );
			else fprintf( stdout, " ");
		}
		printf("\n");
	}
}

int main( int argc, char * argv[] ) {

	const int N = 100;
	int a[N];
	int thread_id = 0;
	//int nthreads = 1;
	
	#pragma omp parallel private (thread_id)
	{
		int n_threads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();
		//int ist_x_thread = N / n_threads;
		//int start = ist_x_thread * thread_id;
		//int end = start + ist_x_thread;
		int i;
		#pragma omp for schedule (dynamic)
		for(i = 0; i < N; ++i) { 
			a[i] = thread_id;
		}
		//TODO in single thread
		#pragma omp single nowait
		{
			print_usage(a,N,n_threads);
		}
	}	

	return 0;
}
