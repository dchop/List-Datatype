// /**
//  * Sample test routine for executing each function at least once.
//  * Copyright Brian Fraser, 2020
//  */

// #include "list.h"
// #include <stdio.h>
// #include <assert.h>
// #include <string.h>
// #include <stdlib.h>
// #include "list.c"

// // Macro for custom testing; does exit(1) on failure.
// #define CHECK(condition) do{ \
//     if (!(condition)) { \
//         printf("ERROR: %s (@%d): failed condition \"%s\"\n", __func__, __LINE__, #condition); \
//         exit(1);\
//     }\
// } while(0)



// // For checking the "free" function called
// static int complexTestFreeCounter = 0;
// static void complexTestFreeFn(void* pItem) 
// {
//     CHECK(pItem != NULL);
//     complexTestFreeCounter++;
//     printf("counter %d \n", complexTestFreeCounter);
// }

// // For searching
// static bool itemEquals(void* pItem, void* pArg) 
// {
//     return (pItem == pArg);
// }

// void List_print1(List* pList) {
//     Node *pNode = pList->head;
//     // printf("head is", *((int*)(pNode->value)));
//     while(pNode != NULL) {
//         printf("%d->", *((int*)(pNode->value)));
//         pNode = pNode->next;
//     }
//     printf("\n");
// }

// static void testComplex()
// {
//     // Empty list
//     List* pList1 = List_create();
//     int added = 41;
//     CHECK(List_add(pList1, &added) == 0);
//     int three = 3;
//     CHECK(List_insert(pList1, &three) == 0);
//     CHECK(List_next(pList1) == &added);
//     CHECK(List_next(pList1) == NULL);

//     List_free(pList1, complexTestFreeFn);
//     CHECK(complexTestFreeCounter == 2);

//     List* pList2 = List_create();
//     int five = 4;
//     CHECK(List_append(pList2, &five) == 0);

//     List_free(pList1, complexTestFreeFn);
//     CHECK(complexTestFreeCounter == 2);

//     // List* pList2 = List_create();
//     // int four = 4;
//     // CHECK(List_append(pList2, &four) == 0);
//     List_concat(pList1, pList2);
//     CHECK(List_count(pList1) == 3);
//     List_print1(pList1);
//     CHECK(List_curr(pList1) == NULL);
//     // CHECK(List_prev(pList1) == &four);

//     List* pList3 = List_create();

//     // CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);

//     // int three = 3;
//     // CHECK(List_add(pList1, &three) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     int added1 = 9;
//     CHECK(List_add(pList1, &added1) == 0);
//     CHECK(List_remove(pList1) == &added1);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);
//     CHECK(List_add(pList1, &added) == 0);

//     CHECK(List_add(pList1, &added) == -1);
    

//     // CHECK(pList != NULL);
//     // CHECK(List_count(pList) == 0);

//     // // Add 
//     // int added = 41;
//     // CHECK(List_add(pList, &added) == 0);
//     // CHECK(List_count(pList) == 1);
//     // CHECK(List_curr(pList) == &added);

//     // // Insert
//     // int inserted = 42;
//     // CHECK(List_insert(pList, &inserted) == 0);
//     // CHECK(List_count(pList) == 2);
//     // CHECK(List_curr(pList) == &inserted);
    
//     // // Prepend
//     // int prepended = 43;
//     // CHECK(List_prepend(pList, &prepended) == 0);
//     // CHECK(List_count(pList) == 3);
//     // CHECK(List_curr(pList) == &prepended);
    
//     // // Append
//     // int appended = 44;
//     // CHECK(List_append(pList, &appended) == 0);
//     // CHECK(List_count(pList) == 4);
//     // CHECK(List_curr(pList) == &appended);
    
//     // // Next through it all (from before list)
//     // CHECK(List_first(pList) == &prepended);
//     // CHECK(List_prev(pList) == NULL);
//     // CHECK(List_next(pList) == &prepended);
//     // CHECK(List_next(pList) == &inserted);
//     // CHECK(List_next(pList) == &added);
//     // CHECK(List_next(pList) == &appended);
//     // CHECK(List_next(pList) == NULL);
//     // CHECK(List_next(pList) == NULL);

//     // // Prev through it all
//     // //   starting from past end
//     // CHECK(List_last(pList) == &appended);
//     // CHECK(List_next(pList) == NULL);
//     // CHECK(List_prev(pList) == &appended);
//     // CHECK(List_prev(pList) == &added);
//     // CHECK(List_prev(pList) == &inserted);
//     // CHECK(List_prev(pList) == &prepended);
//     // CHECK(List_prev(pList) == NULL);
//     // CHECK(List_prev(pList) == NULL);

//     // // Remove first
//     // CHECK(List_first(pList) == &prepended);
//     // CHECK(List_remove(pList) == &prepended);
//     // CHECK(List_curr(pList) == &inserted);

//     // // Trim last
//     // CHECK(List_trim(pList) == &appended);
//     // CHECK(List_curr(pList) == &added);

//     // List_print1(pList);

//     // // Free remaining 2 elements
//     // complexTestFreeCounter = 0;
//     // List_free(pList, complexTestFreeFn);
//     // CHECK(complexTestFreeCounter == 2);

//     // List_print1(pList);

//     // // Concat
//     // int one = 1;
//     // int two = 2;
//     // int three = 3;
//     // int four = 4;
//     // List* pList1 = List_create();
//     // List_add(pList1, &one);
//     // List_add(pList1, &two);
//     // List_print1(pList1);
//     // List_print1(pList);
//     // List* pList2 = List_create();
//     // List_add(pList2, &three);
//     // List_add(pList2, &four);
//     // List_print1(pList);
//     // List_print1(pList1);
//     // List_print1(pList2);
    
//     // List_concat(pList1, pList2);
//     // CHECK(List_count(pList1) == 4);
//     // List_print1(pList1);
//     // CHECK(List_first(pList1) == &one);
//     // CHECK(List_last(pList1) == &four);


//     // // Search
//     // List_first(pList1);
//     // CHECK(List_search(pList1, itemEquals, &two) == &two);
//     // CHECK(List_search(pList1, itemEquals, &two) == &two);
//     // CHECK(List_search(pList1, itemEquals, &one) == NULL);
// }

// int main(int argCount, char *args[]) 
// {
//     testComplex();

//     // We got here?!? PASSED!
//     printf("********************************\n");
//     printf("           PASSED\n");
//     printf("********************************\n");
//     return 0;
// }