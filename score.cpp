//=================================================================
// [score.cpp]
// スコアアニメーション制御
// 制作者：野村 悠人	更新日：2023/08/29
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
// マクロ定義
//=================================================================
#define PARTITION_PATTERN_X (5)	// テクスチャの分割数(横)
#define PARTITION_PATTERN_Y (5)	// テクスチャの分割数(縦)
#define PATTERN_WIDTH	(1.0f / PARTITION_PATTERN_X) // 表示テクスチャの横幅
#define PATTERN_HEIGHT	(1.0f / PARTITION_PATTERN_Y) // 表示テクスチャの縦幅

#define HEART_NUM	(10)	// テクスチャ(ハート)の表示番号
#define BONE_NUM	(11)	// テクスチャ(骨)の表示番号
#define CLOCK_NUM	(12)	// テクスチャ(時計)の表示番号


//=================================================================
// グローバル変数
//=================================================================
unsigned int	g_ScoreTexture;	// テクスチャID
SCORE			g_Score;		// 実体

//=================================================================
// スコア初期化処理
//=================================================================
void InitScore()
{

	g_ScoreTexture = LoadTexture("rom:/number.tga");

	g_Score.pos = MakeFloat2(1500.0f , 260.0f);
	g_Score.size = MakeFloat2(DISP_NUM_SIZE, DISP_NUM_SIZE);

	
	g_Score.point = 0;
}


//=================================================================
// スコア終了処理
//=================================================================
void UninitScore()
{

	UnloadTexture(g_ScoreTexture);

}


//=================================================================
// スコアアップデート処理
//=================================================================
void UpdateScore()
{

}


//=================================================================
// スコア描画処理
//=================================================================
void DrawScore()
{
	TIME* p_Time = GetTime();
	BALL* p_Ball = GetBall();

	// スコア表示
	DrawNum(g_Score.point, g_Score.pos, g_Score.size, SCORE_DISIT);

	// 体力表示
	DrawHealth(p_Ball->health, MakeFloat2(1584.0f, 540.0f),g_Score.size);
}

//=================================================================
// スコア増減関数
//=================================================================
void AddScore(int value) 
{
	g_Score.point += value;

	// オーバーフロー対策
	if (g_Score.point >= 1000000)
	{
		g_Score.point = 999999;
	}
}

//=================================================================
// スコア取得
//=================================================================
int GetScorePoint(void) 
{
	return g_Score.point;
}

//=================================================================
// ナンバー描画処理
//=================================================================
void DrawNum(int num, Float2 numPos, Float2 size, int numDisit)
{
	int editNum;		 // 編集用番号
	Float2 editPos; // 編集用表示横位置
	editNum = num;
	editPos = numPos;
	
	for (int i = 0; i < numDisit; i++) {
		int num;		// 一桁保存用
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
// 体力描画処理
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



