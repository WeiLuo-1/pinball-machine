
/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Wei Luo */
/* system includes go first */
#include <stdio.h>
#include <stdbool.h>

/* includes for constants and tyupes are next */
#include "debug.h"
#include "structs.h"

/* includes for functions go last */
#include "input.h"
#include "sim.h"


//Read all balls
bool read_all(struct Sim *table, FILE *fp)
{
	/* at this point we need to declare out data */
	struct Ball steel, *sbp = &steel;
	int tokens;

	sbp->table = table;  // do this early

	while( 5 == (tokens = 
		fscanf(fp, "%hhx %lf %lf %lf %lf",&sbp->bits,
		&sbp->X, &sbp->Y, &sbp->theta, &sbp->force)
		    )
	    )
	{
	    launch_ball(table, sbp);
	}
	if(TEXT)printf("Final scanf call returned %d\n", tokens);

	return (table->playlist != NULL);
}


