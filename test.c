#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
// Needed for testing maximum amount of nodes in list
static int arr[LIST_MAX_NUM_NODES] = {0};
static bool initArray = false;

// Generate array with ascending values and return the item at any index
void* getArrayItemAtIndex(int idx) {
    if (idx > LIST_MAX_NUM_NODES) {
        return NULL;
    }
    if (!initArray) {
        for (int i=0; i<LIST_MAX_NUM_NODES; i++) {
            arr[i] = i;
        }
        initArray = true;
    }
    void* ptr = &arr[idx];
    return ptr;
}

#define CHECK(condition) do{ \
    if (!(condition)) { \
        printf("ERROR: %s (@%d): failed condition \"%s\"\n", __func__, __LINE__, #condition); \
        errors++;\
    }\
} while(0)


static int complexTestFreeCounter = 0;
static int errors = 0;

static void complexTestFreeFn(void* pItem) 
{
    CHECK(pItem != NULL);
    complexTestFreeCounter++;
}

static bool itemEquals(void* pItem, void* pArg) 
{
    return (pItem == pArg);
}

static bool itemGreater(void* pItem, void* pArg) 
{   
    int item = *((int*)pItem);
    int arg = *((int*)pArg);
    return (item > arg);
}

// Test cases provided by the instructor
static void providedTestsTestSuite() {

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
    
    printf("INSTRUCTOR TEST SUITE COMPLETED\n");
    if (errors == 0) {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("           PASSED\n");
        printf("********************************\n\n");
    } else {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("          %d TEST FAILED\n", errors);
        printf("********************************\n\n");
    }
    List_free(pList1, complexTestFreeFn);
    List_free(pList2, complexTestFreeFn);
}

/*  
    Tests cases instantiating the maximum number of lists(10)
    and appending all the available nodes to one and checking 
    NO available nodes can be appended if maximum number of nodes are reached
*/
static void testListCapacity() {
    errors = 0;

    List* ll  = List_create();
    CHECK(ll != NULL);
    List* ll2 = List_create();
    CHECK(ll2 != NULL);
    List* ll3 = List_create();
    CHECK(ll3 != NULL);
    List* ll4 = List_create();
    CHECK(ll4 != NULL);
    List* ll5 = List_create();
    CHECK(ll5 != NULL);
    List* ll6 = List_create();
    CHECK(ll6 != NULL);
    List* ll7 = List_create();
    CHECK(ll7 != NULL);
    List* ll8 = List_create();
    CHECK(ll8 != NULL);
    List* ll9 = List_create();
    CHECK(ll9 != NULL);
    List* ll10 = List_create();
    CHECK(ll10 != NULL);
    List* ll11 = List_create();
    CHECK(ll11 == NULL);
    CHECK(List_first(ll) == NULL);

    static void* appended;
    for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
        appended = getArrayItemAtIndex(i);
        CHECK(List_count(ll) == i);
        CHECK(List_append(ll, appended) == 0);
        CHECK(List_first(ll) == getArrayItemAtIndex(0));
        CHECK(List_last(ll) == appended);
        CHECK(List_curr(ll) == appended);
    }

    CHECK(List_count(ll) == 100);
    appended = getArrayItemAtIndex(0);
    CHECK(List_append(ll2, appended) == -1);

    CHECK(List_prev(ll) == getArrayItemAtIndex(LIST_MAX_NUM_NODES-2));
    CHECK(List_prev(ll) == getArrayItemAtIndex(LIST_MAX_NUM_NODES-3));
    CHECK(List_remove(ll) == getArrayItemAtIndex(LIST_MAX_NUM_NODES-3));
    CHECK(List_curr(ll) == getArrayItemAtIndex(LIST_MAX_NUM_NODES-2));
    CHECK(List_remove(ll) == getArrayItemAtIndex(LIST_MAX_NUM_NODES-2));
    CHECK(List_count(ll) == LIST_MAX_NUM_NODES - 2);

    CHECK(List_append(ll2, appended) == 0);
    CHECK(List_first(ll2) == getArrayItemAtIndex(0));
    CHECK(List_append(ll2, getArrayItemAtIndex(1)) == 0);
    CHECK(List_last(ll2) == getArrayItemAtIndex(1));
    CHECK(List_curr(ll2) == getArrayItemAtIndex(1));

    CHECK(List_append(ll2, appended) == -1);

    printf("LIST CAPACITY TEST SUITE COMPLETED\n");
    if (errors == 0) {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("           PASSED\n");
        printf("********************************\n\n");
    } else {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("          %d TEST FAILED\n", errors);
        printf("********************************\n\n");
    }

    List_free(ll, complexTestFreeFn);
    List_free(ll2, complexTestFreeFn);
    List_free(ll3, complexTestFreeFn);
    List_free(ll4, complexTestFreeFn);
    List_free(ll5, complexTestFreeFn);
    List_free(ll6, complexTestFreeFn);
    List_free(ll7, complexTestFreeFn);
    List_free(ll8, complexTestFreeFn);
    List_free(ll9, complexTestFreeFn);
    List_free(ll10, complexTestFreeFn);
    List_free(ll11, complexTestFreeFn);
}

