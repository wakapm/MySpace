/* function.cpp */
#include "DxLib.h"
#include "Header.h"

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
int Translate_Color(ch_t *ch, int j, int i) {

	int color;

	switch (ch->map[j][i + PUZ_COL]) {
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
	}
	return color;
}