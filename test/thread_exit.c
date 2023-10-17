#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_hello(void *arg) {
	printf("Hello World! It's me, thread #%ld!\n", (long)arg);
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[5];
	int rc;
	long t;

	for (t = 0; t < 5; t++) {
		printf("Creating thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
		if (rc) {
			printf("ERROR: return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	pthread_exit(NULL);
	return 0;
}
