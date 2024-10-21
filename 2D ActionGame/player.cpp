//=========================================================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "player.h"
#include "Input.h"
#include "Block.h"
#include "game.h"
#include "enemy.h"
//#include "Block.h"
//#include "result.h"

//=========================================================================================================
//���C���֐�
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define JP (-45)	//�W�����v��
#define GB (+3)		//�d��

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_pTextureplayer = NULL;						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;				//���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_player.pos;										//�v���C���[�̈ʒu
D3DXVECTOR3 g_movePlayer;										//�v���C���[�̈ړ���
D3DXVECTOR3 g_rotPlayer;										//�v���C���[�̌���
Player g_player;												//�v���C���[�̏��
int g_nCounterAnimPlayer = 0;									//�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer = 0;									//�A�j���[�V�����p�^�[����
float g_fLengthPlayer;											//�Ίp���̒���
float g_fAnglePlayer;											//�Ίp���̊p�x

//=========================================================================================================
// �v���C���[�̏���������
//=========================================================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\player000.png",
		&g_pTextureplayer);

	g_nCounterAnimPlayer = 0;									//�A�j���[�V�����J�E���^�[�̏�����
	g_nPatternAnimPlayer = 0;									//�A�j���[�V�����p�^�[���̏�����
	g_player.pos = D3DXVECTOR3(50.0f, 670.0f, 0.0f);			//�v���C���[�̈ʒu
	g_movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�v���C���[�̈ړ���
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�v���C���[�̑O��̈ʒu
	//g_player.nLife = 2;										//�v���C���[�̗̑�
	g_player.bDisp = true;										//�v���C���[���\�����Ă���Ƃ�
	g_player.bUse = true;										//�v���C���[���g�p����Ă���Ƃ�
	g_player.bRightMove = true;									//�v���C���[�����E�������Ă���Ƃ�
	g_player.bJump = false;										//�v���C���[���W�����v���ĂȂ��Ƃ�
	g_player.bStepOn = false;									//�v���C���[������ł��Ȃ��Ƃ�

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf(200.0f * 350.0f + 200.0f * 200.0f) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x - PLAYER_WIDTH;
	pVtx[0].pos.y = g_player.pos.y - PLAYER_HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + PLAYER_WIDTH;
	pVtx[1].pos.y = g_player.pos.y - PLAYER_HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - PLAYER_WIDTH;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + PLAYER_WIDTH;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);


	//���_�����A�����b�N
	g_pVtxBuffplayer->Unlock();

}

//=========================================================================================================
//�v���C���[�̏I������
//=========================================================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureplayer != NULL)

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffplayer != NULL)
		{
			g_pVtxBuffplayer->Release();
			g_pVtxBuffplayer = NULL;
		}
}

