//=========================================================================================================
//
// ���U���g�̏��� [result.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "result.h"
#include "Input.h"
#include "fade.h"

//=========================================================================================================
//���C���֐�
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//�e�N�X�`���̃|�C���^(���U���g)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//���_�o�b�t�@�ւ̃|�C���^(���U���g)
RESULT g_Result = RESULT_LOSE;

//=========================================================================================================
// ���U���g��ʂ̏���������
//=========================================================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_Result == RESULT_WIN)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\texture\\result.png",
			&g_pTextureResult);
	}
	else if (g_Result == RESULT_LOSE)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\texture\\GameOver.png",
			&g_pTextureResult);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	g_Result = RESULT_LOSE;								//���U���g�̏�����

	VERTEX_2D* pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���U���g)
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�����A�����b�N
	g_pVtxBuffResult->Unlock();
}

//=========================================================================================================
// ���U���g��ʂ̏I������
//=========================================================================================================
void UninitResult(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffResult != NULL)
		{
			g_pVtxBuffResult->Release();
			g_pVtxBuffResult = NULL;
		}

}

//=========================================================================================================
// ���U���g��ʂ̍X�V����
//=========================================================================================================
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_TITLE);
	}
}

//=========================================================================================================
// ���U���g��ʂ̕`�揈��
//=========================================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=========================================================================================================
// ���U���g��ʂ̌��ʏ���
//=========================================================================================================
void SetResult(RESULT result)
{
	g_Result = result;
}
