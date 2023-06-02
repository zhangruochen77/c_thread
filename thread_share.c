#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>

int SHARE_VAL = 0;

void *th_run(void *arg) {

	printf("share val = %d\n", SHARE_VAL);
	SHARE_VAL += 100;
	return NULL;
}

int main() {
	pthread_t t;
	int i = 1;
	printf("befor create thread share val = %d\n", SHARE_VAL);
	pthread_create(&t, NULL, &th_run, (void *)i);

	sleep(1);
	printf("after create thread share val = %d\n", SHARE_VAL);
	return 0;
}
