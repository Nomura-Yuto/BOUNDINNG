//=================================================================
// [ball.cpp]
// �{�[������
// ����ҁF�쑺 �I�l	�X�V���F2023/08/29
//=================================================================
#include "main.h"
#include "sound.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "ball.h"
#include "player.h"
#include "score.h"

//=================================================================
// �}�N����`
//=================================================================
#define BALL_SIZE		(75.0f)	// �{�[���̃T�C�Y
#define BALL_GRAVITY	(2.0f)	// �{�[���̏d��
#define INIT_BALL_SPEED	(-5.0f)	// �{�[���̏������x
#define BALL_SPEED_X	(4.0f)	// �{�[���̈ړ����x(X)
#define MAX_HEALTH		(10)	// �ő�̗�

//=================================================================
// �v���g�^�C�v�錾
//=================================================================
void BallCollision(void);

//=================================================================
// �O���[�o���ϐ�
//=================================================================
unsigned int	g_BallTexture;	// �e�N�X�`��ID
BALL			g_Ball;			// ����

//=================================================================
// �{�[������������
//=================================================================
void InitBall()
{
	g_BallTexture = LoadTexture("rom:/ball.tga");
	
	g_Ball.pos = MakeFloat2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
	g_Ball.oldPos = g_Ball.pos;
	g_Ball.size = MakeFloat2(BALL_SIZE, BALL_SIZE);
	g_Ball.vel = MakeFloat2(0.0f, INIT_BALL_SPEED);
	g_Ball.health = MAX_HEALTH;
	g_Ball.gravity = BALL_GRAVITY;
}

//=================================================================
// �{�[���I������
//=================================================================
void UninitBall()
{

	UnloadTexture(g_BallTexture);

}

//=================================================================
// �{�[���A�b�v�f�[�g����
//=================================================================
void UpdateBall()
{
	g_Ball.oldPos = g_Ball.pos;

	g_Ball.vel.y += g_Ball.gravity;
	
	// �ړ�
	g_Ball.pos.x += g_Ball.vel.x;
	g_Ball.pos.y += g_Ball.vel.y;
		
	// ���ǔ���
	if (g_Ball.pos.x <= 460.0f + g_Ball.size.x / 2)
	{
		g_Ball.vel.x *= -1.0f;
		g_Ball.pos.x = 460.0f + g_Ball.size.x / 2;

	}

	// �E�ǔ���
	if (g_Ball.pos.x >= 1460.0f - g_Ball.size.x / 2) 
	{
		g_Ball.vel.x *= -1.0f;
		g_Ball.pos.x = 1460.0f - g_Ball.size.x / 2;

	}

	// ��ǔ���
	if (g_Ball.pos.y < 40.0f + g_Ball.size.y / 2)
		g_Ball.vel.y *= -1.0f;

	// ���ǔ���
	if (g_Ball.pos.y > (float)SCREEN_HEIGHT - g_Ball.size.y / 2)
		g_Ball.vel.y *= -1.0f;

	// �����蔻��
	BallCollision();
}


//=================================================================
// �{�[���`�揈��
//=================================================================
void DrawBall()
{

	DrawSprite(g_BallTexture, g_Ball.pos.x, g_Ball.pos.y, g_Ball.size.x, g_Ball.size.y,
						0.0f, 0.0f, 1.0f, 1.0f);


}

//=================================================================
// ����(�{�[��)�̃A�h���X�擾�p�֐�(�Q�b�^�[)
//=================================================================
BALL* GetBall(void) 
{
	return &g_Ball;
}

//=================================================================
// �̗͌���
//=================================================================
void DownHealth(void)
{
	g_Ball.health--;
}

//=================================================================
// �̗͑���
//=================================================================
void AddHealth(int value)
{
	g_Ball.health += value;
}

