/**
 * Sample test routine for executing each function at least once.
 * Copyright Brian Fraser, 2020
 */

#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "list.c"

// Macro for custom testing; does exit(1) on failure.
#define CHECK(condition) do{ \
    if (!(condition)) { \
        printf("ERROR: %s (@%d): failed condition \"%s\"\n", __func__, __LINE__, #condition); \
        exit(1);\
    }\
} while(0)



// For checking the "free" function called
static int complexTestFreeCounter = 0;
static void complexTestFreeFn(void* pItem) 
{
    CHECK(pItem != NULL);
    complexTestFreeCounter++;
    printf("counter %d \n", complexTestFreeCounter);
}

// For searching
static bool itemEquals(void* pItem, void* pArg) 
{
    return (pItem == pArg);
}

void List_print1(List* pList) {
    Node *pNode = pList->head;
    // printf("head is", *((int*)(pNode->value)));
    while(pNode != NULL) {
        printf("%d->", *((int*)(pNode->value)));
        pNode = pNode->next;
    }
    printf("\n");
}

static void testComplex()
{
    List* pList1 = List_create();
    int three = 3;
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);

    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);

    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);

    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);

    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    CHECK(List_add(pList1, &three) == 0);
    int k = 6;
    CHECK(List_add(pList1, &k) == 0);
    CHECK(List_remove(pList1));


    CHECK(List_add(pList1, &three) == 0);
}

int main(int argCount, char *args[]) 
{
    testComplex();

    // We got here?!? PASSED!
    printf("********************************\n");
    printf("           PASSED\n");
    printf("********************************\n");
    return 0;
}