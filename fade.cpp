//=================================================================
// [fade.cpp]
// フェード処理制御
// 制作者：野村 悠人	更新日：2023/06/26
//=================================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "sound.h"
#include "fade.h"


//=================================================================
// グローバル変数
//=================================================================
unsigned int g_FadeTexture;	 // テクスチャID
float		 g_FadeAlpha;	 // フェードのアルファ値
MODE_FADE	 g_FadeState;	 // フェードの状態


//=================================================================
// 初期化処理
//=================================================================
void InitFade()
{
	g_FadeTexture = NULL;

	// フェード値の初期化
	g_FadeAlpha = 0.0f;

	// フェードステートの初期化
	g_FadeState = FADE_NONE;
}


//=================================================================
// 終了処理
//=================================================================
void UninitFade()
{
	UnloadTexture(g_FadeTexture);
}


//=================================================================
// 更新処理
//=================================================================
void UpdateFade()
{
	switch (g_FadeState)
	{
	case FADE_NONE:
		break;
	case FADE_IN:
		g_FadeAlpha -= FADE_SPEED;

		// フェードインの終了判定
		if (g_FadeAlpha <= 0.0f) 
		{
			g_FadeState = FADE_NONE;
		}
		break;
	case FADE_OUT:
		g_FadeAlpha += FADE_SPEED;

		// フェードアウトの終了判定
		if (g_FadeAlpha >= 1.0f) 
		{
			g_FadeState = FADE_IN;

			SCENE* p_Scene = GetScene();

			// BGMのストップ
			StopBGM();

			// シーン切り替え
			switch (*p_Scene)
			{
			case SCENE_TITLE:
				SwapScene(SCENE_TUTORIAL);
				break;
			case SCENE_TUTORIAL:
				SwapScene(SCENE_GAME);
				break;
			case SCENE_GAME:
				SwapScene(SCENE_RESULT);
				break;
			case SCENE_RESULT:
				SwapScene(SCENE_TITLE);
				break;
			default:
				break;
			}

		}
		break;
	default:
		break;
	}
}


//=================================================================
// 描画処理
//=================================================================
void DrawFade()
{
	DrawSpriteColor(g_FadeTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH, SCREEN_HEIGHT,
					0.0f, 0.0f, 0.0f, 0.0f,
					1.0f, 1.0f, 1.0f, g_FadeAlpha);

}

//=================================================================
// フェードの切り替え
//=================================================================
void SwapFade(MODE_FADE state)
{
	// フェードステートの切り替え
	g_FadeState = state;

	// フェード値の初期化
	switch (g_FadeState)
	{
	case FADE_NONE:
		break;
	case FADE_IN:
		g_FadeAlpha = 1.0f;
		break;
	case FADE_OUT:
		g_FadeAlpha = 0.0f;
		break;
	default:
		break;
	}

}

//=================================================================
// 現在のフェードステートの取得
//=================================================================
MODE_FADE GetFadeState(void) 
{
	return g_FadeState;
}
