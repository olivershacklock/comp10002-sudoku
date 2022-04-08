/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.
   
   Signed by: [ Oliver Henry Alfred Shacklock 1264212 ]
   Dated:     [ 6/09/2021 ]

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/

/****************************************************************/

/* stage one */
void read_grid(int grid[]);
void print_grid(int grid[], int n);
int num_unknown_cells(int grid[], int n);

/* stage two */
int validate_grid(int grid[], int n);
void tally_set(int cur_set, int cell_mates[], int grid[]);
int is_violation(int value, int instances, int cur_set);

/* stage three */
void strategy_1(int grid[]);
void update_grid(int recieve[], int send[]);
int new_value_S1(int grid[], int cell_num, int n);

/****************************************************************/

/* main program controls all the action
*/
int
main(int argc, char *argv[]) {

	/* initialise grid and c2s */
    int grid[NCLL] = {0};
    fill_c2s();

	/* stage one - read and print grid */
	read_grid(grid);
	printf("\n");
	print_grid(grid, NCLL);
    int num_unknown = num_unknown_cells(grid, NCLL);
    printf("%d cells are unknown\n\n", num_unknown);   
    
    /* stage two - validate grid */
	int valid_grid = validate_grid(grid, NCLL);
	if (!valid_grid) {
		return 0;
	}    
	
    /* stage three - implement strategy one */
    strategy_1(grid);	
	num_unknown = num_unknown_cells(grid, NCLL);
	print_grid(grid, NCLL);
	printf("%2d cells are unknown\n", num_unknown);
	if (!num_unknown) {
		printf("\nta daa!!!\n");
	}
	return 0;
}

/* reads sudoku grid into 1-dimensional array
*/
void
read_grid(int grid[]) {
	int cur_value = 0, i = 0;
	while (scanf("%d", &cur_value) == 1) {
		grid[i++] = cur_value;
	}
    return;
	
}

/* prints the sudoku grid in a more readable format 
*/
void
print_grid(int grid[], int n) {
	int cells_printed, cur_value = 0, i;

	/* print every cell */ 
    for (i = 0; i < n; i++) {
    	cur_value = grid[i];
		cells_printed = i;
    	
    	/* tackle formatting before printing the next number */
		if ((cells_printed % NDIG) != 0) {
    		printf(" ");
    	}
		if ((cells_printed % NDIM) == 0 && (cells_printed % NDIG != 0)) {
			printf("| ");
		}
		if ((cells_printed % NDIG) == 0 && (cells_printed != 0)) {
			printf("\n");
		}
    	if ((cells_printed % (NDIM * NDIG) == 0) && (cells_printed != 0)) {
    		printf("------+-------+------\n");
    	}	
    	
    	/* print cell, replacing 0 with . */
    	if (cur_value == 0) {
    		printf(".");
    	}
    	else {
    		printf("%d", cur_value);
    	}
    }
    printf("\n\n");
}

/* counts the number of unknown cells
*/
int
num_unknown_cells(int grid[], int n) {
	int num_unknown_cells = 0, cur_value, i;
	for (i = 0; i < n; i++) {
		cur_value = grid[i];
		if (cur_value == 0) {
			num_unknown_cells++;
		}
	}
	return num_unknown_cells;
}

/* checks if the grid is a sudoku
*/
int
validate_grid(int grid[], int n) {
	int cur_set, value, instances, valid_grid = 1;
	int violations = 0, sets_violated = 0, first_set_violation, i, j;
	
	/* check for invalid sets */
	for (i = 0; i < NSET; i++) {
		
		/* tally instances of numbers 1-9 */
		int cell_mates[NDIG] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		cur_set = i;
		first_set_violation = 1;
		tally_set(cur_set, cell_mates, grid);
		
		/* check for violations */
		for (j = 0; j < NDIG; j++) {
			value = j + 1;
			instances = cell_mates[j];

			/* tally violations */
			if (is_violation(value, instances, cur_set)) {
				if (first_set_violation) {
					sets_violated++;
					first_set_violation=0;
				}
				violations++;
				valid_grid = 0;
			}
		}
	}

	/* summary of violations */
	if (violations) {
		if (sets_violated == 1) {
			printf("\n1 set has a violation\n");
		}
		else {
			printf("\n%d different sets have violations\n", sets_violated);
		}
		printf("%d violations in total\n", violations);
		
	}
    return valid_grid;
}

