//=========================================================================================================
//
// 敵の処理 [enemy.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "enemy.h"
#include "player.h"
#include "score.h"
#include "Block.h"
//#include "bullet.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_ENEMY (128)											//敵の最大数
#define NUM_ENEMY (4)											//敵の種類
#define ENEMY_WIDTH (40)										//敵の大きさ(横)
#define ENEMY_HEIGHT (80)										//敵の大きさ(縦)
#define TIME (5)												//時間
#define SECONDS (30)											//秒数

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy;
D3DXVECTOR3 g_moveEnemy;										//敵の移動量
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報(最大数)
//Enemy g_Enemy;													//敵の情報
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

	//敵のテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Enemy.png",
		&g_apTextureEnemy[0]);

	//2体目
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Enemy1.png",
		&g_apTextureEnemy[1]);

	//3体目
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Enemy2.png",
		&g_apTextureEnemy[2]);

	//4体目
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Enemy3.png",
		& g_apTextureEnemy[3]);


	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].Counter = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].bLand = true;
	}
	g_nNumEnemy = 0;											//敵(複数)の初期化

	//敵を倒した時のスコア
	g_aEnemy[0].nScore = 500;
	g_aEnemy[1].nScore = 800;
	g_aEnemy[2].nScore = 1200;
	g_aEnemy[3].nScore = 200;

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
		pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH;
		pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH;
		pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH;
		pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH;
		pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y;
		pVtx[3].pos.z = 0.0f;

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

		//テクスチャ座標の設定(敵)
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

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[nCntEnemy].Counter++;
				if (g_aEnemy[nCntEnemy].Counter >= SECONDS)	//一定時間の経過
				{
					//SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-7.0f, 0.0f, 0.0f),100, ENEMY_STATE_ENEMY);
					g_aEnemy[nCntEnemy].Counter = 0;
				}
				break;

			case ENEMYSTATE_DAMEGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}

			g_aEnemy[nCntEnemy].move.y += GB;							//重力加算

			//前回の位置を保存(敵)
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;

			//敵の位置を更新
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			if (CollisionBlock(
				&g_aEnemy[nCntEnemy].pos,
				&g_aEnemy[nCntEnemy].posOld,
				&g_aEnemy[nCntEnemy].move,
				ENEMY_WIDTH, ENEMY_HEIGHT,
				g_aEnemy[nCntEnemy].bLand) == false)

			{
				//g_aEnemy[nCntEnemy].move.x *= -1.0f;
				g_aEnemy[nCntEnemy].move.x *= -1.0f;
			}



			//頂点座標の設定(敵)
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y;
			pVtx[3].pos.z = 0.0f;
		}
		pVtx += 4;
	}
	//頂点情報をアンロック
	g_pVtxBuffEnemy->Unlock();
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
		{
			//敵が使用されている

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
		{
			//敵が使用されてない
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = nLife;

			//頂点座標の設定(敵)
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//テクスチャ座標の設定(敵)
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
		AddScore(g_aEnemy[nCntEnemy].nScore);
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

	bool bHit = false;											//ヒットしているかどうか

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//左右の敵の当たり判定
			if (pPos->x + PLAYER_WIDTH / 2 > g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH
				&& pPos->x - PLAYER_WIDTH / 2 < g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH)
			{
				//上の当たり判定
				if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT
					&& pPos->y > g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT)
				{
					bHit = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT;
					pMove->y = 0.0f;

					HitEnemy(nCntEnemy, 5);
				}
				//下の当たり判定
				else if (pPosOld->y - PLAYER_HEIGHT >= g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT
					&& pPos->y - PLAYER_HEIGHT < g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT)
				{
					bHit = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT - PLAYER_WIDTH;
					pMove->y = 0.0f;
					//bHit = false;
				}
			}
			//敵のy(Old)の範囲がブロックに重なっている時の当たり判定
			if (pPosOld->y > g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT
				&& pPosOld->y - ENEMY_HEIGHT < g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT)
			{
				//敵が左から右のブロックにめり込んだ
				if (pPosOld->x + PLAYER_WIDTH / 2 <= g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH
					&& pPos->x + PLAYER_WIDTH / 2 > g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH)
				{
					pPos->x = g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH - PLAYER_WIDTH / 2;
					pMove->x = 0.0f;
				}
				//敵が右から左のブロックにめり込んだ
				if (pPosOld->x - PLAYER_WIDTH / 2 >= g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH
					&& pPos->x - PLAYER_WIDTH / 2 < g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH)
				{
					pPos->x = g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH + PLAYER_WIDTH / 2;
					pMove->x = 0.0f;
				}

				//HitPlayer(5);
			}
		}
	}
	return bHit;
}