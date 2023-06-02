#include <stdio.h>

int *get() {

	int val = 10;
	return (int *)val;
}

int main() {
	int *val = get();

	printf("%d\n", *val);
	return 0;
}
