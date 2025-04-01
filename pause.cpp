//=================================================================
// [pause.cpp]
// ボックス制御
// 製作者：野村 悠人		更新日：2023/09/04
//=================================================================
#include "main.h"
#include "pause.h"
#include "controller.h"
#include "sprite.h"
#include "sound.h"
#include "texture.h"
#include "player.h"
#include "fade.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct {
	Float2 pos;		// 座標
	Float2 size;	// サイズ
	bool	use;	// 使用フラグ
} BUTTON;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PAUSE			g_Pause;
unsigned int	g_PauseTexture = 0;		// テクスチャID
unsigned int	g_ContinueButtonTexture = 0;	// テクスチャID
unsigned int	g_ContinueButtonRedTexture = 0;	// テクスチャID
unsigned int	g_EndButtonTexture = 0;	// テクスチャID
unsigned int	g_EndButtonRedTexture = 0;	// テクスチャID
unsigned int	g_GuideButtonTexture = 0;	// テクスチャID

BUTTON g_ContinueButton;	// 選択ボタン
BUTTON g_EndButton;	// 選択ボタン
BUTTON g_GuideButton;	// 選択ボタン
//=============================================================================
// 初期化処理
//=============================================================================
void InitPause(void)
{
	//テクスチャの読み込み
	g_PauseTexture = NULL;
	g_ContinueButtonTexture = LoadTexture("rom:/continue_button_blue.tga");
	g_ContinueButtonRedTexture = LoadTexture("rom:/continue_button_red.tga");
	g_EndButtonTexture = LoadTexture("rom:/end_button_blue.tga");
	g_EndButtonRedTexture = LoadTexture("rom:/end_button_red.tga");
	g_GuideButtonTexture = LoadTexture("rom:/guide_white.tga");

	//初期化
	g_Pause.use = false;

	g_ContinueButton.pos = MakeFloat2(SCREEN_WIDTH / 2, 360.0f);
	g_ContinueButton.size = MakeFloat2(480.0f, 240.0f);
	g_ContinueButton.use = true;

	g_EndButton.pos = MakeFloat2(SCREEN_WIDTH / 2, 720.0f);
	g_EndButton.size = MakeFloat2(480.0f, 240.0f);
	g_EndButton.use = false;
	
	g_GuideButton.pos = MakeFloat2(1620.0f, 860.0f);
	g_GuideButton.size = MakeFloat2(540.0f, 300.0f);
	g_GuideButton.use = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPause(void)
{
	UnloadTexture(g_PauseTexture);
	UnloadTexture(g_ContinueButtonTexture);
	UnloadTexture(g_EndButtonTexture);
	UnloadTexture(g_GuideButtonTexture);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePause(void)
{
	// ボタンの選択
	if (GetControllerTrigger(NpadButton::B::Index))
	{
		g_ContinueButton.use = false;
	}
	else if (GetControllerTrigger(NpadButton::X::Index))
	{
		g_ContinueButton.use = true;
	}

	// 選択したボタンの判定
	if (g_ContinueButton.use)
	{
		if (GetControllerTrigger(NpadButton::A::Index))
		{
			g_Pause.use = false;
		}
	}
	else
	{
		if (GetControllerTrigger(NpadButton::A::Index))
		{
			SwapFade(FADE_OUT);
		}
	}

	// pause画面の終了
	if (GetControllerTrigger(NpadButton::Plus::Index))
	{
		g_Pause.use = false;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPause(void)
{	
	if (g_Pause.use) 
	{
		DrawSpriteColor(g_PauseTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, PAUSE_FADE_ALPHA);

		DrawSprite(g_GuideButtonTexture, g_GuideButton.pos.x, g_GuideButton.pos.y,
			g_GuideButton.size.x, g_GuideButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f);

		// 選択したボタンに対応した描画
		if (g_ContinueButton.use)
		{
			DrawSprite(g_ContinueButtonRedTexture, g_ContinueButton.pos.x, g_ContinueButton.pos.y,
				g_ContinueButton.size.x, g_ContinueButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f);

			DrawSprite(g_EndButtonTexture, g_EndButton.pos.x, g_EndButton.pos.y,
				g_EndButton.size.x, g_EndButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f);
		}
		else
		{
			DrawSprite(g_ContinueButtonTexture, g_ContinueButton.pos.x, g_ContinueButton.pos.y,
				g_ContinueButton.size.x, g_ContinueButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f);

			DrawSprite(g_EndButtonRedTexture, g_EndButton.pos.x, g_EndButton.pos.y,
				g_EndButton.size.x, g_EndButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f);
		}
	}
}
		
//=============================================================================
// 実体のアドレス取得関数
//=============================================================================
PAUSE *GetPause(void) 
{
	return &g_Pause;
}
