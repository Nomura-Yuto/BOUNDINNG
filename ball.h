//=================================================================
// [ball.h]
// ボール制御ヘッダ
// 制作者：野村 悠人	更新日：2023/08/29
//=================================================================
#pragma once		// インクルードガード


//=================================================================
// 構造体宣言
//=================================================================
typedef struct {
	Float2 pos;		// 座標
	Float2 oldPos;	// 1F前の座標
	Float2 size;	// サイズ
	Float2 vel;		// 速度
	int health;
	float gravity;
}BALL;

// ポリゴンの4辺の位置
typedef struct {
	float top;		// 上辺
	float botom;	// 下辺
	float left;		// 左辺
	float right;	// 右辺
}BOX;

//=================================================================
// プロトタイプ宣言
//=================================================================
void InitBall();
void UninitBall();
void UpdateBall();
void DrawBall();
void DownHealth(void);
void AddHealth(int value);
BALL* GetBall(void);