//=================================================================
// �{�[���ƃv���C���[�̓����蔻�菈��
//=================================================================
void BallCollision(void) 
{
	PLAYER	*p_Player;
	p_Player = GetPlayer();
	bool hitX = false;
	bool hitY = false;
	bool bound = false;
	
	BOX Player = {
		p_Player->pos.y - p_Player->size.y / 2, // ���
		p_Player->pos.y + p_Player->size.y / 2, // ����
		p_Player->pos.x - p_Player->size.x / 2, // ����
		p_Player->pos.x + p_Player->size.x / 2, // �E��
	};

	BOX Ball{
		g_Ball.pos.y - g_Ball.size.y / 2, // ���
		g_Ball.pos.y + g_Ball.size.y / 2, // ����
		g_Ball.pos.x - g_Ball.size.x / 2, // ����
		g_Ball.pos.x + g_Ball.size.x / 2, // �E��
	};

	BOX OldBall{
		g_Ball.oldPos.y - g_Ball.size.y / 2, // ���
		g_Ball.oldPos.y + g_Ball.size.y / 2, // ����
		g_Ball.oldPos.x - g_Ball.size.x / 2, // ����
		g_Ball.oldPos.x + g_Ball.size.x / 2, // �E��
	};

	// �\�����W�Ƃ̓����蔻��
	if (p_Player->displayPos.y - p_Player->size.y / 2 >= OldBall.botom &&
		p_Player->displayPos.y - p_Player->size.y / 2 <= Ball.botom)
	{
		g_Ball.pos.y = p_Player->displayPos.y - p_Player->size.y / 2 - g_Ball.size.y / 2;
		hitY = true;
	}

	if (p_Player->jump)
	{
		// �^�C�~���O�悭�U�������̔���
		if (Ball.botom >= p_Player->displayPos.y - p_Player->size.y / 2 &&
			Ball.botom <= p_Player->pos.y)
		{
			bound = true;
		}
	}

	// �����蔻��
	if (Ball.right	> Player.left  &&
		Ball.left	< Player.right &&
		Ball.botom	> Player.top   &&
		Ball.top	< Player.botom)
	{
		// �㔻��
		if (Player.top >= OldBall.botom &&
			Player.top <= Ball.botom)
		{
			g_Ball.pos.y = Player.top - g_Ball.size.y / 2;
			hitY = true;
		}

		// ������
		if (Player.botom <= OldBall.top &&
			Player.botom >= Ball.top)
		{
			hitY = true;
		}

		// ������
		if (Player.left >= OldBall.right &&
			Player.left <= Ball.right)
		{
			hitX = true;
		}

		// �E����
		if (Player.right <= OldBall.left &&
			Player.right >= Ball.left)
		{
			hitX = true;
		}
	}
	
	// �ʏ�̃o�E���h����
	if (hitX)
	{
		g_Ball.vel.x *= -1.0f;
	}
	if (hitY)
	{
		g_Ball.vel.y *= -1.0f;

		// �R���g���[���[�̌X������
		if (p_Player->angle == ANGLE_NORMAL)
		{
			g_Ball.vel.x = 0.0f;
		}
		if (p_Player->angle == ANGLE_LEFT)
		{
			g_Ball.vel.x = -BALL_SPEED_X;
		}
		if (p_Player->angle == ANGLE_RIGHT)
		{
			g_Ball.vel.x = BALL_SPEED_X;
		}
	}

	// �^�C�~���O�ǂ��U�������̃o�E���h����
	if (bound)
	{
		PlaySE(WSD_JUMP_CUTE);
		AddScore(BOUND_SCORE);

		g_Ball.vel.y = INIT_BALL_SPEED * 8.0f;

		// �R���g���[���[�̌X������
		if (p_Player->angle == ANGLE_NORMAL)
		{
			g_Ball.vel.x = 0.0f;
		}
		if (p_Player->angle == ANGLE_LEFT)
		{
			g_Ball.vel.x = -BALL_SPEED_X;
		}
		if (p_Player->angle == ANGLE_RIGHT)
		{
			g_Ball.vel.x = BALL_SPEED_X;
		}

		SetControllerRightVibration(1);
	}
}