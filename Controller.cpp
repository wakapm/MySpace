#include "DxLib.h"
#include "Header.h"

extern int Key[256];//�L�[
extern int main_state;

void Controller(ch_t *ch) {

	int hoge;

	if (Key[KEY_INPUT_X] == 1) {

	//	break;
	}
	//�E��������E�B(��2�}�X�̘g�Ȃ̂�-2)
	if (Key[KEY_INPUT_RIGHT] == 1 && ch->x != PUZ_ROW - 2) {
		ch->x++;
	}
	//���������獶�B
	if (Key[KEY_INPUT_LEFT] == 1 && ch->x != 0) {
		ch->x--;
	}
	//�㉟�������B
	if (Key[KEY_INPUT_UP] == 1 && ch->y != 0) {
		ch->y--;
	}
	//���������牺�B������ΉE���B
	if (Key[KEY_INPUT_DOWN] == 1 && ch->y != PUZ_COL - 1) {
		ch->y++;
	}
	//���E�V���b�t��
	if (Key[KEY_INPUT_Z] == 1 ) {
		hoge = ch->map[ch->x][ch->y + 8];
		ch->map[ch->x][ch->y + 8] = ch->map[ch->x + 1][ch->y + 8];
		ch->map[ch->x + 1][ch->y + 8] = hoge;
		main_state = 1;
	}

}

void Move_Only_Controller(ch_t *ch) {

	int hoge;


	//�E��������E�B(��2�}�X�̘g�Ȃ̂�-2)
	if (Key[KEY_INPUT_RIGHT] == 1 && ch->x != PUZ_ROW - 2) {
		ch->x++;
	}
	//���������獶�B
	if (Key[KEY_INPUT_LEFT] == 1 && ch->x != 0) {
		ch->x--;
	}
	//�㉟�������B
	if (Key[KEY_INPUT_UP] == 1 && ch->y != 0) {
		ch->y--;
	}
	//���������牺�B������ΉE���B
	if (Key[KEY_INPUT_DOWN] == 1 && ch->y != PUZ_COL - 1) {
		ch->y++;
	}


}