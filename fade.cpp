//=================================================================
// [fade.cpp]
// �t�F�[�h��������
// ����ҁF�쑺 �I�l	�X�V���F2023/06/26
//=================================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "sound.h"
#include "fade.h"


//=================================================================
// �O���[�o���ϐ�
//=================================================================
unsigned int g_FadeTexture;	 // �e�N�X�`��ID
float		 g_FadeAlpha;	 // �t�F�[�h�̃A���t�@�l
MODE_FADE	 g_FadeState;	 // �t�F�[�h�̏��


//=================================================================
// ����������
//=================================================================
void InitFade()
{
	g_FadeTexture = NULL;

	// �t�F�[�h�l�̏�����
	g_FadeAlpha = 0.0f;

	// �t�F�[�h�X�e�[�g�̏�����
	g_FadeState = FADE_NONE;
}


//=================================================================
// �I������
//=================================================================
void UninitFade()
{
	UnloadTexture(g_FadeTexture);
}


//=================================================================
// �X�V����
//=================================================================
void UpdateFade()
{
	switch (g_FadeState)
	{
	case FADE_NONE:
		break;
	case FADE_IN:
		g_FadeAlpha -= FADE_SPEED;

		// �t�F�[�h�C���̏I������
		if (g_FadeAlpha <= 0.0f) 
		{
			g_FadeState = FADE_NONE;
		}
		break;
	case FADE_OUT:
		g_FadeAlpha += FADE_SPEED;

		// �t�F�[�h�A�E�g�̏I������
		if (g_FadeAlpha >= 1.0f) 
		{
			g_FadeState = FADE_IN;

			SCENE* p_Scene = GetScene();

			// BGM�̃X�g�b�v
			StopBGM();

			// �V�[���؂�ւ�
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
// �`�揈��
//=================================================================
void DrawFade()
{
	DrawSpriteColor(g_FadeTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					SCREEN_WIDTH, SCREEN_HEIGHT,
					0.0f, 0.0f, 0.0f, 0.0f,
					1.0f, 1.0f, 1.0f, g_FadeAlpha);

}

//=================================================================
// �t�F�[�h�̐؂�ւ�
//=================================================================
void SwapFade(MODE_FADE state)
{
	// �t�F�[�h�X�e�[�g�̐؂�ւ�
	g_FadeState = state;

	// �t�F�[�h�l�̏�����
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
// ���݂̃t�F�[�h�X�e�[�g�̎擾
//=================================================================
MODE_FADE GetFadeState(void) 
{
	return g_FadeState;
}
