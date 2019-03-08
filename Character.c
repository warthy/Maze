#include<stdio.h>
#include "graphics.h"
#include "Global.h"

#define SPEED 5
#define WIDTH 10


Coordinates position;
DIRECTION orientation;


void initCharacterPosition() {
	orientation = NORTH;
	position.x = 0;
	position.y = 0;
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

void MoveUp() {
	orientation = NORTH;
	position.y -= SPEED;
}

void MoveDown() {
	orientation = SOUTH;
	position.y += SPEED;
}

void MoveRight() {
	orientation = EAST;
	position.x += SPEED;
}

void MoveLeft() {
	orientation = WEST;
	position.x -= SPEED;
}

Coordinates GetPosition() {
	return position;
}