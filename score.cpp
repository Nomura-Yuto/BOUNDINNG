//=================================================================
// [score.cpp]
// �X�R�A�A�j���[�V��������
// ����ҁF�쑺 �I�l	�X�V���F2023/08/29
//=================================================================
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "ball.h"
#include "player.h"

void DrawHealth(int health, Float2 healthPos, Float2 size);

//=================================================================
// �}�N����`
//=================================================================
#define PARTITION_PATTERN_X (5)	// �e�N�X�`���̕�����(��)
#define PARTITION_PATTERN_Y (5)	// �e�N�X�`���̕�����(�c)
#define PATTERN_WIDTH	(1.0f / PARTITION_PATTERN_X) // �\���e�N�X�`���̉���
#define PATTERN_HEIGHT	(1.0f / PARTITION_PATTERN_Y) // �\���e�N�X�`���̏c��

#define HEART_NUM	(10)	// �e�N�X�`��(�n�[�g)�̕\���ԍ�
#define BONE_NUM	(11)	// �e�N�X�`��(��)�̕\���ԍ�
#define CLOCK_NUM	(12)	// �e�N�X�`��(���v)�̕\���ԍ�


//=================================================================
// �O���[�o���ϐ�
//=================================================================
unsigned int	g_ScoreTexture;	// �e�N�X�`��ID
SCORE			g_Score;		// ����

//=================================================================
// �X�R�A����������
//=================================================================
void InitScore()
{

	g_ScoreTexture = LoadTexture("rom:/number.tga");

	g_Score.pos = MakeFloat2(1500.0f , 260.0f);
	g_Score.size = MakeFloat2(DISP_NUM_SIZE, DISP_NUM_SIZE);

	
	g_Score.point = 0;
}


//=================================================================
// �X�R�A�I������
//=================================================================
void UninitScore()
{

	UnloadTexture(g_ScoreTexture);

}


//=================================================================
// �X�R�A�A�b�v�f�[�g����
//=================================================================
void UpdateScore()
{

}


//=================================================================
// �X�R�A�`�揈��
//=================================================================
void DrawScore()
{
	TIME* p_Time = GetTime();
	BALL* p_Ball = GetBall();

	// �X�R�A�\��
	DrawNum(g_Score.point, g_Score.pos, g_Score.size, SCORE_DISIT);

	// �̗͕\��
	DrawHealth(p_Ball->health, MakeFloat2(1584.0f, 540.0f),g_Score.size);
}

//=================================================================
// �X�R�A�����֐�
//=================================================================
void AddScore(int value) 
{
	g_Score.point += value;

	// �I�[�o�[�t���[�΍�
	if (g_Score.point >= 1000000)
	{
		g_Score.point = 999999;
	}
}

//=================================================================
// �X�R�A�擾
//=================================================================
int GetScorePoint(void) 
{
	return g_Score.point;
}

//=================================================================
// �i���o�[�`�揈��
//=================================================================
void DrawNum(int num, Float2 numPos, Float2 size, int numDisit)
{
	int editNum;		 // �ҏW�p�ԍ�
	Float2 editPos; // �ҏW�p�\�����ʒu
	editNum = num;
	editPos = numPos;
	
	for (int i = 0; i < numDisit; i++) {
		int num;		// �ꌅ�ۑ��p
		num = editNum % 10;
		editNum /= 10;

		editPos.x = numPos.x + size.x *(numDisit - i);

		DrawSprite(g_ScoreTexture, editPos.x, editPos.y,
			size.x, size.y,
			(num % PARTITION_PATTERN_X) * (1.0f / PARTITION_PATTERN_X),
			(num / PARTITION_PATTERN_X) * (1.0f / PARTITION_PATTERN_Y),
			PATTERN_WIDTH, PATTERN_HEIGHT);
	}
}

//=================================================================
// �̗͕`�揈��
//=================================================================
void DrawHealth(int health, Float2 healthPos, Float2 size)
{
	for (int i = 0; i < health; i++)
	{
		DrawSpriteColor(g_ScoreTexture, healthPos.x + size.x * (i % 5), healthPos.y + size.y * (i / 5),
			size.x, size.y,
			(HEART_NUM % PARTITION_PATTERN_X) * (1.0f / PARTITION_PATTERN_X),
			(HEART_NUM / PARTITION_PATTERN_X) * (1.0f / PARTITION_PATTERN_Y),
			PATTERN_WIDTH, PATTERN_HEIGHT,
			1.0f, 0.0f, 0.0f, 1.0f);
	}
}



