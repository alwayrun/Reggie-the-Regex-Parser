#include "list-test.h"

////
// test void list_push(list)

result test_list_push() {
	int passed = 0;
	char* description = "list_push(list, void*)";

	list l = list_create();
	list_push(l, &42);

	passed = is_equal(list_len(l), 1);

	list_destroy(l);

	return (result){passed, description};
}

////
// test int list_len(list);

result test_list_len_NoNodes() {
	int passed = 0;
	char* description = "list_len(list) : NoNodes CASE";

	list l = list_create();

	passed = is_equal(list_len(), 0);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_len_OnePushed() {
	int passed = 0;
	char* description = "list_len(list) : OnePushed CASE";

	list l = list_create();
	list_push(l, &42);

	passed = is_equal(list_len(l), 1);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_len_OnePushedThenPoped() {
	int passed = 0;
	char* description = "list_len(list) : OnePushedThenPoped CASE";

	list l = list_create();
	list_push(l, &42);
	list_pop(l);

	passed = is_equal(list_len(l), 0);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_len_OnePushedThenInsertAt0() {
	int passed = 0;
	char* description = "list_len(list) : OnePushedThenInsertAt0 CASE";

	list l = list_create();
	list_push(l, &42);
	list_insertAt(l, 0, &7);

	passed = is_equal(list_len(l), 2);

	list_destroy(l);

	return (result){passed, description};
}

////
// test void* list_peek(list)

result test_list_peek_EmptyList() {
	int passed = 0;
	char* description = "list_peek(list) : EmptyList CASE";

	list l = list_create();

	passed = is_equal(list_peek(l), 0);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_peek_OnePushed() {
	int passed = 0;
	char* description = "list_peek(list) : OnePushed CASE";

	list l = list_create();
	int* value = &42;
	list_push(l, value);

	passed = is_equal(list_peek(l), value);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_peek_TwoPushed() {
	int passed = 0;
	char* description = "list_peek(list) : TwoPushed CASE";

	list l = list_create();
	int* value = &42;
	list_push(l, &7);
	list_push(l, value);

	passed = is_equal(list_peek(l), value);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_peek_TwoPushedOnePoped() {
	int passed = 0;
	char* description = "list_peek(list) : TwoPushedOnePoped CASE";

	list l = list_create();
	int* value = &42;
	list_push(l, value);
	list_push(l, &7);
	list_pop(l);

	passed = is_equal(list_peek(l), value);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_peek_OnePushedOnePoped() {
	int passed = 0;
	char* description = "list_peek(list) : OnePushedOnePoped CASE";

	list l = list_create();
	list_push(l, &42);
	list_pop(l);


	passed = is_equal(list_peek(l), 0);

	list_destroy(l);

	return (result){passed, description};
}

////
// test void* list_pop(list)

result test_list_pop_EmptyList() {
	int passed = 0;
	char* description = "list_pop(list) : EmptyList CASE";

	list l = list_create();
	list_pop(l);

	passed = is_equal(list_peek(l), 0) && is_equal(list_len(l), 0);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_pop_PopOne() {
	int passed = 0;
	char* description = "list_pop(list) : PopOne CASE";

	list l = list_create();
	list_push(l, &42);
	list_pop(l);

	passed = is_equal(list_peek(l), 0);

	list_destroy(l);

	return (result){passed, description};
}

////
// test void list_insertAt(list, int, void*)

result test_list_insertAt_InsertAt1WithLen0() {
	int passed = 0;
	char* description = "list_insertAt(list, int, void*) : InsertAt1WithLen0 CASE";

	list l = list_create();
	int* value = &42;
	list_insertAt(l, 1, value);

	passed = is_equal(list_peek(l), value) && is_equal(list_len(l), 1);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_insertAt_InsertAtNegative1WithLen0() {
	int passed = 0;
	char* description = "list_insertAt(list, int, void*) : InsertAtNegative1WithLen0 CASE";

	list l = list_create();
	int* value = &42;
	list_insertAt(l, -1, value);

	passed = is_equal(list_peek(l), value) && is_equal(list_len(l), 1);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_insertAt_InsertAt1WithLen1() {
	int passed = 0;
	char* description = "list_insertAt(list, int, void*) : InsertAt1WithLen1 CASE";

	list l = list_create();
	int* value0 = &42;
	int* value1 = &7;
	list_push(l, value0);
	list_insertAt(l, 1, value1);

	passed = is_equal(list_peek(l), value1) && 
			 is_equal(list->head->value, value0) && 
			 is_equal(list_len(l), 2);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_insertAt_InsertAtNegative1WithLen1() {
	int passed = 0;
	char* description = "list_insertAt(list, int, void*) : InsertAtNegative1WithLen1 CASE";

	list l = list_create();
	int* value0 = &42;
	int* value1 = &7;
	list_push(l, value0);
	list_insertAt(l, -1, value1);

	passed = is_equal(list_peek(l), value0) && 
			 is_equal(list->head->value, value1) && 
			 is_equal(list_len(l), 2);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_insertAt_InsertAt0WithLen1() {
	int passed = 0;
	char* description = "list_insertAt(list, int, void*) : InsertAt0WithLen1 CASE";

	list l = list_create();
	int* value0 = &42;
	int* value1 = &7;
	list_push(l, value0);
	list_insertAt(l, 0, value1);

	passed = is_equal(list_peek(l), value0) && 
			 is_equal(list->head->value, value1) && 
			 is_equal(list_len(l), 2);

	list_destroy(l);

	return (result){passed, description};
}

////
// test void* list_removeFrom(list, int)

result test_list_removeFrom_RemoveFrom0WithLen0() {
	int passed = 0;
	char* description = "list_removeFrom(list, int) : RemoveFrom0WithLen0 CASE";

	list l = list_create();

	passed = is_equal(list_removeFrom(l, 0), 0);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_removeFrom_RemoveFrom1WithLen0() {
	int passed = 0;
	char* description = "list_removeFrom(list, int) : RemoveFrom1WithLen0 CASE";

	list l = list_create();

	passed = is_equal(list_removeFrom(l, 1), 0);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_removeFrom_RemoveFrom0WithLen1() {
	int passed = 0;
	char* description = "list_removeFrom(list, int) : RemoveFrom0WithLen1 CASE";

	list l = list_create();
	int* value = &42;
	list_push(l, value);

	passed = is_equal(list_removeFrom(l, 0), value) &&
			 is_equal(list_len(l), 0);

	list_destroy(l);

	return (result){passed, description};
}

result test_list_removeFrom_RemoveFrom0WithLen2() {
	int passed = 0;
	char* description = "list_removeFrom(list, int) : RemoveFrom0WithLen2 CASE";

	list l = list_create();
	int* value1 = &42;
	int* value0 = &7;
	list_push(l, value0);
	list_push(l, value1);

	passed = is_equal(list_removeFrom(l, 0), value0) &&
			 is_equal(list_len(l), 1) &&
			 is_equal(list_peek(l), value1);

	list_destroy(l);

	return (result){passed, description};
}

////
// main function and test list definition

static tests TESTS = {
	// test void list_push(list, void*)
	&test_list_push,

	// test int list_len(list)
	&test_list_len_NoNodes,
	&test_list_len_OnePushed,
	&test_list_len_OnePushedThenPoped,
	&test_list_len_OnePushedThenInsertAt0,

	// test void* list_peek(list)
	&test_list_peek_EmptyList,
	&test_list_peek_OnePushed,
	&test_list_peek_TwoPushed,
	&test_list_peek_TwoPushedOnePoped,
	&test_list_peek_OnePushedOnePoped,

	// test void* list_pop(list)
	&test_list_pop_EmptyList,
	&test_list_pop_PopOne,

	// test void list_insertAt(list, int, void*)
	&test_list_insertAt_InsertAt1WithLen0,
	&test_list_insertAt_InsertAtNegative1WithLen0,
	&test_list_insertAt_InsertAt1WithLen1,
	&test_list_insertAt_InsertAtNegative1WithLen1,
	&test_list_insertAt_InsertAt0WithLen1,

	// test void* list_removeFrom(list, int)
	&test_list_removeFrom_RemoveFrom0WithLen0,
	&test_list_removeFrom_RemoveFrom1WithLen0,
	&test_list_removeFrom_RemoveFrom0WithLen1,
	&test_list_removeFrom_RemoveFrom0WithLen2,
	
	0
};

int main(int argc, char** argv) {
	run_tests(TESTS);
	return 0;
}