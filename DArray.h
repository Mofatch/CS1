/*
 * DArray.h
 *
 *  Created on: May 21, 2014
 *      Author: lugoh008
 */

#ifndef DARRAY_H_
#define DARRAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
 
#define UNDEF 255	//could not use MIN_INT because we are working with bytes

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int uint;
//typedef struct DArray DArray;	//typedef for struct convenience

struct DArray{
	Byte* data;
	uint size;
	uint length;
};

//No need to type word struct because of the typedef located above
//DArray theData;

/**
 * Default allocation method, will allocate 10 elements maximum.
 * The DArray will increase in size when needed.
 */
/*struct DArray* allocDefaultDArray(){
	return allocDArray(10);

}*/

/**
 * Allocates size elements space instead of 10.
 */
struct DArray* allocDArray(uint size){
	struct DArray* array;
	array = (struct DArray*)malloc(sizeof(struct DArray));
	array->data = calloc(size, sizeof(Byte));
	array->size = size;	//holds the max capacity.
	array->length = 0;	//holds the number of current elements
	return array;
}

/**
 * Free the memory space so that it can be reused later.
 * We free stuff from bottom up so that we dont loose track of the memory space before the free.
 * We also must check there is something allocated, otherwise our program can crash.
 */
void releaseDArray(struct DArray* array){
	if(array){
		if(array->data){
			free(array->data);
		}
		free(array);
	}
}

/**
 * Adds an element at the end of the DArray.
 */
void appendDArray(struct DArray* array, Byte b){
	//increase size when the number of elements is equal to the size (no space for new data).
	if(array->length == array->size){
		fprintf(stderr, "Warning: Size of dynamic array is increasing to %d\n", 2*array->size);
		//increase size
		array->data = (Byte*)realloc(array->data, 2*array->size*sizeof(Byte));
												//2*array->size is twice more positions
												//* sizeof(Byte) will reserve the correct size per position
		array->size = 2*array->size*sizeof(Byte);
	}
	array->data[array->length++] = b;
	//1) array->data[array->length] = b;
	//2) ++array->length;
}

/**
 * Remove the element at position pos, and return it.
 */
Byte removeDArray(struct DArray* array, uint pos){
	//cant remove from an empty list
	if(array->length == 0){
		fprintf(stderr, "Error: Attempt to remove from an empty list\n");
		return UNDEF;	//nothing to remove
	}
	if(pos >= 0 && pos < array->length){
		//can remove
		Byte value = array->data[pos];
		//everything after pos must be shifted back
		memcpy((array->data + pos), (array->data + pos + 1), (array->length - 1) - pos);
		//then the last element is now one position behind
		--array->length;
		return value;
	}
	return UNDEF;
}

/**
 * Set an element at a given position pos to newValue, and return the oldValue.
 */
Byte setDArray(struct DArray* array, uint pos, Byte newValue){
	if(array->length == 0){
		fprintf(stderr, "Error: Attempt to set an empty list\n");
		return UNDEF;	//cannot set an empty list
	}
	if(pos >= 0 && pos < array->length){
		//can set
		Byte toReturn = array->data[pos];
		array->data[pos] = newValue;
		return toReturn;
	}
	fprintf(stderr, "Error: Invalid position to set, returning %u\n", UNDEF);
	return UNDEF;	//this should never happen
}

/**
 * Returns true if the value is included in the array, false otherwise.
 */
bool containsDArray(struct DArray* array, Byte value){
	int i = 0;
	for(i = 0; i < array->length; ++i){
		if(array->data[i] == value){
			return true;
		}
	}
	//false is return if the array is run completely and value is never found.
	return false;
}

/**
 * Applies a function to all elements in the array.
 * *function is a function pointer to a function that receives a Byte and returns a Word.
 * Such function is applied to all elements in the array.
 * The result, is an array containing the return value for each function call.
 */
Word* applyDArray(struct DArray* array, Word (*function)(Byte)){
	//# of returned values is the same as the array length (1 value per element in array)
	Word* returnValues = (Word*)calloc(array->length, sizeof(Word));
	int i = 0;
	for(i = 0; i < array->length; ++i){
		//function application, just like any other function call.
		returnValues[i] = function(array->data[i]);
	}
	return returnValues;
}

/**
 * Prints the content of the array as a Set. Also prints its length and count values.
 */
void printDArray(struct DArray* array){
	fprintf(stdout, "Dynamic Array Info:\nLength = %d\nSize = %d\nData = {", array->length, array->size);
	int i = 0;
	for(i = 0; i < array->length; ++i){
		fprintf(stdout, "%d", array->data[i]);
		if(i != array->length - 1){
			fprintf(stdout, ", ");
		}
	}
	fprintf(stdout, "}\n");
}

#endif /* DARRAY_H_ */