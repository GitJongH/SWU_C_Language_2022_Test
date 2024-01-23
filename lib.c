#include"tetris.h"



void gotoxy(int row, int column){

    static HANDLE h = NULL;
    COORD c = { column, row };

	if (!h){
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(h, c);
}


int getTimer(int timeValue){
	static unsigned int oldtime=0;
	unsigned int newtime;

	newtime = GetTickCount64();

	if( (newtime - oldtime) > timeValue){
		oldtime = newtime;
		return SUCCESS;
	}

	return FAIL;
}

void waiting(int timeValue){
	while(1){
		if(getTimer(timeValue)==SUCCESS) break;
	}
}

int getKey(){
	int key ;
	key=getch();
	if(key == 224) key = getch();
	return key;
}

