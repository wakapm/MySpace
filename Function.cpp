/* function.cpp */
#include "DxLib.h"
#include "Header.h"
#include "math.h"

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
int Translate_Color(int num) {

	int color;

	switch (num) {
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
		default:
			color = 199;//黒
			break;
	}
	return color;
}

//*****************************
//　対象桁の数字抽出
//　例：12345の4桁目⇒2
//  (math.hを使用)
//*****************************
int Pick_Number(int gene,int pick) {

	int answer;

	int hoge1, hoge2, hoge3;

	hoge1 = gene / pow(10, pick - 1);
	hoge2 = gene / pow(10, pick);
	hoge3 = hoge2 * 10;

	//べき乗と差を利用して対象桁を抽出
	answer = hoge1 - hoge3;


	return answer;
}