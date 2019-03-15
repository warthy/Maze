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
	
	//If the movement is possible (not blocked by wall) we update character position
	if (isMovementAllowed(temp, maze)) position = temp;
}

bool isMovementAllowed(Coordinates temp, Maze maze) {
	if (temp.x - USER_WIDTH < 0 || temp.y - USER_WIDTH < 0 || temp.x + USER_WIDTH > getmaxx() || temp.y + USER_WIDTH > getmaxy())
		return FALSE;

	return TRUE;
}

Coordinates GetPosition() {
	return position;
}