#include"tetris.h"


extern Point	block[NUM_BLOCK_TYPE][NUM_BLOCK_DIR][NUM_BLOCK_POINT];

extern int baseGround[SIZE_ROW][SIZE_COLUMN];
extern int displayGround[SIZE_ROW][SIZE_COLUMN];

Point	currentPoint;
Block	currentBlock;

//set based on input key
Point	tempPoint;
Block	tempBlock;

void init(){
	int i, k;

	//1.set base
	for(i=0;i<SIZE_ROW;i++){
		for(k=0;k<SIZE_COLUMN;k++){
			baseGround[i][k] = G_EMPTY;
		}
	}

	for(k=0;k<SIZE_COLUMN;k++){
		baseGround[0][k] = G_WALL;
		baseGround[SIZE_ROW-1][k] = G_WALL;
	}

	for(i=0;i<SIZE_ROW;i++){
		baseGround[i][0] = G_WALL;
		baseGround[i][SIZE_COLUMN-1] = G_WALL;
	}

	//2. set previous
	for(i=0;i<SIZE_ROW;i++){
		for(k=0;k<SIZE_COLUMN;k++){
			previousGround[i][k]=G_EMPTY;
		}
	}

	srand(time(NULL));
	generateBlock();
	
}

void generateBlock(){
	//1. set currentPoint
	currentPoint.row = 1;
	currentPoint.column = SIZE_COLUMN/2;

	//2. set currentBlock;
#ifdef _MY_TEST
	currentBlock.type = 1; //for test
#else
	currentBlock.type = rand()%NUM_BLOCK_TYPE; 
#endif
	currentBlock.dir  = rand()%NUM_BLOCK_DIR;  
}

void showGround(int addBlockFlag){
	int i,k;
	int row, column;
	//copy base
	for(i=0;i<SIZE_ROW;i++){
		for(k=0;k<SIZE_COLUMN;k++){
			displayGround[i][k]=baseGround[i][k];
		}
	}
	//add block on display
	if(addBlockFlag == SUCCESS){
		for(i=0;i<NUM_BLOCK_POINT;i++){
			row = block[currentBlock.type][currentBlock.dir][i].row;
			column = block[currentBlock.type][currentBlock.dir][i].column;

			row		+=currentPoint.row;
			column	+=currentPoint.column;

			displayGround[row][column]=G_BLOCK;
		}
	}

	//print	
	for(i=0;i<SIZE_ROW;i++){
		for(k=0;k<SIZE_COLUMN;k++){
			if(displayGround[i][k] != previousGround[i][k]){
				gotoxy(i,k*2);
				switch(displayGround[i][k]){
				case G_EMPTY:
					printf("  ");
					break;
				case G_WALL:
					printf("бр");
					break;
				case G_BLOCK:
					printf("бс");
					break;
				default:
					break;
				}
			}
		}		
	}
	gotoxy(SIZE_ROW+1,0);
	printf("t=%d, d=%d, p=(%d,%d)", currentBlock.type, currentBlock.dir, currentPoint.row, currentPoint.column);

	// copy
	for(i=0;i<SIZE_ROW;i++){
		for(k=0;k<SIZE_COLUMN;k++){
			previousGround[i][k] = displayGround[i][k];
		}
	}
}


void setTempBlock(int key){

	tempPoint = currentPoint;
	tempBlock = currentBlock;
	switch(key){
	case KEY_DOWN:
		tempPoint.row +=1;
		break;
	case KEY_RIGHT:
		tempPoint.column +=1;
		break;
	case KEY_LEFT:
		tempPoint.column -=1;
		break;
	case KEY_UP:
		tempBlock.dir = (tempBlock.dir +1) % NUM_BLOCK_DIR;				
		break;
	default:
		break;
	}
}

int checkMove(){
	int row, column, i;

	//check ...?????????
	for(i=0;i<NUM_BLOCK_POINT;i++){
		row = block[tempBlock.type][tempBlock.dir][i].row;
		column = block[tempBlock.type][tempBlock.dir][i].column;

		row		+=tempPoint.row;
		column	+=tempPoint.column;

		if(baseGround[row][column] != G_EMPTY) return FAIL;
	}
	
	//if it is possilbe to move....
	return SUCCESS;
}

void moveBlock(){
	currentBlock = tempBlock;
	currentPoint = tempPoint;
}

void addBlockonBase(){
	int i, row, column;

	for(i=0;i<4;i++){
		row = currentPoint.row + block[currentBlock.type][currentBlock.dir][i].row;
		column = currentPoint.column + block[currentBlock.type][currentBlock.dir][i].column;

		baseGround[row][column] = G_BLOCK;
	}
}

int removeOneLine(int row){
	int i, k;

	for(k=1; k < SIZE_COLUMN-1;k++){
		if(baseGround[row][k] == G_EMPTY){
			return FAIL; //not remove
		}
	}

	//remove
	for(i=row; i>1; i--){
		for(k=1; k < SIZE_COLUMN-1;k++){
			baseGround[i][k] = baseGround[i-1][k];
		}
	}
	return SUCCESS;
}

void removeLines(){
	int i;
	for(i=SIZE_ROW-2 ; i>1 ; i--){
		if( removeOneLine(i) == SUCCESS){
			showGround(FAIL);
			waiting(500);
			i++;
		}
	}
}

int checkFinish(){

	int i, row, column;

	for(i=0;i<4;i++){
		row = currentPoint.row + block[currentBlock.type][currentBlock.dir][i].row;
		column = currentPoint.column + block[currentBlock.type][currentBlock.dir][i].column;

		if( baseGround[row][column] != G_EMPTY){
			gotoxy(SIZE_ROW/2-1, 5);
			printf("=================");
			gotoxy(SIZE_ROW/2, 5);
			printf("   GAME OVER     ");
			gotoxy(SIZE_ROW/2+1, 5);
			printf("=================");
			return SUCCESS;
		}
	}
	return FAIL;
}