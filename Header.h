/* proto.h */

#ifndef _HEADER_H_
#define _HEADER_H_


//�~����
#define PI	3.1415926535897932384626433832795f

#define PUZZLE_X 32
#define PUZZLE_Y 80

#define PUZ_ROW 8
#define PUZ_COL 8
#define PUZ_MAX_COL 16

#define BURST 100

//�G�L������ލ��v
#define ENEMY 20

typedef struct {
	int x, y, img, muki, walking_flag, gold, get_gold;
	int skill_point;
	int set_x, set_y;
	int active_player;//ch[0]�̂݋@�\

	//HP:TP:Attack:Defence:Speed:Technique:Skill:�����X�L���|�C���g��
	int maxhp, hp, maxtp, tp;

	//�������̌��ԍ�
	int equip;
	char name[20];
	//���x�����ɕK�v�Ȍo���l
	int exp_in_level[32];

	int skill_count;
	//�ő�X�L��Lv
	int skill_lv;
	//�A�N�e�B�u�X�L���K����
	int act_skill_count;

	//�X�L�����j���[�̃J�[�\���ʒu���������Ŏ���(�O���[�o�����Ə����ז��H)
	int sk_x, sk_y;
	//���x���A�b�v�̃��j���[�̃J�[�\���ʒu(���x���A�b�v�n��ch[0]�̂ݎg�p)
	int sta_y;
	int point[5];

	//�h�{�h�����N�Ȃǂ̃t���O
	int item_flag[10];
	//�Ñ�̂��炭����
	int regacy;
	//���݂̃X�e�[�W
	int stage;


	//�p�Y��8*11(�\����8*8)
	int map[8][16];
	//�����\��(8*8�B�O�̂���16)
	int reserve[8][16];
	//��������(8*8�B�O�̂���16)
	int fall[8][16];
	//�j��A�j���[�V�����p�z��
	int burst_x[BURST],burst_y[BURST];

	//�j�����J�E���^
	int burst_current;
	//�j����ID
	int burst_id;
	//�j��Ǘ��z��(burst_manage[�J�E���^]=ID)
	int burst_manage[BURST];
	//�j��A�j���[�V�����^�C���J�E���^
	int burst_timer[BURST];
	//�j���F
	int burst_color[BURST];

	//�F���
	int color_num;

	//���[���p�̃X�e�[�g�ϐ�
	int rule_state;

}ch_t;

//�摜�p�\����
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
	int mini_enemy[140];//�}�b�v��ɕ\������G�L�����A�C�R��
	int m_boss[20];//20�͓K��
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

	int timer;//�摜�\���p�^�C�}�[

	int stand[4];//�����G�\���p

	int hourglass[10];//�펞�v�p
	int status_win_image[2];//�X�e�[�^�X��ʏ���p


	int heart;
}graph_t;

typedef struct {
	//���O
	char name[20];
	//�摜
	int img;
	//HP:TP:Attack:Defence:Speed:Technique:TechDefence
	int maxhp, hp, maxtp, tp, at, de, sp, te, td;
	//1�^�[�������l
	int u_at, u_de, u_sp, u_te, u_td;
	//�����ϐ� �΁A���A���A�n
	int fir, wat, win, ear;
	//�l���S�[���h,�l���o���l,�l���A�C�e��
	int gold, exp, item[2];

	//�����X�L���Ƃ������邩�ȁH
	//������ʂƂ�

	//�{�X�̍s���p�^�[��
	int ai;
	//�{�X�̓���\��
	int special;
	//�����X�L��
	int skill[4];
	//�s���\��J�E���g
	int count_down;
	//�s���\����ꕨ
	int reserve[10];

}enemy_t;

//�v���g�^�C�v�̐錾

//�yFunciton.cpp�z

extern int GetHitKeyStateAll_2(int KeyStateBuf[]);
extern void wait_fanc(void);
extern int Translate_Color(ch_t *ch, int j, int i);

//�yFirst.cpp�z

extern void Init(ch_t *ch,enemy_t *en);
extern void Final_Check(ch_t *ch, int x, int y);

//�yDraw_Graph.cpp�z

extern void Draw_Graph(ch_t *ch, graph_t *gr,enemy_t *en);

//�yLoad_Graph.cpp�z

extern void Load_Graph(graph_t *gr);

//�yController.cpp�z

extern void Controller(ch_t *ch);
extern void Move_Only_Controller(ch_t *ch);

//�yApply_Rule.cpp�z

extern void Apply_Rule(ch_t *ch, graph_t *gr);
extern int Gravity_Search(ch_t *ch, int x, int y);
extern void Set_Burst(ch_t *ch, int x, int y);
#endif