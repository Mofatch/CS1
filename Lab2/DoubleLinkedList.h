#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>

// typedefs
typedef unsigned int uint;
typedef unsigned long ulong;
typedef void* Object;
typedef struct _DNode {
  Object data;
  struct _DNode *prev;
  struct _DNode *next;
} DNode;
typedef struct _DoubleLinkedList {
  DNode *head;
  DNode *tail;
  uint length;
  uint elementSize;
} DoubleLinkedList;
typedef struct _BigInt {
  DoubleLinkedList *number;
} BigInt;

// prototypes
void appendDList(DoubleLinkedList *list, Object newElement);
void insertDList(DoubleLinkedList *list, Object newElement);

DNode* allocNode(uint elementSize) {
  DNode *newNode = (DNode *)malloc(sizeof(DNode));
  newNode->prev = NULL;
  newNode->next = NULL;
  newNode->data = (Object)malloc(sizeof(elementSize));

  return newNode;
}

DoubleLinkedList* allocDList(uint elementSize) {
  DoubleLinkedList *newList = malloc(sizeof(DoubleLinkedList));
  newList->head = NULL;
  newList->tail = NULL;
  newList->elementSize = elementSize;
  newList->length = 0;

  return newList;
}

void releaseDList(DoubleLinkedList *list) {
  DNode *navigator = list->head;

  while (navigator) {
    // free the nodes and data within
    if(navigator->prev) {
      if(navigator->prev->data) {
        free(navigator->prev->data);
        navigator->prev->data = NULL;
      }
      free(navigator->prev);
      navigator->prev = NULL;
    }
    // if navigator is at the end, free navigator
    if(!navigator->next) {
      if(navigator->data) {
        free(navigator->data);
        navigator->data = NULL;
      }
      free(navigator);
      navigator = NULL;
      break;
    }
    // step forward
    navigator = navigator->next;
  }
  // free the list
  free(list);
}

void insertDListElementAt(DoubleLinkedList* list, Object newElement, uint position) {
  DNode *newNode = allocNode(list->elementSize);
  newNode->data = newElement;

  // if the position is out of range, allowing for appending
  if(position > list->length)
    puts("Position out of range.");
  else if(position == list->length)
    appendDList(list, newElement);
  else if(position == 0) {
    insertDList(list, newElement);
  }
  else {
    // make a navigator and index
    DNode *navigator = list->head;
    int index = 0;
    while(navigator) {
      if(index == position) {
        // connect newNode to prev
        newNode->prev = navigator->prev;
        newNode->prev->next = newNode;

        // connect newNode to next
        newNode->next = navigator;
        navigator->prev = newNode;

        // increment the list length and exit the loop
        list->length++;
        break;
      }
      index++;
      navigator = navigator->next;
    } 
  }
}

void appendDList(DoubleLinkedList *list, Object newElement) {
  DNode *newNode = allocNode(list->elementSize);
  newNode->data = newElement;

  // empty list
  if(list->length == 0) {
    list->head = newNode;
  }
  // length 1
  else if(list->length == 1) {
    list->head->next = newNode;
    newNode->prev = list->head;
  }
  // length 2+
  else {
    list->tail->next = newNode;
    newNode->prev = list->tail;
  }

  // change tail and increment list length
  list->tail = newNode;
  list->length++;
}

void printDList(DoubleLinkedList *list) {
  DNode *navigator = list->head;

  printf("{");
  // if it is a list of characters
  if(list->elementSize == sizeof(char)) {
    while(navigator) {
      if(navigator->next)
        printf("%c,", *(char *)navigator->data);
      else
        printf("%c", *(char *)navigator->data);

      // move forward
      navigator = navigator->next;
    }
  }
  // otherwise, it's a list of uints
  else {
    while(navigator) {
      if(navigator->next)
        printf("%u,", *(uint *)navigator->data);
      else
        printf("%u", *(uint *)navigator->data);

      // move forward
      navigator = navigator->next;
    }
    
  }
  printf("}\n");
}

void insertDList(DoubleLinkedList *list, Object newElement) {
  DNode *newNode = allocNode(list->elementSize);
  newNode->data = newElement;

  // empty list
  if(list->length == 0) {
    // make newNode tail as well
    list->tail = newNode;
  }
  // length 1
  else if(list->length == 1) {
    // connect newNode to tail
    newNode->next = list->tail;
    list->tail->prev = newNode;
  }
  // length 2+
  else {
    list->head->prev = newNode;
    newNode->next = list->head;
  }

  // make new head and increment list length
  list->head = newNode;
  list->length++;
}

DoubleLinkedList* reverseDList(DoubleLinkedList *list) {
  DoubleLinkedList *newList = allocDList(list->elementSize);

  // create a navigator
  DNode *navigator = list->head;

  while(navigator) {
    insertDList(newList, navigator->data);
    navigator = navigator->next;
  }

  return newList;
}

Object removeDList(DoubleLinkedList *list, int position) {
  int index = 0;
  Object element;
  DNode *navigator = list->head;
  
  // out of bounds
  if(position >= list->length || position < 0) {
    puts("Position out of range.");
    return NULL;
  }
  // empty list
  else if(list->length == 0) {
    puts("The list is empty.");
    return NULL;
  }
  // length 1
  else if(list->length == 1) {
    element = navigator->data;
    list->head = NULL;
    list->tail = NULL;
  }
  // length 2+
  else{
    while(navigator) {
      if(index == position) {
        // collect data
        element = navigator->data;

        // first element
        if(index == 0) {
          navigator->next->prev = NULL;
          list->head = navigator->next;
        }
        // last element
        else if(index == (list->length - 1)) {
          navigator->prev->next = NULL;
          list->tail = navigator->prev;
        }
        // anything in the range (first,last)
        else {
          navigator->prev->next = navigator->next;
          navigator->next->prev = navigator->prev;
        }

        break;
      }
      // step forward
      navigator = navigator->next;
      index++;
    }
  }
  // decrement list length and free node
  list->length--;
  free(navigator);

  return element;
}

DoubleLinkedList* halfList(DoubleLinkedList *list) {
  // create blank list
  DoubleLinkedList *newList = allocDList(list->elementSize);

  // create navigator and index counter
  DNode *navigator = list->head;
  int index = 0;

  while(navigator) {
    if(index >= ( (double)list->length / 2) ) {
      appendDList(newList, navigator->data);
    }

    // move forward
    navigator = navigator->next;
    index++;
  }

  return newList;
}

void printElement(Object element) {
    printf("%u\n", *(uint *)element);
}
#endif