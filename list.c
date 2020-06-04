/**
 * list.c for Assignment 1, CMPT 300 Summer 2020
 * Name: Devansh Chopra
 * Student #: 301-275-491
 */

// Header files imported
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Declaring List Array and Nodes Array of structs
static List Arr[LIST_MAX_NUM_HEADS];
static Node Nodes[LIST_MAX_NUM_NODES];

// Helper variables
static int Head_Index= 0;
static int Head_List_counter = 0;
static List* HeadsList = NULL;
static int Node_Index = 0;
static int Node_List_counter = 0;
static Node* NodesList = NULL;
static bool FirstTime_ListCreate = true;

// Helper Functions 
static void* HeadList_Pop();
static void HeadList_Push(void* pItem);
static void* NodesList_Pop();
static void NodesList_Push(void* pItem);

void printNodesList(Node* List);

// Creates an empty list
List* List_create(){
    if (FirstTime_ListCreate){
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
    FirstTime_ListCreate = false;
    }
    List* NewList;
    if (Head_Index < LIST_MAX_NUM_HEADS){
        NewList = &(Arr[Head_Index]);
        Head_Index++;
    }
    else{
        if(Head_List_counter == 0){
            return NULL;
        }
        NewList = HeadList_Pop();
    }

    printf("Head Index in the Head Array is: %d\n", Head_Index);
    // printf("50 %p\n", &(Arr[Head_Index]));
    return NewList;
}

// Returns the number of items in pList.
int List_count(List* pList){
    if(pList==NULL){
        return -1;
    }
    if(pList->number_of_nodes < 0 || pList == NULL){
        return -1;
    }
    else{
    printf("Number of nodes in the list %d\n", pList->number_of_nodes);
    return pList->number_of_nodes;
    }
}

// Returns a pointer to the first item in pList and makes the first item the current item.
void* List_first(List* pList){
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
    if(pList->head == NULL){
        pList->current = NULL;
        return NULL;
    }
    if(pList->check_if_at_head || pList->check_if_at_tail){
        pList->check_if_at_head = false;
        pList->check_if_at_tail = false;
    }
    pList->current = pList->head;
    Node* temp = pList->current;
    return temp->value;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
void* List_last(List* pList){
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
    if(pList->head == NULL && pList->current == pList->head){
        pList->current = NULL;
        return NULL;
    }
    if(pList->check_if_at_head || pList->check_if_at_tail){
        pList->check_if_at_head = false;
        pList->check_if_at_tail = false;
    }
    pList->current = pList->tail;
    Node* temp = pList->current;
    return temp->value;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
void* List_next(List* pList){
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
    if(pList->head == NULL && pList->current == pList->head){
        pList->current = NULL;
        return NULL;
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
        return NULL;
    }
    else if (pList->check_if_at_tail){
        return NULL;
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
void* List_prev(List* pList){
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
    if(pList->head == NULL && pList->current == pList->head){
        Node* temp = pList->head;
        pList->current = NULL;
        return NULL;
    }
    else if (pList->current == pList->head){
        pList->check_if_at_head = true;
        return NULL;
    }
    else if(pList->check_if_at_head){
        return NULL;
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
void* List_curr(List* pList){
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
    if (pList->check_if_at_head || pList->check_if_at_tail || (pList->head == NULL && pList->head == pList->current)){
        return NULL;
    }
    else{
    Node* temp = pList->current;
    printf("The new current item after List_curr is: %d\n", *((int *)(temp->value)));
    return temp->value;
    }
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
int List_add(List* pList, void* pItem){
    if(pList->number_of_nodes < 0 || pList == NULL){
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
    if(pList->head == NULL && pList->head == pList->current){
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

// Adds item to pList directly before the current item, and makes the new item the current one. 
int List_insert(List* pList, void* pItem){
    if(pList->number_of_nodes < 0 || pList == NULL){
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
    if(pList->head == NULL && pList->head == pList->current){
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

// Adds item to the end of pList, and makes the new item the current one. 
int List_append(List* pList, void* pItem){
    if(pList->number_of_nodes < 0 || pList == NULL){
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
    if(pList->head == NULL && pList->head == pList->current){
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
int List_prepend(List* pList, void* pItem){
    if(pList->number_of_nodes < 0 || pList == NULL){
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
    if(pList->head == NULL && pList->head == pList->current){
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

// Return current item and take it out of pList. Make the next item the current one.
void* List_remove(List* pList){
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
    if (pList->check_if_at_head || pList->check_if_at_tail || (pList->head == NULL && pList->head == pList->current)){
        return NULL;
    }
    Node* temp = pList->current;
    if(pList->number_of_nodes == 1){
        pList->head = NULL;
        pList->tail = NULL;
        pList->current = NULL;
    }
    else if (pList->current == pList->head && pList->current != NULL && pList->head != NULL) {
        pList->head = temp->next;
        Node* temp1 = pList->head;
        temp1->previous = NULL;
        pList->current = pList->head;
        printf("The new current/head item after List_remove is: %d\n", *((int *)(temp1->value)));
    }
    else if (pList->current == pList->tail && pList->current != NULL && pList->tail != NULL) {
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

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
void List_concat(List* pList1, List* pList2){
    if(pList1->number_of_nodes < 0 || pList1 == NULL || pList2->number_of_nodes < 0 || pList2 == NULL){
        return;
    }
    if(pList1 == pList2){
        return;
    }
    if(pList1->head == NULL && pList2->head == NULL){
        //merge list2 in one and put list2's head back into the stack
        //current pointer is null
    }
    else if(pList1->head == NULL && pList2->head != NULL){
        pList1->head = pList2->head;
        pList1->tail = pList2->tail;
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

// Delete pList. itemFree is a pointer to a routine that frees an item. 
void List_free(List* pList, FREE_FN pItemFreeFn){
    if(pList == NULL || pList->number_of_nodes < 0){
        return;
    }
    // if(pList->number_of_nodes < 0){
    //     return;
    // }
    // if(pList->head == NULL && pList == HeadsList){
    //     return;
    // }
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
}

// Return last item and take it out of pList. Make the new last item the current one.
void* List_trim(List* pList){
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
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
    if(pList->number_of_nodes < 0 || pList == NULL){
        return NULL;
    }
    if(pList->head == NULL){
        return NULL;
    }
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
    return NULL;
}

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
    else{
        return NULL;
    }
}