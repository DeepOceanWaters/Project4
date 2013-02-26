
/*__________________________HEADER STUFF______________________________________*/

// includes...
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// defines...
#define NUMTHREADS 8
#define VECLEN 1000000

// structs...
struct data {
	double *a;
	double *b;
	int veclen;
	int offset;
};

// functions...
void *dotprod(void *arg);

/*_________________________END HEADER STUFF___________________________________*/

// global variables...
double sum;
pthread_t threads[NUMTHREADS];
pthread_mutex_t mutex_sum; /* Naming convention: mutex_[var_name] */


int main(int argc, char *argv[])
{
	double *a = (double *) malloc(NUMTHREADS * VECLEN * sizeof(double));
	double *b = (double *) malloc(NUMTHREADS * VECLEN * sizeof(double));
	
	struct data d[NUMTHREADS];
	
	pthread_attr_t attr;
	
	for(int i = 0; i < VECLEN * NUMTHREADS; ++i) {
		a[i] = 1.0;
		b[i] = 1.0;
	}
	
	sum = 0.0;
	
	pthread_mutex_init(&mutex_sum, NULL);
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	// create pthreads
	for(int i = 0; i < NUMTHREADS; ++i) {
		d[i].a = a;
		d[i].b = b;
		d[i].offset = i;
		d[i].veclen = VECLEN;
		pthread_create(&threads[i], &attr, dotprod, (void*) &d[i]);
	}
	
	// destroy attr
	pthread_attr_destroy(&attr);
	
	// wait for threads => like waiting for children
	for(int i = 0; i < NUMTHREADS; ++i)
		pthread_join(threads[i], NULL);
		
	printf("Sum = %f\n", sum);
	free(a);
	free(b);
	pthread_mutex_destroy(&mutex_sum);
	
	return 0;
}

void *dotprod(void *arg)
{
	int start;
	int end;
	int length;
	double *x;
	double *y;
	
	double sub_sum;
	
	struct data *d = (struct data*) arg;
	length = d->veclen;
	start = d->offset * length;
	end = start + length;
	x = d->a;
	y = d->b;
	
	sub_sum = 0.0;
	
	for(int i = start; i < end; ++i)
		sum += x[i] * y[i];
	
	pthread_exit((void*) 0);
	
	return NULL;
}


	      /* This white space is used for viewing pleasure */



/*_____________________________END OF FILE____________________________________*/
