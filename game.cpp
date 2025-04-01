//=================================================================
// [game.cpp]
// ゲームシーン制御
// 制作者：野村 悠人	更新日：2023/08/29
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
// グローバル変数
//=================================================================
PAUSE* p_Pause;
BALL* p_Ball;
EXPLOSION* p_Explosion;


//=================================================================
// 初期化処理
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

	// BGMの再生
	PlayBGM(STRM_HARUNOPAYAPAYA_1);
}


//=================================================================
// 終了処理
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
// 更新処理
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

		// シーンの切り替え
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
// 描画処理
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
