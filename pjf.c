#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *func(void *arg) {
	int *p = malloc(sizeof(int));
	*p = 1;
	return (void *)p;
}

int main() {
	pthread_t pids[5];
	int i, ret;
	for (i = 0; i < 5; i++) {
		ret = pthread_create(&pids[i], NULL, func, NULL);
		if (0 != ret) {
			fprintf(stderr, "create error, %s\n", strerror(ret));
			_exit(0);
		}
	}
	int *p;

	for (i = 0; i < 5; i++) {
		ret = pthread_join(pids[i], (void **)&p);
		if (0 != ret) {
			fprintf(stderr, "join error, %s\n", strerror(ret));
			_exit(1);
		}

		printf("join get pid = %d\n", *p);
		free(p);
	}

	return 0;
}
