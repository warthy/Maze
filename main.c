#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>   

#include "Global.h"
#include "Character.h"

bool isWin;
void initGame();

int main() {
	int gd = DETECT, gm = 0;
	initgraph(&gd, &gm, "");
	initGame();

	int keyPressed = 0;
	do {
		clearviewport();
		DrawCharacter();
		
		delay(50);
		if (_kbhit()) {
			keyPressed = _getch();
			switch (keyPressed) {
				case KEY_UP:
					if (1) {
						MoveUp();
					}
					break;
				case KEY_DOWN:
					if (1) {
						MoveDown();
					}
					break;
				case KEY_RIGHT:
					if (1) {
						MoveRight();
					}
					break;
				case KEY_LEFT:
					if (1) {
						MoveLeft();
					}
					break;
			}
		}

	} while (isWin || keyPressed != KEY_ESCAPE);

	return 0;
}


void initGame() {
	initCharacterPosition();
	isWin = FALSE;
}