
/* COpyright 2023 Neil Kirby */
/* Wei Luo */

#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "debug.h"
#include "altmem.h"

#include "memory.h"

//Allocate ball
struct Ball *allocate_ball()
{
	struct Ball *bp;
	static int allocations = 0;
	
	if( bp = alternative_calloc(1, sizeof(struct Ball)))
	{
	    allocations++;
	    if(TEXT)printf("DIAGNOSTIC: %d balls allocated\n", allocations);
	}
	else
	{
	    if(TEXT)printf("ERROR: failed to allocate ball\n");
	}

	return bp;

}

// I might get called as an action function, hence the signature
//Free ball
void free_ball(void *data)
{
	static int freed = 0;

	if(data)
	{
	    freed++;
	    alternative_free(data);
	    if(TEXT)printf("DIAGNOSTIC: %d balls freed\n", freed);
	}
	else
	{
	    if(TEXT)printf("ERROR: tried to free NULL pointer.\n");
	}

}