/* implementation of strategy one
*/
void
strategy_1(int grid[]) {

	/* copy grid so that changes can be made in isolation */
	int grid_next[NCLL], i;
	update_grid(grid_next, grid);
	
	/* find and apply valid changes to each cell */
	int cur_cell, cur_value, new_value, grid_changed = 0, header = 1;
	for (i = 0; i < NCLL; i++) {
		cur_cell = i;
		cur_value = grid[i];
		
		/* check if change can be made */
		new_value = new_value_S1(grid, cur_cell, NCLL);
		if (cur_value == 0 && (new_value)) {
		    if (header) {
		    	printf("strategy one\n");
		    	header = 0;
		    }
		    
			/* record change to grid */ 
			grid_next[cur_cell] = new_value;
			grid_changed = 1;
			printf("row %d col %d must be %d\n", 
				rownum(cur_cell), colnum(cur_cell), new_value);
		}
	}
	
	/* apply change to the original grid */
	update_grid(grid, grid_next);
	
	/* repeat strategy one until no changes are found */
	if (grid_changed) {
		printf("\n");
		strategy_1(grid);
	}
}

/* tallys the instances of values 1-9 in a set
*/
void
tally_set(int cur_set, int cell_mates[], int grid[]) {
	int cur_value, i;
	for (i = 0; i < NDIG; i++) {
		cur_value = grid[s2c[cur_set][i]];
		if (cur_value != 0) {
			cell_mates[cur_value - 1]++;
		}
	}
}
	
/* checks and prints if a violation is present
*/
int
is_violation(int value, int instances, int cur_set) {

	/* check if grid is NOT a sudoku */
	if (instances > 1) {
		int ROW_OFFSET = (-1);
		int COL_OFFSET = (NDIG - 1);
		int SQR_OFFSET = ((2 * NDIG) - 1);

		/* check if set is a row */
		if (cur_set <= COL_OFFSET) {
			int row_num = cur_set - ROW_OFFSET;
			printf("set %2d (row %d): %d instances of %d\n", 
				cur_set, row_num, instances, value);
		}
		
		/* check if set is a column */
		else if (cur_set <= SQR_OFFSET) {
			int col_num = cur_set - COL_OFFSET;
			printf("set %2d (col %d): %d instances of %d\n", 
				cur_set, col_num, instances, value);
		}
		
		/* set is a square */
		else {
			int sqr_num = cur_set - SQR_OFFSET;
			printf("set %2d (sqr %d): %d instances of %d\n", 
				cur_set, sqr_num, instances, value);
		}
		return 1;
	}
	return 0;
}

/* copys one grid to another */
void
update_grid(int recieve[], int send[]) {
	int i;
	for (i = 0; i < NCLL; i++) {
		recieve[i] = send[i];
	}
}

/* checks if an empty cell can be assigned
*/ 
int
new_value_S1(int grid[], int cur_cell, int n) {
	
	/* tally cell mates */
	int cell_mates[NDIG] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int cur_set, potential_values = 0, i;
	for (i = 0; i < NGRP; i++) {  
		cur_set = c2s[cur_cell][i];	
		tally_set(cur_set, cell_mates, grid);
	}
	
	/* check for unused values */
	int value, value_count, new_value;
	for (i = 0; i < NDIG; i++) {
		value = i + 1;
		value_count = cell_mates[i];
		if (value_count == 0) {
			potential_values++;
			new_value = value;
		}
		
		/* more than one potential value - cannot make change */
		if (potential_values > 1) {
			break;
		}
	}
	
	/* implement new value if it is the only possibility */
	if (potential_values == 1) {
		return new_value;
	}
	return 0;
} 

/* algorithms are fun */
/*************************************************/ 