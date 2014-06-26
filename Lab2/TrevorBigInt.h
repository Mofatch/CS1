/*
 * 	Names: 		Trevor Minnix, Travis Bashor
 * 	Class:		COP3502C-14Summer C001
 * 	Lab Group:	Lab11
 *
 * 	Description: This header file contains function prototypes and type
 * 	definitions for BigInt.c.
 */

#ifndef BIGINT_H_
#define BIGINT_H_

typedef unsigned int uint;
typedef unsigned long ulong;
typedef void* Object;

typedef struct _BigInt{
	DoubleLinkedList* number;
}BigInt;

//allocates memory for a BigInt and initializes the first digit of the number stored
BigInt* allocBigInt(uint);

//frees memory allocated to BigInt
void releaseBigInt(BigInt*);

//makes sure number is in base 10
void simplifyBigInt(BigInt*);

//adds two BigInts and returns a pointer to a new BigInt
BigInt* addBigInt(BigInt*, BigInt*);

//returns an BigInt* the holds the sum of the digits of the input BigInt*
BigInt* sumOfDigits(BigInt*);

//mulitplies two BigInts and returns a new BigInt
BigInt* multiplyBigInt(BigInt*, BigInt*);

//shifts number left (multiplies by ten)
BigInt* shiftLeftBigInt(BigInt*);

//shifts number right (divides number by ten and truncates)
BigInt* shiftRightBigInt(BigInt*);

//returns 	-1 if first is smaller than second
//			 1 if first is larger than second
//			 0 if first is equal to second
int compareBigInt(BigInt*, BigInt*);

//returns true if BigInt is evenly divisible by digit
bool isBigIntDividableBy(BigInt*, uint);

//converts BigInt to int
uint toInt(BigInt*);

//prints a BigInt
void printBigInt(BigInt*);

#endif /* BIGINT_H_ */
