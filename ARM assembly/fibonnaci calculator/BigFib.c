// THe main file which handle s the fibonacci calculations

#include <stdlib.h>
#include <errno.h>
#include "heapstats.h"

typedef unsigned int bigNumN[];

int bigAdd(bigNumN bigN0P, const bigNumN bigN1P, unsigned int maxN0Size);

int bigFib(int n, int maxSize, unsigned **bNP) {
	
	//error checking
	
	if(n<0 || maxSize<0 ||  bNP == NULL){
		errno = EINVAL;
		return -1;
	}
	
	
	unsigned* bNa = malloc(4*(1 + maxSize));
	// check for null pointer being returned or not
	if (bNa== NULL){
		errno = ENOMEM;
		return -1;
	}

	unsigned* bNb = malloc(4*(1 + maxSize));
	// check for null pointer being returned or not

	if (bNb== NULL){
		errno = ENOMEM;
		return -1;
	}
	
	HEAPSTATS;

	// ... fill in code here for sure ****
	int carryReturn = 0;
	
	*bNa = maxSize;
	*(bNa+1) = 1;
	
	*bNb = maxSize;
	*(bNb+1) = 0;
	
	if(maxSize == 0)
	{
		*bNP = bNa;
		return 0;
	}		
	int counter = 2;
	
	for(; counter<= n; counter++){

		carryReturn = bigAdd(bNb , bNa , maxSize);
		
		if(carryReturn == 1)
		{
			//overflow
			*bNP = bNa;
			return counter-1;
		}
		
		//Swap
		unsigned* temp = bNb;
		bNb = bNa;
		bNa = temp;
		
		//print
		printf("%d = %x\n", counter , bNa[1]);
	}
	free(bNb);
	// The following two lines of code are just examples.
	// You might not always want to do them.
	if(*bNa > maxSize){
		return -1;
	}
	*bNP = bNa; // don't forget to free the other allocated memory 
	return n;
}

