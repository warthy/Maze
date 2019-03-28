#ifndef GLOBAL_H
#define GLOBAL_H

#define USER_RANGE 100


typedef enum { NORTH, EAST, SOUTH, WEST } DIRECTION;
typedef struct coordinates { int x; int y; } Coordinates;
typedef enum { FALSE, TRUE } bool;
typedef int Schema[100][100];
typedef struct maze { Schema schema; Coordinates start; Coordinates finish;} Maze;

#endif


