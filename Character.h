#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct coordinates { int x; int y; } Coordinates;

extern void initCharacterPosition();
extern void DrawCharacter();
extern void MoveUp();
extern void MoveDown();
extern void MoveRight();
extern void MoveLeft();
extern Coordinates GetPosition();

#endif