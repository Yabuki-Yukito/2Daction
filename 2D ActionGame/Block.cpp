//=========================================================================================================
//
// �u���b�N�̏��� [Block.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "Block.h"
//#include "explosion.h"
//#include "enemy.h"
//#include "effect.h"

//=========================================================================================================
//���C���֐�
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_BLOCK (128)													//�ʂ̍ő吔
#define WIDTH (100.0f)													//��
#define HEIGHT (100.0f)													//����

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�u���b�N�\���̂̒�`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;													//�ʒu
	D3DXVECTOR3 move;													//�ړ�
	float fWidth;														//�v���C���[�̕�
	float fHeight;														//�v���C���[�̍���
	int nLife;															//����
	BlockTYPE type;														//�u���b�N�̎��
	bool bUse;															//�g�p���Ă��邩�ǂ���
}Block;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;								//�e�N�X�`���ւ̃|�C���^(�u���b�N)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;							//���_�J���[�ւ̃|�C���^(�u���b�N)
D3DXVECTOR3 g_posBlock;													//�u���b�N�̈ʒu
D3DXVECTOR3 g_rotBlock;													//�u���b�N�̊p�x(����)
float g_fAngleBlock;													//�u���b�N�̑Ίp���̊p�x
float g_fLengthBlock;													//�u���b�N�̑Ίp���̒���
Block g_aBlock[MAX_BLOCK];												//�u���b�N�̑������

//=========================================================================================================
// �u���b�N�̏���������
//=========================================================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\block000.jpg",
		&g_pTextureBlock);

	//�u���b�N���̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�u���b�N�̑����̈ʒu
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�u���b�N�̑����̈ړ���
		g_aBlock[nCntBlock].nLife = 100;								//�u���b�N�̑����̎���(�̗�)
		g_aBlock[nCntBlock].bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 15.0f, g_aBlock[nCntBlock].pos.y - 15.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 15.0f, g_aBlock[nCntBlock].pos.y - 15.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 15.0f, g_aBlock[nCntBlock].pos.y + 15.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 15.0f, g_aBlock[nCntBlock].pos.y + 15.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;														//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

}

//=========================================================================================================
// �u���b�N�̏I������
//=========================================================================================================
void UninitBlock(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=========================================================================================================
// �u���b�N�̍X�V����
//=========================================================================================================
void UpdateBlock(void)
{

}

//=========================================================================================================
// �u���b�N�̕`�揈��
//=========================================================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice{};
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�u���b�N���g�p����Ă���Ƃ�
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);

		}
	}
}

//=========================================================================================================
// �u���b�N�̐ݒ菈��
//=========================================================================================================
void SetBlock(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	int nCntBlock;
	VERTEX_2D* pVtx = 0;

	//���_�o�b�t�@�����b�N����
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�u���b�N���g�p����Ă��Ȃ�
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].bUse = true;						//�g�p����Ă����Ԃɂ���

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=========================================================================================================
// �u���b�N�̓����蔻��
//=========================================================================================================
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
	bool bLanding = false;	//���n���Ă��邩�ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//���E�̓����蔻��
			if (pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth
				&& pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{
				//��̓����蔻��
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight
					&& pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
					pMove->y = 0.0f;
				}
				//���̓����蔻��
				else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
					&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight;
					pMove->y = 0.0f;
					bLanding = false;
				}
			}
			//�v���C���[��y(Old)�͈̔͂��u���b�N�ɏd�Ȃ��Ă��鎞�̓����蔻��
			if (pPosOld->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight
				&& pPosOld->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{
				//X��������E�̃u���b�N�ɂ߂荞��
				if (pPosOld->x + fWidth / 2 <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth
					&& pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - fWidth / 2;
					pMove->x = 0.0f;
				}
				//X���E���獶�̃u���b�N�ɂ߂荞��
				if (pPosOld->x - fWidth / 2 >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
					&& pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth / 2;
					pMove->x = 0.0f;
				}
			}
		}
	}
	return bLanding;
}