#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t t1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t t2 = PTHREAD_MUTEX_INITIALIZER;

void *fun1(void *arg) {
	pthread_mutex_lock(&t1);
	printf("p1 get lock1\n");
	sleep(1);
	pthread_mutex_lock(&t2);
	printf("p1 get lock2\n");
}

void *fun2(void *arg) {
	pthread_mutex_lock(&t2);
	printf("p2 get lock2\n");
	sleep(1);
	pthread_mutex_lock(&t1);
	printf("p2 get lock1\n");
}

int main () {
	pthread_t p1, p2;
	pthread_create(&p1, NULL, fun1, NULL);
	pthread_create(&p2, NULL, fun2, NULL);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_mutex_destroy(&t1);
	pthread_mutex_destroy(&t2);
	return 0;
}
