//=================================================================
// [block.cpp]
// ブロック制御
// 制作者：野村 悠人	更新日：2023/09/04
//=================================================================
#include <stdlib.h>
#include "main.h"
#include "controller.h"
#include "sound.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "ball.h"
#include "player.h"
#include "explosion.h"
#include "score.h"

//=================================================================
// プロトタイプ宣言
//=================================================================
void BlockCollision(void);

//=================================================================
// グローバル変数
//=================================================================
unsigned int	g_BlockTexture;			// テクスチャID
BLOCK			g_Block[MAX_BLOCK];		// 実体
TIME*			p_Time;					// 経過時間取得用のポインタ

//=================================================================
// ブロック初期化処理
//=================================================================
void InitBlock()
{
	srand((unsigned int)time(NULL));
	
	g_BlockTexture = LoadTexture("rom:/block.tga");

	// ブロックの初期化
	for (int i = 0; i < MAX_BLOCK; i++) 
	{
		g_Block[i].pos = MakeFloat2(0.0f , 0.0f);
		g_Block[i].oldPos = g_Block[i].pos;
		g_Block[i].size = MakeFloat2(0.0f, 0.0f);

		g_Block[i].type = 0;
		g_Block[i].use = false;
	}

	p_Time = GetTime();
}

//=================================================================
// ブロック終了処理
//=================================================================
void UninitBlock()
{

	UnloadTexture(g_BlockTexture);

}

//=================================================================
// ブロックアップデート処理
//=================================================================
void UpdateBlock()
{
	bool blockSet = false;
	float randSpeed;
	
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (g_Block[i].use)
		{
			g_Block[i].oldPos = g_Block[i].pos;

			g_Block[i].pos.y += g_Block[i].vel.y;


			if (g_Block[i].pos.y >= (float)SCREEN_HEIGHT + (float)g_Block[i].size.y)
			{
				// スコアの加算
				AddScore(BASE_SCORE * (g_Block[i].type + 1));

				g_Block[i].use = false;
				blockSet = true;
			}
		}
	}
	// ブロックの生成間隔
	if (p_Time->frame == 90)
	{
		blockSet = true;
	}

	if (blockSet)
	{
		randSpeed = rand() % 5 + 5;
		SetBlock(MakeFloat2(BLOCK_SIZE_X, BLOCK_SIZE_Y), // サイズ
			MakeFloat2(0.0f, randSpeed));	// 速度
		
	}
	
	// 当たり判定
	BlockCollision();
}


//=================================================================
// ブロック描画処理
//=================================================================
void DrawBlock()
{
	for (int i = 0; i < MAX_BLOCK; i++) 
	{
		if (g_Block[i].use) 
		{
			DrawSprite(g_BlockTexture, g_Block[i].pos.x, g_Block[i].pos.y,
				g_Block[i].size.x, g_Block[i].size.y,
				0.0f, 0.25 * (g_Block[i].type % 4), 1.0f, 0.25f);
		}
	}

}

//=================================================================
// セット関数
//=================================================================
void SetBlock(Float2 size, Float2 vel) 
{
	int random;
	int collarRand;


	for (int i = 0; i < MAX_BLOCK; i++) 
	{
		if (!g_Block[i].use) 
		{
			random = rand() % (int)(1000 - BLOCK_SIZE_X);
			collarRand = rand() % 4;

			g_Block[i].pos = MakeFloat2(460 + BLOCK_SIZE_X / 2 + random, - BLOCK_SIZE_Y);
			g_Block[i].oldPos = g_Block[i].pos;
			g_Block[i].size = size;
			g_Block[i].vel = vel;
			g_Block[i].type = collarRand;
			g_Block[i].use = true;
			break;
		}
	}
}

//=================================================================
// 実体(ブロック)のアドレス取得用関数(ゲッター)
//=================================================================
BLOCK* GetBlock(void) 
{
	return g_Block;
}

//=================================================================
// ブロックの当たり判定処理
//=================================================================
void BlockCollision(void) 
{
	BALL	*p_Ball;
	p_Ball = GetBall();
	bool hit = false;

	BOX Ball = 
	{
		p_Ball->pos.y - p_Ball->size.y / 2, // 上辺
		p_Ball->pos.y + p_Ball->size.y / 2, // 下辺
		p_Ball->pos.x - p_Ball->size.x / 2, // 左辺
		p_Ball->pos.x + p_Ball->size.x / 2, // 右辺
	};

	BOX OldBall = 
	{
		p_Ball->oldPos.y - p_Ball->size.y / 2, // 上辺
		p_Ball->oldPos.y + p_Ball->size.y / 2, // 下辺
		p_Ball->oldPos.x - p_Ball->size.x / 2, // 左辺
		p_Ball->oldPos.x + p_Ball->size.x / 2, // 右辺
	};
	
	BOX Block;
	BOX OldBlock;
	
	for (int i = 0; i < MAX_BLOCK; i++) 
	{
		if (g_Block[i].use) 
		{
			Block.top	= g_Block[i].pos.y - g_Block[i].size.y / 2; // 上辺
			Block.botom	= g_Block[i].pos.y + g_Block[i].size.y / 2; // 下辺
			Block.left	= g_Block[i].pos.x - g_Block[i].size.x / 2; // 左辺
			Block.right	= g_Block[i].pos.x + g_Block[i].size.x / 2; // 右辺

			OldBlock.top	= g_Block[i].oldPos.y - g_Block[i].size.y / 2; // 上辺
			OldBlock.botom	= g_Block[i].oldPos.y + g_Block[i].size.y / 2; // 下辺
			OldBlock.left	= g_Block[i].oldPos.x - g_Block[i].size.x / 2; // 左辺
			OldBlock.right	= g_Block[i].oldPos.x + g_Block[i].size.x / 2; // 右辺
			
			// 当たり判定
			if (Ball.right >= Block.left  &&
				Ball.left	<= Block.right &&
				Ball.botom	>= Block.top &&
				Ball.top <= Block.botom)
			{

				// 上判定
				if (Block.top >= OldBall.botom &&
					Block.top <= Ball.botom ||
					Ball.top >= OldBlock.botom &&
					Ball.top <= Block.botom)
				{

					hit = true;
				}

				// 下判定
				if (Block.botom <= OldBall.top &&
					Block.botom >= Ball.top || 
					Ball.botom <= OldBlock.top &&
					Ball.botom >= Block.top)
				{

					hit = true;
				}

				// 左判定
				if (Block.left >= OldBall.right &&
					Block.left <= Ball.right ||
					Ball.left >= OldBlock.right &&
					Ball.left <= Block.right)
				{

					hit = true;
				}

				// 右判定
				if (Block.right <= OldBall.left &&
					Block.right >= Ball.left ||
					Ball.right <= OldBlock.left &&
					Ball.right >= Block.left)
				{

					hit = true;
				}				
			}

			// 当たったかの判定
			if (hit) 
			{
				hit = false;
				DownHealth();

				PlaySE(WSD_STONE_BREAK1);

				// 爆発アニメーションのセット
				SetExplosion(MakeFloat2(g_Block[i].pos.x, g_Block[i].pos.y), // 座標
					MakeFloat2(200.0f, 200.0f)); // サイズ

				g_Block[i].use = false;

				SetBlock(MakeFloat2(BLOCK_SIZE_X, BLOCK_SIZE_Y), // サイズ
					MakeFloat2(0.0f, 5.0f)); // 速度

				break;
			}
		
		}
	}
}