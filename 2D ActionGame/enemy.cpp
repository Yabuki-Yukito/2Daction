//=========================================================================================================
//
// 敵の処理 [enemy.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "enemy.h"
#include "player.h"
//#include "bullet.h"
//#include "score.h"

//=========================================================================================================
//メイン関数
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_ENEMY (128)											//敵の最大数
#define NUM_ENEMY (3)											//敵の種類
#define SIZE (40)												//敵の大きさ
#define TIME (5)												//時間
#define SECONDS (30)											//秒数

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy;
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報
int g_nNumEnemy = 0;											//敵の総数

//=========================================================================================================
// 敵の初期化処理
//=========================================================================================================
void InitEnemy()
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//テクスチャ(?枚分)の読み込み
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

	g_nNumEnemy = 0;											//敵(複数)の初期化

	//g_aEnemy[0].nScore = 500;
	//g_aEnemy[1].nScore = 1500;
	//g_aEnemy[2].nScore = 1000;

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//敵情報の初期化
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;												//頂点データのポインタを4つ分を進める

		//頂点情報をアンロック
		g_pVtxBuffEnemy->Unlock();
	}

}

//=========================================================================================================
// 敵の終了処理
//=========================================================================================================
void UninitEnemy()
{
	int nCntbackgraund;											//背景カウント

//テクスチャ(?枚分)の破棄
	for (nCntbackgraund = 0; nCntbackgraund < NUM_ENEMY; nCntbackgraund++)
	{
		if (g_apTextureEnemy[nCntbackgraund] != NULL)
		{
			g_apTextureEnemy[nCntbackgraund]->Release();
			g_apTextureEnemy[nCntbackgraund] = NULL;
		}

	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=========================================================================================================
// 敵の更新処理
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
				if (g_aEnemy[nCntEnemy].BulletCounter >= SECONDS)	//一定時間の経過
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

					//頂点バッファをロックし、頂点情報へのポインタを取得
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//頂点情報をアンロック
					g_pVtxBuffEnemy->Unlock();
				}
				break;
			}
		}
	}
}
//=========================================================================================================
// 敵の描画処理
//=========================================================================================================
void DrawEnemy()
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================
// 敵の設定処理
//=========================================================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int nLife)
{
	int nCntEnemy;

	VERTEX_2D* pVtx{};

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されてない
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = nLife;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - SIZE, g_aEnemy[nCntEnemy].pos.y - SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + SIZE, g_aEnemy[nCntEnemy].pos.y - SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - SIZE, g_aEnemy[nCntEnemy].pos.y + SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + SIZE, g_aEnemy[nCntEnemy].pos.y + SIZE, 0.0f);

			//rhw tex等...

			g_aEnemy[nCntEnemy].bUse = true;

			g_nNumEnemy++;
			break;
		}
		pVtx += 4;
	}
	//頂点情報をアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================
// 敵の取得処理
//=========================================================================================================
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];										//敵の情報を返す
}

//=========================================================================================================
// 敵のヒット処理
//=========================================================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx{};

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	//敵の体力が0になったときの処理
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//敵が消える処理
		g_aEnemy[nCntEnemy].bUse = false;

		g_nNumEnemy--;
		//AddScore(g_aEnemy[nCntEnemy].nScore);
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;			//敵がダメージを受けた状態
		g_aEnemy[nCntEnemy].nCounterState = TIME;				//ダメージ状態を保つ時間を設定

		pVtx += 4 * nCntEnemy;									//敵がヒットした時(4つ分)

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//頂点情報をアンロック
		g_pVtxBuffEnemy->Unlock();

	}
}

//=========================================================================================================
// 敵の数を取得する処理
//=========================================================================================================
int GetEnemyNum()
{
	return g_nNumEnemy;											//敵の総数を返す
}

//=========================================================================================================
// 敵の当たり判定
//=========================================================================================================
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	Player* pPlayer;											//プレイヤー情報へのポインタ

	pPlayer = GetPlayer();										//敵情報の戦闘アドレスが代入される

	bool bHit = false;	//着地しているかどうか

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//左右上下の敵の当たり判定
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
			//敵のy(Old)の範囲がブロックに重なっている時の当たり判定
			if (pPosOld->y > g_aEnemy[nCntEnemy].pos.y - SIZE
				&& pPosOld->y - SIZE < g_aEnemy[nCntEnemy].pos.y + SIZE)
			{
				//敵が左から右のブロックにめり込んだ
				if (pPosOld->x + PLAYER_WIDTH / 2 <= g_aEnemy[nCntEnemy].pos.x - SIZE
					&& pPos->x + PLAYER_WIDTH / 2 > g_aEnemy[nCntEnemy].pos.x - SIZE)
				{
					pPos->x = g_aEnemy[nCntEnemy].pos.x - SIZE - PLAYER_WIDTH / 2;
					pMove->x = 0.0f;
				}
				//敵が右から左のブロックにめり込んだ
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