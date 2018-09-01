#include "DxLib.h"
#include "Header.h"
#include <math.h>

int Key[256];//キー
unsigned int counter = 0;//カウンター
int main_state = 0;//メインステート変数

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メイン構造体
	ch_t ch;
	//画像描画構造体
	graph_t gr;
	//敵データ構造体
	enemy_t en;
	//敵データマスタ構造体
	enemy_t em[20];
	//スキルデータ構造体
	skill_t sk[50];

	//ウィンドウ化と初期化処理
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1;

	Load_Graph(&gr);
	Load_Skill(sk);
	Init(&ch,&en);

	while (!ProcessMessage() && !ClearDrawScreen()
		&& !GetHitKeyStateAll_2(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//ﾒｯｾｰｼﾞ処理  画面をｸﾘｱ  ｷｰﾎﾞｰﾄﾞ入力状態取得  ESCが押されると終了

		
		switch(main_state) {
			case 0:
				Controller(&ch);
				break;
			case 1:
				Move_Only_Controller(&ch);
				Apply_Rule(&ch, &gr);
				break;
			case 2:
				//戦闘
				Battle(&ch, &en,sk);
				break;
		}
		Draw_Graph(&ch,&gr,&en,sk);


		if (Key[KEY_INPUT_X] == 1) {
			Init(&ch, &en);

		}

		if (counter != 65535)counter++;	//１周毎にカウント
		else counter = 0;
		ScreenFlip();//裏画面を表画面に反映
		wait_fanc();//約６０フレームに調整
	}



	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void Init(ch_t *ch,enemy_t *en) {
	int i, j;
	int keep[2];

	ch->x = 0;
	ch->y = 0;

	ch->set_y = 6;

	ch->color_num = 5;

	//モード初期化
	ch->mode = 0;

	//変数初期化
	ch->rule_state = 0;
	ch->battle_state = 0;

	//後々ちゃんと入れる
	//敵のステータス
	en->maxhp = 100;
	en->hp = 100;

	//破裂初期化
	ch->burst_id = 0;
	ch->burst_current = 0;
	for (i = 0; i < 100; i++) {
		ch->burst_manage[i] = 0;
	}

	//パズル初期化
	for (i = 0; i < 8; i++) {
		for (j = 0; j < PUZ_MAX_COL; j++) {
			ch->map[i][j] = GetRand(ch->color_num - 1)+1;
			ch->fall[i][j] = 0;
		}
	}
	//縦方向3連探索
	for (i = 0; i < PUZ_COL; i++) {
		for (j = 2; j < PUZ_ROW; j++) {
			keep[0] = ch->map[i][j + PUZ_COL - 2];
			keep[1] = ch->map[i][j + PUZ_COL - 1];
			//縦方向3連同色なら最後の色を変える
			if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
				//色変更
				if (ch->map[i][j + PUZ_COL] != ch->color_num) {
					ch->map[i][j + PUZ_COL]++;
				}
				else {
					ch->map[i][j + PUZ_COL]=1;
				}
				//最終チェック
				Final_Check(ch, i, j);
			}
		}
	}
	
	//横方向3連探索
	for (j = 0; j < PUZ_ROW; j++) {
		for (i = 2; i < PUZ_COL; i++) {
			keep[0] = ch->map[i - 2][j + PUZ_COL];
			keep[1] = ch->map[i - 1][j + PUZ_COL];
			//横方向3連同色なら最後の色を変える
			if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
				//色変更
				if (ch->map[i][j + PUZ_COL] != ch->color_num) {
					ch->map[i][j + PUZ_COL]++;
				}
				else {
					ch->map[i][j + PUZ_COL] = 1;
				}
				//最終チェック
				Final_Check(ch,i,j);
			}
		}
	}
	
}

