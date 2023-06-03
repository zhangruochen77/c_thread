#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
/**
* 要杀死一个线程 需要线程进入保存点
* 也就是说 线程需要进入到达内核状态
* 才能够接受到杀死的信息 否则不会被杀死
*/
void err(int errno) {
	fprintf(stderr, "error, %sn", strerror(errno));
	_exit(1);
}

void *func(void *arg) {
	printf("pthread before sleep\n");
	while (1) {
		
	}
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
