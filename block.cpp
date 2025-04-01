//=================================================================
// [block.cpp]
// �u���b�N����
// ����ҁF�쑺 �I�l	�X�V���F2023/09/04
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
// �v���g�^�C�v�錾
//=================================================================
void BlockCollision(void);

//=================================================================
// �O���[�o���ϐ�
//=================================================================
unsigned int	g_BlockTexture;			// �e�N�X�`��ID
BLOCK			g_Block[MAX_BLOCK];		// ����
TIME*			p_Time;					// �o�ߎ��Ԏ擾�p�̃|�C���^

//=================================================================
// �u���b�N����������
//=================================================================
void InitBlock()
{
	srand((unsigned int)time(NULL));
	
	g_BlockTexture = LoadTexture("rom:/block.tga");

	// �u���b�N�̏�����
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
// �u���b�N�I������
//=================================================================
void UninitBlock()
{

	UnloadTexture(g_BlockTexture);

}

//=================================================================
// �u���b�N�A�b�v�f�[�g����
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
				// �X�R�A�̉��Z
				AddScore(BASE_SCORE * (g_Block[i].type + 1));

				g_Block[i].use = false;
				blockSet = true;
			}
		}
	}
	// �u���b�N�̐����Ԋu
	if (p_Time->frame == 90)
	{
		blockSet = true;
	}

	if (blockSet)
	{
		randSpeed = rand() % 5 + 5;
		SetBlock(MakeFloat2(BLOCK_SIZE_X, BLOCK_SIZE_Y), // �T�C�Y
			MakeFloat2(0.0f, randSpeed));	// ���x
		
	}
	
	// �����蔻��
	BlockCollision();
}


//=================================================================
// �u���b�N�`�揈��
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
// �Z�b�g�֐�
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
// ����(�u���b�N)�̃A�h���X�擾�p�֐�(�Q�b�^�[)
//=================================================================
BLOCK* GetBlock(void) 
{
	return g_Block;
}

//=================================================================
// �u���b�N�̓����蔻�菈��
//=================================================================
void BlockCollision(void) 
{
	BALL	*p_Ball;
	p_Ball = GetBall();
	bool hit = false;

	BOX Ball = 
	{
		p_Ball->pos.y - p_Ball->size.y / 2, // ���
		p_Ball->pos.y + p_Ball->size.y / 2, // ����
		p_Ball->pos.x - p_Ball->size.x / 2, // ����
		p_Ball->pos.x + p_Ball->size.x / 2, // �E��
	};

	BOX OldBall = 
	{
		p_Ball->oldPos.y - p_Ball->size.y / 2, // ���
		p_Ball->oldPos.y + p_Ball->size.y / 2, // ����
		p_Ball->oldPos.x - p_Ball->size.x / 2, // ����
		p_Ball->oldPos.x + p_Ball->size.x / 2, // �E��
	};
	
	BOX Block;
	BOX OldBlock;
	
	for (int i = 0; i < MAX_BLOCK; i++) 
	{
		if (g_Block[i].use) 
		{
			Block.top	= g_Block[i].pos.y - g_Block[i].size.y / 2; // ���
			Block.botom	= g_Block[i].pos.y + g_Block[i].size.y / 2; // ����
			Block.left	= g_Block[i].pos.x - g_Block[i].size.x / 2; // ����
			Block.right	= g_Block[i].pos.x + g_Block[i].size.x / 2; // �E��

			OldBlock.top	= g_Block[i].oldPos.y - g_Block[i].size.y / 2; // ���
			OldBlock.botom	= g_Block[i].oldPos.y + g_Block[i].size.y / 2; // ����
			OldBlock.left	= g_Block[i].oldPos.x - g_Block[i].size.x / 2; // ����
			OldBlock.right	= g_Block[i].oldPos.x + g_Block[i].size.x / 2; // �E��
			
			// �����蔻��
			if (Ball.right >= Block.left  &&
				Ball.left	<= Block.right &&
				Ball.botom	>= Block.top &&
				Ball.top <= Block.botom)
			{

				// �㔻��
				if (Block.top >= OldBall.botom &&
					Block.top <= Ball.botom ||
					Ball.top >= OldBlock.botom &&
					Ball.top <= Block.botom)
				{

					hit = true;
				}

				// ������
				if (Block.botom <= OldBall.top &&
					Block.botom >= Ball.top || 
					Ball.botom <= OldBlock.top &&
					Ball.botom >= Block.top)
				{

					hit = true;
				}

				// ������
				if (Block.left >= OldBall.right &&
					Block.left <= Ball.right ||
					Ball.left >= OldBlock.right &&
					Ball.left <= Block.right)
				{

					hit = true;
				}

				// �E����
				if (Block.right <= OldBall.left &&
					Block.right >= Ball.left ||
					Ball.right <= OldBlock.left &&
					Ball.right >= Block.left)
				{

					hit = true;
				}				
			}

			// �����������̔���
			if (hit) 
			{
				hit = false;
				DownHealth();

				PlaySE(WSD_STONE_BREAK1);

				// �����A�j���[�V�����̃Z�b�g
				SetExplosion(MakeFloat2(g_Block[i].pos.x, g_Block[i].pos.y), // ���W
					MakeFloat2(200.0f, 200.0f)); // �T�C�Y

				g_Block[i].use = false;

				SetBlock(MakeFloat2(BLOCK_SIZE_X, BLOCK_SIZE_Y), // �T�C�Y
					MakeFloat2(0.0f, 5.0f)); // ���x

				break;
			}
		
		}
	}
}