#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>

void *th_run(void *arg) {
	int i = (int)arg;
	printf("this is %dth thread, i'm tid = %lu, pid = %d\n", i, pthread_self(), getpid());
	return NULL;
}

int main() {
	pthread_t t;
	int i;
	for (i = 0; i < 5; i++) {
		int ret = pthread_create(&t, NULL, &th_run, (void *)i); // create thread 这个函数执行参数不需要获取地址 本身拿取的就是指针值
		if (0 != ret) { // on error
			fprintf(stderr, "create thread error, %s\n", strerror(ret));
		}
	}

	sleep(1);
	return 0;
}
