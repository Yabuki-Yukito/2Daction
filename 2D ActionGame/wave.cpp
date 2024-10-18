//=========================================================================================================
////
//// �E�F�[�u�̏��� [wave.cpp]
//// Author : yabuki yukito
////
//=========================================================================================================

//#include "wave.h"
//#include "enemy.h"
//#include <stdio.h>
//
////�}�N����`
//
//#define MAX_WORD (256)
//#define WAVE_0 "data\\Wave0.txt"
//#define WAVE_1 "data\\Wave1.txt"
//
////�E�F�[�u�̍\����
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 move;
//	int nType;
//	bool bUse;
//}Load;
//
////�O���[�o���ϐ�
//
//Load g_Load[MAX_ENEMY];
//int g_nCntEnemy;
//int g_nWave;
//bool g_bfinish;
//
////�E�F�[�u�̏���������
//void InitWave(void)
//{
//	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
//	{
//		g_Load[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_Load[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_Load[nCnt].nType = 0;
//		g_Load[nCnt].bUse = false;
//	}
//	g_nCntEnemy = 0;
//	g_nWave = 0;
//	g_bfinish = false;
//}
//
////�E�F�[�u�̓Ǎ�����
//void LoadWave(void)
//{
//	FILE* pFile;
//
//	int nType = 0, nLife = 0;
//	D3DXVECTOR3 pos = {};
//
//	//�G�̐�
//	g_nCntEnemy = GetEnemyNum();
//
//	//�e�E�F�[�u�̃t�@�C�����J��
//	switch (g_nWave)
//	{
//	case 0: //�E�F�[�u0
//
//		pFile = fopen(WAVE_0, "r");
//		break;
//
//	case 1:
//
//		pFile = fopen(WAVE_1, "r");
//		break;
//
//	default:
//
//		pFile = NULL;
//
//		g_bfinish = true;
//
//		break;
//	}
//
//	if (pFile != NULL)
//	{
//		while (1)
//		{
//			char aString[MAX_WORD];
//
//			//�t�@�C���Ǎ�
//			fscanf(pFile, "%s", &aString[0]);
//			if (strcmp(aString, "ENEMYSET") == 0)
//			{
//				while (1)
//				{
//					//�t�@�C���Ǎ�
//					fscanf(pFile, "%s", &aString[0]);
//
//					if (strcmp(aString, "TYPE") == 0)
//					{
//						//���
//						fscanf(pFile, "%d", &nType);
//					}
//					else if (strcmp(aString, "POS") == 0)
//					{
//						//�ʒu�̎擾
//						fscanf(pFile, "%f", &pos.x);
//						fscanf(pFile, "%f", &pos.y);
//						fscanf(pFile, "%f", &pos.z);
//					}
//					else if (strcmp(aString, "END_ENEMYSET") == 0)
//					{
//						//�G�̐ݒ�
//						SetEnemy(pos, nType);
//
//						break;
//					}
//				}
//			}
//			if (strcmp(aString, "END_SCRIPI") == 0)
//			{
//				break;
//			}
//
//		}
//		//�t�@�C�������
//		fclose(pFile);
//
//		//�E�F�[�u�̃J�E���g
//		g_nWave++;
//
//	}
//	else
//	{
//		return;
//	}
//
//}
//
////�E�F�[�u���̎擾����
//int GetWave(void)
//{
//	return g_nWave;
//}
//
////�E�F�[�u�I���̎擾����
//bool GetFinish(void)
//{
//	return g_bfinish;
//}