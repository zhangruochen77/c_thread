#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>

void *th_run(void *arg) {
	int i = *((int *)arg);
	printf("this is %dth thread\n", i++);
	return NULL;
}

int main() {
	pthread_t t;
	int i;
	for (i = 0; i < 5; i++) {
		int ret = pthread_create(&t, NULL, &th_run, (void *)&i); // 参数取地址 拿到共享数据地址信息
		if (0 != ret) { // on error
			fprintf(stderr, "create thread error, %s\n", strerror(ret));
			_exit(1);
		}
		usleep(1);
	}

	sleep(1);
	printf("main get i %d\n", i);
	return 0;
}
