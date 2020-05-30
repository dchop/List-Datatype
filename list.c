#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static List Arr[LIST_MAX_NUM_HEADS] = {NULL};
static Node Nodes[LIST_MAX_NUM_NODES] = {NULL};

// Number of heads used
static int Number_of_Heads_used = 0;

static List *Head_Stack[LIST_MAX_NUM_HEADS] = {NULL};
static int Head_Stack_counter = LIST_MAX_NUM_HEADS-1;

// Number of nodes used
static int Number_of_Nodes_used = 0;

static Node *Node_Stack[LIST_MAX_NUM_NODES] = {NULL};
static int Node_Stack_counter = LIST_MAX_NUM_NODES-1;

static bool k = true;

List* List_create(){
    if(Number_of_Heads_used >= LIST_MAX_NUM_HEADS){
        return NULL;
    }

    if (k){
    for(int i=0; i <= LIST_MAX_NUM_HEADS-1; i++){
        List *New = &(Arr[i]); // Putting the address of the element to New
        Arr[i].head = NULL;
        Arr[i].current = NULL;
        Arr[i].tail = NULL;
        Arr[i].number_of_nodes = 0;
        // printf("31 %p\n", New);
        Head_Stack[i] = New;
    }

    for(int j=0; j <= LIST_MAX_NUM_NODES-1; j++){
        List *New1 = &(Nodes[j]);
        Nodes[j].value = 0;
        Nodes[j].next = NULL;
        Nodes[j].previous = NULL;
        Node_Stack[j] = New1;
    }
    k = false;
    }

    printf("49 %d\n", Head_Stack_counter);
    printf("50 %p\n", (Head_Stack[Head_Stack_counter]));
    List *K = (Head_Stack[Head_Stack_counter]);
    // Arr[Number_of_Heads_used] = *K;
    Number_of_Heads_used++;
    Head_Stack[Head_Stack_counter] = NULL;
    Head_Stack_counter--;
    return K;

    
    // if(numSpareLists){
    //     printf("YO\n");
    //     List *NewList = spareLists[numSpareLists -1];
    //     spareLists[numSpareLists - 1] = NULL;
    //     numSpareLists--;
    //     return NewList;
    // }
    // else{
    // Number_of_Heads_used++;
    // Arr[Number_of_Heads_used].head = NULL;
    // Arr[Number_of_Heads_used].current = NULL;
    // Arr[Number_of_Heads_used].tail = NULL;
    // return &(Arr[Number_of_Heads_used]);
    // }
    
    // for(int i=0; i<LIST_MAX_NUM_HEADS; i++){
    //     if(Arr[i] == NULL){
    //         List* ll;
    //         Arr[i] = ll;
    //         printf("15 %p\n", Arr[i]);
    //         return ll;
    //     }
    // }
    // return -1;
    // List linkedList;
    // linkedList.head = NULL;

    // return (linkedList.head);
}

