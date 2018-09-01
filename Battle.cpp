#include "DxLib.h"
#include "Header.h"

extern int Key[256];//キー
extern int main_state;

void Battle(ch_t *ch, enemy_t *en, skill_t sk[]) {

	int i,j,k;
	int chk_num;

	switch (ch->battle_state) {

	case 0:

		//攻撃枠の左からループ
		for (i = 0; i < PUZ_ROW; i++) {

			//手持ちスキルのループ
			for (j = 0; j < 6; j++) {

				//はみ出る場合は探索しない
				if (i + sk[j].number > PUZ_ROW) {
					continue;
				}
				//スキルとの合致をチェック
				for (k = 0; k < sk[j].number; k++) {

					//geneから数字の抜き出し(高い桁(左)から探索)
					chk_num = Pick_Number(sk[j].gene, sk[j].number - k);

					//色が一致したら
					if (chk_num == ch->map[i+k][ch->set_y + PUZ_COL]) {
						//gene最後の数ならスキル発動
						if (k == sk[j].number - 1) {
							en->hp -= sk[j].base_damage;
						}
						//最後の数でないなら探索続行
					}
					else {
						//違えばこのスキルの探索は中断
						break;
					}
				}
			}
		
		}

		main_state = 1;
		break;

	}

}

