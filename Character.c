
#include<stdio.h>
#define SPEED 10

typedef enum { NORTH, EAST, SOUTH, WEST } DIRECTION;
typedef struct coordinates { int x; int y; } Coordinates;


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
			printf("going north");
			break;
	
		case SOUTH:
			printf("going south");
			break;

		case EAST:
			printf("going east");
			break;

		case WEST:
			printf("going westh");
			break;
	}
}

void MoveUp() {
	orientation = NORTH;
	position.y += SPEED;
}

void MoveDown() {
	orientation = SOUTH;
	position.y -= SPEED;
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