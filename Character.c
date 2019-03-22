#include<stdio.h>
#include <graphics.h>
#include "Global.h"

#define SPEED 5


Coordinates position;
DIRECTION orientation;


void initCharacterPosition(Coordinates startPoint) {
	orientation = NORTH;
	position = startPoint;
}

/*
* Function:  DrawCharacter
* --------------------
* draw the character thanks to its position and
* face the orientation of the image according to the last movements made
*
*  returns: void
*/
void DrawCharacter() {
	switch (orientation) {
		case NORTH:
			rectangle(position.x - USER_WIDTH, position.y - USER_WIDTH, position.x + USER_WIDTH, position.y + USER_WIDTH);
			break;
	
		case SOUTH:
			rectangle(position.x - USER_WIDTH, position.y - USER_WIDTH, position.x + USER_WIDTH, position.y + USER_WIDTH);
			break;

		case EAST:
			rectangle(position.x - USER_WIDTH, position.y - USER_WIDTH, position.x + USER_WIDTH, position.y + USER_WIDTH);
			break;

		case WEST:
			rectangle(position.x - USER_WIDTH, position.y - USER_WIDTH, position.x + USER_WIDTH, position.y + USER_WIDTH);
			break;
	}
}

void MoveCharacter(int keyPressed, Maze maze) {

	Coordinates temp = position;

	switch (keyPressed) {
		case KEY_UP:
			orientation = NORTH;
			temp.y -= SPEED;
			break;
		case KEY_DOWN:
			orientation = SOUTH;
			temp.y += SPEED;
			break;
		case KEY_RIGHT:
			orientation = EAST;
			temp.x += SPEED;
			break;
		case KEY_LEFT:
			orientation = WEST;
			temp.x -= SPEED;
			break;
	}
	
	//If the movement is possible (not blocked by wall or extremities) we update character position
	if (isMovementAllowed(temp, maze)) position = temp;
}

bool isMovementAllowed(Coordinates temp, Maze maze) {
	//Check we are inside the maze/window
	if (temp.x - USER_WIDTH < 0 || temp.y - USER_WIDTH < 0 || temp.x + USER_WIDTH > getmaxx() || temp.y + USER_WIDTH > getmaxy())
		return FALSE;

	int column = (2 * ((int)(temp.x / 20.0)) + 1) / 2;
	int line = (2 * ((int)(temp.y / 20.0)) + 1) / 2;

	switch (orientation) {
		case NORTH:
			if (maze.schema[line][column] || (!(temp.x % 20) && (maze.schema[line][column + 1]))) {
				return FALSE;
			}
			else if (temp.y < ((2 * line + 1) * BLOC_WIDTH) - USER_WIDTH) {
				if (maze.schema[line - 1][column]) {
					return FALSE;
				}
				else if (temp.x < ((2 * column + 1) * BLOC_WIDTH) - USER_WIDTH) {
					if (maze.schema[line - 1][column - 1]) {
						return FALSE;
					}
				}
				else if (temp.x > ((2 * column + 1) * BLOC_WIDTH) + USER_WIDTH) {
					if (maze.schema[line - 1][column + 1]) {
						return FALSE;
					}
				}
			}
			
			break;

		case SOUTH:
			if (maze.schema[line][column] || (!(temp.x % 20) && (maze.schema[line][column - 1]))) {
				return FALSE;
			}
			else if (temp.y > ((2 * line + 1) * BLOC_WIDTH) + USER_WIDTH) {
				if (maze.schema[line + 1][column]) {
					return FALSE;
				}
				else if (temp.x < ((2 * column + 1) * BLOC_WIDTH) - USER_WIDTH) {
					if (maze.schema[line + 1][column - 1]) {
						return FALSE;
					}
				}
				else if (temp.x > ((2 * column + 1) * BLOC_WIDTH) + USER_WIDTH) {
					if (maze.schema[line + 1][column + 1]) {
						return FALSE;
					}
				}
			}
			break;

		case EAST:
			if (maze.schema[line][column] || (!(temp.y % 20) && (maze.schema[line + 1][column]))) {
				return FALSE;
			}
			else if (temp.x > ((2 * column + 1) * BLOC_WIDTH) + USER_WIDTH) {
				if (maze.schema[line][column + 1]) {
					return FALSE;
				}
				else if (temp.y < ((2 * line + 1) * BLOC_WIDTH) - USER_WIDTH) {
					if (maze.schema[line - 1][column + 1]) {
						return FALSE;
					}
				}
				else if (temp.y >((2 * line + 1) * BLOC_WIDTH) + USER_WIDTH) {
					if (maze.schema[line + 1][column + 1]) {
						return FALSE;
					}
				}
			}
			break;

		case WEST:
			if (maze.schema[line][column] || (!(temp.y % 20) && (maze.schema[line - 1][column]))) {
				return FALSE;
			}
			else if (temp.x < ((2 * column + 1) * BLOC_WIDTH) - USER_WIDTH) {
				if (maze.schema[line][column - 1]) {
					return FALSE;
				}
				else if (temp.y < ((2 * line + 1) * BLOC_WIDTH) - USER_WIDTH) {
					if (maze.schema[line - 1][column - 1]) {
						return FALSE;
					}
				}
				else if (temp.y >((2 * line + 1) * BLOC_WIDTH) + USER_WIDTH) {
					if (maze.schema[line + 1][column - 1]) {
						return FALSE;
					}
				}
			}
			break;
	}
	return TRUE;
}

Coordinates GetPosition() {
	return position;
}