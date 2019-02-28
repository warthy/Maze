#include <stdio.h>
#include "library\graphics.h"

#include "Character.h"

typedef enum { false, true } bool;
bool isWin;
void initGame();

int main() {

	initGame();

	int keyPressed = 0;
	do {
		DrawCharacter();

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
}


void initGame() {
	initCharacterPosition();
	isWin = false;
}