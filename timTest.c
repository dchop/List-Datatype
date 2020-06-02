#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static int errors = 0;
static bool passed = true;
// Macro for custom testing; does exit(1) on failure.
#define CHECK(condition) do{ \
    if (!(condition)) { \
        printf("ERROR: %s (@%d): failed condition \"%s\"\n", __func__, __LINE__, #condition); \
        errors++;\
    }\
} while(0)

static bool initArr = false;
static int arr[LIST_MAX_NUM_NODES] = {0};

// Generate array with ascending values and return the item at any index
void* getArr(int idx) {
    if (idx > LIST_MAX_NUM_NODES) {
        return NULL;
    }
    if (!initArr) {
        for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
            arr[i] = i;
        }
        initArr = true;
    }
    void* ptr = &arr[idx];
    return ptr;
}

// For checking the "free" function called
static int complexTestFreeCounter = 0;
static void complexTestFreeFn(void* pItem) 
{
    CHECK(pItem != NULL);
    complexTestFreeCounter++;
}

// For searching
static bool itemEquals(void* pItem, void* pArg) 
{
    return (pItem == pArg);
}

static void sampleTest()
{
    // Empty list
    List* pList = List_create();
    CHECK(pList != NULL);
    CHECK(List_count(pList) == 0);

    // Add 
    int added = 41;
    CHECK(List_add(pList, &added) == 0);
    CHECK(List_count(pList) == 1);
    CHECK(List_curr(pList) == &added);

    // Insert
    int inserted = 42;
    CHECK(List_insert(pList, &inserted) == 0);
    CHECK(List_count(pList) == 2);
    CHECK(List_curr(pList) == &inserted);
    
    // Prepend
    int prepended = 43;
    CHECK(List_prepend(pList, &prepended) == 0);
    CHECK(List_count(pList) == 3);
    CHECK(List_curr(pList) == &prepended);
    
    // Append
    int appended = 44;
    CHECK(List_append(pList, &appended) == 0);
    CHECK(List_count(pList) == 4);
    CHECK(List_curr(pList) == &appended);
    
    // Next through it all (from before list)
    CHECK(List_first(pList) == &prepended);
    CHECK(List_prev(pList) == NULL);
    CHECK(List_next(pList) == &prepended);
    CHECK(List_next(pList) == &inserted);
    CHECK(List_next(pList) == &added);
    CHECK(List_next(pList) == &appended);
    CHECK(List_next(pList) == NULL);
    CHECK(List_next(pList) == NULL);

    // Prev through it all
    //   starting from past end
    CHECK(List_last(pList) == &appended);
    CHECK(List_next(pList) == NULL);
    CHECK(List_prev(pList) == &appended);
    CHECK(List_prev(pList) == &added);
    CHECK(List_prev(pList) == &inserted);
    CHECK(List_prev(pList) == &prepended);
    CHECK(List_prev(pList) == NULL);
    CHECK(List_prev(pList) == NULL);

    // Remove first
    CHECK(List_first(pList) == &prepended);
    CHECK(List_remove(pList) == &prepended);
    CHECK(List_curr(pList) == &inserted);

    // Trim last
    CHECK(List_trim(pList) == &appended);
    CHECK(List_curr(pList) == &added);

    // Free remaining 2 elements
    complexTestFreeCounter = 0;
    List_free(pList, complexTestFreeFn);
    CHECK(complexTestFreeCounter == 2);


    // Concat
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    List* pList1 = List_create();
    List_add(pList1, &one);
    List_add(pList1, &two);
    List* pList2 = List_create();
    List_add(pList2, &three);
    List_add(pList2, &four);
    
    List_concat(pList1, pList2);
    CHECK(List_count(pList1) == 4);
    CHECK(List_first(pList1) == &one);
    CHECK(List_last(pList1) == &four);


    // Search
    List_first(pList1);
    CHECK(List_search(pList1, itemEquals, &two) == &two);
    CHECK(List_search(pList1, itemEquals, &two) == &two);
    CHECK(List_search(pList1, itemEquals, &one) == NULL);

	printf("Sample Test Complete\n");
    if (errors == 0) {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("           PASSED\n");
        printf("********************************\n\n");
    } else {
        // We got here?!? FAILED!
        printf("********************************\n");
        printf("          %d TEST FAILED\n", errors);
        printf("********************************\n\n");
		passed = false;
    }
	errors = 0;
    List_free(pList1, complexTestFreeFn);
}

	// printf("Hello World!\n");
