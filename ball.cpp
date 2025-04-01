//=================================================================
// [ball.cpp]
// ボール制御
// 制作者：野村 悠人	更新日：2023/08/29
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
// マクロ定義
//=================================================================
#define BALL_SIZE		(75.0f)	// ボールのサイズ
#define BALL_GRAVITY	(2.0f)	// ボールの重力
#define INIT_BALL_SPEED	(-5.0f)	// ボールの初期速度
#define BALL_SPEED_X	(4.0f)	// ボールの移動速度(X)
#define MAX_HEALTH		(10)	// 最大体力

//=================================================================
// プロトタイプ宣言
//=================================================================
void BallCollision(void);

//=================================================================
// グローバル変数
//=================================================================
unsigned int	g_BallTexture;	// テクスチャID
BALL			g_Ball;			// 実体

//=================================================================
// ボール初期化処理
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
// ボール終了処理
//=================================================================
void UninitBall()
{

	UnloadTexture(g_BallTexture);

}

//=================================================================
// ボールアップデート処理
//=================================================================
void UpdateBall()
{
	g_Ball.oldPos = g_Ball.pos;

	g_Ball.vel.y += g_Ball.gravity;
	
	// 移動
	g_Ball.pos.x += g_Ball.vel.x;
	g_Ball.pos.y += g_Ball.vel.y;
		
	// 左壁判定
	if (g_Ball.pos.x <= 460.0f + g_Ball.size.x / 2)
	{
		g_Ball.vel.x *= -1.0f;
		g_Ball.pos.x = 460.0f + g_Ball.size.x / 2;

	}

	// 右壁判定
	if (g_Ball.pos.x >= 1460.0f - g_Ball.size.x / 2) 
	{
		g_Ball.vel.x *= -1.0f;
		g_Ball.pos.x = 1460.0f - g_Ball.size.x / 2;

	}

	// 上壁判定
	if (g_Ball.pos.y < 40.0f + g_Ball.size.y / 2)
		g_Ball.vel.y *= -1.0f;

	// 下壁判定
	if (g_Ball.pos.y > (float)SCREEN_HEIGHT - g_Ball.size.y / 2)
		g_Ball.vel.y *= -1.0f;

	// 当たり判定
	BallCollision();
}


//=================================================================
// ボール描画処理
//=================================================================
void DrawBall()
{

	DrawSprite(g_BallTexture, g_Ball.pos.x, g_Ball.pos.y, g_Ball.size.x, g_Ball.size.y,
						0.0f, 0.0f, 1.0f, 1.0f);


}

//=================================================================
// 実体(ボール)のアドレス取得用関数(ゲッター)
//=================================================================
BALL* GetBall(void) 
{
	return &g_Ball;
}

//=================================================================
// 体力減少
//=================================================================
void DownHealth(void)
{
	g_Ball.health--;
}

//=================================================================
// 体力増加
//=================================================================
void AddHealth(int value)
{
	g_Ball.health += value;
}

//=================================================================
// ボールとプレイヤーの当たり判定処理
//=================================================================
void BallCollision(void) 
{
	PLAYER	*p_Player;
	p_Player = GetPlayer();
	bool hitX = false;
	bool hitY = false;
	bool bound = false;
	
	BOX Player = {
		p_Player->pos.y - p_Player->size.y / 2, // 上辺
		p_Player->pos.y + p_Player->size.y / 2, // 下辺
		p_Player->pos.x - p_Player->size.x / 2, // 左辺
		p_Player->pos.x + p_Player->size.x / 2, // 右辺
	};

	BOX Ball{
		g_Ball.pos.y - g_Ball.size.y / 2, // 上辺
		g_Ball.pos.y + g_Ball.size.y / 2, // 下辺
		g_Ball.pos.x - g_Ball.size.x / 2, // 左辺
		g_Ball.pos.x + g_Ball.size.x / 2, // 右辺
	};

	BOX OldBall{
		g_Ball.oldPos.y - g_Ball.size.y / 2, // 上辺
		g_Ball.oldPos.y + g_Ball.size.y / 2, // 下辺
		g_Ball.oldPos.x - g_Ball.size.x / 2, // 左辺
		g_Ball.oldPos.x + g_Ball.size.x / 2, // 右辺
	};

	// 表示座標との当たり判定
	if (p_Player->displayPos.y - p_Player->size.y / 2 >= OldBall.botom &&
		p_Player->displayPos.y - p_Player->size.y / 2 <= Ball.botom)
	{
		g_Ball.pos.y = p_Player->displayPos.y - p_Player->size.y / 2 - g_Ball.size.y / 2;
		hitY = true;
	}

	if (p_Player->jump)
	{
		// タイミングよく振ったかの判定
		if (Ball.botom >= p_Player->displayPos.y - p_Player->size.y / 2 &&
			Ball.botom <= p_Player->pos.y)
		{
			bound = true;
		}
	}

	// 当たり判定
	if (Ball.right	> Player.left  &&
		Ball.left	< Player.right &&
		Ball.botom	> Player.top   &&
		Ball.top	< Player.botom)
	{
		// 上判定
		if (Player.top >= OldBall.botom &&
			Player.top <= Ball.botom)
		{
			g_Ball.pos.y = Player.top - g_Ball.size.y / 2;
			hitY = true;
		}

		// 下判定
		if (Player.botom <= OldBall.top &&
			Player.botom >= Ball.top)
		{
			hitY = true;
		}

		// 左判定
		if (Player.left >= OldBall.right &&
			Player.left <= Ball.right)
		{
			hitX = true;
		}

		// 右判定
		if (Player.right <= OldBall.left &&
			Player.right >= Ball.left)
		{
			hitX = true;
		}
	}
	
	// 通常のバウンド処理
	if (hitX)
	{
		g_Ball.vel.x *= -1.0f;
	}
	if (hitY)
	{
		g_Ball.vel.y *= -1.0f;

		// コントローラーの傾き判定
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

	// タイミング良く振った時のバウンド処理
	if (bound)
	{
		PlaySE(WSD_JUMP_CUTE);
		AddScore(BOUND_SCORE);

		g_Ball.vel.y = INIT_BALL_SPEED * 8.0f;

		// コントローラーの傾き判定
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