#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>

void *th_run(void *arg) {
	printf("this is run thread\n");

	return NULL;
}

int main() {
	pthread_t t;
	int i = 1;

	pthread_create(&t, NULL, &th_run, (void *)i);

	sleep(1);
	return 0;
}
