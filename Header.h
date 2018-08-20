/* proto.h */

#ifndef _HEADER_H_
#define _HEADER_H_


//円周率
#define PI	3.1415926535897932384626433832795f

#define PUZZLE_X 32
#define PUZZLE_Y 80

#define PUZ_ROW 8
#define PUZ_COL 8
#define PUZ_MAX_COL 16

#define BURST 100

//敵キャラ種類合計
#define ENEMY 20

typedef struct {
	int x, y, img, muki, walking_flag, gold, get_gold;
	int skill_point;
	int set_x, set_y;
	int active_player;//ch[0]のみ機能

	//HP:TP:Attack:Defence:Speed:Technique:Skill:所持スキルポイント仮
	int maxhp, hp, maxtp, tp;

	//装備中の剣番号
	int equip;
	char name[20];
	//レベル毎に必要な経験値
	int exp_in_level[32];

	int skill_count;
	//最大スキルLv
	int skill_lv;
	//アクティブスキル習得数
	int act_skill_count;

	//スキルメニューのカーソル位置をこっちで持つ(グローバルだと少し邪魔？)
	int sk_x, sk_y;
	//レベルアップのメニューのカーソル位置(レベルアップ系はch[0]のみ使用)
	int sta_y;
	int point[5];

	//栄養ドリンクなどのフラグ
	int item_flag[10];
	//古代のがらくた数
	int regacy;
	//現在のステージ
	int stage;


	//パズル8*11(表示は8*8)
	int map[8][16];
	//消去予約(8*8。念のため16)
	int reserve[8][16];
	//落下距離(8*8。念のため16)
	int fall[8][16];
	//破裂アニメーション用配列
	int burst_x[BURST],burst_y[BURST];

	//破裂数カウンタ
	int burst_current;
	//破裂数ID
	int burst_id;
	//破裂管理配列(burst_manage[カウンタ]=ID)
	int burst_manage[BURST];
	//破裂アニメーションタイムカウンタ
	int burst_timer[BURST];
	//破裂色
	int burst_color[BURST];

	//色種類
	int color_num;

	//ルール用のステート変数
	int rule_state;

}ch_t;

//画像用構造体
typedef struct {
	int image[2][16], img_map[50], img_map2[100];
	int hp_bar[3];
	int roll[6];
	int choice[3];
	int item_window;
	int stat_window[2];
	int skill_window[2];
	int tips_window;

	int sta_item[7];
	int mini_enemy[140];//マップ上に表示する敵キャラアイコン
	int m_boss[20];//20は適当
	int scape[14];
	int logo[2];
	int ex_icon[1];
	int skill_icon[100];
	int arrow[2];
	int ring;
	int background[2];
	int blend[2];
	int jewel[200];
	int icon_emo[540];
	int map_fillter[16];

	int human[5];
	int some_icon[10];

	int timer;//画像表示用タイマー

	int stand[4];//立ち絵表示用

	int hourglass[10];//戦時計用
	int status_win_image[2];//ステータス画面飾り用


	int heart;
}graph_t;

typedef struct {
	//名前
	char name[20];
	//画像
	int img;
	//HP:TP:Attack:Defence:Speed:Technique:TechDefence
	int maxhp, hp, maxtp, tp, at, de, sp, te, td;
	//1ターン強化値
	int u_at, u_de, u_sp, u_te, u_td;
	//属性耐性 火、水、風、地
	int fir, wat, win, ear;
	//獲得ゴールド,獲得経験値,獲得アイテム
	int gold, exp, item[2];

	//所持スキルとかもいるかな？
	//特殊効果とか

	//ボスの行動パターン
	int ai;
	//ボスの特殊能力
	int special;
	//所持スキル
	int skill[4];
	//行動予約カウント
	int count_down;
	//行動予約入れ物
	int reserve[10];

}enemy_t;

//プロトタイプの宣言

//【Funciton.cpp】

extern int GetHitKeyStateAll_2(int KeyStateBuf[]);
extern void wait_fanc(void);
extern int Translate_Color(ch_t *ch, int j, int i);

//【First.cpp】

extern void Init(ch_t *ch,enemy_t *en);
extern void Final_Check(ch_t *ch, int x, int y);

//【Draw_Graph.cpp】

extern void Draw_Graph(ch_t *ch, graph_t *gr,enemy_t *en);

//【Load_Graph.cpp】

extern void Load_Graph(graph_t *gr);

//【Controller.cpp】

extern void Controller(ch_t *ch);
extern void Move_Only_Controller(ch_t *ch);

//【Apply_Rule.cpp】

extern void Apply_Rule(ch_t *ch, graph_t *gr);
extern int Gravity_Search(ch_t *ch, int x, int y);
extern void Set_Burst(ch_t *ch, int x, int y);
#endif