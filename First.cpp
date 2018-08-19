#include "DxLib.h"
#include "Header.h"
#include <math.h>

int Key[256];//�L�[
unsigned int counter = 0;//�J�E���^�[
int main_state = 0;//���C���X�e�[�g�ϐ�

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���C���\����
	ch_t ch;
	//�摜�`��\����
	graph_t gr;
	//�G�f�[�^�\����
	enemy_t en;
	//�G�f�[�^�}�X�^�\����
	enemy_t em[20];

	//�E�B���h�E���Ə���������
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1;

	Load_Graph(&gr);
	Init(&ch,&en);

	while (!ProcessMessage() && !ClearDrawScreen()
		&& !GetHitKeyStateAll_2(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//ү���ޏ���  ��ʂ�ر  ���ް�ޓ��͏�Ԏ擾  ESC���������ƏI��

		
		switch(main_state) {
			case 0:
				Controller(&ch);
				break;
			case 1:
				Move_Only_Controller(&ch);
				Apply_Rule(&ch, &gr);
				break;
		}
		Draw_Graph(&ch,&gr,&en);


		if (Key[KEY_INPUT_X] == 1) {
			Init(&ch, &en);

		}

		if (counter != 65535)counter++;	//�P�����ɃJ�E���g
		else counter = 0;
		ScreenFlip();//����ʂ�\��ʂɔ��f
		wait_fanc();//��U�O�t���[���ɒ���
	}



	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void Init(ch_t *ch,enemy_t *en) {
	int i, j;
	int keep[2];

	ch->x = 0;
	ch->y = 0;

	ch->set_y = 6;

	ch->color_num = 5;

	//�ϐ�������
	ch->rule_state = 0;

	//��X�����Ɠ����
	//�G�̃X�e�[�^�X
	en->maxhp = 100;
	en->hp = 100;

	//�p�Y��������
	for (i = 0; i < 8; i++) {
		for (j = 0; j < PUZ_MAX_COL; j++) {
			ch->map[i][j] = GetRand(ch->color_num - 1)+1;
			ch->fall[i][j] = 0;
		}
	}
	//�c����3�A�T��
	for (i = 0; i < PUZ_COL; i++) {
		for (j = 2; j < PUZ_ROW; j++) {
			keep[0] = ch->map[i][j + PUZ_COL - 2];
			keep[1] = ch->map[i][j + PUZ_COL - 1];
			//�c����3�A���F�Ȃ�Ō�̐F��ς���
			if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
				//�F�ύX
				if (ch->map[i][j + PUZ_COL] != ch->color_num) {
					ch->map[i][j + PUZ_COL]++;
				}
				else {
					ch->map[i][j + PUZ_COL]=1;
				}
				//�ŏI�`�F�b�N
				Final_Check(ch, i, j);
			}
		}
	}
	
	//������3�A�T��
	for (j = 0; j < PUZ_ROW; j++) {
		for (i = 2; i < PUZ_COL; i++) {
			keep[0] = ch->map[i - 2][j + PUZ_COL];
			keep[1] = ch->map[i - 1][j + PUZ_COL];
			//������3�A���F�Ȃ�Ō�̐F��ς���
			if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
				//�F�ύX
				if (ch->map[i][j + PUZ_COL] != ch->color_num) {
					ch->map[i][j + PUZ_COL]++;
				}
				else {
					ch->map[i][j + PUZ_COL] = 1;
				}
				//�ŏI�`�F�b�N
				Final_Check(ch,i,j);
			}
		}
	}
	
}

//�����z�u��3�A���ɂȂ�Ȃ��悤�ɂ��邽�߂̍ŏI����
//�F��5��ނ���A�l�݂̔z�u�͂Ȃ��O��
//�Ăяo���ʒu�I�ɍ������ɂ͑����Ă��Ȃ����Ƃ��ۏ؂���Ă���
void Final_Check(ch_t *ch,int x,int y) {
	int keep[2];

	//�E���ɂ���2�͋ʂ��z�u�\�Ȃ�
	if (x + 2 < PUZ_ROW) {
		keep[0] = ch->map[x + 1][y + PUZ_COL];
		keep[1] = ch->map[x + 2][y + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//�F�ύX
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
			//�ċA�ŏI�`�F�b�N
			Final_Check(ch, x, y);
		}
	}
	//�㑤�ɂ���2�͋ʂ��z�u�\�Ȃ�
	if (y - 2 > 0) {
		keep[0] = ch->map[x][y - 2 + PUZ_COL];
		keep[1] = ch->map[x][y - 1 + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//�F�ύX
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
		}
	}
	//�㑤�Ɖ����ɂP���ʂ��z�u�\�Ȃ�
	if (y - 1 > 0 && y + 1 < PUZ_COL) {
		keep[0] = ch->map[x][y - 1 + PUZ_COL];
		keep[1] = ch->map[x][y + 1 + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//�F�ύX
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
			//�ċA�ŏI�`�F�b�N
			Final_Check(ch, x, y);
		}
	}
	//�����ɂ���2�͋ʂ��z�u�\�Ȃ�
	if (y + 2 < PUZ_COL) {
		keep[0] = ch->map[x][y + 2 + PUZ_COL];
		keep[1] = ch->map[x][y + 1 + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//�F�ύX
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
			//�ċA�ŏI�`�F�b�N
			Final_Check(ch, x, y);
		}
	}


}

/*
20180819 ���~�̊Ԉ�T�ԐG�ꂸ�B�����A�j���[�V�����ǉ��A�A���E�����Ƃ̌��ˍ����𒲐�����{�p�Y�������͂������񊮐��B
20180808 �����Ώۂ�_�ł��Ă��������悤�ɁB�܂��A���I�ȂƂ���͓���Ă��Ȃ��̂ő��������͂�����̂̌��h������������炵���B
20180807 �d�͂��������B�A�j���[�V�������l�����畨���ɑ΂��ė�������������ƂƂ炦��ׂ��ȋC�����邪�A�����̊ȕւ����d�����Ĉ�U�󔒂�������
�@�@�@�@ ������グ�Ă���ƌ����Ƃ����`���ɂ��Ă���B
20180806 �O���̃o�O�́A�c������3�A������ɂ�Final_Check()�֐������܂��Ȃ��Ɖ�3�A�ŉ����N����Ȃ��ꍇ�ɏC�������^�C�~���O���Ȃ����Ƃɂ����́B
�@�@�@�@ �C�������B�Ǝv�������܂������B�c3�A�̐^�񒆂���3�A�h�~�ɂ���Ď~�߂��ꍇ���P�A���Ă��Ȃ��������߂Ɛ����B���ԃp�^�[�����ǉ��B
	 �@�@�Ƃ肠�������v�����B�F�ύX��PUZ_COL��8��16-8�̈Ӗ����������݂��Ă���B���ӁB
	   �@�����܂�ɂ܂�������B��3�A�̏C���Ł���3�A�ɂȂ����ꍇ�̕ύX�Ł���3�A���V���ɂł���ꍇ���ΏہH�ŏI�`�F�b�N���ċA�ɂ����̂ł���łǂ��H
		 X�L�[��Init()�Ăт܂����B
20180805 �g�A�G�A�n�[�g�ȂǊO���������ɂ��₩�ɁB�����z�u��3�A���������Ȃ��悤�ɒ����p�̃��[�`�����쐬�B���񂩉񂵂ċH��3�A����������̂Ńo�O����B
20180803 ��3�ŏ�����悤��
20180802 ���݉�`�x�ŊJ���J�n�B8*8�̃p�Y����ʁA�ʓ���ւ�����

*/