static void capacity()
{
	int a = 1;
	int b = 2;	
	int c = 3;
	List* ll = List_create();
	printf("\nAddress: %p\n", ll);

	List_append(ll, &a);
	List_next(ll);
	List_prev(ll);
	List_add(ll, &b);
	List_insert(ll, &c);

    // Free remaining 2 elements
    complexTestFreeCounter = 0;
    List_free(ll, complexTestFreeFn);
    CHECK(complexTestFreeCounter == 3);

	List_search(ll, itemEquals, &b);

	List* l1 = List_create();
	CHECK(l1 != NULL);
	List* l2 = List_create();
	CHECK(l2 != NULL);
	List* l3 = List_create();
	CHECK(l3 != NULL);
	List* l4 = List_create();
	CHECK(l4 != NULL);
	List* l5 = List_create();
	CHECK(l5 != NULL);
	List* l6 = List_create();
	CHECK(l6 != NULL);
	List* l7 = List_create();
	CHECK(l7 != NULL);
	List* l8 = List_create();
	CHECK(l8 != NULL);
	List* l9 = List_create();
	CHECK(l9 != NULL);
	List* l10 = List_create();
	CHECK(l10 != NULL);
	List* l11 = List_create(); 
	CHECK(l11 == NULL);

	// void *append;
	for (int i = 0; i < 10; i ++) {
		List_append(l1, getArr(i));
		List_append(l2, getArr(i+10));
		List_append(l3, getArr(i+20));
		List_append(l4, getArr(i+30));
		List_append(l5, getArr(i+40));
		List_append(l6, getArr(i+50));
		List_append(l7, getArr(i+60));
		List_append(l8, getArr(i+70));
		List_append(l9, getArr(i+80));
		List_append(l10, getArr(i+90));
	}
	CHECK(List_count(l1) == 10);
	CHECK(List_count(l2) == 10);
	CHECK(List_count(l3) == 10);
	CHECK(List_count(l4) == 10);
	CHECK(List_count(l5) == 10);
	CHECK(List_count(l6) == 10);
	CHECK(List_count(l7) == 10);
	CHECK(List_count(l8) == 10);
	CHECK(List_count(l9) == 10);
	CHECK(List_count(l10) == 10);

	List_concat(l1, l2);
	List_concat(l1, l3);
	List_concat(l1, l3);
	List_concat(l1, l4);
	List_concat(l1, l5);
	List_concat(l1, l6);
	List_concat(l1, l7);
	List_concat(l1, l8);
	List_concat(l1, l9);
	List_concat(l1, l10);
	CHECK(List_count(l1) == 100);
	CHECK(List_count(l10) == 0);
	List_free(l2, complexTestFreeFn);

	int hundred = 100;
	CHECK(List_add(l1, &hundred) == -1);
	CHECK(List_last(l1) == getArr(99));
	CHECK(List_next(l1) == NULL);
	CHECK(List_prev(l1) == getArr(99));
	CHECK(List_first(l1) == getArr(0));

	for (int i = 0; i < 50; i++) {
		CHECK(List_first(l1) == getArr(i));
		CHECK(List_remove(l1) == getArr(i));
		CHECK(List_trim(l1) == getArr(99-i));
	}

    CHECK(List_add(l2, getArr(1)) == 0);

    List_free(l1, complexTestFreeFn);
    List_free(l2, complexTestFreeFn);
	List_free(l3, complexTestFreeFn);
	List_free(l4, complexTestFreeFn);
	List_free(l5, complexTestFreeFn);
	List_free(l6, complexTestFreeFn);
	List_free(l7, complexTestFreeFn);
	List_free(l8, complexTestFreeFn);
	List_free(l9, complexTestFreeFn);
	List_free(l10, complexTestFreeFn);

	printf("Capacity Test Complete\n");
    if (errors == 0) {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("           PASSED\n");
        printf("********************************\n\n");
    } else {
        // We got here?!? FAILED!
        printf("********************************\n");
        printf("          %d TEST FAILED\n", errors);
        printf("********************************\n\n");
		passed = false;
    }
	errors = 0;
}

static void fre() {
    int a = 5;
	List* l1 = List_create();
    List_append(l1, &a);

    List_free(l1, complexTestFreeFn);
    List_free(l1, complexTestFreeFn);

}

int main()
{
	sampleTest();
	capacity();
    // fre();
	if (passed) {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("          ALL PASSED\n");
        printf("********************************\n\n");
    } else {
        // We got here?!? FAILED!
        printf("********************************\n");
        printf("          TEST(s) FAILED\n");
        printf("********************************\n\n");
		passed = false;
    }

	return 0;
}