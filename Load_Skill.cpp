#include "DxLib.h"
#include "Header.h"

void Load_Skill(skill_t sk[]) {

	//ファイルで読み込みとする予定
	sk[0].number = 2;
	sk[0].gene = 99;//9は全種類
	sk[0].base_damage = 1;

	sk[1].number = 2;
	sk[1].gene = 11;//赤赤を意味する
	sk[1].base_damage = 1;

	sk[2].number = 3;
	sk[2].gene = 232;//青黄青を意味する
	sk[2].base_damage = 12;

	sk[3].number = 8;
	sk[3].gene = 45454545;//緑紫緑紫緑紫緑紫
	sk[3].base_damage = 100;

}