//=================================================================
// [main.cpp]
// メイン関数
// 制作者：野村 悠人	更新日：2023/09/04
//=================================================================
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "sound.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "score.h"
#include "fade.h"

//=================================================================
// プロトタイプ宣言
//=================================================================
void Init();
void Uninit();
void Update();
void Draw();

//=================================================================
// グローバル変数
//=================================================================
SCENE g_scene = SCENE_TITLE;
TIME g_time;


//=================================================================
// メイン関数
//=================================================================
extern "C" void nnMain()
{
	Init();

    while( true )
	{
		Update();
		Draw();
	}

	Uninit();
}


//=================================================================
// 初期化処理
//=================================================================
void Init()
{
	// サウンドの初期化  ※InitSystem();より前で呼ぶ
	InitSound();

	InitSystem();
	InitController();

	// 時間計測用の変数の初期化
	g_time.frame = 0;
	g_time.seconds = 0;

	// フェードの初期化
	InitFade();
	
	switch (g_scene)
	{
	case SCENE_TITLE:	// タイトルの初期化
		InitTitle();
		break;

	case SCENE_TUTORIAL: //チュートリアルの初期化
		InitTutorial();
		break;

	case SCENE_GAME:	// 各シーンの初期化		
		InitGame();
		break;

	case SCENE_RESULT:	// リザルトの初期化
		InitResult();
		break;

	default:
		break;
	}
}


//=================================================================
// 終了処理
//=================================================================
void Uninit()
{
	// スコアの終了処理
	UninitScore();

	switch (g_scene)
	{
	case SCENE_TITLE:	// タイトルの終了処理
		UninitTitle();
		break;

	case SCENE_TUTORIAL: //チュートリアルの終了処理
		UninitTutorial();
		break;

	case SCENE_GAME:	// 各シーンの終了処理		
		UninitGame();
		break;

	case SCENE_RESULT:	// リザルトの終了処理
		UninitResult();
		break;

	default:
		break;
	}

	// フェードの終了処理
	UninitFade();

	// サウンドの終了処理
	UninitSound();

	UninitController();
	UninitSystem();
	
}


//=================================================================
// 更新処理
//=================================================================
void Update()
{
	// サウンドの更新処理
	UpdateSound();

	UpdateController();

	// 経過時間の計測
	g_time.frame++;
	if (g_time.frame % 60 + 1 == 60)
	{
		g_time.seconds++;
	}
	// 2秒でframeのリセット
	if (g_time.frame == 120)
	{
		g_time.frame = 0;
	}

	switch (g_scene)
	{
	case SCENE_TITLE:	// タイトルの更新処理
		UpdateTitle();
		break;

	case SCENE_TUTORIAL: //チュートリアルの更新処理
		UpdateTutorial();
		break;

	case SCENE_GAME:	// 各シーンの更新処理		
		UpdateGame();
		break;

	case SCENE_RESULT:	// リザルトの更新処理
		UpdateResult();
		break;

	default:
		break;
	}
	
	// フェードの更新処理
	UpdateFade();
}


//=================================================================
// 描画処理
//=================================================================
void Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (g_scene)
	{
	case SCENE_TITLE:	// タイトルの描画
		DrawTitle();
		break;

	case SCENE_TUTORIAL: //チュートリアルの描画
		DrawTutorial();
		break;

	case SCENE_GAME:	// 各シーンの描画		
		DrawGame();
		break;

	case SCENE_RESULT:	// リザルトの描画
		DrawResult();
		break;

	default:
		break;
	}

	// フェードの描画
	DrawFade();

	SwapBuffers();
}

//=================================================================
// シーン切り替え
//=================================================================
void SwapScene(SCENE scene) 
{
	// 切り替え前シーンの終了処理
	switch (g_scene)
	{
	case SCENE_TITLE:	// タイトルの終了処理
		UninitTitle();
		break;

	case SCENE_TUTORIAL: //チュートリアルの終了処理
		UninitTutorial();
		break;

	case SCENE_GAME:	// 各シーンの終了処理		
		UninitGame();
		break;

	case SCENE_RESULT:	// リザルトの終了処理
		UninitResult();
		break;

	default:
		break;
	}

	// シーンの切り替え
	g_scene = scene;
	
	// 切り替え後シーンの初期化
	switch (g_scene)
	{
	case SCENE_TITLE:	// タイトルの初期化
		InitTitle();
		break;

	case SCENE_TUTORIAL: //チュートリアルの初期化
		InitTutorial();
		break;

	case SCENE_GAME:	// 各シーンの初期化		
		InitGame();
		break;

	case SCENE_RESULT:	// リザルトの初期化
		InitResult();
		break;

	default:
		break;
	}
}

//=================================================================
// 現在のシーンの取得
//=================================================================
SCENE *GetScene(void) 
{
	return &g_scene;
}

//=================================================================
// 経過時間の取得
//=================================================================
TIME *GetTime(void)
{
	return &g_time;
}
