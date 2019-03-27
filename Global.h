#ifndef GLOBAL_H
#define GLOBAL_H

#define USER_RANGE 100


#define USER_WIDTH 5
#define BLOC_WIDTH 10
#define FINISH_WIDTH 10

#define MAZE_HEIGHT 23
#define MAZE_WIDTH 31


typedef enum { NORTH, EAST, SOUTH, WEST } DIRECTION;
typedef struct coordinates { int x; int y; } Coordinates;
typedef enum { FALSE, TRUE } bool;
typedef int Schema[100][100];
typedef struct maze { Schema schema; Coordinates start; Coordinates finish;} Maze;

#endif


