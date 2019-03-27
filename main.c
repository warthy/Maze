#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>   

#include "Global.h"
#include "Character.h"
#include "Maze.h"



bool isWin();
void initGame();

int main() {
	int gd = DETECT, gm = 0;
	initgraph(&gd, &gm, "RGB");
	initGame();
	

	int keyPressed = 0, i = 0;
	do {
		setactivepage(i % 2);

		clearviewport();
		drawCharacter();
		drawMaze(getCharacterPosition());

		delay(10);

		if (_kbhit()) {
			keyPressed = _getch();
			moveCharacter(keyPressed, getMaze());
		}

		setvisualpage(i % 2);
		i++;

	} while (1);

	return 0;
}


void initGame() {
	initMaze();
	initCharacterPosition(getMaze().start);
}

bool isWin() {
	Coordinates playerPos = getCharacterPosition();
	Coordinates finishPos = getMaze().finish;
	
	if (
		(playerPos.x < finishPos.x + USER_WIDTH && playerPos.x > finishPos.x - USER_WIDTH) &&
		(playerPos.y < finishPos.y + USER_WIDTH && playerPos.y > finishPos.y - USER_WIDTH)
	) {
		return TRUE;
	}
	return FALSE;
}