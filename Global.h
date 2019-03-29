#ifndef GLOBAL_H
#define GLOBAL_H

#define USER_RANGE 100

#define KB_UP 38
#define KB_LEFT 37
#define KB_DOWN 40
#define KB_RIGHT 39
#define KB_ENTER 13
#define KB_ESC 27
#define KB_F1 112


typedef enum { NONE, NORTH, EAST, SOUTH, WEST } DIRECTION;
typedef struct coordinates { int x; int y; } Coordinates;
typedef enum { FALSE, TRUE } bool;
typedef int Schema[100][100];
typedef struct maze { Schema schema; Coordinates start; Coordinates finish;} Maze;

#endif


