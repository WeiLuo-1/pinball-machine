
/* Copyright 2023 Neil Kirby, not for disclosure */
/* All physics goes here */
/* Wei Luo */

#define GRAVITY	(-47.052534795)	/* inches per second per second */
#define LEFT_LIMIT	(-12.0)
#define RIGHT_LIMIT	(12.0)
#define UPPER_LIMIT	(48.0)
#define LOWER_LIMIT	(0.0)
#define INELASTIC	(0.95)
#define TWO	(2.0)
#define FIVE	(5.0)
#define ONE	(1.0)
#define HALF	(0.5)
#define HALF_CIRCLE	(180.0)
#define FLIPPER_VY	(75.0)
#define FLIPPER_VX	(6.4)

/* and now for the flippers */
#define FLIPPER_MAX_X_LEFT -2.0
#define FLIPPER_MAX_Y_LEFT 1.0
#define FLIPPER_MIN_X_LEFT -5.0
#define FLIPPER_MIN_Y_LEFT 0.0

#define FLIPPER_MAX_X_RIGHT 5.0
#define FLIPPER_MAX_Y_RIGHT 1.0
#define FLIPPER_MIN_X_RIGHT 2.0
#define FLIPPER_MIN_Y_RIGHT 0.0

#include <stdbool.h>
#include <math.h>

#include "constants.h"
#include "structs.h"

#include "output.h"

/* validate my own header file */
#include "physics.h"

//Check if the ball is on table
bool on_table(struct Ball *bp)
{
	return( bp->Y >= LOWER_LIMIT);
}

//Check if the ball is on table
bool off_table(void *data)	
{
	// criteria function
	struct Ball *bp = data;

	return (!on_table(bp));
}

//Print ball data after the ball hits left wall then update ball data
static void left_wall(struct Ball *bp)
{
	if(bp->X < LEFT_LIMIT)
	{
	    left_message(bp);
	    bp->X = TWO * LEFT_LIMIT - bp->X;
	    bp->VX = -bp->VX;
	    bp->VX *= INELASTIC;
	    bp->VY *= INELASTIC;
	}
}

//Print ball data after the ball hits right wall then update ball data
static void right_wall( struct Ball *bp)
{
	if(bp->X > RIGHT_LIMIT)
	{
	    right_message(bp);
	    bp->X = TWO * RIGHT_LIMIT - bp->X;
	    bp->VX = -bp->VX;
	    bp->VX *= INELASTIC;
	    bp->VY *= INELASTIC;
	}
}

//Print ball data after the ball hits top wall then update ball data
static void top_wall( struct Ball *bp)
{
	if(bp->Y > UPPER_LIMIT)
	{
	    top_message(bp);
	    bp->Y = TWO * UPPER_LIMIT - bp->Y;
	    bp->VY = -bp->VY;
	    bp->VX *= INELASTIC;
	    bp->VY *= INELASTIC;
	}
}

//Print ball data after the ball hits left flipper then update ball data
static void left_flipper( struct Ball *bp)
{
	if(
		(bp->X >= FLIPPER_MIN_X_LEFT) &&
		(bp->X <= FLIPPER_MAX_X_LEFT) &&
		(bp->Y >= FLIPPER_MIN_Y_LEFT) &&
		(bp->Y <= FLIPPER_MAX_Y_LEFT) 
	    )
	    {
	    	left_flipper_message(bp);
		bp->VY += FLIPPER_VY;
		bp->VX += FLIPPER_VX;
		bp->Y += ONE;
	    }
}

//Print ball data after the ball hits right flipper then update ball data
static void right_flipper( struct Ball *bp)
{
	if(
		(bp->X >= FLIPPER_MIN_X_RIGHT) &&
		(bp->X <= FLIPPER_MAX_X_RIGHT) &&
		(bp->Y >= FLIPPER_MIN_Y_RIGHT) &&
		(bp->Y <= FLIPPER_MAX_Y_RIGHT) 
	    )
	    {
	    	right_flipper_message(bp);
		bp->VY += FLIPPER_VY;
		bp->VX += -FLIPPER_VX;
		bp->Y += ONE;
	    }
}

//All constraints of balls
void constraints( struct Ball *bp)
{
	void (*todo[])(struct Ball *bp) = { left_wall, right_wall, 
		top_wall, left_flipper, right_flipper};
	int i, count = sizeof(todo)/sizeof(todo[0]);

	for(i=0; i<count; i++)todo[i](bp);

}

//Update ball data
void update_ball( void * data)	
{
	//action function
	struct Ball *bp = data;

	move(DELTA_T, bp);
	constraints(bp);
}

//Update ball according to time
void move(double dt, struct Ball *bp)
{
	/* position first, then velocity */
	bp->X += bp->VX * dt;
	bp->Y += bp->VY * dt + HALF * GRAVITY * dt * dt;
	/* no change in VX */
	bp->VY += GRAVITY * dt;
}

//Convert polar coordinate to cartision coordinate
void polar2cart(struct Ball *bp)
{
	double computedVX = bp->force * cos( bp->theta * M_PI / HALF_CIRCLE );
	double computedVY = bp->force * sin( bp->theta * M_PI / HALF_CIRCLE );

	bp->VX = computedVX;
	bp->VY = computedVY;
}
