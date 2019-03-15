#include<stdio.h>
#include <graphics.h>
#include "Global.h"

#define SPEED 5
#define WIDTH 5


Coordinates position;
DIRECTION orientation;


void initCharacterPosition(Coordinates startPoint) {
	orientation = NORTH;
	position = startPoint;
}

void DrawCharacter() {
	switch (orientation) {
		case NORTH:
			rectangle(position.x - WIDTH, position.y - WIDTH, position.x + WIDTH, position.y + WIDTH);
			break;
	
		case SOUTH:
			rectangle(position.x - WIDTH, position.y - WIDTH, position.x + WIDTH, position.y + WIDTH);
			break;

		case EAST:
			rectangle(position.x - WIDTH, position.y - WIDTH, position.x + WIDTH, position.y + WIDTH);
			break;

		case WEST:
			rectangle(position.x - WIDTH, position.y - WIDTH, position.x + WIDTH, position.y + WIDTH);
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

}

Coordinates GetPosition() {
	return position;
}