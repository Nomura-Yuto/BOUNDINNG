//=================================================================
// [fade.h]
// フェード処理制御ヘッダ
// 制作者：野村 悠人	更新日：2023/06/26
//=================================================================
#pragma once


//=================================================================
// マクロ定義
//=================================================================
#define FADE_SPEED (0.04f)

//=================================================================
// 列挙体宣言
//=================================================================
typedef enum { // フェードのステート
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}MODE_FADE;

//=================================================================
// プロトタイプ宣言
//=================================================================
void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void SwapFade(MODE_FADE state);
MODE_FADE GetFadeState(void);