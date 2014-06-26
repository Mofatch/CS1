/*
 * BigInt.h
 *
 *  Created on: Jun 5, 2014
 *      Author: Trevor
 */

#ifndef BIGINT_H_
#define BIGINT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "TrevorDLL.h"

typedef unsigned int uint;
typedef unsigned long ulong;
typedef void* Object;

typedef struct _BigInt{
	DoubleLinkedList* number;
}BigInt;

// prototypes
void simplifyBigInt(BigInt* bi);
BigInt* shiftLeftBigInt(BigInt* bi);
uint* allocDigit(uint number);
uint toInt(BigInt* bi);

//allocates memory for a BigInt and initializes the first digit of the number stored
BigInt* allocBigInt(uint digit){
	//allocate memory
	BigInt* bi = (BigInt*)malloc(sizeof(BigInt));
	bi->number = allocDList(sizeof(uint));

	//add smallNumber as the first digit in bi
	appendDList(bi->number, allocDigit(digit));

	simplifyBigInt(bi);

	return bi;
}

//frees memory allocated to BigInt
void releaseBigInt(BigInt* bi){
	if(bi->number){
		releaseDList(bi->number);
	}
	free(bi);
	return;
}

//makes sure number is in base 10
void simplifyBigInt(BigInt* bi){
	uint temp;
	bool simplified = true;
	DNode* ptr = bi->number->tail;

	//check last element
	if(*(uint*)(bi->number->tail->data)  > 9){
		puts("too big");
		simplified = false;
		temp = *(uint*)ptr->data / 10;
		appendDList(bi->number, &temp);
		*(uint*)ptr->data %= 10;
	}

	ptr = ptr->prev;

	//run through remaining element moving from tail to head
	while(ptr){
		puts("wheeeee!");
		if(*(uint*)ptr->data > 9){
			simplified = false;
			*(uint*)ptr->next->data += *(uint*)ptr->data /10;
			*(uint*)ptr->data %= 10;
		}
		ptr = ptr->prev;
	}

	//remove any leading zero
	while(bi->number->tail && *(uint*)bi->number->tail->data == 0 && bi->number->length != 1){
		puts("removing zeroes...");
		removeDList(bi->number, bi->number->length - 1);
	}

	if(simplified){
		return;
	}
	else{
		simplifyBigInt(bi);
	}

	return;
}

//adds two BigInts and returns a pointer to a new BigInt
BigInt* addBigInt(BigInt* first, BigInt* second){
	//counter
	int i;
	//hold largest length
	uint len = (first->number->length >= second->number->length ? first->number->length : second->number->length);
	//hold temporary sum for 1 DNode
	uint tempSum = 0;
	//hold sum
	BigInt* sum = allocBigInt(0);
	//pointers for DNodes in each BigInt
	DNode* ptr1 = first->number->head;
	DNode* ptr2 = second->number->head;

	//empty the sum dll
	removeDList(sum->number, 0);

	//add each digit of the two numbers, allowing value greater than 9
	for(i = 0; i < len; ++i){
		if(ptr1){
			tempSum += *(uint*)ptr1->data;
			ptr1 = ptr1->next;
		}
		if(ptr2){
			tempSum += *(uint*)ptr2->data;
			ptr2 = ptr2->next;
		}
		appendDList(sum->number, &tempSum);
		tempSum = 0;
	}

	simplifyBigInt(sum);

	return sum;
}

BigInt* sumOfDigits(BigInt* bi){
	BigInt* tempSum;
	BigInt* sum = allocBigInt(0);
	DNode* ptr = bi->number->head;

	while(ptr){
		tempSum = allocBigInt(*(uint*)ptr->data);
		sum = addBigInt(sum, tempSum);
		releaseBigInt(tempSum);
		ptr = ptr->next;
	}

	return sum;
}

BigInt* multiplyBigInt(BigInt* first, BigInt*second){
	uint i, j, k;
	uint tempDigit;
	//BigInt to hold product and to hold temporary int
	BigInt* product;
	BigInt* tempProduct;
	//pointers to hold individual digits
	DNode* ptr1 = first->number->head;
	DNode* ptr2 = second->number->head;



	//check for empty BigInt
	if(!ptr1 || !ptr2){
		printf("Error: cannot multiply by empty list\n");
		return NULL;
	}

	//allocation after checking for empty list
	product = allocBigInt(0);
	tempProduct = allocBigInt(0);

	//empty tempProduct
	removeDList(tempProduct->number, 0);

	for(i = 0; i < first->number->length; ++i){

		//creates tempProduct which stores the result of each digit of second being multiplied by one the ith digit of first
		for(j = 0; j < second->number->length; ++j){
			tempDigit = *(uint*)ptr1->data * *(uint*)ptr2->data;
			appendDList(tempProduct->number, &tempDigit);
			ptr2 = ptr2->next;
		}
		simplifyBigInt(tempProduct);

		//shift left to increase place value of tempProduct
		for(k = 0; k < i; ++k){
			tempProduct = shiftLeftBigInt(tempProduct);
		}

		//add tempProduct to product and then tempProduct will be recalcuated for the next digit of first
		product = addBigInt(product, tempProduct);
		simplifyBigInt(product);

		//empty tempProduct
		releaseBigInt(tempProduct);
		tempProduct = allocBigInt(0);
		removeDList(tempProduct->number, 0);

		//increment first and reset second
		ptr1 = ptr1->next;
		ptr2 = second->number->head;
	}

	releaseBigInt(tempProduct);

	return product;
}

