/*
 * 	Names: 		Trevor Minnix, Travis Bashor
 * 	Class:		COP3502C-14Summer C001
 * 	Lab Group:	Lab11
 *
 * 	Description: These functions allow for the use of a double linked list data
 * 	structure. A double linked list is a collections of nodes that point to
 * 	both the previous and next node in the list. Nodes at the tail and head of
 * 	the list point to NULL. The functions provided include appending,
 * 	inserting, and removing items from a list, reversing a list, halving a
 * 	list, printing a list, and printing the address pointers of the nodes of
 * 	a list.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DoubleLinkedList.h"

//allocates memory for DoubleLinkedList contained DNodes that hold data of elementSize bytes
DoubleLinkedList* allocDList(uint elementSize){
	DoubleLinkedList* dlist = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
	dlist->head = NULL;
	dlist->tail = NULL;
	dlist->length = 0;
	dlist->elementSize = elementSize;

	return dlist;
}

//allocates memory for a DNodes that holds data of elementSize bytes
DNode* allocDNode(uint elementSize){
	DNode* node = (DNode*)malloc(sizeof(DNode));
	node->data = (Object)malloc(sizeof(elementSize));
	node->next = NULL;
	node->prev = NULL;

	return node;
}

//frees memory from DList
void releaseDList(DoubleLinkedList* dlist){
	DNode* ptr1;
	DNode* ptr2;

	//free DNodes until given a null value for next
	ptr1 = dlist->head;
	while(ptr1){
		ptr2 = ptr1->next;
		//free data within node
		if(ptr1->data){
			free(ptr1->data);
		}
		free(ptr1);
		ptr1 = ptr2;
	}

	free(dlist);
}

//adds an element at the end of a DoubleLinkedList
void appendDList(DoubleLinkedList* dlist, Object newElement){

	//declare DNode to hold newElement
	DNode* new = allocDNode(dlist->elementSize);
	//new->data = newElement;
	memcpy(new->data, newElement, dlist->elementSize);

	//case for length == 0
	if(dlist->length == 0){
		dlist->head = new;
		dlist->tail = new;
		dlist->length += 1;
		return;
	}

	//fix addresses
	dlist->tail->next = new;
	new->prev = dlist->tail;
	dlist->tail = new;

	//increment length
	dlist->length += 1;

	return;
}

//adds and element at the beginning of a DoubleLinkedList
void insertDList(DoubleLinkedList* dlist, Object newElement){
	//declare DNode to hold newElement
	DNode* new;

	if(dlist->length == 0){
		appendDList(dlist, newElement);
		return;
	}

	//allocate new
	new = allocDNode(dlist->elementSize);
	//new->data = newElement;
	memcpy(new->data, newElement, dlist->elementSize);

	//fix addresses
	new->next = dlist->head;
	dlist->head->prev = new;
	dlist->head = new;

	//increment length
	dlist->length += 1;

	return;
}

//adds an element at the specified position in a DoubleLinkedList
void insertDListElementAt(DoubleLinkedList* dlist, Object newElement, uint position){
	int i;
	DNode* ptr = dlist->head;

	//declare DNode ptr to hold new
	//allocation will occur in this function if the insert and append function are not called, as they allocate their own DNode
	DNode* new;

	//give error message if the requested position is out of bounds
	if(position > dlist->length){	//inserting to length is valid, as it is equivalent to append
		printf("Error: position out of bounds.\n");
		return;
	}

	//case for position == 0
	if(position == 0){
		insertDList(dlist, newElement);
		return;
	}

	//case for position == length
	if(position == dlist->length){
		appendDList(dlist, newElement);
		return;
	}

	//allocate memory for new
	new = allocDNode(dlist->elementSize);
	//new->data = newElement;
	memcpy(new->data, newElement, dlist->elementSize);

	//get the address of the node before position
	for(i = 0; i < position-1; ++i){
		ptr = ptr->next;
	}

	//fix addresses of next and prev for new and surrounding nodes
	new->prev = ptr;
	new->next = ptr->next;
	new->next->prev = new;
	ptr->next = new;

	//increment dlist length
	dlist->length += 1;

	return;
}

//returns the address of a DoubleLinkedList that contains the elements of the input list in reverse order
DoubleLinkedList* reverseDList(DoubleLinkedList* dlist){
	int i;
	DNode* ptr = dlist->head;
	//create and allocate new dlist
	DoubleLinkedList* revlist = allocDList(dlist->elementSize);

	//add elements to revlist, if there are any
	for(i = 0; i < dlist->length; ++i){
		insertDList(revlist, ptr->data);
		ptr = ptr->next;
	}

	return revlist;
}

//returns the address of a DoubleLinkedList that contains the elements of the input list after the midpoint
DoubleLinkedList* halfList(DoubleLinkedList* dlist){
	int i;
	DNode* ptr = dlist->tail;
	DoubleLinkedList* halflist = allocDList(dlist->elementSize);

	for(i = 0; i < dlist->length - (dlist->length/2); ++i){
		insertDList(halflist, ptr->data);
		ptr = ptr->prev;
	}

	return halflist;
}

//removes the element at the input position in a DoubleLinkedList
Object removeDList(DoubleLinkedList* dlist, int position){
	int i;
	Object removedData = (Object)malloc(dlist->elementSize);
	DNode* ptr = dlist->head;

	//check for valid position
	if(position > dlist->length - 1 || position < 0 || dlist->length == 0){
		//printf("Error: out of bounds.\n");
		return NULL;
	}

	//get to position in dlist
	for(i = 0; i < position; ++i){
		ptr = ptr->next;
	}

	//store data to be removed
	//removedData = ptr->data;
	memcpy(removedData, ptr->data, dlist->elementSize);

	//fix addresses and then free the specified DNode
	if(dlist->length == 1){							//length == 1 case
		dlist->head = NULL;
		dlist->tail = NULL;
	}
		else if(position == 0){						//head case
			ptr->next->prev = NULL;
			dlist->head = ptr->next;
		}
			else if(position == dlist->length - 1){	//tail case
				ptr->prev->next = NULL;
				dlist->tail = ptr->prev;
			}
				else{								//middle case
						ptr->prev->next = ptr->next;
						ptr->next->prev = ptr->prev;
				}

	//free node
	free(ptr->data);
	free(ptr);

	//decrement dlist length
	dlist->length -= 1;

	return removedData;
}

//prints the elements of a DoubleLinkedList (as characters) in braces and separated by commas
void printDList(DoubleLinkedList* dlist){
	int i;
	DNode* ptr = dlist->head;

	printf("{");
	if(dlist->head){
		printf("%c", *(uint*)ptr->data);
		ptr = ptr->next;
	}

	for(i = 1; i < dlist->length; ++i){
		printf(",%c", *(char*)ptr->data);
		ptr = ptr->next;
	}
	printf("}\n");
}

//prints addresses of linked list elements in both directions
void debugDList(DoubleLinkedList* list){
    DNode* iter = list->head;
    while(iter){
        printf("%p\t", iter);
        iter = iter->next;
    }
    printf("\n");
    iter = list->tail;
    while(iter){
        printf("%p\t", iter);
        iter = iter->prev;
    }
    printf("\n\n");
}
