#include "DxLib.h"
#include "Header.h"


void Draw_Graph(ch_t *ch, graph_t *gr,enemy_t *en,skill_t sk[]) {

	int i,j;
	int color,pick_id;
	int base_x, base_y;
	int move_x_a, move_x_b, move_y_a, move_y_b;

	int mes_color = GetColor(0, 0, 0), shd_color = GetColor(255, 255, 255), hp_color = GetColor(255,200,0);

	static unsigned int draw_counter = 0;

	// 画面を黒で塗りつぶす
	DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), TRUE);
	//背景描画
	DrawGraph(0, 0, gr->scape[0], TRUE);

	//パズル背景
	//DrawBox(PUZZLE_X, PUZZLE_Y, 32 * PUZ_ROW + PUZZLE_X, 32 * PUZ_COL + PUZZLE_Y, GetColor(255, 255, 255), TRUE);
	DrawBox(PUZZLE_X, PUZZLE_Y, 32 * PUZ_ROW + PUZZLE_X, 32 * PUZ_COL + PUZZLE_Y, GetColor(55, 55, 55), TRUE);
	DrawExtendGraph(PUZZLE_X, PUZZLE_Y, 32*PUZ_ROW + PUZZLE_X, 32 * PUZ_COL + PUZZLE_Y, gr->skill_window[0], TRUE);

	//玉描画
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {

			//消去は描画なし
			if (ch->map[j][i + PUZ_COL] != 0) {

				//色をセット 
				color = Translate_Color(ch->map[j][i + PUZ_COL]);

				//消去前点滅　カウンタが奇数のときに小さい玉
				if (ch->rule_state == 1 && ch->reserve[j][i] == 1 && draw_counter%10 <= 4) {
					DrawExtendGraph(32 * j + PUZZLE_X, 32 * i + PUZZLE_Y, 32 * j + 32 + PUZZLE_X, 32 * i + 32 + PUZZLE_Y, gr->jewel[color-3], TRUE);
				}else {
					//重力落下対応玉表示
					//ch->fallが着地点からの距離を示す
					//表示枠内ならば表示
					if (32 * i - ch->fall[j][i + PUZ_COL] >= 0) {
						DrawExtendGraph(32 * j + PUZZLE_X, 32 * i + PUZZLE_Y - ch->fall[j][i + PUZ_COL], 32 * j + 32 + PUZZLE_X, 32 * i + 32 + PUZZLE_Y - ch->fall[j][i + PUZ_COL], gr->jewel[color], TRUE);
					}
					//通常玉表示
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

	// 透過色を変更
	//SetTransColor(255, 255, 255);
	//DrawGraph(24 * ch->x + PUZZLE_X, 24 * ch->y + PUZZLE_Y, gr->choice[0], TRUE);

	//枠描画
	if (ch->mode == 0) {
		DrawExtendGraph(32 * ch->x + PUZZLE_X, 32 * ch->y + PUZZLE_Y, 32 * ch->x + 64 + PUZZLE_X, 32 * ch->y + 32 + PUZZLE_Y, gr->choice[0], TRUE);
	}
	else if(ch->mode == 1) {
		DrawExtendGraph(32 * ch->x + PUZZLE_X, 32 * ch->y + PUZZLE_Y, 32 * ch->x + 32 + PUZZLE_X, 32 * ch->y + 32 + PUZZLE_Y, gr->choice[0], TRUE);
	}
	DrawExtendGraph(PUZZLE_X, 32 * ch->set_y + PUZZLE_Y, 32*8 + PUZZLE_X, 32 * ch->set_y + 32 + PUZZLE_Y, gr->choice[1], TRUE);


	//敵配置
	DrawGraph(370, 40, gr->m_boss[0], TRUE);
	//敵HP

	//hpバーの表示
	DrawGraph(370, 160, gr->hp_bar[0], TRUE);
	DrawRectGraph(370, 160, 0, 0, 7 + 114 * (en->hp * 100 / en->maxhp) / 100, 32, gr->hp_bar[1], TRUE, FALSE);
	//hp表示
	SetFontSize(12);
	DrawFormatString(410 - 1, 160 - 1, mes_color, "%d/%d", en->hp, en->maxhp);//影
	DrawFormatString(410 + 1, 160 + 1, mes_color, "%d/%d", en->hp, en->maxhp);//影
	DrawFormatString(410    , 160    , hp_color, "%d/%d", en->hp, en->maxhp);//

	//ハート
	for (i = 0; i < 5; i++) {
		DrawGraph(370 + 24 * i, 200, gr->heart, TRUE);
	}

	//スキルウィンドウ
	// 画面を白で塗りつぶす
	DrawBox(310, 240, 600, 440, GetColor(255, 255, 255), FALSE);
	DrawBox(310 + 4, 240 + 4, 600 + 4, 440 + 4, GetColor(255, 255, 255), FALSE);
	DrawBox(310 + 6, 240 + 6, 600 - 2, 440 - 2, GetColor(200, 200, 245), TRUE);
	
	//スキルお品書き(後々所持スキルを表示するようにする)
	SetFontSize(20);
	ChangeFont("ＭＳゴシック");

	for (i = 0; i < 6; i++) {
		for (j = 0; j < sk[i].number; j++) {

			//スキル発動用の玉の色をgeneより抽出
			pick_id = Pick_Number(sk[i].gene, sk[i].number - j);
			color = Translate_Color(pick_id);

			DrawExtendGraph(320 + 20 * j, 250 + 20 * i, 320 + 20 * j + 20,250 + 20 * i + 20, gr->jewel[color], TRUE);
		}
		DrawFormatString(320 + 20 * j + 1, 250 + 20 * i + 1, shd_color, "%dダメージ", sk[i].base_damage);//影
		DrawFormatString(320 + 20 * j    , 250 + 20 * i    , mes_color, "%dダメージ", sk[i].base_damage);//
	}
	//DrawExtendGraph(360, 240, 600, 440, gr->skill_window[0], TRUE);


	//玉消去時の破裂描画
	for (i = 0; i < BURST; i++) {
		if (ch->burst_timer[i] > 0) {
			//長いので変数化。8は中心から描画するためにずらしている座標。
			base_x = 32 * ch->burst_x[i] + PUZZLE_X + 8;
			base_y = 32 * ch->burst_y[i] + PUZZLE_Y + 8;

			move_x_a = (30 - ch->burst_timer[i]) * 3;
			move_x_b = (30 - ch->burst_timer[i]) * 2;
			move_y_a = (24 - ch->burst_timer[i]) *(24 - ch->burst_timer[i])/2;
			move_y_b = (26 - ch->burst_timer[i]) *(26 - ch->burst_timer[i])/2;
			
			//破裂4方向

			//右上
			DrawExtendGraph(base_x + move_x_a, base_y + move_y_a,
							base_x + move_x_a + 32, base_y + move_y_a + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);
			//右下
			DrawExtendGraph(base_x + move_x_b, base_y + move_y_b,
							base_x + move_x_b + 32, base_y + move_y_b + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);

			//右上
			DrawExtendGraph(base_x - move_x_a, base_y + move_y_a,
							base_x - move_x_a + 32, base_y + move_y_a + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);
			//右下
			DrawExtendGraph(base_x - move_x_b, base_y + move_y_b,
							base_x - move_x_b + 32, base_y + move_y_b + 32,
							gr->jewel[ch->burst_color[i] - 3], TRUE);

			ch->burst_timer[i]--;
		}
	}
	

	if (draw_counter != 65535)draw_counter++;	//１周毎にカウント
	else draw_counter = 0;
}