//shifts number left (multiplies by ten)
BigInt* shiftLeftBigInt(BigInt* bi){
	uint a;
	DNode* ptr = bi->number->tail;
	BigInt* result = allocBigInt(0);
	puts("removing...");
	printf("%u", toInt(result));
	removeDList(result->number, 0);

	//copy input list
	while(ptr){
		insertDList(result->number, ptr->data);
		ptr = ptr->prev;
	}

	//add a zero
	a = 0;
	insertDList(result->number, &a);

	return result;
}

//shifts number right (divides number by ten and truncates)
BigInt* shiftRightBigInt(BigInt* bi){
	DNode* ptr = bi->number->tail;
	BigInt* result = allocBigInt(0);
	removeDList(result->number, 0);

	//copy input list
	while(ptr){
		insertDList(result->number, ptr->data);
		ptr = ptr->prev;
	}

	//remove first digit
	removeDList(result->number, 0);

	return result;
}

//returns 	-1 if first is smaller than second
//			 1 if first is larger than second
//			 0 if first is equal to second
int compareBigInt(BigInt* first, BigInt* second){
	DNode* ptr1;
	DNode* ptr2;

	//compare by length
	if(first->number->length > second->number->length){
		return 1;
	}
	if(first->number->length < second->number->length){
		return -1;
	}

	//if lengths are equal, check each digit
	ptr1 = first->number->tail;
	ptr2 = second->number->tail;

	while(ptr1){	//if lengths are 0, the BigInts are equal and this loop will not be performed
		if(*(uint*)ptr1->data > *(uint*)ptr2->data){
			return 1;
		}
		if(*(uint*)ptr1->data < *(uint*)ptr2->data){
			return -1;
		}

		ptr1 = ptr1->prev;
		ptr2 = ptr2->prev;
	}

	return 0;
}

//returns true if BigInt is evenly divisible by digit
bool isBigIntDividableBy(BigInt* bi, uint digit){
	int tempInt = 0;
	BigInt* tempBigInt;

	switch(digit){
	case 2:
		//divisible by 2 if even
		if(*(uint*)bi->number->head->data % 2 == 0){
			return true;
		}
		else{
			return false;
		}
		break;
	case 3:
		//divisible by 3 if the sum of digits is divisible by 3
		//get sum of digits
		tempBigInt = sumOfDigits(bi);
//		while(tempBigInt->number->length > 1){		//reduce to one digit
//			tempBigInt = sumOfDigits(tempBigInt);
//		}

		if(*(uint*)tempBigInt->number->head->data % 3 == 0){
			releaseBigInt(tempBigInt);
			return true;
		}
		else{
			releaseBigInt(tempBigInt);
			return false;
		}

		break;
	case 4:
		//divisible by 4 if last two digits are divisible by 4
		tempInt = (*(uint*)bi->number->head->data) + 10*(*(uint*)bi->number->head->next->data);
		if(tempInt % 4 == 0){
			return true;
		}
		else{
			return false;
		}
		break;
	case 5:
		//divisible by 5 if number ends in a 5 or 0
		if(*(uint*)bi->number->head->data % 5 == 0){
			return true;
		}
		else{
			return false;
		}
		break;
	case 6:
		//divisible by 6 if divisible by 2 and 3
		if(isBigIntDividableBy(bi, 2) && isBigIntDividableBy(bi, 2)){
			return true;
		}
		else{
			return false;
		}
		break;
	case 8:
		//divisible by 8 if the last three digits are divisible by 8
		tempInt = (*(uint*)bi->number->head->data) + 10*(*(uint*)bi->number->head->next->data) + 100*(*(uint*)bi->number->head->next->next->data);
		if(tempInt % 8 == 0){
			return true;
		}
		else{
			return false;
		}
		break;
	case 9:
		//divisible by 9 if the sum of the digits is divisible by 9

		//get sum of digits
		tempBigInt = sumOfDigits(bi);
		//reduce to one digit
		while(tempBigInt->number->length > 1){
			tempBigInt = sumOfDigits(tempBigInt);
		}

		if(*(uint*)tempBigInt->number->head->data % 9 == 0){
			releaseBigInt(tempBigInt);
			return true;
		}
		else{
			releaseBigInt(tempBigInt);
			return false;
		}
		break;
	default:
		break;
	}

	return 0;
}

//converts BigInt to int
uint toInt(BigInt* bi){
	int i = 0;
	int sum = 0;
	DNode* ptr = bi->number->head;

	for(i = 0; i < bi->number->length; ++i){
		sum += *(uint*)ptr->data * pow(10, i);
		ptr = ptr->next;
	}

	return sum;
}

//prints a BigInt
void printBigInt(BigInt* bi){
	int i;
	DNode* ptr = bi->number->tail;

	for(i = 0; i < bi->number->length; ++i){
		if(i != 0 && (bi->number->length-i)%3 == 0){
			printf(",");	//put commas every third place value
		}
		printf("%u", *(uint*)ptr->data);
		ptr = ptr->prev;
	}

}

// create memory for a given uint
uint* allocDigit(uint number) {
  uint *myNum = malloc(sizeof(number));
  *myNum = number;

  return myNum;
}

#endif /* BIGINT_H_ */
