#ifndef GLOBAL_H
#define GLOBAL_H

//CHANGE VALUE TO 1 TO SEE THE MAZE COMPLETELY
#define CHEATER_MODE 0;
#if CHEATER_MODE
	#define USER_RANGE 100000
#else
	#define USER_RANGE 100
#endif

#define USER_WIDTH 5
#define BLOC_WIDTH 10

typedef enum { NORTH, EAST, SOUTH, WEST } DIRECTION;
typedef struct coordinates { int x; int y; } Coordinates;
typedef enum { FALSE, TRUE } bool;
typedef int Schema[24][32];
typedef struct maze { Schema schema; Coordinates start; Coordinates finish; } Maze;

#endif


