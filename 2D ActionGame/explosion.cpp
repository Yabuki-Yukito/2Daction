//#include "explosion.h"
//
////�}�N����`
//#define MAX_EXPLOSION (128) //�����̍ő吔
//
////�e�\���̂̒�`
//typedef struct
//{
//	D3DXVECTOR3 pos; //�ʒu
//	D3DXCOLOR col; //�F
//	int nCounterAnim ; //�A�j���[�V�����J�E���^�[
//	int nPatternAnim ; //�A�j���[�V�����p�^�[����
//	bool bUse; //�g�p���Ă��邩�ǂ���
//}Explosion;
//
////�O���[�o���ϐ�
//LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
//Explosion g_aExplosion[MAX_EXPLOSION]; //�����̏��
//int g_nCounterAnimExplosion=0; //�A�j���[�V�����J�E���^�[
//int g_nPatternAnimExplosion=0; //�A�j���[�V�����p�^�[����
//
////�e�̏���������
//void InitExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntExplosion;
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\texture\\explosion000.png",
//		&g_pTextureExplosion);
//
//	//�e���̏�����
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aExplosion[nCntExplosion].col = (0.0f, 0.0f, 0.0f);
//		g_aExplosion[nCntExplosion].bUse = false; //�g�p���Ă��Ȃ���Ԃɂ���
//	}
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffExplosion,
//		NULL);
//
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 20.0f, g_aExplosion[nCntExplosion].pos.y - 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 20.0f, g_aExplosion[nCntExplosion].pos.y - 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 20.0f, g_aExplosion[nCntExplosion].pos.y + 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 20.0f, g_aExplosion[nCntExplosion].pos.y + 20.0f, 0.0f);
//
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
//
//		pVtx += 4; //���_�f�[�^�̃|�C���^��4���i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffExplosion->Unlock();
//
//}
////�e�̏I������
//void UninitExplosion(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_pTextureExplosion != NULL)
//	{
//		g_pTextureExplosion->Release();
//		g_pTextureExplosion = NULL;
//	}
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffExplosion != NULL)
//	{
//		g_pVtxBuffExplosion->Release();
//		g_pVtxBuffExplosion = NULL;
//	}
//}
////�e�̍X�V����
//void UpdateExplosion(void)
//{
//	int nCntExplosion;
//	VERTEX_2D* pVtx = 0;
//
//	//���_�o�b�t�@�����b�N
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntExplosion].bUse == true)
//		{//�������g�p����Ă���
//
//			g_nCounterAnimExplosion++; //�J�E���^�[�����Z
//
//			if ((g_nCounterAnimExplosion % 8) == 0)
//			{
//				g_nCounterAnimExplosion = 0; //�J�E���^�[�����Z
//				g_nPatternAnimExplosion = (g_nPatternAnimExplosion + 1) % 8;
//				g_nCounterAnimExplosion = 0; //�J�E���^�[�������l�ɖ߂�
//				g_nPatternAnimExplosion++; //�p�^�[�������X�V
//
//				if (g_nPatternAnimExplosion == 8)
//				{
//					g_nPatternAnimExplosion = 0; //�p�^�[����.�������l�ɖ߂�
//				}
//
//				//�e�N�X�`���̍��W�̍X�V
//				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].pos.x + 0.0f, 0.0f);
//				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].pos.x + 1.0f, 0.0f);
//				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].pos.x - 0.0f, 1.0f);
//				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].pos.x + 1.0f, 1.0f);
//			}
//			pVtx += 4;
//		}
//		//���_�o�b�t�@���A�����b�N
//		g_pVtxBuffExplosion->Unlock();
//	}
//}
////�e�̕`�揈��
//void DrawExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice{};
//	int nCntExplosion;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
//	
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//	
//	//�e�N�X�`���̐ݒ�
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntExplosion].bUse == true)
//		{
//			//�e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, g_pTextureExplosion);
//
//			//�e���g�p����Ă���
//			//�|���S���̕`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//										  nCntExplosion*4,
//													2);		
//		}
//	}
//}
////�e�̐ݒ菈��
//void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 col)
//{
//	int nCntExplosion;
//	VERTEX_2D* pVtx = 0;
//
//	//���_�o�b�t�@
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntExplosion].bUse == false)
//		{
//			//�������g�p����Ă��Ȃ�
//			g_aExplosion[nCntExplosion].pos = pos;
//			//g_aExplosion[nCntExplosion].col = move;
//			g_aExplosion[nCntExplosion].bUse = false;
//
//			//���_���W�̐ݒ�
//			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10.0f, g_aExplosion[nCntExplosion].pos.y - 10.0f, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 10.0f, g_aExplosion[nCntExplosion].pos.y - 10.0f, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10.0f, g_aExplosion[nCntExplosion].pos.y + 10.0f, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 10.0f, g_aExplosion[nCntExplosion].pos.y + 10.0f, 0.0f);
//
//			//g_aExplosion[nCntExplosion].col = move;
//			g_aExplosion[nCntExplosion].bUse = true; //�g�p����Ă����Ԃɂ���
//			break;
//		}
//		pVtx += 4;
//	}
//}