#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include "Global.h"

#define SPEED 5


Coordinates position;
DIRECTION orientation;
float U_SIZE;

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
			rectangle(position.x - U_SIZE, position.y - U_SIZE, position.x + U_SIZE, position.y + U_SIZE);
			break;
	
		case SOUTH:
			rectangle(position.x - U_SIZE, position.y - U_SIZE, position.x + U_SIZE, position.y + U_SIZE);
			break;

		case EAST:
			rectangle(position.x - U_SIZE, position.y - U_SIZE, position.x + U_SIZE, position.y + U_SIZE);
			break;

		case WEST:
			rectangle(position.x - U_SIZE, position.y - U_SIZE, position.x + U_SIZE, position.y + U_SIZE);
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
	const int BLOC_FULL_WIDTH = getBlocFullSize();

	/* Check that we are inside the maze/window. */
	if (temp.x - U_SIZE < 0 || temp.y - U_SIZE < 0 || temp.x + U_SIZE > getmaxx() || temp.y + U_SIZE > getmaxy())
		return FALSE;

	int col = (int)(round(temp.x / (float)(BLOC_FULL_WIDTH)) - 1);
	int row = (int)(round(temp.y / (float)(BLOC_FULL_WIDTH)) - 1);

	switch (orientation) {
		/* Trying to go up. */
		case NORTH:
			if (maze.schema[row][col] || (temp.x % BLOC_FULL_WIDTH && !(temp.x % 10) && maze.schema[row][col + 1]))
				return FALSE;
			else if (temp.y < (BLOC_FULL_WIDTH * (row + 1)) - U_SIZE) {
				if (maze.schema[row - 1][col])
					return FALSE;
				else if (temp.x < (BLOC_FULL_WIDTH * (col + 1)) - U_SIZE)
					if (maze.schema[row - 1][col - 1])
						return FALSE;
				else if (temp.x > (BLOC_FULL_WIDTH * (col + 1)) + U_SIZE)
					if (maze.schema[row - 1][col + 1])
						return FALSE;
			}
			
			break;

		/* Trying to go down. */
		case SOUTH:
			if (maze.schema[row][col] || (temp.x % BLOC_FULL_WIDTH && !(temp.x % 10) && maze.schema[row][col - 1]))
				return FALSE;
			else if (temp.y > (BLOC_FULL_WIDTH * (row + 1)) + U_SIZE)
				if (maze.schema[row + 1][col])
					return FALSE;
				else if (temp.x < (BLOC_FULL_WIDTH * (col + 1)) - U_SIZE)
					if (maze.schema[row + 1][col - 1])
						return FALSE;
				else if (temp.x > (BLOC_FULL_WIDTH * (col + 1)) + U_SIZE)
					if (maze.schema[row + 1][col + 1]) {
						return FALSE;
			}
			break;

		/* Trying to go right. */
		case EAST:
			if (maze.schema[row][col] || (temp.y % BLOC_FULL_WIDTH && !(temp.y % 10) && maze.schema[row + 1][col]))
				return FALSE;
			else if (temp.x > (BLOC_FULL_WIDTH * (col + 1)) + U_SIZE) {
				if (maze.schema[row][col + 1])
					return FALSE;
				else if (temp.y < (BLOC_FULL_WIDTH * (row + 1)) - U_SIZE)
					if (maze.schema[row - 1][col + 1])
						return FALSE;
				else if (temp.y >(BLOC_FULL_WIDTH * (row + 1)) + U_SIZE)
					if (maze.schema[row + 1][col + 1])
						return FALSE;
			}
			break;

		/* Trying to go left. */
		case WEST:
			if (maze.schema[row][col] || (temp.y % BLOC_FULL_WIDTH && !(temp.y % 10) && maze.schema[row - 1][col]))
				return FALSE;
			else if (temp.x <  (BLOC_FULL_WIDTH * (col + 1)) - U_SIZE) {
				if (maze.schema[row][col - 1])
					return FALSE;
				else if (temp.y < (BLOC_FULL_WIDTH * (row + 1)) - U_SIZE)
					if (maze.schema[row - 1][col - 1])
						return FALSE;
				else if (temp.y >(BLOC_FULL_WIDTH * (row + 1)) + U_SIZE)
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

void setCharacterSize(float userSize) {
	/* Round to 1 decimal */
	U_SIZE = floorf(userSize * 10) / 10;
}