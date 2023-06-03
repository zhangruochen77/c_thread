#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

struct data {
	pthread_t tid;
	char msg[20];
};

void *func(void *arg) {
	struct data *d;
	d = malloc(sizeof(d));
	d->tid = pthread_self();
	strcpy(d->msg, "hello world");

	pthread_exit((void *)d);
}

int main() {
	pthread_t t;
	int ret = pthread_create(&t, NULL, func, NULL);
	if (-1 == ret) {
		fprintf(stderr, "create error, %s\n", strerror(ret));
		_exit(1);
	}
	
	struct data *d;
	ret = pthread_join(t, (void **)&d);
	if (-1 == ret) {
		fprintf(stderr, "join error, %s\n", strerror(ret));
		_exit(1);
	}
	
	printf("get thread val = %s, pid = %lu\n", d->msg, d->tid);
	return 0;
}
