#include"tetris.h"

/* 학기말 Test - A 반
** 1. 학번:
** 2. 이름:
** 문제
** (1) 컴파일 오류를 수정해서 정상적으로 컴파일/실행 되게 하시오
** (2) 게임 시작을 알리는 start()함수를 작성하고, 
       게임 시작 전 main()에서 호출하시오.
	   start()함수는 학번과 이름을 입력 받아 화면 중간에 출력한다.
**     start()함수는 사용자가 키보드에 아무 키나 입력하면 return 한다.
**     입력받은 학번과 이름은 게임 종료 시 score.txt 파일에 점수와 함께 기록된다.
** (3) z자 블럭을 1개를 추가하시오.
** (4) score 정보를 화면에 출력하시오. (라인이 하나 삭제될 때마다 10점씩 증가).
** (5) 스패이스 키가 입력되면 현재 블럭을 맨 아래로 떨어뜨리시오.
** (6) score.txt 파일에 학번, 이름, 스코어를 저장하시오.
*/

extern Point currentPoint;

int main(){
	int key;
	int changed;

	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);

	system("mode con: cols=40 lines=30");
	
	init();
	showGround(SUCCESS);

	while(1){
		changed = FAIL;
		if(getTimer(1000) == SUCCESS ){
			key = KEY_DOWN;
			changed = SUCCESS;
			
		}
		else if(kbhit()){
			key = getKey();
			changed = SUCCESS;
		}

		if(changed == SUCCESS){
			setTempBlock(key);
			if( checkMove() == SUCCESS){
					moveBlock();
					showGround(SUCCESS);					
			}
			else if(key == KEY_DOWN){
				//add a block on baseGround
				addBlockonBase();
				//check remove...
				removeLines();

				//new block
				generateBlock();
				if( checkFinish()==SUCCESS){
					break;
				}
				showGround(SUCCESS);					
			}
		}	
	}	
	return 0;
}