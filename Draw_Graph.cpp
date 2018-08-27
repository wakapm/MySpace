#include "DxLib.h"
#include "Header.h"


void Draw_Graph(ch_t *ch, graph_t *gr,enemy_t *en,skill_t sk[]) {

	int i,j;
	int color,pick_id;
	int base_x, base_y;
	int move_x_a, move_x_b, move_y_a, move_y_b;

	int mes_color = GetColor(0, 0, 0), shd_color = GetColor(255, 255, 255), hp_color = GetColor(255,200,0);

	static unsigned int draw_counter = 0;

	// ��ʂ����œh��Ԃ�
	DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), TRUE);
	//�w�i�`��
	DrawGraph(0, 0, gr->scape[0], TRUE);

	//�p�Y���w�i
	//DrawBox(PUZZLE_X, PUZZLE_Y, 32 * PUZ_ROW + PUZZLE_X, 32 * PUZ_COL + PUZZLE_Y, GetColor(255, 255, 255), TRUE);
	DrawBox(PUZZLE_X, PUZZLE_Y, 32 * PUZ_ROW + PUZZLE_X, 32 * PUZ_COL + PUZZLE_Y, GetColor(55, 55, 55), TRUE);
	DrawExtendGraph(PUZZLE_X, PUZZLE_Y, 32*PUZ_ROW + PUZZLE_X, 32 * PUZ_COL + PUZZLE_Y, gr->skill_window[0], TRUE);

	//�ʕ`��
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {

			//�����͕`��Ȃ�
			if (ch->map[j][i + PUZ_COL] != 0) {

				//�F���Z�b�g 
				color = Translate_Color(ch->map[j][i + PUZ_COL]);

				//�����O�_�Ł@�J�E���^����̂Ƃ��ɏ�������
				if (ch->rule_state == 1 && ch->reserve[j][i] == 1 && draw_counter%10 <= 4) {
					DrawExtendGraph(32 * j + PUZZLE_X, 32 * i + PUZZLE_Y, 32 * j + 32 + PUZZLE_X, 32 * i + 32 + PUZZLE_Y, gr->jewel[color-3], TRUE);
				}else {
					//�d�͗����Ή��ʕ\��
					//ch->fall�����n�_����̋���������
					//�\���g���Ȃ�Ε\��
					if (32 * i - ch->fall[j][i + PUZ_COL] >= 0) {
						DrawExtendGraph(32 * j + PUZZLE_X, 32 * i + PUZZLE_Y - ch->fall[j][i + PUZ_COL], 32 * j + 32 + PUZZLE_X, 32 * i + 32 + PUZZLE_Y - ch->fall[j][i + PUZ_COL], gr->jewel[color], TRUE);
					}
					//�ʏ�ʕ\��
					//DrawExtendGraph(32 * j + PUZZLE_X, 32 * i + PUZZLE_Y, 32 * j + 32 + PUZZLE_X, 32 * i + 32 + PUZZLE_Y, gr->jewel[color], TRUE);
				}
			}
			//DrawExtendGraph(32 * j + 32, 32 * i + 80, 32 * j + 32 + 32, 32 * i + 80 + 32, gr->jewel[color], TRUE);
			/*
			DrawExtendGraph(32*j + 32, 32*i + 80, 32*j + 32 + 32, 32*i + 80 + 32, gr->skill_icon[2], TRUE);
			DrawExtendGraph(32 * j + 200, 32 * i + 80, 32 * j + 200 + 32, 32 * i + 80 + 32, gr->skill_icon[59], TRUE);
			*/
		}
	}

	// ���ߐF��ύX
	//SetTransColor(255, 255, 255);
	//DrawGraph(24 * ch->x + PUZZLE_X, 24 * ch->y + PUZZLE_Y, gr->choice[0], TRUE);

	//�g�`��
	if (ch->mode == 0) {
		DrawExtendGraph(32 * ch->x + PUZZLE_X, 32 * ch->y + PUZZLE_Y, 32 * ch->x + 64 + PUZZLE_X, 32 * ch->y + 32 + PUZZLE_Y, gr->choice[0], TRUE);
	}
	else if(ch->mode == 1) {
		DrawExtendGraph(32 * ch->x + PUZZLE_X, 32 * ch->y + PUZZLE_Y, 32 * ch->x + 32 + PUZZLE_X, 32 * ch->y + 32 + PUZZLE_Y, gr->choice[0], TRUE);
	}
	DrawExtendGraph(PUZZLE_X, 32 * ch->set_y + PUZZLE_Y, 32*8 + PUZZLE_X, 32 * ch->set_y + 32 + PUZZLE_Y, gr->choice[1], TRUE);


	//�G�z�u
	DrawGraph(370, 40, gr->m_boss[0], TRUE);
	//�GHP

	//hp�o�[�̕\��
	DrawGraph(370, 160, gr->hp_bar[0], TRUE);
	DrawRectGraph(370, 160, 0, 0, 7 + 114 * (en->hp * 100 / en->maxhp) / 100, 32, gr->hp_bar[1], TRUE, FALSE);
	//hp�\��
	SetFontSize(12);
	DrawFormatString(410 - 1, 160 - 1, mes_color, "%d/%d", en->hp, en->maxhp);//�e
	DrawFormatString(410 + 1, 160 + 1, mes_color, "%d/%d", en->hp, en->maxhp);//�e
	DrawFormatString(410    , 160    , hp_color, "%d/%d", en->hp, en->maxhp);//

	//�n�[�g
	for (i = 0; i < 5; i++) {
		DrawGraph(370 + 24 * i, 200, gr->heart, TRUE);
	}

	//�X�L���E�B���h�E
	// ��ʂ𔒂œh��Ԃ�
	DrawBox(310, 240, 600, 440, GetColor(255, 255, 255), FALSE);
	DrawBox(310 + 4, 240 + 4, 600 + 4, 440 + 4, GetColor(255, 255, 255), FALSE);
	DrawBox(310 + 6, 240 + 6, 600 - 2, 440 - 2, GetColor(200, 200, 245), TRUE);
	
	//�X�L�����i����(��X�����X�L����\������悤�ɂ���)
	SetFontSize(20);
	ChangeFont("�l�r�S�V�b�N");

	for (i = 0; i < 6; i++) {
		for (j = 0; j < sk[i].number; j++) {

			//�X�L�������p�̋ʂ̐F��gene��蒊�o
			pick_id = Pick_Number(sk[i].gene, sk[i].number - j);
			color = Translate_Color(pick_id);

			DrawExtendGraph(320 + 20 * j, 250 + 20 * i, 320 + 20 * j + 20,250 + 20 * i + 20, gr->jewel[color], TRUE);
		}
		DrawFormatString(320 + 20 * j + 1, 250 + 20 * i + 1, shd_color, "%d�_���[�W", sk[i].base_damage);//�e
		DrawFormatString(320 + 20 * j    , 250 + 20 * i    , mes_color, "%d�_���[�W", sk[i].base_damage);//
	}
	//DrawExtendGraph(360, 240, 600, 440, gr->skill_window[0], TRUE);


	//�ʏ������̔j���`��
	for (i = 0; i < BURST; i++) {
		if (ch->burst_timer[i] > 0) {
			//�����̂ŕϐ����B8�͒��S����`�悷�邽�߂ɂ��炵�Ă�����W�B
			base_x = 32 * ch->burst_x[i] + PUZZLE_X + 8;
			base_y = 32 * ch->burst_y[i] + PUZZLE_Y + 8;

			move_x_a = (30 - ch->burst_timer[i]) * 3;
			move_x_b = (30 - ch->burst_timer[i]) * 2;
			move_y_a = (24 - ch->burst_timer[i]) *(24 - ch->burst_timer[i])/2;
			move_y_b = (26 - ch->burst_timer[i]) *(26 - ch->burst_timer[i])/2;
			
			//�j��4����

			//�E��
			DrawExtendGraph(base_x + move_x_a, base_y + move_y_a,
							base_x + move_x_a + 32, base_y + move_y_a + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);
			//�E��
			DrawExtendGraph(base_x + move_x_b, base_y + move_y_b,
							base_x + move_x_b + 32, base_y + move_y_b + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);

			//�E��
			DrawExtendGraph(base_x - move_x_a, base_y + move_y_a,
							base_x - move_x_a + 32, base_y + move_y_a + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);
			//�E��
			DrawExtendGraph(base_x - move_x_b, base_y + move_y_b,
							base_x - move_x_b + 32, base_y + move_y_b + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);

			ch->burst_timer[i]--;
		}
	}
	

	if (draw_counter != 65535)draw_counter++;	//�P�����ɃJ�E���g
	else draw_counter = 0;
}

