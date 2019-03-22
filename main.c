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
	

	int keyPressed = 0, i=0;
	do {
		setactivepage(i % 2);

		clearviewport();
		DrawCharacter();
		DrawMaze(GetPosition());

		delay(10);

		if (_kbhit()) {
			keyPressed = _getch();
			MoveCharacter(keyPressed, GetMaze());
		}

		setvisualpage(i % 2);
		i++;

	} while (!isWin() && keyPressed != KEY_ESCAPE);

	return 0;
}


void initGame() {
	initCharacterPosition(GetMaze().start);
}

bool isWin() {
	Coordinates playerPos = GetPosition();
	Coordinates finishPos = GetMaze().finish;
	
	if (
		(playerPos.x < finishPos.x + USER_WIDTH && playerPos.x > finishPos.x - USER_WIDTH) &&
		(playerPos.y < finishPos.y + USER_WIDTH && playerPos.y > finishPos.y - USER_WIDTH)
	) {
		return TRUE;
	}
	return FALSE;
}