// Returns the number of items in pList.
int List_count(List* pList){
    printf("90 Number of nodes %d\n", pList->number_of_nodes);
    return pList->number_of_nodes;
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    if (Number_of_Nodes_used >= LIST_MAX_NUM_NODES){
        return -1;
    }
    printf("Number of nodes in list %d\n", pList->number_of_nodes);
    printf("Node Stack counter %d\n", Node_Stack_counter);
    Node *new = (Node_Stack[Node_Stack_counter]);
    new->value = pItem;
    printf("%d\n ", *(int *)(new->value));
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
    Node *checker = pList->head;
    printf("data = %d\n", *((int *)(checker->value)));
    Node_Stack[Node_Stack_counter] = NULL;
    pList->number_of_nodes++;
    Number_of_Nodes_used++;
    Node_Stack_counter--;
    return 0;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    if (Number_of_Nodes_used >= LIST_MAX_NUM_NODES){
        return -1;
    }
    printf("Number of nodes in list %d\n", pList->number_of_nodes);
    printf("Node Stack counter %d\n", Node_Stack_counter);
    Node *new = (Node_Stack[Node_Stack_counter]);
    new->value = pItem;
    printf("%d\n ", *(int *) (new->value));
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
    Node *checker = pList->head;
    printf("data = %d\n", *((int *)(checker->value)));
    Node_Stack[Node_Stack_counter] = NULL;
    pList->number_of_nodes++;
    Number_of_Nodes_used++;
    Node_Stack_counter--;
    return 0;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert(List* pList, void* pItem){
    if (Number_of_Nodes_used >= LIST_MAX_NUM_NODES){
        return -1;
    }
    printf("Number of nodes in list %d\n", pList->number_of_nodes);
    printf("Node Stack counter %d\n", Node_Stack_counter);
    Node *new = (Node_Stack[Node_Stack_counter]);
    new->value = pItem;
    printf("%d\n ", *(int *) (new->value));
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
    // else if (pList->current == pList->head){
    //     Node* temp = pList->current;
    //     new->next = temp;
    //     temp->previous = new;
    //     pList->head = new;
    //     pList->current = new;

    // }
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
    // Node *checker = pList->head;
    // printf("data = %d\n", *((int *)(checker->value)));
    Node_Stack[Node_Stack_counter] = NULL;
    pList->number_of_nodes++;
    Number_of_Nodes_used++;
    Node_Stack_counter--;
    return 0;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_add(List* pList, void* pItem){
    if (Number_of_Nodes_used >= LIST_MAX_NUM_NODES){
        return -1;
    }
    // printf("Number of nodes in list %d\n", pList->number_of_nodes);
    printf("Node Stack counter %d\n", Node_Stack_counter);
    Node *new = (Node_Stack[Node_Stack_counter]);
    new->value = pItem;
    printf("%d\n ", *(int *) (new->value));
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
   
    // Node *checker = pList->head;
    // printf("data = %d\n", *((int *)(checker->value)));
    Node_Stack[Node_Stack_counter] = NULL;
    pList->number_of_nodes++;
    Number_of_Nodes_used++;
    Node_Stack_counter--;
    return 0;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if(pList->head == NULL){
        Node* temp = pList->head;
        temp->value = NULL;
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
        temp->value = NULL;
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
        temp->value = NULL;
        return NULL;
    }
    else if(pList->check_if_at_head){
        pList->current = pList->head;
        Node* temp = pList->current;
        pList->check_if_at_head = false;
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
    printf("251 data inside ListLast = %d\n", *((int *)(temp->value)));
    pList->current = temp->next;
    temp = pList->current;
    printf("252 data inside ListLast = %d\n", *((int *)(temp->value)));
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
        temp->value = NULL;
        return NULL;
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
        return temp->value;
    }
    else{
    Node* temp2 = pList->current;
    Node* checker = pList->head;
    printf("343 data inside ListLast = %d\n", *(int*)(checker->value));
    printf("251 data inside ListLast = %d\n", *(int*)(temp2->value));
    pList->current = temp2->previous;
    temp2 = pList->current;
    printf("252 data inside ListLast = %d\n", *(int*)(temp2->value));
    return temp2->value;
    }
}
// Returns a pointer to the current item in pList.
// Returns NULL if current is before the start of the pList, or after the end of the pList.
void* List_curr(List* pList){
    if (pList->check_if_at_head || pList->check_if_at_tail){
        // void* returning = NULL
        return NULL;
    }
    else{
    Node* temp = pList->current;
    return temp->value;
    }
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    // if (Number_of_Nodes_used >= LIST_MAX_NUM_NODES){
    //     return;
    // }
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
    // List* head_available = pList2;
    pList2->head = NULL;
    pList2->current = NULL;
    pList2->tail = NULL;
    pList2->number_of_nodes = 0;
    Head_Stack_counter++;
    Number_of_Heads_used--;
    Head_Stack[Head_Stack_counter] = pList2;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    if(pList->check_if_at_head == true || pList->check_if_at_tail == true){
        return NULL;
    }
    Node* returning;
    Node* temp = pList->current;

    if(pList->number_of_nodes == 1){
        pList->head = NULL;
        pList->tail = NULL;
    }

    //Implement the case when there is only one node in the list 

    // if(pList->current == pList->head && pList->number_of_nodes == 1){
    //         // Node* node_available = temp;
    //         temp->next = NULL;
    //         temp->previous = NULL;
    //         temp->value = 0;
    //         Node_Stack_counter++;
    //         Number_of_Nodes_used--;
    //         pList->number_of_nodes--;
    //         Node_Stack[Node_Stack_counter] = temp;

    //         // List* head_available = pList;
    //         pList->head = NULL;
    //         pList->current = NULL;
    //         pList->tail = NULL;
    //         pList->number_of_nodes = 0;
    //         Head_Stack_counter++;
    //         Number_of_Heads_used--;
    //         Head_Stack[Head_Stack_counter] = pList;
    //         return returning; 

    // }
    else if (pList->current == pList->head) {
        pList->head = temp->next;
        Node* temp1 = pList->head;
        temp1->previous = NULL;
        returning = temp->value;
        // Node* temp = pList->current;
        // returning = temp->value;
        // printf("yoooo", *((int*)(returning)));
        // Node* temp1 = temp->next;
        // temp1->previous = pList->head;
        // temp = pList->head;
        // pList->head = temp->next;
        // temp1 = pList->head;
        // temp1->previous = NULL;
        pList->current = pList->head;
    }
    else if (pList->current == pList->tail) {
        pList->tail = temp->previous;
        Node* temp1 = pList->tail;
        temp1->next = NULL;
        returning = temp->value;
        pList->current = pList->tail;
    }
    else {
        Node* toReturn = pList->current;
        returning = toReturn->value;
        Node* temp = pList->current;
        Node* temp1 = temp->previous;
        temp1->next = temp->next;
        Node* temp2 = temp->next;
        temp2->previous = temp->previous;
        pList->current = temp2;
    }
    // Node* node_available = temp;
    temp->next = NULL;
    temp->previous = NULL;
    temp->value = 0;
    Node_Stack_counter++;
    Number_of_Nodes_used--;
    pList->number_of_nodes--;
    Node_Stack[Node_Stack_counter] = temp;
    return returning;  
}
// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    if(pList->head == NULL){
        return NULL;
    }
    pList->current = pList->tail;
    return List_remove(pList);
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
    Node* temp;
    while(pList->current){
        temp = pList->current;
        printf("497 data inside ListLast = %d\n", *((int *)(temp->value)));
        printf("k is: %d\n", k);
        if(temp->value && (*pComparator)(temp->value, pComparisonArg)){
            pList->current = temp;
            return temp->value;
        }
        pList->current = temp->next;

    }
    pList->check_if_at_tail = true;
    return NULL;
}

