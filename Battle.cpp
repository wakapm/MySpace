#include "DxLib.h"
#include "Header.h"

extern int Key[256];//�L�[
extern int main_state;

void Battle(ch_t *ch, enemy_t *en, skill_t sk[]) {

	int i,j,k;
	int chk_num;

	switch (ch->battle_state) {

	case 0:

		//�U���g�̍����烋�[�v
		for (i = 0; i < PUZ_ROW; i++) {

			//�莝���X�L���̃��[�v
			for (j = 0; j < 6; j++) {

				//�͂ݏo��ꍇ�͒T�����Ȃ�
				if (i + sk[j].number > PUZ_ROW) {
					continue;
				}
				//�X�L���Ƃ̍��v���`�F�b�N
				for (k = 0; k < sk[j].number; k++) {

					//gene���琔���̔����o��(������(��)����T��)
					chk_num = Pick_Number(sk[j].gene, sk[j].number - k);

					//�F����v������
					if (chk_num == ch->map[i+k][ch->set_y + PUZ_COL]) {
						//gene�Ō�̐��Ȃ�X�L������
						if (k == sk[j].number - 1) {
							en->hp -= sk[j].base_damage;
						}
						//�Ō�̐��łȂ��Ȃ�T�����s
					}
					else {
						//�Ⴆ�΂��̃X�L���̒T���͒��f
						break;
					}
				}
			}
		
		}

		main_state = 1;
		break;

	}

}

