#ifndef CHARACTER_H
#define CHARACTER_H

extern void initCharacterPosition(Coordinates);
extern void drawCharacter();
extern void moveCharacter(Maze);
extern void setCharacterSize(float userSize);
extern Coordinates getCharacterPosition();

#endif