//=================================================================
// [pause.cpp]
// �{�b�N�X����
// ����ҁF�쑺 �I�l		�X�V���F2023/09/04
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
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct {
	Float2 pos;		// ���W
	Float2 size;	// �T�C�Y
	bool	use;	// �g�p�t���O
} BUTTON;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PAUSE			g_Pause;
unsigned int	g_PauseTexture = 0;		// �e�N�X�`��ID
unsigned int	g_ContinueButtonTexture = 0;	// �e�N�X�`��ID
unsigned int	g_ContinueButtonRedTexture = 0;	// �e�N�X�`��ID
unsigned int	g_EndButtonTexture = 0;	// �e�N�X�`��ID
unsigned int	g_EndButtonRedTexture = 0;	// �e�N�X�`��ID
unsigned int	g_GuideButtonTexture = 0;	// �e�N�X�`��ID

BUTTON g_ContinueButton;	// �I���{�^��
BUTTON g_EndButton;	// �I���{�^��
BUTTON g_GuideButton;	// �I���{�^��
//=============================================================================
// ����������
//=============================================================================
void InitPause(void)
{
	//�e�N�X�`���̓ǂݍ���
	g_PauseTexture = NULL;
	g_ContinueButtonTexture = LoadTexture("rom:/continue_button_blue.tga");
	g_ContinueButtonRedTexture = LoadTexture("rom:/continue_button_red.tga");
	g_EndButtonTexture = LoadTexture("rom:/end_button_blue.tga");
	g_EndButtonRedTexture = LoadTexture("rom:/end_button_red.tga");
	g_GuideButtonTexture = LoadTexture("rom:/guide_white.tga");

	//������
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
// �I������
//=============================================================================
void UninitPause(void)
{
	UnloadTexture(g_PauseTexture);
	UnloadTexture(g_ContinueButtonTexture);
	UnloadTexture(g_EndButtonTexture);
	UnloadTexture(g_GuideButtonTexture);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{
	// �{�^���̑I��
	if (GetControllerTrigger(NpadButton::B::Index))
	{
		g_ContinueButton.use = false;
	}
	else if (GetControllerTrigger(NpadButton::X::Index))
	{
		g_ContinueButton.use = true;
	}

	// �I�������{�^���̔���
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

	// pause��ʂ̏I��
	if (GetControllerTrigger(NpadButton::Plus::Index))
	{
		g_Pause.use = false;
	}
}

//=============================================================================
// �`�揈��
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

		// �I�������{�^���ɑΉ������`��
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
// ���̂̃A�h���X�擾�֐�
//=============================================================================
PAUSE *GetPause(void) 
{
	return &g_Pause;
}
