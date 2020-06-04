/**
 * myTest.c for Assignment 1, CMPT 300 Summer 2020
 * Name: Devansh Chopra
 * Student #: 301-275-491
 */

#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static int errors = 0;
// Macro for custom testing; does exit(1) on failure.
#define CHECK(condition) do{ \
    if (!(condition)) { \
        printf("ERROR: %s (@%d): failed condition \"%s\"\n", __func__, __LINE__, #condition); \
        errors++;\
    }\
} while(0)

static int NodesArray[LIST_MAX_NUM_NODES];

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

void List_print1(List* pList) {
    Node *pNode = pList->head;
    while(pNode != NULL) {
        printf("%d->", *((int*)(pNode->value)));
        pNode = pNode->next;
    }
    printf("\n");
}

static void* fillUpArray() {
    for (int i; i< LIST_MAX_NUM_NODES; i++){
        NodesArray[i] = i;
    }
}

static void* pickNewNode(int value){
    void* toReturn = &NodesArray[value];
    return toReturn;
}

static void checkLimit(){
    fillUpArray();

    List* pList1 = List_create();
	CHECK(pList1 != NULL);
	List* pList2 = List_create();
	CHECK(pList2 != NULL);
	List* pList3 = List_create();
	CHECK(pList3 != NULL);
	List* pList4 = List_create();
	CHECK(pList4 != NULL);
	List* pList5 = List_create();
	CHECK(pList5 != NULL);
	List* pList6 = List_create();
	CHECK(pList6 != NULL);
	List* pList7 = List_create();
	CHECK(pList7 != NULL);
	List* pList8 = List_create();
	CHECK(pList8 != NULL);
	List* pList9 = List_create();
	CHECK(pList9 != NULL);
	List* pList10 = List_create();
	CHECK(pList10 != NULL);
	List* pList11 = List_create(); // Reached max List - should not create
	CHECK(pList11 == NULL);

    // Filling up lists
	for (int i = 0; i < 5; i ++) {
		List_append(pList1, pickNewNode(i));
		List_insert(pList2, pickNewNode(i+5));
		List_prepend(pList3, pickNewNode(i+10));
		List_add(pList4, pickNewNode(i+15));
		List_add(pList5, pickNewNode(i+20));
		List_insert(pList6, pickNewNode(i+25));
		List_append(pList7, pickNewNode(i+30));
		List_append(pList8, pickNewNode(i+35));
		List_prepend(pList9, pickNewNode(i+40));
		List_prepend(pList10, pickNewNode(i+45));
	}

    CHECK(List_count(pList1) == 5);
	CHECK(List_count(pList2) == 5);
	CHECK(List_count(pList3) == 5);
	CHECK(List_count(pList4) == 5);
	CHECK(List_count(pList5) == 5);
	CHECK(List_count(pList6) == 5);
	CHECK(List_count(pList7) == 5);
	CHECK(List_count(pList8) == 5);
	CHECK(List_count(pList9) == 5);
	CHECK(List_count(pList10) == 5);
    CHECK(List_count(pList11) == -1);

    CHECK(List_prev(pList1) == &NodesArray[3]);
    CHECK(List_prev(pList1) == &NodesArray[2]);
    CHECK(List_prev(pList1) == &NodesArray[1]);
    CHECK(List_prev(pList1) == &NodesArray[0]);
    CHECK(List_prev(pList1) == NULL);
    CHECK(List_prev(pList1) == NULL);
    CHECK(List_prev(pList1) == NULL);
    
    CHECK(List_next(pList3) == &NodesArray[13]);
    CHECK(List_next(pList3) == &NodesArray[12]);
    CHECK(List_next(pList3) == &NodesArray[11]);
    CHECK(List_next(pList3) == &NodesArray[10]);
    CHECK(List_next(pList3) == NULL);
    CHECK(List_next(pList3) == NULL);

    CHECK(List_remove(pList1) == NULL);
    CHECK(List_remove(pList3) == NULL);

    List_free(pList2, complexTestFreeFn);
    List* pList12 = List_create();

    List_concat(pList1, pList2);
    List_concat(pList1, pList12);

    List_free(pList5, complexTestFreeFn);
    CHECK(List_count(pList1) == 5);

    List* pList13 = List_create();
    List_concat(pList13, pList3);
    CHECK(List_count(pList13) == 5);
    
    List_last(pList7);
    List_next(pList7);
    List_concat(pList7, pList8);
    CHECK(List_curr(pList7) == NULL);

    
    CHECK(List_count(pList7) == 10);

    List_first(pList1);
    CHECK(List_search(pList1, itemEquals, &NodesArray[4]) == &NodesArray[4]);
    
    List_free(pList1, complexTestFreeFn);
    List_free(pList2, complexTestFreeFn);
	List_free(pList3, complexTestFreeFn);
	List_free(pList4, complexTestFreeFn);
	List_free(pList5, complexTestFreeFn);
	List_free(pList6, complexTestFreeFn);
	List_free(pList7, complexTestFreeFn);
	List_free(pList8, complexTestFreeFn);
	List_free(pList9, complexTestFreeFn);
    List_free(pList10, complexTestFreeFn);
    List_free(pList11, complexTestFreeFn);
    List_free(pList12, complexTestFreeFn);
    List_free(pList13, complexTestFreeFn);

    printf("Test1 Complete\n");
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
    }
	errors = 0;
}

