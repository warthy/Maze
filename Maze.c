#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <math.h>
#include "Global.h"


Maze mazeSelected;

void carveMaze(int x, int y) {
	int x1, y1;
	int x2, y2;
	int dx, dy;
	int dir, count;

	dir = rand() % 4;
	count = 0;
	while (count < 3) {
		dx = 0; dy = 0;
		switch (dir) {
			case 0:  dy = 1;  break;
			case 1:  dx = 1;  break;
			case 2:  dy = -1; break;
			default: dx = -1; break;
		}

		x1 = x + dx;
		y1 = y + dy;
		x2 = x1 + dx;
		y2 = y1 + dy;

		if (
			x2 >= 0 && x2 < MAZE_HEIGHT &&
			y2 >= 0 && y2 < MAZE_WIDTH &&
			mazeSelected.schema[x1][y1] == 1 && mazeSelected.schema[x2][y2] == 1
			) 
		{
			
			mazeSelected.schema[x1][y1] = 0;
			mazeSelected.schema[x2][y2] = 0;
			x = x2; y = y2;
			dir = rand() % 4;
			count = 0;
		}
		else {
			dir = (dir + 1) % 4;
			count += 1;
		}
	}

}

void initMaze() {
	int line, column;

	/* Init all maze's values to 1. */
	for (column =0; column < MAZE_WIDTH; column++) {
		for (line = 0; line < MAZE_HEIGHT; line++) {
			mazeSelected.schema[line][column] = 1;
		}
	}

	/* Seed the random number generator. */
	srand(time(0));

	/* Generate random start point. */
	//int randY = rand() % (MAZE_HEIGHT + 1);
	int randY = 0;
	mazeSelected.schema[randY][1] = 0;



	/* Carve the maze. */
	for (column = 1; column < MAZE_WIDTH; column += 2) {
		for (line = 0; line <= MAZE_HEIGHT; line += 2) {
			carveMaze(line, column);
		}
	}

	mazeSelected.schema[randY][0] = 0;
	//mazeSelected.schema[rand() % MAZE_HEIGHT][MAZE_WIDTH] = 0;

	mazeSelected.start.x = USER_WIDTH;
	mazeSelected.start.y = 2 * randY*BLOC_WIDTH + BLOC_WIDTH;

	mazeSelected.start.x = USER_WIDTH;
	mazeSelected.start.y = 2 * randY*BLOC_WIDTH + BLOC_WIDTH;

}


void drawMaze(Coordinates characterPosition) {
	Coordinates bloc = {BLOC_WIDTH, BLOC_WIDTH};
	
	for (int line = 0; line < MAZE_HEIGHT; line++) {
		bloc.x = BLOC_WIDTH;
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



