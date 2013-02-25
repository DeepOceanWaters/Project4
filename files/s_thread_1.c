
/*__________________________HEADER STUFF______________________________________*/

// includes...
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// defines...

// structs...
struct data {
	unsigned long max;
	int thread_id;
};

// functions...
void *start_rout(void *arg);

/*_________________________END HEADER STUFF___________________________________*/



int main(int argc, char *argv[])
{
	struct data d[10];
	pthread_t thread[10];
	
	for(int i = 0; i < 10; i++) {
		d[i].max = i * 2;
		d[i].thread_id = i;
		
		if(0 != pthread_create(&thread[i],
				       NULL,
				       start_rout,
				       (void *) &d[i])) {
			perror("Cannot create thread");
			exit(EXIT_FAILURE);	
		}
	}
	
	for(int i = 0; i < 10; i++)
		pthread_join(thread[i], NULL);
	
	return 0;
}

void *start_rout(void *arg)
{
	struct data *d = (struct data*) arg;
	int max = d->max;
	int thread_id = d->thread_id;
	
	for(int i = 0; i < max; i++)
		printf("%d.%i: Hello, World\n", thread_id, i);
	return NULL;
}

	      /* This white space is used for viewing pleasure */



/*_____________________________END OF FILE____________________________________*/