// Delete pList. itemFree is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFree)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.

void List_free(List* pList, FREE_FN pItemFreeFn){
    if(Head_Stack_counter == 9){
        return;
    }
    if(pList->head == NULL && pList->current == NULL && pList->tail == NULL && pList->number_of_nodes == 0){
        pList->head = NULL;
        pList->current = NULL;
        pList->tail = NULL;
        pList->number_of_nodes = 0;
        Head_Stack_counter++;
        Number_of_Heads_used--;
        Head_Stack[Head_Stack_counter] = pList;
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
    Node_Stack_counter++;
    Number_of_Nodes_used--;
    pList->number_of_nodes--;
    Node_Stack[Node_Stack_counter] = temp;

    // List* head_available = pList;
    pList->head = NULL;
    pList->current = NULL;
    pList->tail = NULL;
    pList->number_of_nodes = 0;
    Head_Stack_counter++;
    Number_of_Heads_used--;
    Head_Stack[Head_Stack_counter] = pList;
    
};


void List_print(List* pList) {
    Node *pNode = pList->head;
    while(pNode != NULL) {
        printf("%d->", *((int*)(pNode->value)));
        pNode = pNode->next;
    }
    printf("\n");
}
void printStates(List* pList) {
    Node* curr = pList->current;
    Node* head = pList->head;
    Node* last = pList->tail;
    int size = pList->number_of_nodes;

    head == NULL?printf("NULL\n"):
                printf("Head:  %d      ", *((int*)(head->value)));
    head->next == NULL?printf("NULL         "):
                printf("Head_next: %d      ", *((int*)(head->next->value)));
    head->previous == NULL?printf("NULL\n"):
                printf("Head_prev: %d\n", *((int*)(head->previous->value)));

    last == NULL?printf("NULL\n"):
                printf("Last:  %d      ", *((int*)(last->value)));
    last->next == NULL?printf("NULL              "):
                printf("Last_next: %d      ", *((int*)(last->next->value)));
    last->previous == NULL?printf("NULL\n"):
                printf("last_prev: %d\n", *((int*)(last->previous->value)));

    if (curr != NULL) {
        curr == NULL?printf("NULL\n"):
                    printf("Curr:  %d      ", *((int*)(curr->value)));
        curr->next == NULL?printf("NULL              "):
                    printf("Curr_next: %d      ", *((int*)(curr->next->value)));
        curr->previous == NULL?printf("NULL\n"):
                    printf("Curr_prev: %d\n", *((int*)(curr->previous->value)));
    }
    
    printf("Size:  %d\n", size);
    printf("\n");
}

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



