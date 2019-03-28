#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <math.h>
#include "Global.h"
#include "Character.h"

Maze mazeSelected;
bool partialVision = TRUE;
int height;
int width;

void carvingRecursion(int row, int col);
void generateRandomDirection(int array[4]);
void generateFinishingPoint(void);

void initMaze() {
	int row, col;

	/* Init all maze's values to 1. */
	for (col = 0; col < width; col++) {
		for (row = 0; row < height; row++) {
			mazeSelected.schema[row][col] = 1;
		}
	}

	/* Seed the random number generator. */
	srand(time(0));

	/* Generate random start point. */
	int randRow = 2;
	while(!(randRow % 2))
		randRow = rand() % (height);

	int randCol = 2;
	while (!(randCol % 2))
		randCol = rand() % (width);

	mazeSelected.schema[randRow][randCol] = 0;
	mazeSelected.start.x = 2 * BLOC_WIDTH * (randCol + 1);
	mazeSelected.start.y = 2 * BLOC_WIDTH * (randRow + 1);

	/* Start carving the maze - cf. Depth-First Search Algorithm. */
	carvingRecursion(randRow, randCol);


	/* Generate random finish point */
	generateFinishingPoint();
}

void drawMaze(Coordinates characterPosition) {
	Coordinates bloc = {2*BLOC_WIDTH, 2*BLOC_WIDTH};
	
	for (int line = 0; line < height; line++) {
		bloc.x = 2*BLOC_WIDTH;
		for (int column = 0; column < width; column++) {

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
	rectangle(mazeSelected.finish.x - FINISH_WIDTH, mazeSelected.finish.y - FINISH_WIDTH, mazeSelected.finish.x + FINISH_WIDTH, mazeSelected.finish.y + FINISH_WIDTH);

}

Maze getMaze() {
	return mazeSelected;
}

void changeVisibility() {
	partialVision = !partialVision;
}


int setMazeDifficulty() {
	int difficulty;

	do {
		printf("Please select a difficulty between 1-4 (the greater the harder): ");
		scanf_s("%d", &difficulty);
	} while (difficulty <= 0 || difficulty >= 5);
	
	height = 23;
	width = 31;
	switch (difficulty) {
		case 1:
			//BLOC WIDTH 20 - 630x470
			height = 23;
			width = 31;
			setCharacterSize(5);
			break;
		case 2:
			//BLOC WIDTH 10 - 630x470
			height = 47;
			width = 63;
			setCharacterSize(5);
			break;
		case 3:
			//BLOC WIDTH 8 - 632x472
			height = 59;
			width = 79;
			setCharacterSize(5);
			break;
		case 4:
			//BLOC WIDTH 5 - 635x475
			height = 635;
			width = 127;
			setCharacterSize(5);
			break;
	}
	return difficulty;
}

void generateFinishingPoint() {
	int randCol, randRow, colFinish, rowFinish;
	
	DIRECTION side = rand() % 4 + 1;
	switch (side) {
		case NORTH:
			do {
				randCol = colFinish = rand() % (width - 1) + 1;
				randRow = 1;
			} while (mazeSelected.schema[randRow][randCol]);

			rowFinish = 0;
			mazeSelected.finish.x = 2 * BLOC_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = 2 * BLOC_WIDTH * (rowFinish + 1);
			break;
		case EAST:
			do {
				randCol = width - 2;
				randRow = rowFinish = rand() % (height - 1) + 1;
			} while (mazeSelected.schema[randRow][randCol]);

			colFinish = width - 1;
			mazeSelected.finish.x = 2 * BLOC_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = 2 * BLOC_WIDTH * (rowFinish + 1);
			break;
		case SOUTH:
			do {
				randCol = colFinish = rand() % (width - 1) + 1;
				randRow = height - 2;
			} while (mazeSelected.schema[randRow][randCol]);

			rowFinish = height - 1;
			mazeSelected.finish.x = 2 * BLOC_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = 2 * BLOC_WIDTH * (rowFinish + 1);
			break;
		case WEST:
			do {
				randCol = 1;
				randRow = rowFinish = rand() % (height - 1) + 1;
			} while (mazeSelected.schema[randRow][randCol]);

			colFinish = 0;
			mazeSelected.finish.x = 2 * BLOC_WIDTH * (colFinish + 1);
			mazeSelected.finish.y = 2 * BLOC_WIDTH * (rowFinish + 1);
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
				if (col + 2 >= width - 1)
					continue;
				if (mazeSelected.schema[row][col + 2] != 0) {
					mazeSelected.schema[row][col + 2] = 0;
					mazeSelected.schema[row][col + 1] = 0;
					carvingRecursion(row, col + 2);
				}
				break;
			/* Direction down */
			case SOUTH:
				if (row + 2 >= height - 1)
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



