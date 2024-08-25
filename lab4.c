

/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Wei Luo */
/* system includes go first */
#include <stdio.h>
#include <stdbool.h>
#include "libpb.h"

/* includes for constants and tyupes are next */
#include "debug.h"
#include "constants.h"
#include "structs.h"

/* includes for functions go last */
#include "n2.h"
#include "input.h"
#include "sim.h"
#include "lab4.h"


//Initialize pb if it's in graphics mode
bool init()
{
	return(TEXT || ( GRAPHICS && pb_initialize()));

}

//Teardown pb
void teardown()
{
	if(GRAPHICS)pb_teardown();
}

//Read all inputs and then run the simulation
void read_and_run(FILE *fp)
{
	struct Sim Balley = { 0.0, 0, NULL, NULL};
	struct Sim *table = &Balley;

	if( read_all(table, fp))run_sim(table);
}

//Decide to run or not
static bool isRun(int argc) {
	bool flag = true;
	if (argc < 2) {
		flag = false;
		printf("ERROR: Insufficient arguments (argc is 1).\n");
	} else if (argc == 3 && (!BONUS || TEXT)) {
		flag = false;
		printf("ERROR: Bonus code is not present.\n");
	}
	return flag;
}

//Open file and run program
void open_run(char *argv[], bool flag) {
	FILE *fp;
	if (fp = fopen(argv[1], "r")) {
		printf("DIAGNOSTIC: Successfully opened %s for reading.\n", argv[1]);
	} else {
		flag = false;
		printf("ERROR: Unable to open %s for reading.\n", argv[1]);
	}
	if (flag && init()) {
		read_and_run(fp);
		teardown();
		fclose(fp);
		printf("DIAGNOSTIC: Input file closed.\n");
	}
}

//Main
int main(int argc, char *argv[])
{
	double start, runtime;

	start = now();	// this is the very first executable statement
	bool bonus = false;
	bool runFlag = isRun(argc);
	if (runFlag) {
		open_run(argv, runFlag);
	}
	/* at this point we are done, graphics has been torn down*/
	runtime = now() - start;
	/* after graphics has been torn down, we can freely print */
	printf("Total runtime is %.9lf seconds\n", runtime);

	return 0;
}

