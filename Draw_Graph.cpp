#include "DxLib.h"
#include "Header.h"

void Draw_Graph(ch_t *ch, graph_t *gr,enemy_t *en) {

	int i,j;
	int color;

	static unsigned int draw_counter = 0;

	// 画面を白で塗りつぶす
	DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), TRUE);
	//背景描画
	DrawGraph(0, 0, gr->scape[0], TRUE);

	//玉描画
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {

			//色変換
			switch(ch->map[j][i+8]) {
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
			//消去は描画なし
			if (ch->map[j][i + PUZ_COL] != 0) {
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
	DrawExtendGraph(32 * ch->x + PUZZLE_X, 32 * ch->y + PUZZLE_Y, 32 * ch->x + 64 + PUZZLE_X, 32 * ch->y + 32 + PUZZLE_Y, gr->choice[0], TRUE);
	DrawExtendGraph(PUZZLE_X, 32 * ch->set_y + PUZZLE_Y, 32*8 + PUZZLE_X, 32 * ch->set_y + 32 + PUZZLE_Y, gr->choice[1], TRUE);


	//敵配置
	DrawGraph(370, 40, gr->m_boss[0], TRUE);
	//敵HP

	//hpバーの表示
	DrawGraph(370, 160, gr->hp_bar[0], TRUE);
	DrawRectGraph(370, 160, 0, 0, 7 + 114 * (en->hp * 100 / en->maxhp) / 100, 32, gr->hp_bar[1], TRUE, FALSE);

	//ハート
	for (i = 0; i < 5; i++) {
		DrawGraph(370 + 24 * i, 200, gr->heart, TRUE);
	}

	if (draw_counter != 65535)draw_counter++;	//１周毎にカウント
	else draw_counter = 0;
}