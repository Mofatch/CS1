/*
 * 	Names: 		Trevor Minnix, Travis Bashor
 * 	Class:		COP3502C-14Summer C001
 * 	Lab Group:	Lab11
 *
 * 	Description: This header file contains function prototypes and type
 * 	definitions for DoubleLinkedList.c.
 */

#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

typedef unsigned int uint;
typedef unsigned long ulong;
typedef void* Object;

typedef struct _DNode{
	Object data;
	struct _DNode* prev;
	struct _DNode* next;
}DNode;

typedef struct _DoubleLinkedList{
	DNode* head;
	DNode* tail;
	uint length;
	uint elementSize;
}DoubleLinkedList;

//allocates memory for DoubleLinkedList contained DNodes that hold data of elementSize bytes
DoubleLinkedList* allocDList(uint);

//allocates memory for a DNodes that holds data of elementSize bytes
DNode* allocDNode(uint);

//frees memory from DList
void releaseDList(DoubleLinkedList*);

//adds an element at the end of a DoubleLinkedList
void appendDList(DoubleLinkedList*, Object);

//adds and element at the beginning of a DoubleLinkedList
void insertDList(DoubleLinkedList*, Object);

//adds an element at the specified position in a DoubleLinkedList
void insertDListElementAt(DoubleLinkedList* dlist, Object, uint);

//returns the address of a DoubleLinkedList that contains the elements of the input list in reverse order
DoubleLinkedList* reverseDList(DoubleLinkedList*);

//returns the address of a DoubleLinkedList that contains the elements of the input list after the midpoint
DoubleLinkedList* halfList(DoubleLinkedList*);

//removes the element at the input position in a DoubleLinkedList
Object removeDList(DoubleLinkedList*, int);

//prints the elements of a DoubleLinkedList (as characters) in braces and separated by commas
void printDList(DoubleLinkedList*);

//prints addresses of linked list elements in both directions
void debugDList(DoubleLinkedList*);

#endif /* DOUBLELINKEDLIST_H_ */
