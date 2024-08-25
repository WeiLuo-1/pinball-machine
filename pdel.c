/* Wei Luo */

#include <stdio.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "pdel.h"

bool compare(void *data1, void *data2) {
	int *x = data1, *y = data2;
	bool r = (*x < *y);
	return r;
}

bool under_five(void *data) {
	int *x = data;
	bool r = (*x < 5);
	return r;
}

void print(void *data) {
	int *x = data;
	printf("%d\n", *x);
}

int main() {
	void *x = NULL;
	ComparisonFunction goesInFrontOf = compare;
	int array[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i = 0; i < 10; i++) {
		int *y = &array[i];
		bool rval = insert(&x, y, goesInFrontOf, 1);
	}
	CriteriaFunction mustGo = under_five;
	ActionFunction disposal = print;
	int num = deleteSome(&x, mustGo, disposal, 1);
	printf("%d numbers deleted(expect 5)\n", num);
	return 0;
}

