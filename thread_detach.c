#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void err(int errnum) {
	fprintf(stderr, "error by: %s\n", strerror(errnum));
	_exit(1);
}

void *func(void *arg) {
	printf("thread start...\n");
	int i = 0;
	for (; i < 100; i++) {
		printf("thread %d\n", i);
		sleep(1);
	}

	printf("thread start...\n");
	return NULL;
}

int main() {
	pthread_t t;
	int ret;
	ret = pthread_create(&t, NULL, func, NULL);
	if (0 != ret) err(ret);
	ret = pthread_detach(t);
	if (0 != ret) err(ret);
	sleep(100);
//	ret = pthread_join(t, NULL);
//	if (0 != ret) err(ret);
	return 0;
}
