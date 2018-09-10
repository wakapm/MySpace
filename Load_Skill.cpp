#include "DxLib.h"
#include "Header.h"
LPCSTR font_path;//�t�H���g

void Load_Skill(skill_t sk[]) {

	//�t�@�C���œǂݍ��݂Ƃ���\��
	sk[0].number = 2;
	sk[0].gene = 33;//
	sk[0].base_damage = 1;

	sk[1].number = 2;
	sk[1].gene = 11;//�ԐԂ��Ӗ�����
	sk[1].base_damage = 2;

	sk[2].number = 3;
	sk[2].gene = 232;//�����Ӗ�����
	sk[2].base_damage = 12;

	sk[3].number = 3;
	sk[3].gene = 351;//������
	sk[3].base_damage = 10;

	sk[4].number = 5;
	sk[4].gene = 44344;//�ΗΉ��Η�
	sk[4].base_damage = 30;

	sk[5].number = 8;
	sk[5].gene = 45454545;//�Ύ��Ύ��Ύ��Ύ�
	sk[5].base_damage = 100;

}

//�t�H���g�̃��[�h
void Load_Font() {
	// ********** �t�H���g�̃��[�h **********
	font_path = "font/toroman.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
								  //font_path = "font/PixelMplus12-Regular.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
}