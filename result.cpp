//=================================================================
// [result.cpp]
// リザルトシーン制御
// 制作者：野村 悠人	更新日：2023/09/04
//=================================================================
#include "main.h"
#include "controller.h"
#include "sound.h"
#include "result.h"
#include "resultbg.h"
#include "fade.h"
#include "score.h"


//=================================================================
// グローバル変数
//=================================================================


//=================================================================
// 初期化処理
//=================================================================
void InitResult()
{
	InitResultBG();

	// BGMの再生
	PlayBGM(STRM_CHOCOLATEDAISAKUSEN_1);
}


//=================================================================
// 終了処理
//=================================================================
void UninitResult()
{
	UninitResultBG();
}


//=================================================================
// 更新処理
//=================================================================
void UpdateResult()
{
	UpdateResultBG();

	// シーンの切り替え
	if (GetControllerTrigger(NpadButton::A::Index)) 
	{
		// SEの再生
		PlaySE(WSD_SE_DECISION);
		SwapFade(FADE_OUT);
	}
}


//=================================================================
// 描画処理
//=================================================================
void DrawResult()
{
	DrawResultBG();

	DrawNum(GetScorePoint(), MakeFloat2(620.0f, 720.0f), MakeFloat2(100.0f, 100.0f), SCORE_DISIT);
}
