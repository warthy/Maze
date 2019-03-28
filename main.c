#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>   

#include "Global.h"
#include "Character.h"
#include "Maze.h"
#include "Bloc.h"



bool isWin();
void initGame();

int main() {
	int gd = DETECT, gm = 0, difficulty;
	printf("Welcome to THE MAZE \n\n");
	difficulty = setDifficulty();
	printf("\n\nMaze generating... \n\n");


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
	const float BLOC_WIDTH = getBlocSize();
	
	if (
		(playerPos.x < finishPos.x + BLOC_WIDTH && playerPos.x > finishPos.x - BLOC_WIDTH) &&
		(playerPos.y < finishPos.y + BLOC_WIDTH && playerPos.y > finishPos.y - BLOC_WIDTH)
	) {
		return TRUE;
	}
	return FALSE;
}


int setDifficulty() {
	int difficulty, height, width;
	float blocWidth;

	do {
		printf("Please select a difficulty between 1-4 (the greater the harder): ");
		scanf_s("%d", &difficulty);
	} while (difficulty <= 0 || difficulty >= 5);

	switch (difficulty) {
		case 1:
			//BLOC FULL WIDTH 20 - 620x460
			blocWidth = 10.0;
			height = 23;
			width = 31;
			break;
		case 2:
			//BLOC FULL WIDTH 16 - 624x464
			blocWidth = 8.0;
			height = 29;
			width = 39;
			break;
		case 3:
			//BLOC FULL WIDTH 10 - 630x470
			blocWidth = 5.0;
			height = 47;
			width = 63;
			break;
		case 4:
			//BLOC FULL WIDTH 8 - 632x472
			blocWidth = 4.0;
			height = 59;
			width = 79;
			break;

	   /*   BROKEN
		*	case 5:
		*		//BLOC FULL WIDTH 4 - 636x476
		*		blocWidth = 2.0;
		*		height = 119;
		*		width = 159;
		*		break;
		*/
	}

	setBlocSize(blocWidth);
	setCharacterSize(blocWidth / 2.0);

	setMazeSize(height, width);

	return difficulty;
}