static void test2()
{
    fillUpArray();
    List* pList1 = List_create();
    CHECK(List_remove(pList1) == NULL);
    CHECK(List_next(pList1) == NULL);

    for(int i = 0; i<LIST_MAX_NUM_NODES; i++){
        List_add(pList1, pickNewNode(i));
    }
	
    CHECK(List_append(pList1, pickNewNode(6)) == -1);
    List* pList2 = List_create();
    List_remove(pList1);

    CHECK(List_append(pList2, pickNewNode(6)) == 0);
    List* pList3 = List_create();
    List* pList4 = List_create();

    CHECK(List_append(pList4, pickNewNode(9)) == -1);
    List* pList5 = List_create();
    List* pList6 = List_create();

    List_first(pList1);
    List_prev(pList1);
    List_prev(pList1);

    CHECK(List_remove(pList1) == NULL);
    List_first(pList1);
    List_remove(pList1);

    List_insert(pList4, pickNewNode(45));
    List_add(pList4, pickNewNode(77));
    List_remove(pList4);

    CHECK(List_remove(pList4) == NULL);
    List_free(pList3, complexTestFreeFn);
    CHECK(List_curr(pList3) == NULL);

    List_first(pList1);
    List_prev(pList1);
    List_prev(pList1);

    CHECK(List_search(pList1, itemEquals, &NodesArray[22]) == &NodesArray[22]);

    List_concat(pList1, pList1);
    List_free(pList1, complexTestFreeFn);
    List_append(pList6, pickNewNode(99));
	CHECK(List_count(pList6) == 1);
    CHECK(List_next(pList5) == NULL);

    List_free(pList1, complexTestFreeFn);
    List_free(pList2, complexTestFreeFn);
    List_free(pList3, complexTestFreeFn);
    List_free(pList4, complexTestFreeFn);
    List_free(pList5, complexTestFreeFn);
    List_free(pList6, complexTestFreeFn);

    List* pList8 = List_create();
    CHECK(List_trim(pList8) == NULL);
    CHECK(List_insert(pList8, pickNewNode(2)) == 0);
    CHECK(List_insert(pList8, pickNewNode(2)) == 0);

    complexTestFreeCounter = 0;
    List_free(pList8, complexTestFreeFn);
    CHECK(complexTestFreeCounter == 2);

    printf("Test2 Complete\n");
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
    }
	errors = 0;


}

int main() 
{
    checkLimit();
    test2();

    // We got here?!? PASSED!
    printf("********************************\n");
    printf("          ALL PASSED\n");
    printf("********************************\n");
    return 0;
}