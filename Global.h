#ifndef GLOBAL_H
#define GLOBAL_H

#define USER_WIDTH 5
#define BLOC_WIDTH 10

typedef enum { NORTH, EAST, SOUTH, WEST } DIRECTION;
typedef struct coordinates { int x; int y; } Coordinates;
typedef enum { FALSE, TRUE } bool;
typedef int Schema[24][32];
typedef struct maze { Schema schema; Coordinates start; } Maze;

#endif


