#include <stdlib.h>
#include "list.h"

#define HEAD connecting_node->next
#define TAIL connecting_node->prev

list list_create() {
	// create the list
	list l = calloc(1, sizeof(struct list));

	// create the connecting_node
	l->connecting_node = calloc(1, sizeof(struct list_node));
	l->connecting_node->value = l;
	l->connecting_node->next = l->connecting_node;
	l->connecting_node->prev = l->connecting_node;
	l->len = 0;

	return l;
}

void list_destroy(list l) {
	list_node n = l->HEAD;
	while (n->value != l) {
		list_node next = n->next;
		free(n);
		n = next;
	}
	free(n);
	free(l);
}

// private
// put n between a and b
// a -> b  :=>  a -> n -> b
void __node_insertBetween(list_node n, list_node a, list_node b) {
	n->prev = a;
	n->next = b;

	a->next = n;
	b->prev = n;
}

// private
// remove n
// n must have an n->prev and n->next
// x -> n -> y  :=>  x -> y
void __node_remove(list_node n) {
	list_node prev = n->prev;
	list_node next = n->next;

	prev->next = next;
	next->prev = prev;
}

void list_push(list l, void* value) {
	list_node n = calloc(1, sizeof(struct list_node));
	__node_insertBetween(n, l->TAIL, l->TAIL->next);
	n->value = value;
	l->len += 1;
}

void* list_peek(list l) {
	if (l->TAIL->value == l) return 0;
	return l->TAIL->value;
}

void* list_pop(list l) {
	if (l->TAIL->value == l)
		return 0;

	list_node n = l->TAIL;
	__node_remove(n);
	l->len -= 1;

	void* value = n->value;
	free(n);
	return value;
}

void list_rpush(list l, void* value) {
	list_node n = calloc(1, sizeof(struct list_node));
	__node_insertBetween(n, l->HEAD->prev, l->HEAD);
	n->value = value;
	l->len += 1;
}

void* list_rpeek(list l) {
	if (l->HEAD->value == l) return 0;
	return l->HEAD->value;
}

void* list_rpop(list l) {
	if (l->HEAD->value == l)
		return 0;

	list_node n = l->HEAD;
	__node_remove(n);
	l->len -= 1;
	
	void* value = n->value;
	free(n);
	return value;
}

void list_enqueue(list l, void* value) {
	list_rpush(l, value);
}

void* list_dequeue(list l) {
	return list_pop(l);
}

void list_foreach(list l, foreach_func func) {
	list_node n = l->HEAD;
	while (n->value != l) {
		list_node next = n-> next;
		func(n->value);
		n = next;
	}
}

void list_foreachWithState(list l, foreachWithState_func func, void* state) {
	list_node n = l->HEAD;
	while (n->value != l) {
		list_node next = n-> next;
		func(state, n->value);
		n = next;
	}
}

int list_len(list l) {
	return l->len;
}

// private function
// get the Nth node from the list
// if n >= the length -1, return the tail
// if n <= 0, return the head
list_node __list_getNthNode(list l, int n) {
	if (l->len != 0) {
		if (n <= 0)
			return l->HEAD;
		else if (n >= l->len - 1)
			return l->TAIL;
		else {
			int curr_index = 0;
			list_node curr = l->HEAD;
			while (curr_index < n) {
				curr_index++;
				curr = curr->next;
			}
			return curr;
		}
	} else {
		return 0;
	}
}

void list_insertAt(list l, int index, void* val) {
	list_node i = __list_getNthNode(l, index);
	if (i == l->HEAD)
		list_rpush(l, val);
	else if (i == l->TAIL)
		list_push(l, val);
	else {
		list_node n = calloc(1, sizeof(struct list_node));
		__node_insertBetween(n, i->prev, i);
		n->value = val;
		l->len += 1;
	}
}

void* list_removeFrom(list l, int index) {
	if (l->len == 0) return 0;

	list_node n = __list_getNthNode(l, index);
	if (n == l->HEAD)
		return list_rpop(l);
	else if (n == l->TAIL)
		return list_pop(l);
	else {
		__node_remove(n);
		void* val = n->value;
		free(n);
		l->len -= 1;
		return val;
	}
}

void* list_getFrom(list l, int index) {
	int len = list_len(l);
	if (len == 0) return 0;

	if (index >= len-1) 
		return list_peek(l);
	int curr_index = 0;
	list_node n = l->HEAD;
	while (curr_index < index) {
		curr_index++;
		n = n->next;
	}
	return n->value;
}

int list_getIndex(list l, void* val) {
	list_node n = l->HEAD;
	int index = 0;
	while (n->value != l) {
		if (n->value == val)
			return index;
		index++;
		n = n->next;
	}
	return -1;
}

void list_removeValue(list l, void* val) {
	int index = list_getIndex(l, val);
	if (index != -1) {
		list_removeFrom(l, index);
	}
}

index_value_pair list_find(list l, find_func func, void* state) {
	list_node n = l->HEAD;
	int index = 0;
	while (n->value != l) {
		list_node next = n-> next;
		func(state, n->value);
		n = next;
		index++;
	}
	if (n->value == l)
		return (index_value_pair){-1, 0};
	return (index_value_pair){index, n->value};
}

#undef HEAD
#undef TAIL