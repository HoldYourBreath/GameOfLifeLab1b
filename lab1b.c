/*
 * lab1b.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement -- can copy from Part A */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(int argc, char ** argv)
{
	int n;

	/* TODO: initialize the world, from file argv[1]
	   if command line argument provided (argc > 1), or
	   using hard-coded pattern (use Part A) otherwise */


	for (n = 0; n < NUM_GENERATIONS; n++)
		next_generation();

	/* TODO: output final world state to console and save
	   world to file "world.txt" in current directory */


	return 0;
}

void next_generation(void)
{
	int x, y = 0;
	for (x = 0; x < WORLDWIDTH; x++)
	{
		for (y = 0; y < WORLDHEIGHT; y++)
		{
			int newstate = get_next_state(x, y);
			set_cell_state(x, y, newstate);
		}
	}
	finalize_evolution();
}


int get_next_state(int x, int y)
{
	int nbr_of_neighbors = num_neighbors(x, y);
	int current_cell_state = get_cell_state(x, y);
	int next_state = DEAD;

	if (current_cell_state == ALIVE)
	{
		next_state = ALIVE;

		// A live cell with fewer than two live neighbors dies
		if (nbr_of_neighbors < 2)
		{
			next_state = DEAD;
		}

		// A live cell with more than three live neighbors also dies
		if (nbr_of_neighbors > 3)
		{
			next_state = DEAD;
		}

		// A live cell with exactly two or three live neighbors lives
		if (nbr_of_neighbors == 2 || nbr_of_neighbors == 3)
		{
			next_state = ALIVE;
		}
	}
	if (current_cell_state == DEAD)
	{
		// A dead cell with exactly three neighbors becomes alive
		if (nbr_of_neighbors == 3)
		{
			next_state = ALIVE;
		}
	}
	return next_state;
}

int num_neighbors(int x, int y)
{
	int count = 0;

	// x = x - 1
	if (get_cell_state(x - 1, y - 1) == ALIVE)
		count++;
	if (get_cell_state(x - 1, y) == ALIVE)
		count++;
	if (get_cell_state(x - 1, y + 1) == ALIVE)
		count++;

	// x = x
	if (get_cell_state(x, y - 1) == ALIVE)
		count++;
	if (get_cell_state(x, y + 1) == ALIVE)
		count++;

	// x = x + 1
	if (get_cell_state(x + 1, y - 1) == ALIVE)
		count++;
	if (get_cell_state(x + 1, y) == ALIVE)
		count++;
	if (get_cell_state(x + 1, y + 1) == ALIVE)
		count++;

	return count;
}

