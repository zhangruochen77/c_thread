#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>

void *th_run(void *arg) {
	printf("this is run thread\n");
	int val = 100;
	pthread_exit((void *) val);
}

int main() {
	pthread_t t;

	pthread_create(&t, NULL, &th_run, NULL);

	sleep(1);
	int ret;
	int r = pthread_join(t, (void **)ret);
	if (0 != r) {
		fprintf(stderr, "pthread_join err %s\n", strerror(r));
		_exit(1);
	}
	printf("join get val %d\n", ret);

	return 0;
}
