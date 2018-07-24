#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "threadpool.h"

void *mytask(void *arg)
{
	int id = *(int*)arg;
	free(arg);
	printf("%X thread execute %d task\n", pthread_self(), id);
	sleep(1);
}

int main( void )
{
	threadpool_t pool;

	threadpool_init(&pool, 3);

	for (int i=0; i<10; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		threadpool_add(&pool, mytask, p);
	}

	sleep(15);
	// threadpool_destroy(&pool);
}
