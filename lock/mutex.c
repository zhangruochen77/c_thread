#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mu; // 定义一把锁

void *func(void * arg) {
	while (1) {
		pthread_mutex_lock(&mu); // 上锁
		printf("hello ");
		sleep(rand() % 3);
		printf("world\n");
		pthread_mutex_unlock(&mu); // 解锁
		sleep(rand() % 3);
	}
}

int main() {
	pthread_mutex_init(&mu, NULL); // 初始化
	srand(time(NULL));
	pthread_t t;
	pthread_create(&t, NULL, func, NULL);

	while (1) {
		pthread_mutex_lock(&mu); // 上锁
		printf("HELLO ");
		sleep(rand() % 3);
		printf("WORLD\n");
		pthread_mutex_unlock(&mu); // 解锁
		sleep(rand() % 3);
	}

	pthread_mutex_destory(&mu); // 销毁一把锁
	
	return 0;
}
