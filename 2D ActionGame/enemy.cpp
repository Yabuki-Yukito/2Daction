//=========================================================================================================
//
// �G�̏��� [enemy.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "enemy.h"
#include "player.h"
//#include "bullet.h"
//#include "score.h"

//=========================================================================================================
//���C���֐�
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_ENEMY (128)											//�G�̍ő吔
#define NUM_ENEMY (3)											//�G�̎��
#define SIZE (40)												//�G�̑傫��
#define TIME (5)												//����
#define SECONDS (30)											//�b��

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy;
Enemy g_aEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumEnemy = 0;											//�G�̑���

//=========================================================================================================
// �G�̏���������
//=========================================================================================================
void InitEnemy()
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//�e�N�X�`��(?����)�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\20211009-5.png",
		&g_apTextureEnemy[0]);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].BulletCounter = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	g_nNumEnemy = 0;											//�G(����)�̏�����

	//g_aEnemy[0].nScore = 500;
	//g_aEnemy[1].nScore = 1500;
	//g_aEnemy[2].nScore = 1000;

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�G���̏�����
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;												//���_�f�[�^�̃|�C���^��4����i�߂�

		//���_�����A�����b�N
		g_pVtxBuffEnemy->Unlock();
	}

}

//=========================================================================================================
// �G�̏I������
//=========================================================================================================
void UninitEnemy()
{
	int nCntbackgraund;											//�w�i�J�E���g

//�e�N�X�`��(?����)�̔j��
	for (nCntbackgraund = 0; nCntbackgraund < NUM_ENEMY; nCntbackgraund++)
	{
		if (g_apTextureEnemy[nCntbackgraund] != NULL)
		{
			g_apTextureEnemy[nCntbackgraund]->Release();
			g_apTextureEnemy[nCntbackgraund] = NULL;
		}

	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=========================================================================================================
// �G�̍X�V����
//=========================================================================================================
void UpdateEnemy(void)
{
	VERTEX_2D* pVtx;
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[nCntEnemy].BulletCounter++;
				if (g_aEnemy[nCntEnemy].BulletCounter >= SECONDS)	//��莞�Ԃ̌o��
				{
					//SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-7.0f, 0.0f, 0.0f),100, ENEMY_STATE_ENEMY);
					g_aEnemy[nCntEnemy].BulletCounter = 0;
				}
				break;

			case ENEMYSTATE_DAMEGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//���_�����A�����b�N
					g_pVtxBuffEnemy->Unlock();
				}
				break;
			}
		}
	}
}
//=========================================================================================================
// �G�̕`�揈��
//=========================================================================================================
void DrawEnemy()
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================
// �G�̐ݒ菈��
//=========================================================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int nLife)
{
	int nCntEnemy;

	VERTEX_2D* pVtx{};

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����ĂȂ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = nLife;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - SIZE, g_aEnemy[nCntEnemy].pos.y - SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + SIZE, g_aEnemy[nCntEnemy].pos.y - SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - SIZE, g_aEnemy[nCntEnemy].pos.y + SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + SIZE, g_aEnemy[nCntEnemy].pos.y + SIZE, 0.0f);

			//rhw tex��...

			g_aEnemy[nCntEnemy].bUse = true;

			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	//���_�����A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================
// �G�̎擾����
//=========================================================================================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];										//�G�̏���Ԃ�
}

//=========================================================================================================
// �G�̃q�b�g����
//=========================================================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx{};

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	//�G�̗̑͂�0�ɂȂ����Ƃ��̏���
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//�G�������鏈��
		g_aEnemy[nCntEnemy].bUse = false;

		g_nNumEnemy--;
		//AddScore(g_aEnemy[nCntEnemy].nScore);
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;			//�G���_���[�W���󂯂����
		g_aEnemy[nCntEnemy].nCounterState = TIME;				//�_���[�W��Ԃ�ۂ��Ԃ�ݒ�

		pVtx += 4 * nCntEnemy;									//�G���q�b�g������(4��)

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_�����A�����b�N
		g_pVtxBuffEnemy->Unlock();

	}
}

//=========================================================================================================
// �G�̐����擾���鏈��
//=========================================================================================================
int GetEnemyNum()
{
	return g_nNumEnemy;											//�G�̑�����Ԃ�
}

//=========================================================================================================
// �G�̓����蔻��
//=========================================================================================================
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	Player* pPlayer;											//�v���C���[���ւ̃|�C���^

	pPlayer = GetPlayer();										//�G���̐퓬�A�h���X����������

	bool bHit = false;	//���n���Ă��邩�ǂ���

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//���E�㉺�̓G�̓����蔻��
			if (pPos->x + PLAYER_WIDTH / 2 > g_aEnemy[nCntEnemy].pos.x - SIZE
				&& pPos->x - PLAYER_WIDTH / 2 < g_aEnemy[nCntEnemy].pos.x + SIZE)
			{
				if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - SIZE
					&& pPos->y > g_aEnemy[nCntEnemy].pos.y - SIZE)
				{
					bHit = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y - SIZE;
					pMove->y = 0.0f;

					HitEnemy(nCntEnemy, 5);
				}
				else if (pPosOld->y - PLAYER_HEIGHT >= g_aEnemy[nCntEnemy].pos.y + SIZE
					&& pPos->y - PLAYER_HEIGHT < g_aEnemy[nCntEnemy].pos.y + SIZE)
				{
					bHit = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y + SIZE - PLAYER_WIDTH;
					pMove->y = 0.0f;
				}
			}
			//�G��y(Old)�͈̔͂��u���b�N�ɏd�Ȃ��Ă��鎞�̓����蔻��
			if (pPosOld->y > g_aEnemy[nCntEnemy].pos.y - SIZE
				&& pPosOld->y - SIZE < g_aEnemy[nCntEnemy].pos.y + SIZE)
			{
				//�G��������E�̃u���b�N�ɂ߂荞��
				if (pPosOld->x + PLAYER_WIDTH / 2 <= g_aEnemy[nCntEnemy].pos.x - SIZE
					&& pPos->x + PLAYER_WIDTH / 2 > g_aEnemy[nCntEnemy].pos.x - SIZE)
				{
					pPos->x = g_aEnemy[nCntEnemy].pos.x - SIZE - PLAYER_WIDTH / 2;
					pMove->x = 0.0f;
				}
				//�G���E���獶�̃u���b�N�ɂ߂荞��
				if (pPosOld->x - PLAYER_WIDTH / 2 >= g_aEnemy[nCntEnemy].pos.x + SIZE
					&& pPos->x - PLAYER_WIDTH / 2 < g_aEnemy[nCntEnemy].pos.x + SIZE)
				{
					pPos->x = g_aEnemy[nCntEnemy].pos.x + SIZE + PLAYER_WIDTH / 2;
					pMove->x = 0.0f;
				}

				//HitPlayer(5);
			}
		}
	}
	return bHit;
}