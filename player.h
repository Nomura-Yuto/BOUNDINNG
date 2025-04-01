//=================================================================
// [player.h]
// �v���C���[����w�b�_
// ����ҁF�쑺 �I�l	�X�V���F2023/08/29
//=================================================================
#pragma once		// �C���N���[�h�K�[�h

//=================================================================
// �}�N����`
//=================================================================
#define PLAYER_WIDTH (1000.0f)	// �v���C���[����
#define PLAYER_HEIGHT (64.0f)	// �v���C���[�c��

//=================================================================
// �񋓑̐錾
//=================================================================
typedef enum { // �v���C���[�̌X��
	ANGLE_NORMAL = 0,
	ANGLE_LEFT,
	ANGLE_RIGHT,
	ANGLE_MAX
}PLAYER_ANGLE;

//=================================================================
// �\���̐錾
//=================================================================
typedef struct {
	Float2 pos;			// ���W
	Float2 size;		// �T�C�Y
	Float2 vel;			// ���x
	Float2 jumpOldPos;	// �W�����v�O�̍��W
	Float2 displayPos;	// �\���p�̍��W
	PLAYER_ANGLE angle; // �X��
	bool   jump;		// �W�����v�t���O
}PLAYER;

typedef struct {
	Float2 pos;		// ���W
	Float2 size;	// �T�C�Y
	float rot;		// �p�x
	bool use;		// �g�p�t���O
}ARROW;

//=================================================================
// �v���g�^�C�v�錾
//=================================================================
void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
void JumpPlayer(void);
void SetStartAngle(Float3 angle);
PLAYER* GetPlayer(void); 

