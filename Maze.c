#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <math.h>

#include "Bloc.h"
#include "Global.h"

Maze mazeSelected;
bool partialVision = TRUE;
int HEIGHT;
int WIDTH;

void carvingRecursion(int row, int col);
void generateRandomDirection(int array[4]);
void generateFinishingPoint(int BLOC_FULL_WIDTH);

void initMaze() {
	int row, col;
	const int BLOC_FULL_WIDTH = getBlocFullSize();

	/* Init all maze's values to 1. */
	for (col = 0; col < WIDTH; col++) {
		for (row = 0; row < HEIGHT; row++) {
			mazeSelected.schema[row][col] = 1;
		}
	}

	/* Seed the random number generator. */
	srand(time(0));

	/* Generate random start point. */
	int randRow = 2;
	while(!(randRow % 2))
		randRow = rand() % (HEIGHT);

	int randCol = 2;
	while (!(randCol % 2))
		randCol = rand() % (WIDTH);

	mazeSelected.schema[randRow][randCol] = 0;
	mazeSelected.start.x = BLOC_FULL_WIDTH * (randCol + 1);
	mazeSelected.start.y = BLOC_FULL_WIDTH * (randRow + 1);

	/* Start carving the maze - cf. Depth-First Search Algorithm. */
	carvingRecursion(randRow, randCol);


	/* Generate random finish point */
	generateFinishingPoint(BLOC_FULL_WIDTH);
}

void drawMaze(Coordinates characterPosition) {
	const float BLOC_WIDTH = getBlocSize();
	Coordinates bloc = {2*BLOC_WIDTH, 2*BLOC_WIDTH};
	
	for (int line = 0; line < HEIGHT; line++) {
		bloc.x = 2*BLOC_WIDTH;
		for (int column = 0; column < WIDTH; column++) {

			/* Distance between character's position and bloc's position. */
			int distance = pow(pow(characterPosition.x - bloc.x, 2) + pow(characterPosition.y - bloc.y, 2), 0.5);

			/* Draw a bloc if there is a wall and if bloc is inside character range. */
			if (mazeSelected.schema[line][column] && (!partialVision || distance < USER_RANGE)) {
				bar(bloc.x - BLOC_WIDTH, bloc.y - BLOC_WIDTH, bloc.x + BLOC_WIDTH, bloc.y + BLOC_WIDTH);
			}
			bloc.x += BLOC_WIDTH*2;
		}
		bloc.y += BLOC_WIDTH*2;
	}
	
	/* Draw finish line. */
	setcolor(rgb(255, 0, 0));
	rectangle(mazeSelected.finish.x - BLOC_WIDTH, mazeSelected.finish.y - BLOC_WIDTH, mazeSelected.finish.x + BLOC_WIDTH, mazeSelected.finish.y + BLOC_WIDTH);

}

Maze getMaze() {
	return mazeSelected;
}

void changeVisibility() {
	partialVision = !partialVision;
}

void setMazeSize(int height, int width) {
	HEIGHT = height;
	WIDTH = width;
}

void generateFinishingPoint(const int BLOC_FULL_WIDTH) {
	int randCol, randRow, colFinish, rowFinish;
	
	DIRECTION side = rand() % 4;
	switch (side) {
		case NORTH:
			do {
				randCol = colFinish = rand() % (WIDTH - 1) + 1;
				randRow = 1;
			} while (mazeSelected.schema[randRow][randCol]);

			rowFinish = 0;
			mazeSelected.finish.x = BLOC_FULL_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = BLOC_FULL_WIDTH * (rowFinish + 1);
			break;
		case EAST:
			do {
				randCol = WIDTH - 2;
				randRow = rowFinish = rand() % (HEIGHT - 1) + 1;
			} while (mazeSelected.schema[randRow][randCol]);

			colFinish = WIDTH - 1;
			mazeSelected.finish.x = BLOC_FULL_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = BLOC_FULL_WIDTH * (rowFinish + 1);
			break;
		case SOUTH:
			do {
				randCol = colFinish = rand() % (WIDTH - 1) + 1;
				randRow = HEIGHT - 2;
			} while (mazeSelected.schema[randRow][randCol]);

			rowFinish = HEIGHT - 1;
			mazeSelected.finish.x = BLOC_FULL_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = BLOC_FULL_WIDTH * (rowFinish + 1);
			break;
		case WEST:
			do {
				randCol = 1;
				randRow = rowFinish = rand() % (HEIGHT - 1) + 1;
			} while (mazeSelected.schema[randRow][randCol]);

			colFinish = 0;
			mazeSelected.finish.x = BLOC_FULL_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = BLOC_FULL_WIDTH * (rowFinish + 1);
			break;
	}
	
	mazeSelected.schema[rowFinish][colFinish] = 0;
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
				if (col + 2 >= WIDTH - 1)
					continue;
				if (mazeSelected.schema[row][col + 2] != 0) {
					mazeSelected.schema[row][col + 2] = 0;
					mazeSelected.schema[row][col + 1] = 0;
					carvingRecursion(row, col + 2);
				}
				break;
			/* Direction down */
			case SOUTH:
				if (row + 2 >= HEIGHT - 1)
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



