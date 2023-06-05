#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_pro = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_con = PTHREAD_COND_INITIALIZER;
int val[5];

void *pro(void *arg) {
	int i = 0;
	while (1) {
		pthread_mutex_lock(&lock);
		if (0 != val[i]) { // 产品已经满了 等待
			pthread_cond_wait(&cond_pro, &lock);
		}
		int v = rand() + 1;
		printf("product %d\n", v);
		val[i] = v;
		i = (i++) % 5;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond_con);

		sleep(rand() % 3);
	}
}

void *con(void *arg) {
	int i = 0;
	while (1) {
		pthread_mutex_lock(&lock);
		if (0 == val[i]) { // 没有产品 等待
			pthread_cond_wait(&cond_con, &lock);
		}
		int v = val[i];
		val[i] = 0;
		printf("consume %d\n", v);
		i = (i++) % 5;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond_pro);

		sleep(rand() % 3);
	}
}

int main() {
	srand(time(NULL));
	pthread_t t1, t2;
	pthread_create(&t1, NULL, pro, NULL);
	pthread_create(&t2, NULL, con, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	pthread_mutex_destroy(&lock);
	pthread_cond_broadcast(&cond_pro);
	pthread_cond_broadcast(&cond_con);

	return 0;
}
