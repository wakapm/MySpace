#include "DxLib.h"
#include "Header.h"

extern int main_state;

//ルール適用
//重力と消去・連鎖
void Apply_Rule(ch_t *ch, graph_t *gr) {

	int i,j,overhead;
	int keep[2];//対象の前の色
	static unsigned int rule_counter=0;
	static int reserve_flag = 0;
	static int fall_flag = 0;


	//消去・連鎖
	//ch->map[x][y]
	//    1 2 3 
	//   _______
	//  1|
	//  2|
	//  3|

	switch(ch->rule_state){
	
		//連鎖探索
		case 0:
			//縦方向3連探索
			for (i = 0; i < PUZ_COL; i++) {
				for (j = 2; j < PUZ_ROW; j++) {
					//空白は除外
					if (ch->map[i][j + PUZ_COL] != 0) {
						keep[0] = ch->map[i][j + PUZ_COL - 2];
						keep[1] = ch->map[i][j + PUZ_COL - 1];
						//横方向3連同色なら
						if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
							//reserveに消去フラグ(1)を代入
							ch->reserve[i][j - 2] = 1;
							ch->reserve[i][j - 1] = 1;
							ch->reserve[i][j] = 1;

							//消去点滅させるフラグ
							reserve_flag = 1;
						}
					}
					
				}
			}

			//横方向3連探索
			for (j = 0; j < PUZ_ROW; j++) {
				for (i = 2; i < PUZ_COL; i++) {
					if (ch->map[i][j + PUZ_COL] != 0) {
						keep[0] = ch->map[i - 2][j + PUZ_COL];
						keep[1] = ch->map[i - 1][j + PUZ_COL];
						//縦方向3連同色なら
						if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
							//reserveに消去フラグ(1)を代入
							ch->reserve[i - 2][j] = 1;
							ch->reserve[i - 1][j] = 1;
							ch->reserve[i][j] = 1;

							//消去点滅させるフラグ
							reserve_flag = 1;
						}
					}
				}
			}
			//消した玉があれば消去ステートへ移行
			if (reserve_flag == 1) {
				ch->rule_state++;
				reserve_flag = 0;
			}else{
				//消すものなければ重力
				ch->rule_state = 3;
			}

			rule_counter = 0;
			break;
		case 1:

			//点滅用時間待ち
			rule_counter++;
			//30フレーム経過でステートアップ
			if (rule_counter >= 40) {
				ch->rule_state++;
			}
			break;
		case 2:
			//消去
			for (i = 0; i < PUZ_ROW; i++) {
				for (j = 0; j < PUZ_COL; j++) {
					//消去フラグを立てたマスは消去
					if (ch->reserve[i][j] == 1) {
						//アクティブPUZZLEは8~15
						ch->map[i][j + PUZ_COL] = 0;
						//初期化
						ch->reserve[i][j] = 0;
					}
				}
			}

			ch->rule_state++;
			break;
		case 3:
			//***************重力*****************
			for (i = 0; i < PUZ_ROW; i++) {
				//下からループ
				for (j = PUZ_MAX_COL - 1; j >= 1; j--) {
					if (ch->map[i][j] == 0) {
						//頭上に空白でないマスがどこにあるか探索
						overhead = Gravity_Search(ch, i, j - 1);
						
						//落下物があるなら
						if (overhead != -1) {
							//落下
							ch->map[i][j] = ch->map[i][overhead];
							//落下距離を算出(表示の関係で32倍)
							ch->fall[i][j] = 32 * (j - overhead);
							//なくなったところは0
							ch->map[i][overhead] = 0;
							fall_flag++;
						}

					}
				}
			}

			if (fall_flag == 0) {
				//落下物なかったら操作可能
				ch->rule_state = 0;
				main_state = 0;
			}
			else {
				//もう一回消去チェックのため、フラグ初期化
				fall_flag = 0;
				ch->rule_state++;
			}
			
			break;

		case 4:
			//***************重力描画**************

			for (i = 0; i < PUZ_ROW; i++) {
				//下からループ
				for (j = PUZ_MAX_COL - 1; j >= 1; j--) {
					//落下距離が残っているもの
					if (ch->fall[i][j] > 0) {
						//16だけ落下
						ch->fall[i][j] -= 16;

						//フラグ立てる
						fall_flag++;
					}
				}
			}

			if (fall_flag == 0) {
				//落下物なかったら操作可能
				ch->rule_state = 0;
			}
			else {
				//落下チェックのためフラグ初期化
				fall_flag = 0;
			}

			break;
	}








}

//上を見て空白でないyを返す
int Gravity_Search(ch_t *ch,int x,int y) {
	int answer;

	//配列外は困るのでy-1>=0
	if (ch->map[x][y] == 0 && y - 1 >= 0) {
		answer = Gravity_Search(ch, x, y - 1);
	}else if (ch->map[x][y] == 0) {

		//上に何もない
		answer = -1;

	}else{
		//空白でないyを返す
		answer = y;
	}
	return answer;
}