//初期配置で3連続にならないようにするための最終調整
//色が5種類あり、詰みの配置はない前提
//呼び出す位置的に左方向には揃っていないことが保証されている
void Final_Check(ch_t *ch,int x,int y) {
	int keep[2];

	//右側にあと2つは玉が配置可能なら
	if (x + 2 < PUZ_ROW) {
		keep[0] = ch->map[x + 1][y + PUZ_COL];
		keep[1] = ch->map[x + 2][y + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//色変更
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
			//再帰最終チェック
			Final_Check(ch, x, y);
		}
	}
	//上側にあと2つは玉が配置可能なら
	if (y - 2 > 0) {
		keep[0] = ch->map[x][y - 2 + PUZ_COL];
		keep[1] = ch->map[x][y - 1 + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//色変更
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
		}
	}
	//上側と下側に１つずつ玉が配置可能なら
	if (y - 1 > 0 && y + 1 < PUZ_COL) {
		keep[0] = ch->map[x][y - 1 + PUZ_COL];
		keep[1] = ch->map[x][y + 1 + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//色変更
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
			//再帰最終チェック
			Final_Check(ch, x, y);
		}
	}
	//下側にあと2つは玉が配置可能なら
	if (y + 2 < PUZ_COL) {
		keep[0] = ch->map[x][y + 2 + PUZ_COL];
		keep[1] = ch->map[x][y + 1 + PUZ_COL];

		if (keep[0] == keep[1] && keep[1] == ch->map[x][y + PUZ_COL]) {
			//色変更
			if (ch->map[x][y + PUZ_COL] != ch->color_num) {
				ch->map[x][y + PUZ_COL]++;
			}
			else {
				ch->map[x][y + PUZ_COL] = 1;
			}
			//再帰最終チェック
			Final_Check(ch, x, y);
		}
	}


}

/*
20180901 スキル判定作成。思ったより簡単だった。
20180827 まだ攻撃用のスキル判定は作っていないが、テストプレイで枠内に任意の列を作ろうとしてみたら、思いのほか難しいことが発覚。（意図せず消えるため）
　　　　 試しにVキーで固定化(?)させる操作を追加。これで誤爆しそうなところを事前に固定したりするという案。
	 　　応急処置的な感じで実装簡単そうだから作ったが、これ前提ならば独自性が生み出せそうな気がするので結構面白いかも。
20180826 スキル画面にスキルを表示。
20180823 スキル表示用のウィンドウを仮作成。パズル背景を仮置き。 
20180822 Cキーで攻撃枠の玉を消すように。Cキーでの実行は仮。
20180820 玉の消去時に破裂アニメーションを追加。ちょっとした賑やかし。
20180819 お盆の間一週間触れず。落下アニメーション追加、連鎖・落下との兼ね合いを調整し基本パズル部分はいったん完成。
　　　　 githubにあげてみる。消えた時の破裂アニメーション欲しいので少し作り始める。
20180808 消去対象を点滅してから消えるように。まだ連鎖的なところは入れていないので多少矛盾はあるものの見栄えが少しそれらしく。
20180807 重力を仮実装。アニメーションも考えたら物質に対して落下性質があるととらえるべきな気がするが、実装の簡便さを重視して一旦空白を見つけて
　　　　 上を見上げてそれと交換という形式にしている。
20180806 前日のバグは、縦方向の3連調整後にもFinal_Check()関数を噛ませないと横3連で何も起こらない場合に修正されるタイミングがないことによるもの。
　　　　 修正完了。と思ったがまだ発生。縦3連の真ん中を横3連防止によって止めた場合をケアしていなかったためと推測。中間パターンも追加。
	 　　とりあえず大丈夫そう。色変更のPUZ_COLは8と16-8の意味合いが混在している。注意。
	   　ごくまれにまだ消える。横3連の修正で↓の3連になった場合の変更で↑の3連が新たにできる場合が対象？最終チェックを再帰にしたのでこれでどう？
		 XキーでInit()呼びました。
20180805 枠、敵、ハートなど外装を少しにぎやかに。初期配置で3連が発生しないように調整用のルーチンを作成。何回か回して稀に3連が発生するのでバグあり。
20180803 玉3つで消えるように
20180802 飲み会モチベで開発開始。8*8のパズル画面、玉入れ替え実装

*/
