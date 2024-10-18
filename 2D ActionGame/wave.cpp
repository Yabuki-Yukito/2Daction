//=========================================================================================================
////
//// ウェーブの処理 [wave.cpp]
//// Author : yabuki yukito
////
//=========================================================================================================

//#include "wave.h"
//#include "enemy.h"
//#include <stdio.h>
//
////マクロ定義
//
//#define MAX_WORD (256)
//#define WAVE_0 "data\\Wave0.txt"
//#define WAVE_1 "data\\Wave1.txt"
//
////ウェーブの構造体
//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 move;
//	int nType;
//	bool bUse;
//}Load;
//
////グローバル変数
//
//Load g_Load[MAX_ENEMY];
//int g_nCntEnemy;
//int g_nWave;
//bool g_bfinish;
//
////ウェーブの初期化処理
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
////ウェーブの読込処理
//void LoadWave(void)
//{
//	FILE* pFile;
//
//	int nType = 0, nLife = 0;
//	D3DXVECTOR3 pos = {};
//
//	//敵の数
//	g_nCntEnemy = GetEnemyNum();
//
//	//各ウェーブのファイルを開く
//	switch (g_nWave)
//	{
//	case 0: //ウェーブ0
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
//			//ファイル読込
//			fscanf(pFile, "%s", &aString[0]);
//			if (strcmp(aString, "ENEMYSET") == 0)
//			{
//				while (1)
//				{
//					//ファイル読込
//					fscanf(pFile, "%s", &aString[0]);
//
//					if (strcmp(aString, "TYPE") == 0)
//					{
//						//種類
//						fscanf(pFile, "%d", &nType);
//					}
//					else if (strcmp(aString, "POS") == 0)
//					{
//						//位置の取得
//						fscanf(pFile, "%f", &pos.x);
//						fscanf(pFile, "%f", &pos.y);
//						fscanf(pFile, "%f", &pos.z);
//					}
//					else if (strcmp(aString, "END_ENEMYSET") == 0)
//					{
//						//敵の設定
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
//		//ファイルを閉じる
//		fclose(pFile);
//
//		//ウェーブのカウント
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
////ウェーブ数の取得処理
//int GetWave(void)
//{
//	return g_nWave;
//}
//
////ウェーブ終了の取得処理
//bool GetFinish(void)
//{
//	return g_bfinish;
//}