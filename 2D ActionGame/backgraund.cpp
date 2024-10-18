////=========================================================================================================
////
//// �w�i�̏��� [backgraund.cpp]
//// Author : yabuki yukito
////
////=========================================================================================================
//
//#include "backgraund.h"
//
////=========================================================================================================
////���C���֐�
////=========================================================================================================
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////�}�N����`
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define NUM_BACKGURAUND (3)												//�w�i�̖���
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////�O���[�o���ϐ�
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//LPDIRECT3DTEXTURE9 g_apTexturebackgraund[NUM_BACKGURAUND] = {};			//�e�N�X�`��(3�����j�ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbackgraund = NULL;					//���_�o�b�t�@�ւ̃|�C���^
//float g_aPosTexU[NUM_BACKGURAUND];										//�e�N�X�`�����W�̊J�n�ʒu(U�l)
//
////=========================================================================================================
////�w�i�̏���������
////=========================================================================================================
//void Initbackgraund(void)
//{
//	LPDIRECT3DDEVICE9 pDevice2;
//	int nCntbackgraund;
//
//	//�f�o�C�X�̎擾
//	pDevice2 = GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice2,
//		"data\\texture\\bg100.png",
//		&g_apTexturebackgraund[0]);
//
//	//�e�N�X�`���̓ǂݍ���2
//	D3DXCreateTextureFromFile(pDevice2,
//		"data\\texture\\Galaxy.png",
//		&g_apTexturebackgraund[1]);
//
//	//�e�N�X�`���̓ǂݍ���3
//	D3DXCreateTextureFromFile(pDevice2,
//		"data\\texture\\bg102.png",
//		&g_apTexturebackgraund[2]);
//
//
//	//�e�N�X�`�����W�̊J�n�ʒu(U�l)�̏����l
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		g_aPosTexU[nCntbackgraund] = 0.0f;
//	}
//
//	//���_�o�b�t�@�̐���
//	pDevice2->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*NUM_BACKGURAUND,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffbackgraund,
//		NULL);
//
//	VERTEX_2D* pVtx;													//���_���ւ̃|�C���^
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffbackgraund->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		//���_���W�̐ݒ�(�w�i)
//		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
//
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 1.0f);
//
//		pVtx += 4;															//���_�f�[�^�̃|�C���^��4����i�߂�
//	}
//	//���_�����A�����b�N
//	g_pVtxBuffbackgraund->Unlock();
//}
//
////=========================================================================================================
////�w�i�̏I������
////=========================================================================================================
//void Uninitbackgraund(void)
//{
//	int nCntbackgraund;													//�w�i�J�E���g
//
//	//�e�N�X�`��(3����)�̔j��
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		if (g_apTexturebackgraund[nCntbackgraund] != NULL)
//		{
//			g_apTexturebackgraund[nCntbackgraund]->Release();
//			g_apTexturebackgraund[nCntbackgraund] = NULL;
//		}
//
//	}
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffbackgraund != NULL)
//	{
//		g_pVtxBuffbackgraund->Release();
//		g_pVtxBuffbackgraund = NULL;
//	}
//}
//
////=========================================================================================================
////�w�i�̍X�V����
////=========================================================================================================
//void Updatebackgraund(void)
//{
//	int nCntbackgraund;
//
//	VERTEX_2D* pVtx;													//���_���ւ̃|�C���^
//
//	//�w�i�e�N�X�`��
//	g_aPosTexU[0] -= 0.0030f;											//1���ڂ̈ړ��X�s�[�h
//	g_aPosTexU[1] -= 0.0030f;											//2���ڂ̈ړ��X�s�[�h
//	g_aPosTexU[2] -= 0.0030f;											//3���ڂ̈ړ��X�s�[�h
//
////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffbackgraund->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 1.0f);
//
//		pVtx += 4;														//4��
//	}
//	//���_�����A�����b�N
//	g_pVtxBuffbackgraund->Unlock();
//}
//
////=========================================================================================================
////�w�i�̕`�揈��
////=========================================================================================================
//void Drawbackgraund(void)
//{
//	LPDIRECT3DDEVICE9 pDevice2;
//	int nCntbackgraund;
//
//	//�f�o�C�X�̎擾
//	pDevice2 = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice2->SetStreamSource(0, g_pVtxBuffbackgraund, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice2->SetFVF(FVF_VERTEX_2D);
//
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		//�e�N�X�`���̐ݒ�
//		pDevice2->SetTexture(0,	g_apTexturebackgraund[nCntbackgraund]);				
//
//		//�w�i�̕`��
//		pDevice2->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntbackgraund*4, 2);
//
//	}
//}
//