static void testPositions() {
    errors = 0;

    List* pList = List_create();
    CHECK(List_add(pList, getArrayItemAtIndex(0)) == 0);
    CHECK(List_first(pList) == getArrayItemAtIndex(0));

    CHECK(List_append(pList, getArrayItemAtIndex(1)) == 0);
    CHECK(List_curr(pList) == getArrayItemAtIndex(1));

    CHECK(List_insert(pList, getArrayItemAtIndex(2)) == 0);
    CHECK(List_curr(pList) == getArrayItemAtIndex(2));

    CHECK(List_insert(pList, getArrayItemAtIndex(3)) == 0);
    CHECK(List_curr(pList) == getArrayItemAtIndex(3));

    CHECK(List_add(pList, getArrayItemAtIndex(4)) == 0);
    CHECK(List_curr(pList) == getArrayItemAtIndex(4));

    CHECK(List_prepend(pList, getArrayItemAtIndex(5)) == 0);
    CHECK(List_curr(pList) == getArrayItemAtIndex(5));

    CHECK(List_prepend(pList, getArrayItemAtIndex(6)) == 0);
    CHECK(List_curr(pList) == getArrayItemAtIndex(6));

    CHECK(List_first(pList) == getArrayItemAtIndex(6));
    CHECK(List_next(pList) == getArrayItemAtIndex(5));
    CHECK(List_next(pList) == getArrayItemAtIndex(0));
    CHECK(List_next(pList) == getArrayItemAtIndex(3));
    CHECK(List_next(pList) == getArrayItemAtIndex(4));
    CHECK(List_next(pList) == getArrayItemAtIndex(2));
    CHECK(List_next(pList) == getArrayItemAtIndex(1));
    
    CHECK(List_next(pList) == NULL);
    CHECK(List_next(pList) == NULL);
    CHECK(List_prev(pList) == getArrayItemAtIndex(1));
    CHECK(List_last(pList) == getArrayItemAtIndex(1));
    CHECK(List_insert(pList, getArrayItemAtIndex(7)) == 0);
    CHECK(List_curr(pList) == getArrayItemAtIndex(7));

    CHECK(List_prev(pList) == getArrayItemAtIndex(2));
    CHECK(List_prev(pList) == getArrayItemAtIndex(4));
    CHECK(List_prev(pList) == getArrayItemAtIndex(3));
    CHECK(List_add(pList, getArrayItemAtIndex(8)) == 0);
    CHECK(List_prev(pList) == getArrayItemAtIndex(3));
    CHECK(List_prev(pList) == getArrayItemAtIndex(0));
    CHECK(List_prev(pList) == getArrayItemAtIndex(5));
    CHECK(List_prev(pList) == getArrayItemAtIndex(6));
    
    CHECK(List_prev(pList) == NULL);
    CHECK(List_prev(pList) == NULL);
    CHECK(List_count(pList) == 9);

    CHECK(List_first(pList) == getArrayItemAtIndex(6));
    CHECK(List_next(pList) == getArrayItemAtIndex(5));
    CHECK(List_next(pList) == getArrayItemAtIndex(0));
    CHECK(List_remove(pList) == getArrayItemAtIndex(0));
    CHECK(List_remove(pList) == getArrayItemAtIndex(3));
    CHECK(List_count(pList) == 7);

    CHECK(List_first(pList) == getArrayItemAtIndex(6));
    CHECK(List_remove(pList) == getArrayItemAtIndex(6));
    CHECK(List_first(pList) == getArrayItemAtIndex(5));
    CHECK(List_last(pList) == getArrayItemAtIndex(1));
    CHECK(List_remove(pList) == getArrayItemAtIndex(1));
    CHECK(List_last(pList) == getArrayItemAtIndex(7));
    CHECK(List_trim(pList) == getArrayItemAtIndex(7));
    CHECK(List_trim(pList) == getArrayItemAtIndex(2));
    CHECK(List_count(pList) == 3);
    
    
    printf("POSITIONS TEST SUITE COMPLETED\n");
    if (errors == 0) {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("           PASSED\n");
        printf("********************************\n\n");
    } else {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("          %d TEST FAILED\n", errors);
        printf("********************************\n\n");
    }
    List_free(pList, complexTestFreeFn);
}

static void testConcat() {
    List* pList1 = List_create();
    List_add(pList1, getArrayItemAtIndex(5));
    List_add(pList1, getArrayItemAtIndex(3));
    List* pList2 = List_create();
    List_add(pList2, getArrayItemAtIndex(4));
    List_add(pList2, getArrayItemAtIndex(6));
    
    List_concat(pList1, pList2);
    CHECK(List_count(pList1) == 4);
    CHECK(List_first(pList1) == getArrayItemAtIndex(5));
    CHECK(List_last(pList1) == getArrayItemAtIndex(6));

    List_first(pList1);
    CHECK(List_search(pList1, itemEquals, getArrayItemAtIndex(4)) == getArrayItemAtIndex(4));
    List_curr(pList1);
    CHECK(List_search(pList1, itemGreater, getArrayItemAtIndex(3)) == getArrayItemAtIndex(4));
    CHECK(List_search(pList1, itemEquals, getArrayItemAtIndex(7)) == NULL);

    printf("CONCAT AND SEARCH TEST SUITE COMPLETED\n");
    if (errors == 0) {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("           PASSED\n");
        printf("********************************\n\n");
    } else {
        // We got here?!? PASSED!
        printf("********************************\n");
        printf("          %d TEST FAILED\n", errors);
        printf("********************************\n\n");
    }
    List_free(pList1, complexTestFreeFn);
}
int main() 
{
    providedTestsTestSuite();
    testListCapacity();
    testPositions();
    testConcat();
    return 0;
}
