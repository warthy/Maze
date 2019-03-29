#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>   

#include "Global.h"
#include "Character.h"
#include "Maze.h"
#include "Bloc.h"



bool isWin(void);
void initGame(void);
int setDifficulty(void);
void displayText(int x, int y, char string[], int fontSize);
void clearFullScreen();


/* ENTRY POINT - Game loop*/
int main() {
	int gd = DETECT, gm = 0, difficulty, choiceMade = 0;;

	do {

		initgraph(&gd, &gm, "RGB");
		
		difficulty = setDifficulty();
		displayText(250, 100, "Maze generating...", 10);
		initGame();


		int i = 0, startTime = time(NULL);
		do {
			
			setactivepage(i % 2);
	
			clearviewport();

			drawMaze(getCharacterPosition());
			drawCharacter();
			
			delay(5);

			

			if (keypressed(KB_F1)) {
				changeVisibility();
				delay(100);
			}
				
			else
				moveCharacter(getMaze());
			
			delay(10);
			setvisualpage(i % 2);
			i++;

		} while (!isWin() && !keypressed(KB_ESC));
		/* Game's over */
		clearviewport();
		setcolor(rgb(255, 255, 255));

		int endTime = time(NULL), timeTaken = (endTime - startTime);
		char finishText[100];
		

		/* Winning screen */
		if (isWin()) {
			displayText(20, 100, "CONGRAT'S YOU BEAT THE MAZE !", 30);

			if(timeTaken > 60)	sprintf_s(finishText, 100, "This took you: %dmin and %ds \n\n", (int)(timeTaken / 60), timeTaken % 60);
			else				sprintf_s(finishText, 100, "This took you: %ds \n\n", timeTaken);
			displayText(230, 200, finishText, 12);

			sprintf_s(finishText, 100, "score: %d\n\n", (int)( exp(difficulty) / (float)(timeTaken) ) * 2500);
			displayText(10, getmaxy()-18, finishText, 8);
		}
		/* Gave up screen */
		else {
			displayText(60, 100, "AND IT'S A WIN FOR THE MAZE", 30);

			if (timeTaken > 60)	sprintf_s(finishText, 100, "You gave up after: %dmin and %d s\n\n", (int)(timeTaken / 60), timeTaken % 60);
			else				sprintf_s(finishText, 100, "You gave up after: %d s\n\n", timeTaken);
			displayText(220, 200, finishText, 12);
		}

		displayText(6, 6, "Press ESC to exit program", 4);
		displayText(getmaxx() - 120, 6, "Press ENTER to restart", 4);
		
		choiceMade = 0;

		/* We don't do anything while the player has'nt pressed ENTER or ESC */
		do {
			if (keypressed(KB_ENTER))
				choiceMade = 1;
			else if(keypressed(KB_ESC))
				choiceMade = 2;

		} while (!choiceMade);

	} while (choiceMade == 1);

	return 0;
}


/*
 *  Function:  initGame
 *  --------------------
 *  Initialize the game by generating a maze and setting character starting position.
 *
 *  returns: void
 */
void initGame() {
	initMaze();
	initCharacterPosition(getMaze().start);
}


/*
 *  Function:  isWin
 *  --------------------
 *  Check if the character has found the finishing point.
 *
 *  returns: true if he has win otherwise false
 */
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


/*
 *  Function:  setDifficulty
 *  --------------------
 *  Pick and set difficulty of the maze.
 *
 *  returns: difficulty selected
 */
int setDifficulty() {
	int difficulty, height, width, selected = 1, j = 0, x, y = 380;
	bool confirm = FALSE;
	float blocWidth;
	char number[3];

	do {
		setactivepage(j % 2);
		clearviewport();

		displayText(6, 6, "Press ESC to exit program", 4);
		displayText(290, 100, "Welcome to", 10);
		displayText(145, 150, "THE MAZE", 70);

		displayText(200, 300, "Select a difficulty between 1 and 4 :", 10);
		displayText(205, 317, "Move with the arrow and press Enter to confirm", 4);
		
		if (keypressed(KB_ENTER)) {
			confirm = TRUE;
			delay(300);
		}
		else if (keypressed(KB_LEFT) && selected > 1) {
			selected--;
			delay(300);
		}
		
		else if (keypressed(KB_RIGHT) && selected < 4) {
			selected++;
			delay(300);
		}
		else if (keypressed(KB_ESC))
			exit(0);

		/* Display the 4 possible difficulties */
		for (int i = 1; i < 5; i++) {
			x = (640 / 5)*i;
			sprintf_s(number, 3, " %d", i);
			displayText(x, y, number, 15);

			// Underline selected difficulty.
			if (selected == i && j % 10)
				line(x , y + 25, x + 20, y + 25);
		}

		setvisualpage(j % 2);
		j++;

	} while (!confirm);
	difficulty = selected;

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
	}

	setBlocSize(blocWidth);
	setCharacterSize(blocWidth / 2.0);

	setMazeSize(height, width);

	clearFullScreen();
	return difficulty;
}


/*
 *  Function:  displayText
 *  --------------------
 *  Display text inside window using BGI function
 *  as it displays chineses char if we use BGI function directly.
 *
 *  x: x position of the beginning of the text.
 *  y: y position of the beginning of the text.
 *  string: string which will be displayed.
 *  fontSize: font size of the text .
 *
 *  returns: void
 */
void displayText(int x, int y, char string[], int fontSize) {
	int stringLength = strlen(string), charWidth = 0;
	unsigned short character[1];
	settextstyle(DEFAULT_FONT, HORIZ_DIR, fontSize);

	for (int i=0; i < stringLength; i++) {
		character[0] = string[i];
		outtextxy(x + charWidth, y, character);

		char ch[2];
		ch[0] = (char)(character[0]);
		ch[1] = '\0';
		charWidth += textwidth(ch);
	}
}


void clearFullScreen() {
	setviewport(0, 0, getmaxx(), getmaxy(), 0);
	clearviewport();
}
