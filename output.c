
/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Wei Luo */

#define THOUSAND	1000
#define MILLION		(1000000.0)
#define FOUR		(4.0)

/* system includes go first */
#include <stdio.h>

#include "libpb.h"
#include "n2.h"
#include "linkedlist.h"

/* includes for constants and tyupes are next */
#include "debug.h"
#include "constants.h"
#include "structs.h"

/* includes for functions go last */
#include "bits.h"
#include "sim.h"
#include "output.h"

/* functions internal to this file go here at the top */

//return a string of the given color
static char *color_string(int color) {
	char *array[9] = {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"};
	return array[color];
}

//Output header
static void print_header(double et, int score)
{
	/* VY can hit -100, so it needs more room */
	printf("\n%7s %2s  %9s %9s  %9s %10s  ET=%9.6lf  Score=%4d\n", "Color",
	"ST", "___X_____", "___Y_____", "___VX____", "____VY____", et,score);

}

/* an action function */
//Print ball socres
void print_ball_scores(void *data)
{
	struct Ball *bp = data;

	printf("%7s %02X  %3d points\n", color_string(bp->color), bp->bits, ball_score(bp) );
}

/* an action function */
//Print ball
void print_ball(void *data)
{
	struct Ball *bp = data;

	/* VY can hit -100, so it needs more room */
	printf("%7s %02X  %9.5lf %9.5lf  %9.5lf %10.5lf\n",
	    color_string(bp->color), bp->bits, bp->X, bp->Y, bp->VX, bp->VY );

}

//Draw the bal in graphics
static void draw_ball(void *data)
{
	struct Ball *bp = data;

	pb_ball(get_color(bp->bits), bp->X, bp->Y);
}

//Output header and ball status
static void master_text(struct Sim *table)
{
	sort(table->playlist, sort_by_Y);
	print_header(table->et, table->score);
	iterate( table->playlist, print_ball);
	printf("\n");
}
//Output ball in graphics
static void master_graphics(struct Sim *table)
{
	pb_clear();
	pb_time( (int) (table->et * THOUSAND));
	pb_score(table->score);
	iterate( table->playlist, draw_ball);
	pb_refresh();

	microsleep( (unsigned int)(DELTA_T * MILLION));
}

//Four seconds wait after graphics simulation
static void final_graphics(struct Sim *table)
{
        double wait = 0.0;

        while(wait < FOUR)
        {
            pb_clear();
            pb_time( (int) table->et * THOUSAND);
	    pb_score(table->score);
            pb_refresh();

            microsleep( (unsigned int)(DELTA_T * MILLION));
            wait += DELTA_T;
        }
}

//Final output in text mode
static void final_text(struct Sim *table)
{
	printf("\nThe final scores was %d points:\n", table->score);
	iterate(table->offlist, print_ball_scores);
	printf("\n");
}
/* public functions below here **********************************/

//Output in text mode or graphics mode according to the setting
void master_output(struct Sim *table)
{
	if(TEXT)master_text(table);
	if(GRAPHICS)master_graphics(table);
}

//Do final output in text or graphics according to the setting
void final_output(struct Sim *table)
{
	if(TEXT) final_text(table);
	if(GRAPHICS)final_graphics(table);
}

//Output message when ball is loaded
void load_message( struct Ball *bp)
{
	/* get the color */
	int color = get_color(bp->bits);
	if(GRAPHICS)pb_status("Loaded");
if(TEXT)printf("Loaded %7s %02X %d ball at %9.5lf, %9.5lf %9.5lf deg %9.5lf ips\n",
    		color_string(color), bp->bits, color, bp->X, bp->Y, bp->theta, bp->force);

}

//Output message when ball is launched
void launch_message( struct Ball *bp)
{
	/* get the color */
	int color = get_color(bp->bits);
	if(GRAPHICS)pb_status("Launch");
if(TEXT)printf("Launched %7s %02X %d ball at %9.5lf, %9.5lf at %9.5lf, %9.5lf\n",
    		color_string(color), bp->bits, color, bp->X, bp->Y, bp->VX, bp->VY);

}


/* not technically public but it goes right next to the funcitons that call
 * it */
//Output message when ball hits any wall or drop out of table
static void x_message( char *string,  struct Ball *bp)
{
	/* get the color */
	int color = get_color(bp->bits);
    if(TEXT) printf("%s: %7s %02X  %9.5lf %9.5lf  %9.5lf %10.5lf\n",
	    string, color_string(color), bp->bits, bp->X, bp->Y, bp->VX, bp->VY );

	if(GRAPHICS)pb_status(string);
}

//Output message when ball hits left wall
void left_message( struct Ball *bp)
{
    x_message("Left_ wall", bp);
}

//Output message when ball hits right wall
void right_message( struct Ball *bp)
{
    x_message("Right wall", bp);
}

//Output message when ball hits top wall
void top_message( struct Ball *bp)
{
    x_message("Upper wall", bp);
}

//Output message when ball is off table
void off_message( struct Ball *bp)
{
    x_message("Off table", bp);
}

//Output message when ball hits left flipper
void left_flipper_message( struct Ball *bp)
{
    x_message("Left_ flipper", bp);
    if(GRAPHICS) pb_left();
}

//Output message when ball hits right flipper
void right_flipper_message( struct Ball *bp)
{
    x_message("Right flipper", bp);
    if(GRAPHICS) pb_right();
}

//Output points message
void points_message(int points)
{
	if(TEXT)printf("%d points\n", points);
	// graphics mode does score every frame
}

