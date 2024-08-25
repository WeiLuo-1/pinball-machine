/* Wei Luo */

#include <stdio.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "psor.h"

bool compare(void *data1, void *data2) {
	int *x = data1, *y = data2;
	bool r = (*x < *y);
	return r;
}

void print(void *data) {
	int *x = data;
	printf("%d\n", *x);
}

bool inverseCompare(void *data1, void *data2) {
	int *x = data1, *y = data2;
	bool r = (*x > *y);
	return r;
}

int main() {
	void *x = NULL;
	ComparisonFunction goesInFrontOf = compare;
	int array[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i = 0; i < 10; i++) {
		int *y = &array[i];
		bool rval = insert(&x, y, goesInFrontOf, 1);
	}
	ComparisonFunction cf = inverseCompare;
	sort(x, cf);
	ActionFunction doThis = print;
	iterate(x, doThis);
	return 0;
}

