
/* COpyright 2023 Neil Kirby */
/* Wei Luo */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "linkedlist.h"

#include "constants.h"
#include "structs.h"
#include "debug.h"

#include "memory.h"
#include "output.h"
#include "bits.h"
#include "physics.h"
#include "sim.h"

//Check if there are any balls in play
bool balls_in_play(struct Sim *table)
{
	return( table->playlist != NULL);
}

//Sort two data by their VY value
bool sort_by_VY(void *data1, void *data2)
{
	struct Ball *bp1 = data1, *bp2 = data2;

	return(bp1->VY > bp2->VY);

}

//Sort two data by their Y value
bool sort_by_Y(void *data1, void *data2)
{
	struct Ball *bp1 = data1, *bp2 = data2;

	return(bp1->Y > bp2->Y);

}

//Return the score of a ball
int ball_score(struct Ball *bp)
{
	return( (int) abs(bp->VY));
}

//Insert ball from playlist to offlist
void playlist_to_offlist(void *data)
{
	struct Ball *bp = data;
	off_message(bp);
	if(insert(&bp->table->offlist, bp, sort_by_VY , TEXT))
	{
	    int points = ball_score(bp);
	    bp->table->score += points;
	    points_message(points);
	}
	else
	{
	    printf("ERROR: Unable to insert into off table list, freeing %hhX\n", bp->bits);
	    free_ball(bp);
	}

}

//Delete the off table ball from the playlist
void dead_balls(struct Sim *table)
{
	deleteSome( &table->playlist, off_table, playlist_to_offlist, TEXT);
}

//Update all ball data on the table
void update_table(struct Sim *table)
{
	iterate(table->playlist, update_ball);

}

//Final actions after simulation
void final_actions(struct Sim *table)
{
	final_output(table);
	clear_lists(table);
}

//Run simulaiton
void run_sim(struct Sim *table)
{

	while(balls_in_play(table))
	{
	    master_output(table);
	    table->et += DELTA_T;
	    update_table(table);
	    dead_balls(table);
	}
	final_actions(table);
}

//Set data to the ball
static struct Ball load2launch(struct Ball *inbound)
{
 	// take care of all the fields   
	inbound->color = get_color(inbound->bits);
	inbound->bits = set_in_play(inbound->bits);
	polar2cart(inbound);
	//return the struct, not the pointer.
	return *inbound;
}

//Launch the ball
void launch_ball(struct Sim *table, struct Ball *sbp)
{
	struct Ball *dbp;  	// dynamic ball pointer -> dbp
				// static ball pointer -> sbp

	load_message(sbp);
	if( dbp = allocate_ball())
	{
	    *dbp = load2launch(sbp);	// transfer what we read
	    if( insert(&table->playlist, dbp, sort_by_Y, TEXT))
	    {
		launch_message(dbp);
	    } else {
		if (TEXT) printf("ERROR: Unable to insert into in-play list, freeing %hhX\n", dbp->bits);
		free_ball(dbp);
	    }
	    // else return the dynamic memory
	}

}

//Return true
bool always_true(void *data)
{
	return true;
}

//Clear a list
static void clear_a_list(char *name, void *address_of_head)
{
	int balls = deleteSome(address_of_head, always_true, free_ball, TEXT);
	if(TEXT)printf("Deleted %d balls from %s list.\n", balls, name);
}

//Clear all lists
void clear_lists(struct Sim *table)
{
	clear_a_list("in play", &table->playlist);
	clear_a_list("off table", &table->offlist);
}

