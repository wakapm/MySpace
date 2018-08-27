#include "DxLib.h"
#include "Header.h"

extern int Key[256];//キー
extern int main_state;

void Controller(ch_t *ch) {

	int i,hoge;

	if (Key[KEY_INPUT_X] == 1) {

		//	break;
	}
	//右押したら右。(横2マスの枠なので-2)
	if (Key[KEY_INPUT_RIGHT] == 1 && ch->x != PUZ_ROW - 2) {
		ch->x++;
	}
	//左押したら左。
	if (Key[KEY_INPUT_LEFT] == 1 && ch->x != 0) {
		ch->x--;
	}
	//上押したら上。
	if (Key[KEY_INPUT_UP] == 1 && ch->y != 0) {
		ch->y--;
	}
	//下押したら下。無ければ右下。
	if (Key[KEY_INPUT_DOWN] == 1 && ch->y != PUZ_COL - 1) {
		ch->y++;
	}
	//左右シャッフル
	if (Key[KEY_INPUT_Z] == 1) {

		switch (ch->mode) {

			case 0://横２
				hoge = ch->map[ch->x][ch->y + 8];
				ch->map[ch->x][ch->y + 8] = ch->map[ch->x + 1][ch->y + 8];
				ch->map[ch->x + 1][ch->y + 8] = hoge;
				main_state = 1;
				break;

			case 1://固定化モード
				if (ch->map[ch->x][ch->y + 8] < 10) {
					ch->map[ch->x][ch->y + 8] += 10;
				}
				break;
		}

	}
	//攻撃確定
	if (Key[KEY_INPUT_C] == 1) {
		//消去のルール適用
		ch->rule_state = 1;
		//セットの枠の玉を消去
		for (i = 0; i < PUZ_ROW; i++) {
			ch->reserve[i][ch->set_y] = 1;
		}
		main_state = 1;
	}
	//固定化モード
	if (Key[KEY_INPUT_V] == 1) {
		//横２⇔固定化
		if (ch->mode == 0) {
			ch->mode = 1;
		}
		else {
			ch->mode = 0;
		}
	}

}

void Move_Only_Controller(ch_t *ch) {

	int hoge;


	//右押したら右。(横2マスの枠なので-2)
	if (Key[KEY_INPUT_RIGHT] == 1 && ch->x != PUZ_ROW - 2) {
		ch->x++;
	}
	//左押したら左。
	if (Key[KEY_INPUT_LEFT] == 1 && ch->x != 0) {
		ch->x--;
	}
	//上押したら上。
	if (Key[KEY_INPUT_UP] == 1 && ch->y != 0) {
		ch->y--;
	}
	//下押したら下。無ければ右下。
	if (Key[KEY_INPUT_DOWN] == 1 && ch->y != PUZ_COL - 1) {
		ch->y++;
	}


}