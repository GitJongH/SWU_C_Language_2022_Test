#include "tetris.h"

int baseGround[SIZE_ROW][SIZE_COLUMN];
int displayGround[SIZE_ROW][SIZE_COLUMN];
int previousGround[SIZE_ROW][SIZE_COLUMN];

Point	block[NUM_BLOCK_TYPE][NUM_BLOCK_DIR][NUM_BLOCK_POINT]={
	{{{0,0},{1,0},{2,0},{2,1}},
	 {{0,0},{0,1},{0,2},{1,0}},
	 {{0,0},{0,1},{1,1},{2,1}},
	 {{0,2},{1,0},{1,1},{1,2}}
	}
};