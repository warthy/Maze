#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "Global.h"

#define SPEED 5


Coordinates position;
DIRECTION orientation;
int size;

/*
* Function:  initCharacterPosition
* --------------------
*  initalize character position to the maze' starting point
*
*  startPoint: coordinates of the maze' starting point.
*
*  returns: void
*/
void initCharacterPosition(Coordinates startPoint) {
	orientation = NORTH;
	position = startPoint;
}


/*
* Function:  DrawCharacter
* --------------------
*  draw the character thanks to its position and
*  face the orientation of the image according to the last movements made
*
*  returns: void
*/
void drawCharacter() {
	setcolor(rgb(0, 255, 0));
	switch (orientation) {
		case NORTH:
			rectangle(position.x - size, position.y - size, position.x + size, position.y + size);
			break;
	
		case SOUTH:
			rectangle(position.x - size, position.y - size, position.x + size, position.y + size);
			break;

		case EAST:
			rectangle(position.x - size, position.y - size, position.x + size, position.y + size);
			break;

		case WEST:
			rectangle(position.x - size, position.y - size, position.x + size, position.y + size);
			break;
	}
}


/*
* Function: MoveCharacter
* --------------------
*  change character coordinates if the movement is allowed
*
*  keyPressed: an integer representing the key pressed.
*  maze: the current maze we are playing in.
*
*  returns: void
*/
void moveCharacter(int keyPressed, Maze maze) {

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
	
	/* If the movement is possible (not blocked by wall or extremities) we update character position. */
	if (isMovementAllowed(temp, maze)) position = temp;

}


/*
* Function: isMovementAllowed
* --------------------
*  tell if the movement
*
*  temp: character's temporary coordinates after the movement.
*  maze: the current maze we are playing in.
*
*  returns: True if the movement is allowed and false otherwise. 
*/
bool isMovementAllowed(Coordinates temp, Maze maze) {
	/* Check that we are inside the maze/window. */
	if (temp.x - size < 0 || temp.y - size < 0 || temp.x + size > getmaxx() || temp.y + size > getmaxy())
		return FALSE;

	int col = (int)(round(temp.x / (2.0*BLOC_WIDTH)) - 1);
	int row = (int)(round(temp.y / (2.0*BLOC_WIDTH)) - 1);

	switch (orientation) {
		/* Trying to go up. */
		case NORTH:
			if (maze.schema[row][col] || (temp.x % (2*BLOC_WIDTH) && !(temp.x % 10) && maze.schema[row][col + 1]))
				return FALSE;
			else if (temp.y < (2 * BLOC_WIDTH * (row + 1)) - size) {
				if (maze.schema[row - 1][col])
					return FALSE;
				else if (temp.x < (2 * BLOC_WIDTH * (col + 1)) - size)
					if (maze.schema[row - 1][col - 1])
						return FALSE;
				else if (temp.x > (2 * BLOC_WIDTH * (col + 1)) + size)
					if (maze.schema[row - 1][col + 1])
						return FALSE;
			}
			
			break;

		/* Trying to go down. */
		case SOUTH:
			if (maze.schema[row][col] || (temp.x % (2 * BLOC_WIDTH) && !(temp.x % 10) && maze.schema[row][col - 1]))
				return FALSE;
			else if (temp.y > (2 * BLOC_WIDTH * (row + 1)) + size)
				if (maze.schema[row + 1][col])
					return FALSE;
				else if (temp.x < (2 * BLOC_WIDTH * (col + 1)) - size)
					if (maze.schema[row + 1][col - 1])
						return FALSE;
				else if (temp.x > (2 * BLOC_WIDTH * (col + 1)) + size)
					if (maze.schema[row + 1][col + 1]) {
						return FALSE;
			}
			break;

		/* Trying to go right. */
		case EAST:
			if (maze.schema[row][col] || (temp.y % (2 * BLOC_WIDTH) && !(temp.y % 10) && maze.schema[row + 1][col]))
				return FALSE;
			else if (temp.x > (2 * BLOC_WIDTH * (col + 1)) + size) {
				if (maze.schema[row][col + 1])
					return FALSE;
				else if (temp.y < (2 * BLOC_WIDTH * (row + 1)) - size)
					if (maze.schema[row - 1][col + 1])
						return FALSE;
				else if (temp.y >(2 * BLOC_WIDTH * (row + 1)) + size)
					if (maze.schema[row + 1][col + 1])
						return FALSE;
			}
			break;

		/* Trying to go left. */
		case WEST:
			if (maze.schema[row][col] || (temp.y % (2 * BLOC_WIDTH) && !(temp.y % 10) && maze.schema[row - 1][col]))
				return FALSE;
			else if (temp.x <  (2 * BLOC_WIDTH * (col + 1)) - size) {
				if (maze.schema[row][col - 1])
					return FALSE;
				else if (temp.y < (2 * BLOC_WIDTH * (row + 1)) - size)
					if (maze.schema[row - 1][col - 1])
						return FALSE;
				else if (temp.y >(2 * BLOC_WIDTH * (row + 1)) + size)
					if (maze.schema[row + 1][col - 1])
						return FALSE;
			}
			break;
	}
	return TRUE;
}


/*
* Function: getCharacterPosition
* --------------------
*  tell if the movement is allowed by checking if the temp
*  position isn't in conflict with any block/wall
*
*  returns: character's coordinates
*/
Coordinates getCharacterPosition() {
	return position;
}

void setCharacterSize(userSize) {
	size = userSize;
}