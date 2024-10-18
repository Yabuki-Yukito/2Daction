////=========================================================================================================
////
//// �G�t�F�N�g�̏��� [effect.cpp]
//// Author : yabuki yukito
////
////=========================================================================================================
//
////#include "bullet.h"
////#include "explosion.h"
//#include "enemy.h"
//#include "player.h"
//
////=========================================================================================================
////���C���֐�
////=========================================================================================================
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////�}�N����`
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define MAX_EFFECT (4096)											//�G�t�F�N�g�̍ő吔
//#define MAX_SCREENWIDTH	(1280)										//����
//#define MAX_SCREENHEIGHT (720)										//����
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////�G�t�F�N�g�e�\���̂̒�`
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//typedef struct
//{
//	D3DXVECTOR3 pos;												//�ʒu
//	D3DXVECTOR3 move;												//�ړ���
//	D3DXCOLOR col;													//�F
//	float fRadius;													//���a(�傫��)
//	int nLife;														//����
//	bool bUse;														//�g�p���Ă��邩�ǂ���
//}Effect;
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////�O���[�o���ϐ�
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;							//�e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;					//���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_posEffect;											//�G�t�F�N�g�̈ʒu
//D3DXVECTOR3 g_rotEffect;											//�G�t�F�N�g�̊p�x(����)
//float g_fAngleEffect;												//�G�t�F�N�g�̑Ίp���̊p�x
//float g_fLengthEffect;												//�G�t�F�N�g�̑Ίp���̒���
//Effect g_aEffect[MAX_EFFECT];										//�G�t�F�N�g�̑������
//
////=========================================================================================================
////�G�t�F�N�g�̏���������
////=========================================================================================================
//void InitEffect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntEffect;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\texture\\effect000.jpg",
//		&g_pTextureEffect);
//
//	//�G�t�F�N�g���̏�����
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{
//		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�t�F�N�g�̈ʒu
//		g_aEffect[nCntEffect].nLife = 0;							//�G�t�F�N�g�̎���(�̗�)
//		g_aEffect[nCntEffect].bUse = false;							//�G�t�F�N�g���g�p���Ă��Ȃ���Ԃɂ���
//	}
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffEffect,
//		NULL);
//
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N
//	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{
//		//���_���W�̐ݒ�(�G�t�F�N�g)
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;													//���_�f�[�^�̃|�C���^��4���i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffEffect->Unlock();
//
//}
//
////=========================================================================================================
////�G�t�F�N�g�̏I������
////=========================================================================================================
//void UninitEffect(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_pTextureEffect != NULL)
//	{
//		g_pTextureEffect->Release();
//		g_pTextureEffect = NULL;
//	}
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffEffect != NULL)
//	{
//		g_pVtxBuffEffect->Release();
//		g_pVtxBuffEffect = NULL;
//	}
//}
//
////=========================================================================================================
////�G�t�F�N�g�̍X�V����
////=========================================================================================================
//void UpdateEffect(void)
//{
//	int nCntEffect;
//	VERTEX_2D* pVtx = 0;
//
//	//���_�o�b�t�@�����b�N
//	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{//�G�t�F�N�g���g�p����Ă���
//		if (g_aEffect[nCntEffect].bUse == true)
//		{
//			//���_���W�̍X�V
//			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//
//			if (g_aEffect[nCntEffect].pos.x <= 0.0f || g_aEffect[nCntEffect].pos.x >= MAX_SCREENWIDTH
//				|| g_aEffect[nCntEffect].pos.y <= 0.0f || g_aEffect[nCntEffect].pos.y >= MAX_SCREENHEIGHT)
//			{
//				g_aEffect[nCntEffect].bUse = false;			//�g�p���Ă��Ȃ���Ԃɂ���
//			}
//
//			g_aEffect[nCntEffect].nLife--;
//
//			if (g_aEffect[nCntEffect].nLife <= 0)			//������0��
//			{
//				g_aEffect[nCntEffect].bUse = false;			//�g�p���Ă��Ȃ���Ԃɂ���
//			}
//		}
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffEffect->Unlock();
//}
//
////=========================================================================================================
////�G�t�F�N�g�̕`�揈��
////=========================================================================================================
//void DrawEffect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice{};
//	int nCntEffect;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//a�u�����f�B���O�����Z�����ɐݒ�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{//�G�t�F�N�g���g�p���Ă��鎞
//		if (g_aEffect[nCntEffect].bUse == true)
//		{
//			//�e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, g_pTextureEffect);
//
//			//�|���S���̕`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
//		}
//	}
//
//	//a�u�����f�B���O�����ɖ߂�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//}
//
////=========================================================================================================
////�G�t�F�N�g�̐ݒ菈��
////=========================================================================================================
//void SetEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col, float fRadius,int nLife)
//{
//	int nCntEffect;
//	VERTEX_2D* pVtx = 0;
//
//	//���_�o�b�t�@�����b�N
//	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{//�G�t�F�N�g���g�p���Ă��Ȃ���
//		if (g_aEffect[nCntEffect].bUse == false)
//		{
//			//�G�t�F�N�g���g�p����Ă��Ȃ�
//			g_aEffect[nCntEffect].pos = pos;
//			g_aEffect[nCntEffect].col = col;
//			g_aEffect[nCntEffect].fRadius = fRadius;
//			g_aEffect[nCntEffect].nLife = nLife;
//
//			//���_���W�̐ݒ�
//			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//
//			//���_�J���[�̐ݒ�
//			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//
//			g_aEffect[nCntEffect].bUse = true;							//�g�p����Ă����Ԃɂ���
//			break;
//		}
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffEffect->Unlock();
//}