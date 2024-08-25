/* Wei Luo */

#include <stdio.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "pins.h"

bool goesInfrontOf(void *data1, void *data2) {
	int *x = data1, *y = data2;
	bool r = (*x < *y);
	return r;
}

bool alwaysTrue(void *data) {
	return true;
}

void print(void *data) {
	int *x = data;
	printf("%d\n", *x);
}

int main() {
	void *x = NULL;
	int p = 66;
	int *y = &p;
	ComparisonFunction z = goesInfrontOf;
	bool rval = insert(&x, y, z, 1);
	CriteriaFunction mustGo = alwaysTrue;
	ActionFunction disposal = print;
	int num = deleteSome(&x, mustGo, disposal, 1);
	return 0;
}

