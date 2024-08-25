/* Wei Luo */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "altmem.h"
#include "linkedlist.h"

typedef struct Node{
	struct Node *next;
	void *data;
} Node;

//Allocate node
static Node *allocate_node(int text) {
	Node *np;
	static int allocations = 0;
	if (np = alternative_malloc(sizeof(Node))) {
		allocations++;
		if (text) printf("DIAGNOSTIC: %d nodes allocated.\n", allocations);
	} else {
		if (text) printf("ERROR: linkedlist.c: Failed to malloc a Node\n");
	}
	return np;
}

//Insert into a linked list
bool insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, int text) {
	Node *node;
	node = allocate_node(text);
	if (node == NULL) return false;
	node->data = data;
	Node **hp = p2head;
	while (*hp != NULL && !goesInFrontOf(node->data, (*hp)->data)) {
		hp = &((**hp).next);
	}
	node->next = *hp;
	*hp = node;
	return true;
}

//Free node
static void free_node(void *data, int text) {
	static int freed = 0;
	if (data) {
		freed++;
		alternative_free(data);
		if(text) printf("DIAGNOSTIC: %d nodes freed.\n", freed);
	} else {
		if(text) printf("ERROR: tried to free NULL pointer.\n");
	}
}

//Delete nodes from a linked list
int deleteSome(void *p2head, CriteriaFunction mustGo, ActionFunction disposal, int text) {
	Node **hp = p2head;
	Node *holder;
	int counter = 0;
	while (*hp != NULL) {
		if (mustGo((*hp)->data)) {
			counter++;
			holder = *hp;
			*hp = (**hp).next;
			disposal(holder->data);
			free_node(holder, text);
		} else {
			hp = &((**hp).next);
		}
	}
	return counter;
}

//Iterate through the linkedlist and do something
void iterate(void *head, ActionFunction doThis) {
	Node *hp = head;
	while (hp != NULL) {
		doThis(hp->data);
		hp = (*hp).next;
	}
}

//Swap data
static void swap_data(void *data1, void *data2) {
	Node *n1 = data1, *n2 = data2;
	void *temp;
	temp = n1->data;
	n1->data = n2->data;
	n2->data = temp;
}

//Sort the linked list
void sort(void *hptr, ComparisonFunction cf) {
	Node *stopAt = NULL;
	while (hptr != stopAt) {
		Node *hp = hptr;
		while (hp != stopAt) {
			if (hp->next != stopAt && cf(hp->next->data, hp->data)) {
				swap_data(hp, hp->next);
			} else if (hp->next == stopAt) {
				stopAt = hp;
				break;
			}
			hp = (*hp).next;
		}
	}
}

