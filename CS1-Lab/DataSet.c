/*
 * main.c
 *
 *  Created on: May 21, 2014
 *      Author: lugoh008
 */

#include <stdio.h>
#include <stdlib.h>
#include "DArray.h"
#include "DataSet.h"

Word squareElement(Byte);
Word cubeElement(Byte);

int main(int argc, char** argv){
	//srand will force the random numbers to be always the same, so we can verify that our code works
	//normally we would want them to be different.
	srand(100);
	struct DataSet* setA;
	setA = allocDataSet();

	struct DataSet* setB;
	setB = allocDataSet();


	int i = 0;
	for(i = 0; i < 30; ++i){
		Byte element = rand() % 20;
		appendDataSet(setA, element);
		Byte event = rand() % 100;
		if(event < 30){
			//30% of chance of repeating the same number
			appendDataSet(setB, element);
		}
		else if(event < 65){
			//65% of chance of adding a different element
			//event should be a number between 0 and 99
			//make it between 0 and 49 included
			appendDataSet(setB, event % 50);
		}
		else{
			//C requires an else, even if it is empty,
			//this else does nothing, so setB could be smaller than setA
		}
	}
	//Data has been initialized, now lets test the other methods
	//Print
	printf("SET A IS:\n");
	printDataSet(setA);
	printf("SET B IS:\n");
	printDataSet(setB);

	//Union (notice that union is another C keyword),
	//actually what is does is like a struct,
	//but guarantees the block will be put right after the other
	//in this class you dont need to know it, but once more, if you want to learn
	struct DataSet* unionSet;
	unionSet = unionDataSet(setA, setB);

	printf("A UNION B:\n");
	printDataSet(unionSet);

	//Intersection
	struct DataSet* intersectionSet;
	intersectionSet = intersectionDataSet(setA, setB);

	printf("A INTERSECTION B:\n");
	printDataSet(intersectionSet);

	//Set difference
	struct DataSet* diffSet;
	diffSet = diffDataSet(setA, setB);

	printf("A DIFF B:\n");
	printDataSet(diffSet);

	//Subset Test
	struct DataSet* subsetTest;
	subsetTest = subset(unionSet, 3, 7);

	printf("ORIGINAL SET:\n");
	printDataSet(unionSet);

	printf("SUBSET:\n");
	printDataSet(subsetTest);
	printf("subsetTest %s a subset of unionSet\n", isSubset(subsetTest, unionSet) ? "IS" : "IS NOT");
	printf("unionSet %s a subset of subsetSet\n", isSubset(unionSet, subsetTest) ? "IS" : "IS NOT");

	struct DataSet* emptySet = allocDataSet();
	//no data added so it should be the nullSet
	printf("THE EMPTY SET LOOKS LIKE:\n");
	printDataSet(emptySet);
	printf("emptySet %s equal to the NULL set\n", isNull(emptySet) ? "IS" : "IS NOT");

	struct DataSet* reverseSet = allocDataSet();
	for(i = unionSet->array->length - 1; i >= 0; --i){
		appendDataSet(reverseSet, unionSet->array->data[i]);
	}
	printf("reverseSet %s equal unionSet\n", equals(unionSet, reverseSet) ? "IS" : "IS NOT");
	printf("reverseSet %s %u\n", contains(reverseSet, unionSet->array->data[0]) ? "CONTAINS" : "DOES NOT CONTAIN", unionSet->array->data[0]);
	printDataSet(reverseSet);

	//Statistics:
	printf("ORGINAL SET FOR STATISTICS:\n");
	printDataSet(unionSet);
	printf("Min value %u\n", unionSet->min);
	printf("Max value %u\n", unionSet->max);
	printf("Avg value %.2f\n", AverageDataSet(unionSet));
	printf("Range value %u\n", RangeDataSet(unionSet));

	//Release the DataSets resources after finish their usage.
	releaseDataSet(setA);
	releaseDataSet(setB);

	return 0;
}

Word squareElement(Byte element){
	return element * element;
}

Word cubeElement(Byte element){
	return element * element * element;
}