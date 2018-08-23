#include "DxLib.h"
#include "Header.h"

void Load_Graph(graph_t *gr) {

	LoadDivGraph("img/skillbox.png", 64, 8, 8, 24, 24, gr->skill_icon);
	LoadDivGraph("img/jewel_set.png", 200, 10, 20, 24, 24, gr->jewel);



	gr->scape[0] = LoadGraph("img/06s.jpg");
	gr->choice[0] = LoadGraph("img/swap_frame2.png");
	//gr->choice[1] = LoadGraph("img/set_frame.png");
	gr->choice[1] = LoadGraph("img/kuro1.png");

	gr->m_boss[0] = LoadGraph("img/mon_pudding.png");
	gr->heart = LoadGraph("img/sticon3g-2.png");

	gr->skill_window[0] = LoadGraph("img/Tips_waku.png");

	// “§‰ßF‚ð•ÏX
	SetTransColor(255, 255, 255);

	gr->hp_bar[0] = LoadGraph("img/nframe128_32.png");
	gr->hp_bar[1] = LoadGraph("img/ngage128_32.png");

}