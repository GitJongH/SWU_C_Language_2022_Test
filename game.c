#include"tetris.h"

/* �б⸻ Test - A ��
** 1. �й�:
** 2. �̸�:
** ����
** (1) ������ ������ �����ؼ� ���������� ������/���� �ǰ� �Ͻÿ�
** (2) ���� ������ �˸��� start()�Լ��� �ۼ��ϰ�, 
       ���� ���� �� main()���� ȣ���Ͻÿ�.
	   start()�Լ��� �й��� �̸��� �Է� �޾� ȭ�� �߰��� ����Ѵ�.
**     start()�Լ��� ����ڰ� Ű���忡 �ƹ� Ű�� �Է��ϸ� return �Ѵ�.
**     �Է¹��� �й��� �̸��� ���� ���� �� score.txt ���Ͽ� ������ �Բ� ��ϵȴ�.
** (3) z�� ���� 1���� �߰��Ͻÿ�.
** (4) score ������ ȭ�鿡 ����Ͻÿ�. (������ �ϳ� ������ ������ 10���� ����).
** (5) �����̽� Ű�� �ԷµǸ� ���� ���� �� �Ʒ��� ����߸��ÿ�.
** (6) score.txt ���Ͽ� �й�, �̸�, ���ھ �����Ͻÿ�.
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