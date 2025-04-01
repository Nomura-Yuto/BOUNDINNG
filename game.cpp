//=================================================================
// [game.cpp]
// �Q�[���V�[������
// ����ҁF�쑺 �I�l	�X�V���F2023/08/29
//=================================================================
#include "main.h"
#include "game.h"
#include "controller.h"
#include "sound.h"
#include "bg.h"
#include "player.h"
#include "ball.h"
#include "block.h"
#include "explosion.h"
#include "score.h"
#include "fade.h"
#include "pause.h"


//=================================================================
// �O���[�o���ϐ�
//=================================================================
PAUSE* p_Pause;
BALL* p_Ball;
EXPLOSION* p_Explosion;


//=================================================================
// ����������
//=================================================================
void InitGame()
{
	InitBG();
	InitPlayer();
	InitBall();
	InitBlock();
	InitExplosion();
	InitScore();
	InitPause();

	p_Pause = GetPause();
	p_Ball = GetBall();
	p_Explosion = GetExplosion();

	// BGM�̍Đ�
	PlayBGM(STRM_HARUNOPAYAPAYA_1);
}


//=================================================================
// �I������
//=================================================================
void UninitGame()
{
	UninitBG();
	UninitPlayer();
	UninitBall();
	UninitBlock();
	UninitExplosion();
	UninitPause();
}


//=================================================================
// �X�V����
//=================================================================
void UpdateGame()
{
	bool end = false;

	if (!p_Pause->use)
	{
		UpdateBG();
		UpdatePlayer();
		UpdateBall();
		UpdateBlock();
		UpdateExplosion();
		UpdateScore();

		// �V�[���̐؂�ւ�
		if (GetControllerTrigger(NpadButton::Plus::Index))
			p_Pause->use = true;

		if (p_Ball->health <= 0 && GetFadeState() != FADE_OUT)
			end = true;

		if(end) SwapFade(FADE_OUT);
	}
	else
	{
		UpdatePause();
	}
}


//=================================================================
// �`�揈��
//=================================================================
void DrawGame()
{
	DrawBG();
	DrawPlayer();
	DrawBall();
	DrawBlock();
	DrawExplosion();
	DrawScore();	
	DrawPause();
}
