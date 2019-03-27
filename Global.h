#ifndef GLOBAL_H
#define GLOBAL_H

/* CHANGE VALUE TO 1 TO SEE THE MAZE COMPLETELY */
#define CHEATER_MODE 1;
#if CHEATER_MODE
	#define USER_RANGE 100000
#else
	#define USER_RANGE 100
#endif

#define USER_WIDTH 5
#define BLOC_WIDTH 10
#define MAZE_HEIGHT 24
#define MAZE_WIDTH 32
#define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )

typedef enum { NORTH, EAST, SOUTH, WEST } DIRECTION;
typedef struct coordinates { int x; int y; } Coordinates;
typedef enum { FALSE, TRUE } bool;
typedef int Schema[MAZE_HEIGHT][MAZE_WIDTH];
typedef struct maze { Schema schema; Coordinates start; Coordinates finish; } Maze;

#endif


