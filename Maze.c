#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <math.h>
#include "Global.h"


Maze mazeSelected;
void carvingRecursion(int row, int col);
void generateRandomDirection(int array[4]);

void initMaze() {
	int row, col;

	/* Init all maze's values to 1. */
	for (col = 0; col < MAZE_WIDTH; col++) {
		for (row = 0; row < MAZE_HEIGHT; row++) {
			mazeSelected.schema[row][col] = 1;
		}
	}

	/* Seed the random number generator. */
	srand(time(0));

	/* Generate random start point. */
	int randRow = 2;
	while(!(randRow % 2))
		randRow = rand() % (MAZE_HEIGHT);

	int randCol = 2;
	while (!(randCol % 2))
		randCol = rand() % (MAZE_WIDTH);

	mazeSelected.schema[randRow][randCol] = 0;
	mazeSelected.start.x = 2 * randCol*BLOC_WIDTH + BLOC_WIDTH*2;
	mazeSelected.start.y = 2 * randRow*BLOC_WIDTH + BLOC_WIDTH*2;
	

	/* Start carving the maze - cf. Depth-First Search Algorithm. */
	carvingRecursion(randRow, randCol);
}


void drawMaze(Coordinates characterPosition) {
	Coordinates bloc = {2*BLOC_WIDTH, 2*BLOC_WIDTH};
	
	for (int line = 0; line < MAZE_HEIGHT; line++) {
		bloc.x = 2*BLOC_WIDTH;
		for (int column = 0; column < MAZE_WIDTH; column++) {

			/* Distance between character's position and bloc's position. */
			int distance = pow(pow(characterPosition.x - bloc.x, 2) + pow(characterPosition.y - bloc.y, 2), 0.5);

			/* Draw a bloc if there is a wall and if bloc is inside character range. */
			if (mazeSelected.schema[line][column] && distance < USER_RANGE) {
				bar(bloc.x - BLOC_WIDTH, bloc.y - BLOC_WIDTH, bloc.x + BLOC_WIDTH, bloc.y + BLOC_WIDTH);
			}
			bloc.x += BLOC_WIDTH*2;
		}
		bloc.y += BLOC_WIDTH*2;
	}
	
	/* Draw finish line. */
	//rectangle(mazeSelected.finish.x - BLOC_WIDTH, mazeSelected.finish.y - BLOC_WIDTH, mazeSelected.finish.x + BLOC_WIDTH, mazeSelected.finish.y + BLOC_WIDTH);

}


Maze getMaze() {
	return mazeSelected;
}


void carvingRecursion(int row, int col) {
	int randomDir[4];
	generateRandomDirection(randomDir);

	for (int i = 0; i < 4; i++) {
		switch (randomDir[i]) {
		/* Direction up */
		case NORTH:
			if (row - 2 <= 0)
				continue;
			if (mazeSelected.schema[row - 2][col] != 0) {
				mazeSelected.schema[row - 2][col] = 0;
				mazeSelected.schema[row - 1][col] = 0;
				carvingRecursion(row - 2, col);
			}
			break;
		/* Direction right */
		case EAST:
			if (col + 2 >= MAZE_WIDTH - 1)
				continue;
			if (mazeSelected.schema[row][col + 2] != 0) {
				mazeSelected.schema[row][col + 2] = 0;
				mazeSelected.schema[row][col + 1] = 0;
				carvingRecursion(row, col + 2);
			}
			break;
		/* Direction down */
		case SOUTH:
			if (row + 2 >= MAZE_HEIGHT - 1)
				continue;
			if (mazeSelected.schema[row + 2][col] != 0) {
				mazeSelected.schema[row + 2][col] = 0;
				mazeSelected.schema[row + 1][col] = 0;
				carvingRecursion(row + 2, col);
			}
			break;
		/* Direction left */
		case WEST:
			if (col - 2 <= 0)
				continue;
			if (mazeSelected.schema[row][col - 2] != 0) {
				mazeSelected.schema[row][col - 2] = 0;
				mazeSelected.schema[row][col - 1] = 0;
				carvingRecursion(row, col - 2);
			}
			break;
		}
	}
	
}

void generateRandomDirection(int array[4])
{
	/* Set up array with 4 directions. */
	for (int i = 0; i < 4; i++) {
		array[i] = i;
	}
		
	
	/* Shuffle array - cf. Fisher–Yates shuffle. */
	size_t j;
	for (j = 0; j < 4-1; j++)
	{
		size_t k = j + rand() / (RAND_MAX / (4 - j) + 1);
		int t = array[k];
		array[k] = array[j];
		array[j] = t;
	}
}



