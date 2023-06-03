#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void err(int errno) {
	fprintf(stderr, "error, %sn", strerror(errno));
	_exit(1);
}

void *func(void *arg) {
	printf("pthread before sleep\n");
	sleep(10);
	printf("pthread after sleep\n");
	pthread_exit(NULL);
}

int main() {
	pthread_t t;
	int ret;
	ret = pthread_create(&t, NULL, func, NULL);
	if (0 != ret) {
		err(ret);
	}

	sleep(2);
	printf("to cancel thread %lu\n", t);
	ret = pthread_cancel(t);
	if (0 != ret) {
		err(ret);
	}

	return 0;
}
