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
#include <errno.h>

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
	1-Open the file "filename"
	2-On error, print some useful error message and call abort(). //DONE
	3-Fill in the table world[i][j] with DEAD or ALIVE which is read from the file
	4-Close the file
	*/

	// 1-Open the file "filename"
	FILE *pfile;
	pfile = fopen(filename, "r");

	// 2-On error, print some useful error message and call abort().
 	if (pfile == NULL)
	{
		printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
		printf("Error opening %s for reading. Program terminated.", filename);
		abort();
	}

	// 3-Fill in the table world[i][j] with DEAD or ALIVE which is read from the file
	char mychar;
	int i = 0;
	int j = 0;
	while ((mychar = fgetc(pfile)) != EOF)
	{	
		putchar(mychar);
		
		if (mychar == '*')
		{
			world[i][j] = ALIVE;
			j++;
		}
		if (mychar == ' ')
		{
			world[i][j] = DEAD;
			j++;
		}
		if (mychar == '\n')
		{
			i++;
			j = 0;
		}
	}
	putchar('\n');

	// 4-Close the file
	fclose(pfile);
}

void save_world_to_file(const char * filename) {
	/* Description:
	Save the final state of the world into a file with name "filename". 
    */
	FILE * sFile;
	sFile = freopen(filename, "w", stdout);
	if (sFile != NULL)
	{
		output_world();
		fclose(sFile);
	}
	return 0;
}

/* you shouldn't need to edit anything below this line */

void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider", these are the active cells */
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

// Output world set the current state of the world to stdout
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
