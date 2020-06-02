#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static List Arr[LIST_MAX_NUM_HEADS];
static Node Nodes[LIST_MAX_NUM_NODES];

// Number of heads used
static int Head_Index= 0;
static int Head_List_counter = 0;
static List* HeadsList = NULL;

// Number of nodes used
static int Node_Index = 0;
static int Node_List_counter = 0;
static Node* NodesList = NULL;

static void* HeadList_Pop();
static void HeadList_Push(void* pItem);

void printNodesList(Node* List);

static void* NodesList_Pop();
static void NodesList_Push(void* pItem);

static bool k = true;

List* List_create(){
    if (k){
    for(int i=0; i <= LIST_MAX_NUM_HEADS-1; i++){
        Arr[i].head = NULL;
        Arr[i].current = NULL;
        Arr[i].tail = NULL;
        Arr[i].check_if_at_head = false;
        Arr[i].check_if_at_tail = false;
        Arr[i].number_of_nodes = 0;
    }

    for(int j=0; j <= LIST_MAX_NUM_NODES-1; j++){
        Nodes[j].value = 0;
        Nodes[j].next = NULL;
        Nodes[j].previous = NULL;
    }
    k = false;
    }
    List* K;
    if (Head_Index < LIST_MAX_NUM_HEADS){
        K = &(Arr[Head_Index]);
        Head_Index++;
    }
    else{
        if(Head_List_counter == 0){
            return NULL;
        }
        K = HeadList_Pop();
    }

    printf("Head Index in the Head Array is: %d\n", Head_Index);
    // printf("50 %p\n", &(Arr[Head_Index]));
    return K;
}

