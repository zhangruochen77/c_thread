#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int val;
pthread_rwlock_t lock;

void *funr(void *arg) {
	while (1) {
		pthread_rwlock_rdlock(&lock);
		printf("%lu, read %d\n", pthread_self(), val);
		sleep(rand() % 3);
		pthread_rwlock_unlock(&lock);
		sleep(rand() % 3);
	}

	return NULL;
}

void *funw(void *arg) {
	while (1) {
		pthread_rwlock_wrlock(&lock);
		printf("%lu, write %d\n", pthread_self(), ++val);
		sleep(rand() % 3);
		pthread_rwlock_unlock(&lock);
		sleep(rand() % 3);
	}

	return NULL;
}

int main() {
	val = 0;
	pthread_rwlock_init(&lock, NULL);
	pthread_t rt[5];
	pthread_t wt[3];
	int i = 0;
	for (; i < 5; i++) {
		pthread_create(&rt[i], NULL, funr, NULL);
	}
	for (i = 0; i < 3; i++) {
		pthread_create(&wt[i], NULL, funw, NULL);
	}

	for (; i < 5; i++) {
		pthread_join(rt[i], NULL);
	}
	for (i = 0; i < 3; i++) {
		pthread_join(wt[i], NULL);
	}
	
	pthread_rwlock_destroy(&lock);
	return 0;
}
