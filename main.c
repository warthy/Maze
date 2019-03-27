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
		
		drawMaze(getCharacterPosition());
		drawCharacter();

		delay(10);

		if (_kbhit()) {
			keyPressed = _getch();

			/* KEY_CONTROL is F1 on my computer - UNRIALIBLE*/
			if (keyPressed == KEY_CONTRL)
				changeVisibility();
			else 
				moveCharacter(keyPressed, getMaze());
		}

		setvisualpage(i % 2);
		i++;

	} while (!isWin() && keyPressed != KEY_ESCAPE);

	if(isWin())
		//TODO Display winning screen
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
		(playerPos.x < finishPos.x + FINISH_WIDTH && playerPos.x > finishPos.x - FINISH_WIDTH) &&
		(playerPos.y < finishPos.y + FINISH_WIDTH && playerPos.y > finishPos.y - FINISH_WIDTH)
	) {
		return TRUE;
	}
	return FALSE;
}