// Returns the number of items in pList.
int List_count(List* pList){
    // assert(pList->number_of_nodes >= 0);
    // assert(pList != NULL);
    // if(pList == NULL){
    //     exit();
    // }
    if(pList->number_of_nodes >=0 && pList != NULL){
    printf("Number of nodes in the list %d\n", pList->number_of_nodes);
    return pList->number_of_nodes;
    }
    else{
        return -1;
    }
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    if(pList->number_of_nodes < 0){
        return -1;
    }
    Node* new;
    if (Node_Index >= LIST_MAX_NUM_NODES){
        if(Node_List_counter == 0){
            return -1;
        }
        new = NodesList_Pop();
    }
    else{
        new = &(Nodes[Node_Index]);
        printf("Node Index in the Node Array is: %d\n", Node_Index);
        Node_Index++;
    }
    new->value = pItem;
    printf("Item to be added: %d\n ", *(int *)(new->value));
    if(pList->head == NULL){
        pList->head = new;
        pList->tail = new;
        pList->current = new;
    }
    else{
        new->previous = pList->tail;
        Node* temp = pList->tail;
        temp->next = new;
        pList->tail = new;
        pList->current = new;
    }
    pList->number_of_nodes++;
    return 0;
}
// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    if(pList->number_of_nodes < 0){
        return -1;
    }
    Node* new;
    if (Node_Index >= LIST_MAX_NUM_NODES){
        if(Node_List_counter == 0){
            return -1;
        }
        new = NodesList_Pop();
    }
    else{
        new = &(Nodes[Node_Index]);
        printf("Node Index in the Node Array is: %d\n", Node_Index);
        Node_Index++;
    }
    new->value = pItem;
    printf("Item to be added: %d\n ", *(int *)(new->value));
    if(pList->head == NULL){
        pList->head = new;
        pList->tail = new;
        pList->current = new;
    }
    else{
        new->next = pList->head;
        Node* temp = pList->head;
        temp->previous = new;
        pList->head = new;
        pList->current = new;
    }
    pList->number_of_nodes++;
    return 0;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert(List* pList, void* pItem){
    if(pList->number_of_nodes < 0){
        return -1;
    }
    Node* new;
    if (Node_Index >= LIST_MAX_NUM_NODES){
        if(Node_List_counter == 0){
            return -1;
        }
        new = NodesList_Pop();
    }
    else{
        new = &(Nodes[Node_Index]);
        printf("Node Index in the Node Array is: %d\n", Node_Index);
        Node_Index++;
    }
    new->value = pItem;
    printf("Item to be added: %d\n ", *(int *)(new->value));
    if(pList->head == NULL){
        pList->head = new;
        pList->tail = new;
        pList->current = new;
    }
    else if(pList->check_if_at_head  && pList->head != NULL){
        Node* temp = pList->head;
        pList->check_if_at_head = false;
        temp->previous = new;
        new->next = pList->head;
        pList->current = new;
        pList->head = new;
    }
    else if(pList->check_if_at_tail && pList->tail != NULL){
        Node* temp = pList->tail;
        temp->next = new;
        pList->check_if_at_tail = false;
        new->previous = pList->tail;
        pList->tail = new;
        pList->current = new;
    }
    else{
        Node* temp = pList->current;
        new->previous = temp->previous;
        new->next = pList->current;
        temp = pList->current;
        temp->previous = new;

        if(pList->current == pList->head){
            pList->head = new;
        }
        else{
            temp = new->previous;
            temp->next = new;
        }
        pList->current = new;
    }
    pList->number_of_nodes++;
    return 0;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_add(List* pList, void* pItem){
    if(pList->number_of_nodes < 0){
        return -1;
    }
    Node* new;
    if (Node_Index >= LIST_MAX_NUM_NODES){
        if(Node_List_counter == 0){
            return -1;
        }
        new = NodesList_Pop();
    }
    else{
        new = &(Nodes[Node_Index]);
        printf("Node Index in the Node Array is: %d\n", Node_Index);
        Node_Index++;
    }
    new->value = pItem;
    printf("Item to be added: %d\n ", *(int *)(new->value));
    if(pList->head == NULL){
        pList->head = new;
        pList->tail = new;
        pList->current = new;
    }
    else if(pList->check_if_at_tail && pList->tail != NULL){
        Node* temp = pList->tail;
        temp->next = new;
        pList->check_if_at_tail = false;
        new->previous = pList->tail;
        pList->tail = new;
        pList->current = new;
    }
    else if(pList->check_if_at_head && pList->head != NULL){
        Node* temp = pList->head;
        pList->check_if_at_head = false;
        temp->previous = new;
        new->next = pList->head;
        pList->head = new;
        pList->current = new;
    }
    else{
        Node* temp = pList->current;
        new->next = temp->next;
        new->previous = pList->current;
        temp = pList->current;
        temp->next = new;

        if(pList->current == pList->tail){
            pList->tail = new;
        }
        else{
        temp = new->next;
        temp->previous = new;
        }
        pList->current = new;
    }
    pList->number_of_nodes++;
    return 0;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if(pList->number_of_nodes < 0){
        return -1;
    }
    if(pList->head == NULL){
        Node* temp = pList->head;
        // temp->value = NULL;
        return NULL;
    }
    if(pList->check_if_at_head){
        pList->check_if_at_head = false;
    }
    pList->current = pList->head;
    Node* temp = pList->current;
    return temp->value;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
    if(pList->head == NULL){
        Node* temp = pList->head;
        // temp->value = NULL;
        return NULL;
    }
    if(pList->check_if_at_tail){
        pList->check_if_at_tail = false;
    }
    pList->current = pList->tail;
    Node* temp = pList->current;
    return temp->value;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
    void *returning;
    if(pList->current == pList->head && pList->head == NULL){
        Node* temp = pList->head;
        // temp->value = NULL;
        returning = NULL;
        return returning;
    }
    else if(pList->check_if_at_head){
        pList->current = pList->head;
        Node* temp = pList->current;
        pList->check_if_at_head = false;
        printf("The current/head is now = %d\n", *((int *)(temp->value)));
        return temp->value;
    }
    else if (pList->current == pList->tail){
        pList->check_if_at_tail = true;
        returning = NULL;
        return returning;
    }
    else if (pList->check_if_at_tail){
        returning = NULL;
        return returning;
    }
    else {
    Node* temp = pList->current;
    pList->current = temp->next;
    temp = pList->current;
    printf("The new current item after List_next is: %d\n", *((int *)(temp->value)));
    return temp->value;
    }
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    void *returning;
    if(pList->current == pList->head && pList->head == NULL){
        Node* temp = pList->head;
        // temp->value = NULL;
        returning = NULL;
        return returning;
    }
    else if (pList->current == pList->head){
        pList->check_if_at_head = true;
        returning = NULL;
        return returning;
    }
    else if(pList->check_if_at_head){
        returning = NULL;
        return returning;
    }
    else if(pList->check_if_at_tail){
        pList->current = pList->tail;
        Node* temp = pList->current;
        pList->check_if_at_tail = false;
        printf("The current/tail is now = %d\n", *((int *)(temp->value)));
        return temp->value;
    }
    else{
    Node* temp = pList->current;
    pList->current = temp->previous;
    temp = pList->current;
    printf("The new current item after List_prev is: %d\n", *((int *)(temp->value)));
    return temp->value;
    }
}

// Returns a pointer to the current item in pList.
// Returns NULL if current is before the start of the pList, or after the end of the pList.
void* List_curr(List* pList){
    if (pList->check_if_at_head || pList->check_if_at_tail || pList->head == NULL){
        return NULL;
    }
    else{
    Node* temp = pList->current;
    printf("The new current item after List_curr is: %d\n", *((int *)(temp->value)));
    return temp->value;
    }
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    if (pList2->number_of_nodes < 0){
        return;
    }
    if(pList1->head == NULL && pList2->head == NULL){
        //merge list2 in one and put list2's head back into the stack
        //current pointer is null
    }
    else if(pList1->head == NULL && pList2->head != NULL){
        pList1->head = pList2->head;
        pList1->tail = pList2->tail;
        //now put list2's head back into the stack
        //current pointer is list1's current pointer
    }
    else if(pList1->head != NULL && pList2->head == NULL){
        //put list2's head back into the stack 
        //current pointer is list1's current pointer
    }
    else{
        Node* temp = pList1->tail;
        temp->next = pList2->head;
        temp = pList2->head;
        temp->previous = pList1->tail;
        pList1->tail = pList2->tail;
    }
    pList1->number_of_nodes += pList2->number_of_nodes;
    printf("Number of nodes in pList1 after List_concat now are: %d\n", pList1->number_of_nodes);
    pList2->head = NULL;
    pList2->current = NULL;
    pList2->tail = NULL;
    pList2->check_if_at_head = false;
    pList2->check_if_at_tail = false;
    pList2->number_of_nodes = -1;
    HeadList_Push(pList2);
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    if(pList->check_if_at_head == true || pList->check_if_at_tail == true || pList->head == NULL){
        return NULL;
    }

    Node* temp = pList->current;
    
    if(pList->number_of_nodes == 1){
        pList->head = NULL;
        pList->tail = NULL;
        pList->current = NULL;
    }
    //Implement the case when there is only one node in the list 
    else if (pList->current == pList->head) {
        pList->head = temp->next;
        Node* temp1 = pList->head;
        temp1->previous = NULL;
        pList->current = pList->head;
        printf("The new current/head item after List_remove is: %d\n", *((int *)(temp1->value)));
    }
    else if (pList->current == pList->tail) {
        pList->tail = temp->previous;
        Node* temp1 = pList->tail;
        temp1->next = NULL;
        pList->check_if_at_tail = true;
        pList->current = pList->tail;
        printf("The new current/tail item after List_remove is: %d\n", *((int *)(temp1->value)));
    }
    else {
        Node* toReturn = pList->current;
        Node* temp = pList->current;
        Node* temp1 = temp->previous;
        temp1->next = temp->next;
        Node* temp2 = temp->next;
        temp2->previous = temp->previous;
        pList->current = temp2;
        printf("The new current item after List_remove is: %d\n", *((int *)(temp2->value)));
    }
    NodesList_Push(temp);
    printf("The item to be removed after List_remove is: %d\n", *((int *)(temp->value)));
    pList->number_of_nodes--;
    return temp->value;  
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    if(pList->head == NULL && pList->tail == NULL && pList->number_of_nodes == 0){
        return NULL;
    }
    pList->current = pList->tail;
    Node* temp = List_remove(pList);
    pList->check_if_at_head = false;
    pList->check_if_at_tail = false;
    return temp;
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    if(pList->head == NULL){
        return NULL;
    }
    void* returning;
    Node* temp;
    while(pList->current){
        temp = pList->current;
        printf("Node contains = %d\n", *((int *)(temp->value)));
        if(temp->value && (*pComparator)(temp->value, pComparisonArg)){
            pList->current = temp;
            return temp->value;
        }
        pList->current = temp->next;

    }
    pList->check_if_at_tail = true;
    returning = NULL;
    return returning;
}

// Delete pList. itemFree is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFree)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.

void List_free(List* pList, FREE_FN pItemFreeFn){
    if(pList == NULL){
        return;
    }
    if(pList->number_of_nodes < 0){
        return;
    }
    // if(Head_Index==10 && Head_List_counter == 9){
    //     return;
    // }
    if(pList->head == NULL && pList == HeadsList){
        return;
    }
    if(pList->head == NULL && pList->current == NULL && pList->tail == NULL && pList->number_of_nodes == 0){
        pList->head = NULL;
        pList->current = NULL;
        pList->tail = NULL;
        pList->check_if_at_head = false;
        pList->check_if_at_tail = false;
        pList->number_of_nodes = -1;
        HeadList_Push(pList);
        return;
    }
    pList->check_if_at_head = false;
    pList->check_if_at_tail = false;
    pList->current = pList->head;
    Node* temp;
    while(pList->current){
        temp = pList->current;
        if(pList->current == pList->tail){
            (*pItemFreeFn)(temp->value);
            break;
        }
        (*pItemFreeFn)(temp->value);
        List_remove(pList);
    }
    // Node* node_available = temp;
    temp = pList->current;
    temp->next = NULL;
    temp->previous = NULL;
    temp->value = 0;
    NodesList_Push(temp);

    pList->head = NULL;
    pList->current = NULL;
    pList->tail = NULL;
    pList->number_of_nodes = -1;
    pList->check_if_at_head = false;
    pList->check_if_at_tail = false;
    HeadList_Push(pList); 
};

void printNodesList(Node* List) {
    while(List != NULL) {
        printf("%d->", *((int*)(List->value)));
        List = List->next;
    }
    printf("\n");
}

static void NodesList_Push(void* pItem){
    Node* temp = pItem;
    if(NodesList == NULL){
        temp->next = NULL;
        temp->previous = NULL;
        NodesList = temp;
    }
    else{
        temp->next = NodesList;
        temp->previous = NULL;
        NodesList = temp;
    }
    Node_List_counter++;
    return;
}

static void* NodesList_Pop(){
    if(NodesList != NULL){
        Node* temp = NodesList;
        NodesList = temp->next;
        temp->next = NULL;
        temp->previous = NULL;
        temp->value = 0;
        Node_List_counter--;
        return temp;
    }
    else{
    return NULL;
    }
}

static void HeadList_Push(void* pItem){
    List* temp = pItem;
    if(HeadsList == NULL){
        temp->next = NULL;
        HeadsList = temp;
    }
    else{
        temp->next = HeadsList;
        HeadsList = temp;
    }
    Head_List_counter++;
    return;
}

static void* HeadList_Pop(){
    if(HeadsList != NULL){
        List* temp = HeadsList;
        HeadsList = temp->next;
        temp->current = NULL;
        temp->head = NULL;
        temp->tail = NULL;
        temp->check_if_at_head = false;
        temp->check_if_at_tail = false;
        temp->number_of_nodes = 0;
        Head_List_counter--;
        return temp;
    }
}


// void List_print(List* pList) {
//     Node *pNode = pList->head;
//     while(pNode != NULL) {
//         printf("%d->", *((int*)(pNode->value)));
//         pNode = pNode->next;
//     }
//     printf("\n");
// }
// void printStates(List* pList) {
//     Node* curr = pList->current;
//     Node* head = pList->head;
//     Node* last = pList->tail;
//     int size = pList->number_of_nodes;

//     head == NULL?printf("NULL\n"):
//                 printf("Head:  %d      ", *((int*)(head->value)));
//     head->next == NULL?printf("NULL         "):
//                 printf("Head_next: %d      ", *((int*)(head->next->value)));
//     head->previous == NULL?printf("NULL\n"):
//                 printf("Head_prev: %d\n", *((int*)(head->previous->value)));

//     last == NULL?printf("NULL\n"):
//                 printf("Last:  %d      ", *((int*)(last->value)));
//     last->next == NULL?printf("NULL              "):
//                 printf("Last_next: %d      ", *((int*)(last->next->value)));
//     last->previous == NULL?printf("NULL\n"):
//                 printf("last_prev: %d\n", *((int*)(last->previous->value)));

//     if (curr != NULL) {
//         curr == NULL?printf("NULL\n"):
//                     printf("Curr:  %d      ", *((int*)(curr->value)));
//         curr->next == NULL?printf("NULL              "):
//                     printf("Curr_next: %d      ", *((int*)(curr->next->value)));
//         curr->previous == NULL?printf("NULL\n"):
//                     printf("Curr_prev: %d\n", *((int*)(curr->previous->value)));
//     }
    
//     printf("Size:  %d\n", size);
//     printf("\n");
// }

// int main() {
//     printf("hi\n");
//     List* ll = List_create();
//     List* l2 = List_create();
//     List* l4 = List_create();
//     int a = 5;
//     int b = 6;
//     int c = 7;
//     int d = 8;

//     int a2 = 9;
//     int b2 = 10;
//     int c2 = 11;
//     int d2 = 12;
//     printf("Address of a %p\n", &a);
//     List_append(ll, &a);
//     printf("Address of b %p\n", &b);
//     List_prepend(ll, &b);
//     printf("29 %p\n", ll);
//     List_add(ll, &c);
//     printf("29 %p\n", ll);
//     List_insert(ll, &d);
//     printf("29 %p\n", ll);
//     List_count(ll);


//     List_append(l2, &a2);
//     List_prepend(l2, &b2);
//     List_add(l2, &c2);
//     List_count(l2);
//     Node *first = List_first(ll);
//     printf("data inside ListFirst = %d\n", *((int *)(first->value)));
//     List_print(ll);
//     printStates(ll);
//     Node *last = List_last(ll);
//     printf("375 data inside ListLast = %d\n", *((int *)(last->value)));

//     Node *next = List_next(ll);
//     // printf("data inside Listnext = %d\n", *((int *)(next->value)));

//     Node *prev = List_prev(ll);
//     printf("data inside List_prev = %d\n", *((int *)(prev->value)));

//     Node *curr = List_curr(l2);
//     printf("data inside Listcurr = %d\n", *((int *)(curr->value)));



//     Node *tempPtr = ll->head;
//     printf("Begin Print: \n");
//     int i = 0;
//     while (tempPtr != NULL) {
//         printf("Node #%d:\n", i);
//         printf("next = %d\n", tempPtr->next);
//         // printf("prev = %d\n", tempPtr->previous);
//         printf("data = %d\n", *((int *)(tempPtr->value)));
//         tempPtr = tempPtr->next;
//         i++;
//     }

//     Node *tempPtr1 = l2->head;
//     printf("Begin Print: \n");
//     int j = 0;
//     while (tempPtr1 != NULL) {
//         printf("Node #%d:\n", j);
//         printf("next = %d\n", tempPtr1->next);
//         // printf("prev = %d\n", tempPtr->previous);
//         printf("data = %d\n", *((int *)(tempPtr1->value)));
//         tempPtr1 = tempPtr1->next;
//         j++;
//     }
//     // List* l2 = List_create();
//     // printf("31 %p\n", l2);
//     // List* l3 = List_create();
//     // printf("33 %p\n", l3);

//     // List* l4 = List_create();
//     // printf("29 %p\n", l4);
//     // List* l5 = List_create();
//     // printf("31 %p\n", l5);
//     // List* l6 = List_create();
//     // printf("33 %p\n", l6);

//     // List* l7 = List_create();
//     // printf("29 %p\n", l7);
//     // List* l8 = List_create();
//     // printf("31 %p\n", l8);
//     // List* l9 = List_create();
//     // printf("33 %p\n", l9);

//     // List* l10 = List_create();
//     // printf("29 %p\n", l10);
//     // List* l11 = List_create();
//     // printf("75 %p\n", l11);
//     // List* l12 = List_create();
//     // printf("75 %p\n", l12);
//     // for(int i = 0; i< LIST_MAX_NUM_HEADS; i++){
//     //     printf("36 %p\n", Arr[i]);
//     // }
//     // List* l2 = List_create();
//     // printf("33 %p\n", l2);
//     // List* l4 = List_create();
//     // printf("35 %p\n", l4);
// }



