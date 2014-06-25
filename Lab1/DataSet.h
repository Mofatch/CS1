/* File: DataSet.h
Authors: Travis Bashor/Trevor Minnix
Class: COP3502C, Summer C 2014
DataSet.h: This file implements a math set and its operations.
A math set is defined as linear collection elements with no 
duplicates on it. This library depends on the DArray.h as the 
internal array of the DataSet is really a DArray with additional 
functionality to ensure that no duplicates are found and the 
operations are possible.
*/
#ifndef DATASET_H_
#define DATASET_H_

#include "DArray.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int uint;

struct DataSet {
	struct DArray* array; // address of the array
	Byte min, max;
};

// prototypes
bool contains(struct DataSet* set, Byte val);
Word Sum(struct DataSet* set);

// creates a new data set with a default size-10 array
struct DataSet* allocDataSet() {
	struct DataSet* dataSet = (struct DataSet*) malloc(sizeof(struct DataSet));
	dataSet->array = allocDArray(10);
  dataSet->min = 255;
  dataSet->max = 0;
  return dataSet;
}

// frees memory, starting from the deepest node
void releaseDataSet(struct DataSet* set) {
  if(set) {
    if(set->array) {
      releaseDArray(set->array);
    }
    free(set);
  }
}

// adds a value onto the array within DataSet, checks for new min, max
void appendDataSet(struct DataSet* dataSet, Byte newValue) {
  if(!contains(dataSet, newValue)) {
    appendDArray(dataSet->array, newValue);
    if(newValue > dataSet->max)
      dataSet->max = newValue;
    if(newValue < dataSet->min)
      dataSet->min = newValue;
  }
}

// returns A U B
struct DataSet* unionDataSet(struct DataSet* A, struct DataSet* B) {
  int index;
  struct DataSet *C;
  C = allocDataSet();

  /* Copy A, then add B. Avoiding appendDataSet() here because it would print
   an unnecessary error message during the formation of the Union set. */
  for(index = 0; index < A->array->length; ++index) {
    appendDArray(C->array, A->array->data[index]);
  }

  // add B
  for(index = 0; index < B->array->length; ++index) {
    if(!contains(C, B->array->data[index]))
      appendDArray(C->array, B->array->data[index]);
  }

  // assign min, max
  C->min = (A->min < B->min) ? A->min : B->min;
  C->max = (A->max > B->max) ? A->max : B->max;

  return C;
}

// return set of elements common to A and B
struct DataSet* intersectionDataSet(struct DataSet* A, struct DataSet* B) {
  int index;
  struct DataSet *C;
  C = allocDataSet();

  // add to C all elements of A that are in B
  for(index = 0; index < A->array->length; ++index) {
    if(contains(B, A->array->data[index]))
      appendDataSet(C, A->array->data[index]);
  }

  return C;
}

// return set of elements in A but not B
struct DataSet* diffDataSet(struct DataSet* A, struct DataSet* B) {
  int index;
  struct DataSet *C;
  C = allocDataSet();

  // check in A for values not in B
  for(index = 0; index < A->array->length; ++index) {
    if(!contains(B, A->array->data[index]))
      appendDataSet(C, A->array->data[index]);
  }

  return C;
}

// creates a subset given upper and lower bounds within the parent set
struct DataSet* subset(struct DataSet* set, uint start, uint end) {
  // index out of bounds, start greater than end
  uint i;
  struct DataSet *subset;
  subset = allocDataSet();
  if(start > end) {
    fprintf(stderr, "Starting index greater than ending index\n");
  }
  else if(start < 0 || end >= set->array->length) {
    fprintf(stderr, "Index out of bounds.\n");
  }
  else {
    for(i = start; i <= end; ++i) {
      appendDataSet(subset, set->array->data[i]);
    }
  }
  return subset;
}

// returns true if A is a subset of B
bool isSubset(struct DataSet* A, struct DataSet* B) {
  int i;
  for(i = 0; i < A->array->length; ++i) {
    if(!contains(B, A->array->data[i]))
      return false;
  }
  return true;
}

// returns the average of all values in the set
float AverageDataSet(struct DataSet* set) {
  return Sum(set) / (float) set->array->length;
}

// returns the sum of all values in the set
Word Sum(struct DataSet* set) {
  int index;
  Word sum = 0;
  for(index = 0; index < set->array->length; ++index) {
    sum += set->array->data[index];
  }
  return sum;
}

// returns a new set containing the squared elements of set
struct DataSet* Square(struct DataSet* set) {
  int index;
  struct DataSet *newSet;
  newSet = allocDataSet();
  for(index = 0; index < set->array->length; ++index) {
    appendDataSet(newSet, (uint) pow(set->array->data[index], 2));
  }
  return newSet;
}

// returns the range of the values in the data set
Byte RangeDataSet(struct DataSet* set) {
  return set->max - set->min;
}

void printDataSet(struct DataSet* dataSet) {
  int i; 
  // list all the elements
  printf("Dynamic Array Info:\n");
  printf("Length = %u\n", dataSet->array->length);
  printf("Size = %u\n", dataSet->array->size);
  printf("Data = {");
  for(i = 0; i < dataSet->array->length; ++i) {
    if(i < dataSet->array->length-1)
      printf("%u,", dataSet->array->data[i]);
    else
      printf("%u", dataSet->array->data[i]);
  }
  printf("}\n");
}

// returns true if the set is the null set
bool isNull(struct DataSet* dataSet) {
  return (dataSet->array->length == 0) ? true : false;  
}

// returns true of set contains val
bool contains(struct DataSet* set, Byte val) {
  int i;

  for(i = 0; i < set->array->length; ++i) {
    if( val == set->array->data[i])
      return true;
  }
  return false;
}

// returns true if the sets are the same
bool equals(struct DataSet* A, struct DataSet* B) {
  int i;
  if( A->array->length != B->array->length)
    return false;
  else {
  for(i = 0; i < A->array->length; ++i) {
    // if you can find any in A that aren't in B, they differ
    if(!contains(B, A->array->data[i]))
      return false;
  }
    // if you can't, they are equivalent
    return true;
  }
}

#endif /* DATASET_H_ */