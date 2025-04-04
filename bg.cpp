//=================================================================
// [bg.cpp]
// プレイ画面背景制御
// 制作者：野村 悠人	更新日：2023/09/04
//=================================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"


//=================================================================
// グローバル変数
//=================================================================
unsigned int g_BGTexture;


//=================================================================
// 背景初期化処理
//=================================================================
void InitBG()
{
	g_BGTexture = LoadTexture("rom:/play_bg.tga");
}


//=================================================================
// 背景終了処理
//=================================================================
void UninitBG()
{
	UnloadTexture(g_BGTexture);
}


//=================================================================
// 背景更新処理
//=================================================================
void UpdateBG()
{

}


//=================================================================
// 背景描画処理
//=================================================================
void DrawBG()
{
	DrawSpriteLeftTop(g_BGTexture, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

}
