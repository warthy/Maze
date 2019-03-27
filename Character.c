#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "Global.h"

#define SPEED 5


Coordinates position;
DIRECTION orientation;

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
	if (temp.x - USER_WIDTH < 0 || temp.y - USER_WIDTH < 0 || temp.x + USER_WIDTH > getmaxx() || temp.y + USER_WIDTH > getmaxy())
		return FALSE;

	int col = (int)(round(temp.x / 20.0) - 1);
	int row = (int)(round(temp.y / 20.0) - 1);

	switch (orientation) {
		/* Trying to go up. */
		case NORTH:
			if (maze.schema[row][col] || (temp.x % 20 && !(temp.x % 10) && maze.schema[row][col + 1]))
				return FALSE;
			else if (temp.y < (2 * BLOC_WIDTH * (row + 1)) - USER_WIDTH) {
				if (maze.schema[row - 1][col])
					return FALSE;
				else if (temp.x < (2 * BLOC_WIDTH * (col + 1)) - USER_WIDTH)
					if (maze.schema[row - 1][col - 1])
						return FALSE;
				else if (temp.x > (2 * BLOC_WIDTH * (col + 1)) + USER_WIDTH)
					if (maze.schema[row - 1][col + 1])
						return FALSE;
			}
			
			break;

		/* Trying to go down. */
		case SOUTH:
			if (maze.schema[row][col] || (temp.x % 20 && !(temp.x % 10) && maze.schema[row][col - 1]))
				return FALSE;
			else if (temp.y > (2 * BLOC_WIDTH * (row + 1)) + USER_WIDTH)
				if (maze.schema[row + 1][col])
					return FALSE;
				else if (temp.x < (2 * BLOC_WIDTH * (col + 1)) - USER_WIDTH)
					if (maze.schema[row + 1][col - 1])
						return FALSE;
				else if (temp.x > (2 * BLOC_WIDTH * (col + 1)) + USER_WIDTH)
					if (maze.schema[row + 1][col + 1]) {
						return FALSE;
			}
			break;

		/* Trying to go right. */
		case EAST:
			if (maze.schema[row][col] || (temp.y % 20 && !(temp.y % 10) && maze.schema[row + 1][col]))
				return FALSE;
			else if (temp.x > (2 * BLOC_WIDTH * (col + 1)) + USER_WIDTH) {
				if (maze.schema[row][col + 1])
					return FALSE;
				else if (temp.y < (2 * BLOC_WIDTH * (row + 1)) - USER_WIDTH)
					if (maze.schema[row - 1][col + 1])
						return FALSE;
				else if (temp.y >(2 * BLOC_WIDTH * (row + 1)) + USER_WIDTH)
					if (maze.schema[row + 1][col + 1])
						return FALSE;
			}
			break;

		/* Trying to go left. */
		case WEST:
			if (maze.schema[row][col] || (temp.y % 20 && !(temp.y % 10) && maze.schema[row - 1][col]))
				return FALSE;
			else if (temp.x <  (2 * BLOC_WIDTH * (col + 1)) - USER_WIDTH) {
				if (maze.schema[row][col - 1])
					return FALSE;
				else if (temp.y < (2 * BLOC_WIDTH * (row + 1)) - USER_WIDTH)
					if (maze.schema[row - 1][col - 1])
						return FALSE;
				else if (temp.y >(2 * BLOC_WIDTH * (row + 1)) + USER_WIDTH)
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