//=========================================================================================================
//�v���C���[�̍X�V����
//=========================================================================================================
void UpdatePlayer(void)
{

	//switch (g_player.state)
	//{
	//case PLAYERSTATE_APPEAR:

	//	break;

	//case PLAYERSTATE_NORMAL:

	//	break;

	//case PLAYERSTATE_DAMAGE:

	//	break;

	//case PLAYERSTATE_DEATH:

	//	break;

	//default:

	//	break;
	//}

	//�v���C���[���g�p����Ă��鎞
	if (g_player.bUse == true)
	{
		if (KeyboardRepeat(DIK_A) == true || JoypadPress(JOYKEY_PADLEFT) == true)
		{//A�L�[�������ꂽ
			g_movePlayer.x -= 1.0f;
			g_player.bRightMove = false;						//���������Ă�����
		}
		if (KeyboardRepeat(DIK_D) == true || JoypadPress(JOYKEY_PADRIGHT) == true)
		{//D�L�[�������ꂽ
			g_movePlayer.x += 1.0f;
			g_player.bRightMove = true;							//�E�������Ă�����
		}
		if (KeyboardTrigger(DIK_SPACE) == true || JoypadPress(JOYKEY_L3) == true || JoypadPress(JOYKEY_START) == true)
		{//SPACE�L�[
			if (g_player.bJump == false)
			{
				g_movePlayer.y = JP;
				g_player.bJump = true;
			}
		}
		g_movePlayer.y += GB;									//�d�͉��Z

		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		//�ʒu���X�V
		g_player.pos.x += g_movePlayer.x;
		g_player.pos.y += g_movePlayer.y;

		//�u���b�N�̓����蔻��
		if (CollisionBlock(
			&g_player.pos,		//���݂̈ʒu
			&g_player.posOld,	//�O��̈ʒu
			&g_movePlayer,		//�v���C���[�̈ړ���
			PLAYER_WIDTH, PLAYER_HEIGHT) == true)
		{
			g_player.bJump = false;
		}

		//�G�̓����蔻��
		if (CollisionEnemy(
			&g_player.pos,
			&g_player.posOld,
			&g_movePlayer) == true)
		{
			g_player.bStepOn = false;
			g_player.bJump = false;
		}

		//�ړ��ʂ��X�V(����)
		g_movePlayer.x += (0.0f - g_movePlayer.x) * 0.08f;
		//g_movePlayer.y += (0.0f - g_movePlayer.y) * 0.09f;

		//��ʊO�̏���
		if (g_player.pos.x >= SCREEN_WIDTH)						//��(�E)
		{
			g_player.pos.x = 0;
		}
		else if (g_player.pos.x <= 0)							//��(��)
		{
			g_player.pos.x = SCREEN_WIDTH;
		}
		if (g_player.pos.y >= SCREEN_HEIGHT)					//�n��
		{
			g_player.pos.y = SCREEN_HEIGHT;
			g_movePlayer.y = 0.0f;
			g_player.bJump = false;
		}
		else if (g_player.pos.y <= 0 + PLAYER_HEIGHT)			//��
		{
			g_player.pos.y = 0 + PLAYER_HEIGHT;
			g_movePlayer.y = 0;
		}

		//���_���ւ̃|�C���^
		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_player.pos.x - PLAYER_WIDTH / 2;
		pVtx[0].pos.y = g_player.pos.y - PLAYER_HEIGHT;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_player.pos.x + PLAYER_WIDTH / 2;
		pVtx[1].pos.y = g_player.pos.y - PLAYER_HEIGHT;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_player.pos.x - PLAYER_WIDTH / 2;
		pVtx[2].pos.y = g_player.pos.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_player.pos.x + PLAYER_WIDTH / 2;
		pVtx[3].pos.y = g_player.pos.y;
		pVtx[3].pos.z = 0.0f;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

		////�e�N�X�`�����W�̐ݒ�
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		//pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

		//���_�����A�����b�N
		g_pVtxBuffplayer->Unlock();
	}
	//g_nCounterAnimPlayer++;									//�J�E���^�[�����Z

	//if ((g_nCounterAnimPlayer % 8) == 0)
	//{
	//	g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 8;
	//	g_nCounterAnimPlayer = 0;								//�J�E���^�[�������l�ɖ߂�
	//	g_nPatternAnimPlayer++;									//�p�^�[����.���X�V

	//	if (g_nPatternAnimPlayer == 8)
	//	{
	//		g_nPatternAnimPlayer = 0;							//�p�^�[����.�������l�ɖ߂�
	//	}
	//}

}

//=========================================================================================================
//�v���C���[�̕`�揈��
//=========================================================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;									//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[���\�������Ƃ�
	//if (g_player.bDisp == true)
	//{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureplayer);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//}
}

//=========================================================================================================
//�v���C���[�̎擾����
//=========================================================================================================
Player* GetPlayer(void)
{
	return &g_player;											//�v���C���[�̏���Ԃ�
}

//=========================================================================================================
//�v���C���[�̃q�b�g����
//=========================================================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	VERTEX_2D* pVtx{};

	if (g_player.nLife <= 0)
	{
		//g_nNumEnemy--;

		g_player.bDisp = false;									//�v���C���[���\������ĂȂ���
		g_player.bUse = false;									//�v���C���[���g�p����Ă��Ȃ���
		g_player.state = PLAYERSTATE_DEATH;						//���S���
		g_player.nCounterState = 60;							//��ԊǗ�
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;					//�_���[�W���
		g_player.nCounterState = 5;								//�_���[�W��Ԃ�ۂ��Ԃ�ݒ�

		pVtx += 4 * nDamage;									//�v���C���[�̃q�b�g����(4��)

		//���_�o�b�t�@�����b�N
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_�����A�����b�N
		g_pVtxBuffplayer->Unlock();
	}
}
