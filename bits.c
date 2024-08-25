
/* Copyright 2023 Neil Kirby, not for disclosure */

/* Wei Luo */

#define COLOR_SHIFT 3
#define COLOR_MASK 7

#define STATUS_SHIFT 6
#define STATUS_MASK 7

#define STATUS_IN_PLAY 2

#include <stdio.h>
#include "debug.h"

//Add DEBUG statement
//Set the ball status to be in play
unsigned char set_in_play(unsigned char bits)
{
	if (DEBUG) printf("The bit field is %hhX\n", bits);
	/* don't take this as mgic, work out how it works */
	bits = bits &  ( ~( (unsigned char)STATUS_MASK << STATUS_SHIFT));
	bits = bits | ( (unsigned char)STATUS_IN_PLAY <<STATUS_SHIFT);
	return bits;
}

//Add DEBUG statement
//Get the color of the ball
int get_color(unsigned char bits)
{
	if (DEBUG) printf("The bit field is %hhX", bits);
	int color = (bits >> COLOR_SHIFT) & COLOR_MASK;

	return color;
}

