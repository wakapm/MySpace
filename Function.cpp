/* function.cpp */
#include "DxLib.h"
#include "Header.h"
#include "math.h"

extern int Key[256];//�L�[

//�L�[����
int GetHitKeyStateAll_2(int KeyStateBuf[]) {
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	for (int i = 0; i<256; i++) {
		if (GetHitKeyStateAll_Key[i] == 1) KeyStateBuf[i]++;
		else                            KeyStateBuf[i] = 0;
	}
	return 0;
}

//�t���[���Ǘ��i�P�b�Ԃɖ�60�t���[���ɂȂ�悤�ɒx�����Ă���B�j
void wait_fanc() {
	int term;
	static int t = 0;
	term = GetNowCount() - t;
	if (16 - term>0)
		Sleep(16 - term);
	t = GetNowCount();
	return;
}

//*****************************
//�@�F�ϊ� (i,j)��8*8�œn��
//*****************************
int Translate_Color(int num) {

	int color;

	switch (num) {
		case 1:
			color = 119;//��
			break;
		case 2:
			color = 19;//��
			break;
		case 3:
			color = 89;//���F
			break;
		case 4:
			color = 59;//��
			break;
		case 5:
			color = 159;//��
			break;
		default:
			color = 199;//��
			break;
	}
	return color;
}

//*****************************
//�@�Ώی��̐������o
//�@��F12345��4���ځ�2
//  (math.h���g�p)
//*****************************
int Pick_Number(int gene,int pick) {

	int answer;

	int hoge1, hoge2, hoge3;

	hoge1 = gene / pow(10, pick - 1);
	hoge2 = gene / pow(10, pick);
	hoge3 = hoge2 * 10;

	//�ׂ���ƍ��𗘗p���đΏی��𒊏o
	answer = hoge1 - hoge3;


	return answer;
}