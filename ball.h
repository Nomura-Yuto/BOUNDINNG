//=================================================================
// [ball.h]
// �{�[������w�b�_
// ����ҁF�쑺 �I�l	�X�V���F2023/08/29
//=================================================================
#pragma once		// �C���N���[�h�K�[�h


//=================================================================
// �\���̐錾
//=================================================================
typedef struct {
	Float2 pos;		// ���W
	Float2 oldPos;	// 1F�O�̍��W
	Float2 size;	// �T�C�Y
	Float2 vel;		// ���x
	int health;
	float gravity;
}BALL;

// �|���S����4�ӂ̈ʒu
typedef struct {
	float top;		// ���
	float botom;	// ����
	float left;		// ����
	float right;	// �E��
}BOX;

//=================================================================
// �v���g�^�C�v�錾
//=================================================================
void InitBall();
void UninitBall();
void UpdateBall();
void DrawBall();
void DownHealth(void);
void AddHealth(int value);
BALL* GetBall(void);
