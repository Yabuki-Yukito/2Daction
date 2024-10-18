////=========================================================================================================
////
//// �X�R�A�̏��� [score.cpp]
//// Author : yabuki yukito
////
////=========================================================================================================
//
//#include "score.h"
//
////=========================================================================================================
////���C���֐�
////=========================================================================================================
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////�}�N����`
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define MAX_NUM (8)										//�X�R�A�\���̍ő吔
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////�O���[�o���ϐ�
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//LPDIRECT3DTEXTURE9 g_TextureScore = NULL;				//�e�N�X�`���̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			//���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_posScore;									//�X�R�A�̈ʒu
//int g_nScore;											//�X�R�A�̒l
//
////=========================================================================================================
////�X�R�A�̏���������
////=========================================================================================================
//void InitScore(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\texture\\number000.png",
//		&g_TextureScore);
//
//	g_posScore = D3DXVECTOR3();							//�ʒu�̏�����
//	g_nScore = 0;										//�l��������
//
//	VERTEX_2D* pVtx;									//���_���ւ̃|�C���^
//
//		//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffScore,
//		NULL);
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCount = 0; nCount < MAX_NUM; nCount++)
//	{
//		//�X�R�A��
//		pVtx[0].pos = D3DXVECTOR3(950.0f  + nCount * 40.0f , 0.0f , 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(990.0f + nCount * 40.0f , 0.0f , 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(950.0f  + nCount * 40.0f , 50.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(990.0f + nCount * 40.0f , 50.0f, 0.0f);
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
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f);
//		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.1f);
//
//		pVtx += 4;
//	}
//
//		//���_�����A�����b�N
//		g_pVtxBuffScore->Unlock();
//}
//
////=========================================================================================================
////�X�R�A�̏I������
////=========================================================================================================
//void UninitScore(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_TextureScore != NULL)
//	{
//		g_TextureScore->Release();
//		g_TextureScore = NULL;
//	}
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffScore != NULL)
//	{
//		g_pVtxBuffScore->Release();
//		g_pVtxBuffScore = NULL;
//	}
//}
//
////=========================================================================================================
////�X�R�A�̍X�V����
////=========================================================================================================
//void UpdateScore(void)
//{
//
//}
//
////=========================================================================================================
////�X�R�A�̕`�揈��
////=========================================================================================================
//void DrawScore(void)
//{
//	//�K�v�������̕`��
//	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�ւ̃|�C���^
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	for (int nCount = 0; nCount < MAX_NUM; nCount++)
//	{
//		//�e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, g_TextureScore);
//
//		//�e�N�X�`���̕`��
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCount *4,2);
//	}
//
//
//}
//
////=========================================================================================================
////�X�R�A�̐ݒ菈��
////=========================================================================================================
//void SetScore(int nScore)
//{
//	VERTEX_2D* pVtx{};									//���_���ւ̃|�C���^
//	int aPosTexU[8]{};									//�e���̐������i�[����
//	g_nScore = nScore;									//�X�R�A�̒l��ݒ�
//
//	aPosTexU[0] = g_nScore % 100000000/ 10000000;
//	aPosTexU[1]	= g_nScore % 10000000/ 1000000;
//	aPosTexU[2]	= g_nScore % 1000000/ 100000;
//	aPosTexU[3]	= g_nScore % 100000/ 10000;
//	aPosTexU[4]	= g_nScore % 10000/ 1000;
//	aPosTexU[5]	= g_nScore % 1000/ 100;
//	aPosTexU[6]	= g_nScore % 100/ 10;
//	aPosTexU[7]	= g_nScore % 10/ 1;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCount = 0; nCount < MAX_NUM; nCount++)
//	{
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCount] * 0.1f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCount] * 0.1f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCount] * 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCount] * 0.1f, 1.0f);
//
//		pVtx += 4;
//	}			
//	//���_�����A�����b�N
//	g_pVtxBuffScore->Unlock();
//}
//
////=========================================================================================================
////�X�R�A�̉��Z����
////=========================================================================================================
//void AddScore(int nValue)
//{
//	VERTEX_2D* pVtx{};									//���_���ւ̃|�C���^
//
//	int aPosTexU[8]{};									//�e���̐������i�[����
//	g_nScore += nValue;									//�X�R�A�̒l�����Z����
//
//	aPosTexU[0] = g_nScore % 100000000 / 10000000;
//	aPosTexU[1] = g_nScore % 10000000 / 1000000;
//	aPosTexU[2] = g_nScore % 1000000 / 100000;
//	aPosTexU[3] = g_nScore % 100000 / 10000;
//	aPosTexU[4] = g_nScore % 10000 / 1000;
//	aPosTexU[5] = g_nScore % 1000 / 100;
//	aPosTexU[6] = g_nScore % 100 / 10;
//	aPosTexU[7] = g_nScore % 10 / 1;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCount = 0; nCount < MAX_NUM; nCount++)
//	{
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCount] * 0.1f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCount] * 0.1f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCount] * 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCount] * 0.1f, 1.0f);
//
//		pVtx += 4;
//	}
//
//	//���_�����A�����b�N
//	g_pVtxBuffScore->Unlock();
//}
//
////=========================================================================================================
////�X�R�A�̎擾����
////=========================================================================================================
//int GetScore(void)
//{
//	return g_nScore;									//�X�R�A�̒l��Ԃ�
//}
