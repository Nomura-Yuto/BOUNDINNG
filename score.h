//=================================================================
// [score.h]
// スコアアニメーション制御ヘッダ
// 制作者：野村 悠人	更新日：2023/06/19
//=================================================================
#pragma once		// インクルードガード

//=================================================================
// マクロ定義
//=================================================================
#define BASE_SCORE	(3)		// 加点スコア基礎値
#define BOUND_SCORE (30)	// バウンド時の加点スコア
#define SCORE_DISIT	(6)		// スコアの桁数
#define DISP_NUM_SIZE (60.0f)

//=================================================================
// 構造体宣言
//=================================================================
typedef struct {
	Float2	pos;	// 座標
	Float2	size;	// サイズ

	int		point;	// スコアポイント
}SCORE;

//=================================================================
// プロトタイプ宣言
//=================================================================
void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();
void AddScore(int value);
int GetScorePoint(void);
void DrawNum(int num, Float2 numPos, Float2 size, int numDisit);
