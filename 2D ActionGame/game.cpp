//=========================================================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "game.h"
#include "player.h"
#include "Input.h"
#include "Block.h"
#include "fade.h"
#include "enemy.h"
#include "result.h"
//#include "backgraund.h"
//#include "bullet.h"
//#include "score.h"
//#include "pause.h"
//#include "ranking.h"
//#include "effect.h
//#include "wave.h"

//=========================================================================================================
//���C���֐�
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;													//�|�[�Y�����ǂ���

//=========================================================================================================
// �Q�[����ʂ̏���������
//=========================================================================================================
void InitGame(void)
{
	//�u���b�N�̏���������
	InitBlock();

	//X���W,Y���W,Z���W,�����̍��W,���̍��W
	SetBlock(D3DXVECTOR3(640.0f, 695.0f, 0.0f), 20.0f, 700.0f);			//�u���b�N1��(�n��)�̍��W
	SetBlock(D3DXVECTOR3(300.0f, 490.0f, 0.0f), 30.0f, 180.0f);			//�u���b�N2��(����)�̍��W
	SetBlock(D3DXVECTOR3(1000.0f, 490.0f, 0.0f), 30.0f, 180.0f);		//�u���b�N3��(�E��)�̍��W
	SetBlock(D3DXVECTOR3(650.0f, 270.0f, 0.0f), 30.0f, 170.0f);			//�u���b�N4��(�^��)�̍��W

	//�v���C���[�̏���������
	InitPlayer();

	//�e�̏���������
	//InitBullet();

	//�G�̏���������
	InitEnemy();

	//X���W,Y���W,Z���W
	SetEnemy(D3DXVECTOR3(750.0f, 200.0f, 0.0f), 0.0f, 10.0f);					//�G�̍��W(��)
	SetEnemy(D3DXVECTOR3(300.0f, 420.0f, 0.0f), 0.0f, 10.0f);					//�G�̍��W(��)
	SetEnemy(D3DXVECTOR3(1000.0f, 420.0f, 0.0f), 0.0f, 10.0f);					//�G�̍��W(�E)
	SetEnemy(D3DXVECTOR3(660.0f, 640.0f, 0.0f), 0.0f, 10.0f);					//�G�̍��W(��)


	////�E�F�[�u�̏���������
	//InitWave();

	//�G�t�F�N�g�̏���������
	//InitEffect();

	//�X�R�A�̏���������
	//InitScore();
	//SetScore(0);

	//�w�i�̏���������
	//Initbackgraund();

	//�����̏���������
	//InitExplosion();

	g_gameState = GAMESTATE_NORMAL;									//�ʏ���
	g_nCounterGameState;
	//g_bPause = false;												//�|�[�Y����

	////�Ǎ�����
	//LoadWave();
}

//=========================================================================================================
// �Q�[����ʂ̏I������
//=========================================================================================================
void UninitGame(void)
{
	//�u���b�N�̏I������
	UninitBlock();

	//�v���C���[�̏I������
	UninitPlayer();


	//�e�̏I������
	//UninitBullet();

	//�G�̏I������
	UninitEnemy();

	//�G�t�F�N�g�̏I������
	//UninitEffect();

	//�X�R�A�̏I������
	//UninitScore();

	//�w�i�̏I������
	//Uninitbackgraund();

	//�����̏I������
	//UninitExplosion();
}

//=========================================================================================================
// �Q�[����ʂ̍X�V����
//=========================================================================================================
void UpdateGame(void)
{
	//�u���b�N�̍X�V����
	UpdateBlock();

	//�v���C���[�̍X�V����
	UpdatePlayer();


	//�e�̍X�V����
	//UpdateBullet();

	//�G�̍X�V����
	UpdateEnemy();

	//�G�t�F�N�g�̍X�V����
	//UpdateEffect();

	//�X�R�A�̍X�V����
	//UpdateScore();

	//�w�i�̍X�V����
	//Updatebackgraund();

	//�����̍X�V����
	//UpdateExplosion();

	Player* pPlayer = GetPlayer();										//�v���C���[���ւ̃|�C���^
	Enemy* pEnemy = GetEnemy();											//�G���ւ̃|�C���^

	//�G���̎擾
	int NumEnemy = GetEnemyNum();
	bool bfinish = false;

	if (NumEnemy <= 0)
	{
		SetResult(RESULT_WIN);
		SetGameState(GAMESTATE_END);
		//LoadWave();
	}

	if (pPlayer->bUse == false)										//�v���C���[���g�p����Ă��Ȃ����̏���
	{
		g_gameState = GAMESTATE_END;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:

		//bfinish = GetFinish();

		if (bfinish == true)
		{
			//���[�h�ݒ�
			SetResult(RESULT_WIN);
			SetGameState(GAMESTATE_END);
		}
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//�t�F�[�h�̐ݒ�
			SetFade(MODE_RESULT);

		}
	}
}

//=========================================================================================================
// �Q�[����ʂ̕`�揈��
//=========================================================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	//Drawbackgraund();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//�v���C���[�̕`�揈��
	DrawPlayer();


	//�e�̕`�揈��
	//DrawBullet();

	//�G�̕`�揈��
	DrawEnemy();

	//�G�t�F�N�g�̕`�揈��
	//DrawEffect();

	//�X�R�A�̕`�揈��
	//DrawScore();

	//�����̕`�揈��
	//DrawExplosion();


	//if (g_bPause == true)												//�|�[�Y�����Ă��鎞
	//{												
	//	//�|�[�Y�̕`�揈��
	//	//DrawPause();
	//}
}

//=========================================================================================================
// �Q�[����ʂ̏�ԏ���
//=========================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}

//=========================================================================================================
// �Q�[����ʂ̏�Ԏ擾����
//=========================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=========================================================================================================
// �|�[�Y�̗L�������ݒ菈��
//=========================================================================================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}
