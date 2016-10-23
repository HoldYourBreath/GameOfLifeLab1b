/*
 * lifegame.c
 *
 *  Created on: 2016-10-22
 *      Author: Janne Mäkinen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "lifegame.h"

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDWIDTH][WORLDHEIGHT];

/* next generation cell states */
static int nextstates[WORLDWIDTH][WORLDHEIGHT];

/* functions to write for Part B of lab */
void initialize_world_from_file(const char * filename) {
	/* Description:
	1-Open the filename
	2-Read the state of the world from a file with name "filename". //I assume the state is the picture?
	   3-Assume file exists, is readable
	   4-Assumue the ith character of the jth line (zero-indexed) describes
	   world[i][j] according to the characters CHAR_ALIVE and CHAR_DEAD
	   5-Assume a line does not contain more than 256 characters (including newline). 
	   6-If a line doesn't contain WORLDWIDTH characters, remaining cells in line are presumed DEAD.
	   7-Similarly, if the file does not contain WORLDHEIGHT lines, remaining lines are presumed dead.
	   8-On error, print some useful error message and call abort(). //DONE
	   9-Reset the next generation to DEAD 
	 */

	//1-Open the filename
	
	pfile = fopen(filename, "r");
	// 2-Assume file exists, is readable
	if (pfile == NULL)
	{
	//	8 - On error, print some useful error message and call abort().
		printf("Error opening %s for reading. Program terminated.", filename);
		abort();
	}

	//9-Reset the next generation to DEAD


	/* Read a characters from the file and display it */
	//2 - Read the state of the world from a file with name "filename".
	while ((mychar = fgetc(filename)) != EOF)
		putchar(mychar);
	putchar('\n');

	fclose(pfile);
	remove(filename);


	//	4 - Assumue the ith character of the jth line(zero - indexed) describes
	//	world[i][j] according to the characters CHAR_ALIVE and CHAR_DEAD
	//	5 - Assume a line does not contain more than 256 characters(including newline).
	//	6 - If a line doesn't contain WORLDWIDTH characters, remaining cells in line are presumed DEAD.
	//	7 - Similarly, if the file does not contain WORLDHEIGHT lines, remaining lines are presumed dead.

	


}

void save_world_to_file(const char * filename) {
	/* Description:
	-Save the final state of the world into a file with name "filename". 
		-Same format as used in the initialization function
		-Assume the file can be created
		-if the file exists, overwrite the file. 
	-The ith character of the jth line (zero-indexed) describes world[i][j]
	using the characters CHAR_ALIVE and CHAR_DEAD
	-This file should be readable using the function
	initialize_world_from_file(filename) above; we can use
	it to resume a game later
	 */

	/*FILE * fPointer;
	fPointer = fopen("bacon.txt, "w");
		fprintf(fPointer, "I love cheese\n");
	fclose(fPointer);*/

	return 0;

}

/* you shouldn't need to edit anything below this line */

/* initializes the world to a hard-coded pattern, and resets
   all the cells in the next generation to DEAD */
void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[x][y];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[x][y] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[x][y] = nextstates[x][y];
			nextstates[x][y] = DEAD;
		}
	}
}

void output_world(void) {
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
}
