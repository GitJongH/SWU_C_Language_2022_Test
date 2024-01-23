#ifndef _TETRIS_H
#define _TETRIS_H

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

#if 0
#define _MY_TEST
#endif 

#define	SUCCESS	1
#define	FAIL		0

#define SIZE_ROW		20	
#define SIZE_COLUMN	15

#define NUM_BLOCK_TYPE	1
#define NUM_BLOCK_DIR	4
#define NUM_BLOCK_POINT	4

#define G_EMPTY		0
#define G_WALL		1
#define G_BLOCK		2

#define KEY_NOT			0
#define KEY_UP			72
#define KEY_DOWN			80
#define KEY_RIGHT		77
#define KEY_LEFT			75

typedef struct _Point{
	int row;
	int column;
}Point;

typedef struct _Block{
	int type;
	int dir;
}Block;


void init();
void generateBlock();
void showGround(int);
void setTempBlock(int);
int checkMove();
void moveBlock();
void addBlockonBase();
int removeOneLine(int);
void removeLines();
int checkFinish();

void gotoxy(int row, int column);
int getTimer(int timeValue);
void waiting(int timeValue);
int getKey();

#endif