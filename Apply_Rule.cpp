#include "DxLib.h"
#include "Header.h"

extern int main_state;

//���[���K�p
//�d�͂Ə����E�A��
void Apply_Rule(ch_t *ch, graph_t *gr) {

	int i,j,overhead;
	int keep[2];//�Ώۂ̑O�̐F
	static unsigned int rule_counter=0;
	static int reserve_flag = 0;
	static int fall_flag = 0;


	//�����E�A��
	//ch->map[x][y]
	//    1 2 3 
	//   _______
	//  1|
	//  2|
	//  3|

	switch(ch->rule_state){
	
		//�A���T��
		case 0:
			//�c����3�A�T��
			for (i = 0; i < PUZ_COL; i++) {
				for (j = 2; j < PUZ_ROW; j++) {
					//�󔒂͏��O
					if (ch->map[i][j + PUZ_COL] != 0) {
						keep[0] = ch->map[i][j + PUZ_COL - 2];
						keep[1] = ch->map[i][j + PUZ_COL - 1];
						//������3�A���F�Ȃ�
						if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
							//reserve�ɏ����t���O(1)����
							ch->reserve[i][j - 2] = 1;
							ch->reserve[i][j - 1] = 1;
							ch->reserve[i][j] = 1;

							//�����_�ł�����t���O
							reserve_flag = 1;
						}
					}
					
				}
			}

			//������3�A�T��
			for (j = 0; j < PUZ_ROW; j++) {
				for (i = 2; i < PUZ_COL; i++) {
					if (ch->map[i][j + PUZ_COL] != 0) {
						keep[0] = ch->map[i - 2][j + PUZ_COL];
						keep[1] = ch->map[i - 1][j + PUZ_COL];
						//�c����3�A���F�Ȃ�
						if (keep[0] == keep[1] && keep[1] == ch->map[i][j + PUZ_COL]) {
							//reserve�ɏ����t���O(1)����
							ch->reserve[i - 2][j] = 1;
							ch->reserve[i - 1][j] = 1;
							ch->reserve[i][j] = 1;

							//�����_�ł�����t���O
							reserve_flag = 1;
						}
					}
				}
			}
			//�������ʂ�����Ώ����X�e�[�g�ֈڍs
			if (reserve_flag == 1) {
				ch->rule_state++;
				reserve_flag = 0;
			}else{
				//�������̂Ȃ���Ώd��
				ch->rule_state = 3;
			}

			rule_counter = 0;
			break;
		case 1:

			//�_�ŗp���ԑ҂�
			rule_counter++;
			//30�t���[���o�߂ŃX�e�[�g�A�b�v
			if (rule_counter >= 40) {
				ch->rule_state++;
			}
			break;
		case 2:
			//����
			for (i = 0; i < PUZ_ROW; i++) {
				for (j = 0; j < PUZ_COL; j++) {
					//�����t���O�𗧂Ă��}�X�͏���
					if (ch->reserve[i][j] == 1) {
						//�A�N�e�B�uPUZZLE��8~15
						ch->map[i][j + PUZ_COL] = 0;
						//������
						ch->reserve[i][j] = 0;
					}
				}
			}

			ch->rule_state++;
			break;
		case 3:
			//***************�d��*****************
			for (i = 0; i < PUZ_ROW; i++) {
				//�����烋�[�v
				for (j = PUZ_MAX_COL - 1; j >= 1; j--) {
					if (ch->map[i][j] == 0) {
						//����ɋ󔒂łȂ��}�X���ǂ��ɂ��邩�T��
						overhead = Gravity_Search(ch, i, j - 1);
						
						//������������Ȃ�
						if (overhead != -1) {
							//����
							ch->map[i][j] = ch->map[i][overhead];
							//�����������Z�o(�\���̊֌W��32�{)
							ch->fall[i][j] = 32 * (j - overhead);
							//�Ȃ��Ȃ����Ƃ����0
							ch->map[i][overhead] = 0;
							fall_flag++;
						}

					}
				}
			}

			if (fall_flag == 0) {
				//�������Ȃ������瑀��\
				ch->rule_state = 0;
				main_state = 0;
			}
			else {
				//�����������`�F�b�N�̂��߁A�t���O������
				fall_flag = 0;
				ch->rule_state++;
			}
			
			break;

		case 4:
			//***************�d�͕`��**************

			for (i = 0; i < PUZ_ROW; i++) {
				//�����烋�[�v
				for (j = PUZ_MAX_COL - 1; j >= 1; j--) {
					//�����������c���Ă������
					if (ch->fall[i][j] > 0) {
						//16��������
						ch->fall[i][j] -= 16;

						//�t���O���Ă�
						fall_flag++;
					}
				}
			}

			if (fall_flag == 0) {
				//�������Ȃ������瑀��\
				ch->rule_state = 0;
			}
			else {
				//�����`�F�b�N�̂��߃t���O������
				fall_flag = 0;
			}

			break;
	}








}

//������ċ󔒂łȂ�y��Ԃ�
int Gravity_Search(ch_t *ch,int x,int y) {
	int answer;

	//�z��O�͍���̂�y-1>=0
	if (ch->map[x][y] == 0 && y - 1 >= 0) {
		answer = Gravity_Search(ch, x, y - 1);
	}else if (ch->map[x][y] == 0) {

		//��ɉ����Ȃ�
		answer = -1;

	}else{
		//�󔒂łȂ�y��Ԃ�
		answer = y;
	}
	return answer;
}
