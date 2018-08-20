/* function.cpp */
#include "DxLib.h"
#include "Header.h"

extern int Key[256];//キー

//キー入力
int GetHitKeyStateAll_2(int KeyStateBuf[]) {
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	for (int i = 0; i<256; i++) {
		if (GetHitKeyStateAll_Key[i] == 1) KeyStateBuf[i]++;
		else                            KeyStateBuf[i] = 0;
	}
	return 0;
}

//フレーム管理（１秒間に約60フレームになるように遅くしている。）
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
//　色変換 (i,j)は8*8で渡す
//*****************************
int Translate_Color(ch_t *ch, int j, int i) {

	int color;

	switch (ch->map[j][i + PUZ_COL]) {
		case 1:
			color = 119;//赤
			break;
		case 2:
			color = 19;//青
			break;
		case 3:
			color = 89;//黄色
			break;
		case 4:
			color = 59;//緑
			break;
		case 5:
			color = 159;//紫
			break;
	}
	return color;
}