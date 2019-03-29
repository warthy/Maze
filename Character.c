#include <stdio.h>
#include <math.h>
#include <graphics.h>

#include "Global.h"
#include "Bloc.h"

#define SPEED 1


Coordinates position;
DIRECTION orientation;
float U_SIZE;

/*
 *  Function:  initCharacterPosition
 *  --------------------
 *  Initalize character position to the maze' starting point
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
 *  Function:  DrawCharacter
 *  --------------------
 *  Draw the character thanks to its position and
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
 *  Function: MoveCharacter
 *  --------------------
 *  Change character coordinates if the movement is allowed
 *
 *  keyPressed: an integer representing the key pressed.
 *  maze: the current maze we are playing in.
 *
 *  returns: void
 */
void moveCharacter(Maze maze) {
	Coordinates temp = position;
	int direction = NONE;

	if (keypressed(KB_UP))
		direction = NORTH;
	else if (keypressed(KB_LEFT))
		direction = WEST;
	else if (keypressed(KB_DOWN))
		direction = SOUTH;
	else if (keypressed(KB_RIGHT))
		direction = EAST;

	switch (direction) {
		case NORTH:
			orientation = NORTH;
			temp.y -= SPEED;
			break;
		case SOUTH:
			orientation = SOUTH;
			temp.y += SPEED;
			break;
		case EAST:
			orientation = EAST;
			temp.x += SPEED;
			break;
		case WEST:
			orientation = WEST;
			temp.x -= SPEED;
			break;
	}
	
	/* If the movement is possible (not blocked by wall or extremities) we update character position. */
	if (direction && isMovementAllowed(temp, maze)) position = temp;

}


/*
 *  Function: isMovementAllowed
 *  --------------------
 *  Tell if the movement is allowed by checking if the temp
 *  position isn't in conflict with any block/wall
 *
 *  temp: character's temporary coordinates after the movement.
 *  maze: the current maze we are playing in.
 *
 *  returns: True if the movement is allowed and false otherwise. 
 */
bool isMovementAllowed(Coordinates temp, Maze maze) {
	const float BLOC_WIDTH = getBlocSize();
	const int BLOC_FULL_WIDTH = BLOC_WIDTH * 2;

	/* Check that we are inside the maze/window. */
	if (temp.x - U_SIZE < 0 || temp.y - U_SIZE < 0 || temp.x + U_SIZE > getmaxx() || temp.y + U_SIZE > getmaxy())
		return FALSE;

	int col = (int)(round(temp.x / (float)(BLOC_FULL_WIDTH)) - 1);
	int row = (int)(round(temp.y / (float)(BLOC_FULL_WIDTH)) - 1);

	switch (orientation) {
		/* Trying to go up. */
		case NORTH:
			if (maze.schema[row][col] || (temp.x % BLOC_FULL_WIDTH && !fmod(temp.x, BLOC_WIDTH) && maze.schema[row][col + 1]))
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
			if (maze.schema[row][col] || (temp.x % BLOC_FULL_WIDTH && !fmod(temp.x, BLOC_WIDTH) && maze.schema[row][col - 1]))
				return FALSE;
			else if (temp.y > (BLOC_FULL_WIDTH * (row + 1)) + U_SIZE){
				if (maze.schema[row + 1][col])
					return FALSE;
				else if (temp.x < (BLOC_FULL_WIDTH * (col + 1)) - U_SIZE && maze.schema[row + 1][col - 1])
					return FALSE;
				else if (temp.x > (BLOC_FULL_WIDTH * (col + 1)) + U_SIZE && maze.schema[row + 1][col + 1])
					return FALSE;
			}
			break;

		/* Trying to go right. */
		case EAST:
			if (maze.schema[row][col] || (temp.y % BLOC_FULL_WIDTH && !fmod(temp.y, BLOC_WIDTH) && maze.schema[row + 1][col]))
				return FALSE;
			else if (temp.x > (BLOC_FULL_WIDTH * (col + 1)) + U_SIZE) {
				if (maze.schema[row][col + 1])
					return FALSE;
				else if (temp.y < (BLOC_FULL_WIDTH * (row + 1)) - U_SIZE && maze.schema[row - 1][col + 1])
					return FALSE;
				else if (temp.y > (BLOC_FULL_WIDTH * (row + 1)) + U_SIZE && maze.schema[row + 1][col + 1])
					return FALSE;
			}
			break;

		/* Trying to go left. */
		case WEST:
			if (maze.schema[row][col] || (temp.y % BLOC_FULL_WIDTH && !fmod(temp.y, BLOC_WIDTH) && maze.schema[row - 1][col]))
				return FALSE;
			else if (temp.x <  (BLOC_FULL_WIDTH * (col + 1)) - U_SIZE) {
				if (maze.schema[row][col - 1])
					return FALSE;
				else if (temp.y < (BLOC_FULL_WIDTH * (row + 1)) - U_SIZE && maze.schema[row - 1][col - 1])
					return FALSE;
				else if (temp.y >(BLOC_FULL_WIDTH * (row + 1)) + U_SIZE && maze.schema[row + 1][col - 1])
					return FALSE;
			}
			break;
	}
	return TRUE;
}


/*
 *  Function: getCharacterPosition
 *  --------------------
 *  Get character's current position
 *
 *  returns: character's coordinates
 */
Coordinates getCharacterPosition() {
	return position;
}

/*
 *  Function: setCharacterSize
 *  --------------------
 *  set character size
 *
 *  returns: void
 */
void setCharacterSize(float userSize) {
	/* Round to 1 decimal */
	U_SIZE = floorf(userSize * 10) / 10;
}