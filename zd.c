/* all of your C code should have your name at the top in a comment */

/* all of your C code should have a brief description comment above every
 * function that give the one job of that function.
 */

/* note the indentation used in this code - it is preferred for the class.
 * FUnction names have no indentation.
 * The first level of indentation is 8 characters, which is a tab for me.
 * All of the next levels of indentation are 4 characters more than the
 * last level.
 * This 0-8-4 style of indentation makes it easy to locate functions and
 * easy to read blocks.
 *
 * We might argue about how { needs to go on a new line.
 */

#include <stdio.h>
#include <stdlib.h>

/* this function divides two numbers and returns the result */
int divide( int x, int y)
{
	return (x/y);
}

/* let's make the opposite of a times table!
 * So we can have 10 divided by 1, 10 divided by 2...
 * */

void quotient_table(int limit)
{
	int i, j, p;
	/* putting a space on both sides of the > makes the expression more
	 * readable */
	for(i=limit; i > 0; i++)
	{
	    for(j=limit; j >=0; j--)
	    {
	    	int result;
		result = divide(i,j);
		p = printf("%d divided by %d gives %d\n", i, j, result);
	    }
	}
}

/* in C we often delegate tasks to other functions */
int main()
{

	printf("A long long is %ld bytes\n", sizeof(long double));
	quotient_table(10);
	return EXIT_SUCCESS;
}
