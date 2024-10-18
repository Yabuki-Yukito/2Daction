//=========================================================================================================
//
// ブロックの処理 [Block.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "Block.h"
//#include "explosion.h"
//#include "enemy.h"
//#include "effect.h"

//=========================================================================================================
//メイン関数
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_BLOCK (128)													//玉の最大数
#define WIDTH (100.0f)													//幅
#define HEIGHT (100.0f)													//高さ

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ブロック構造体の定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;													//位置
	D3DXVECTOR3 move;													//移動
	float fWidth;														//プレイヤーの幅
	float fHeight;														//プレイヤーの高さ
	int nLife;															//寿命
	BlockTYPE type;														//ブロックの種類
	bool bUse;															//使用しているかどうか
}Block;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;								//テクスチャへのポインタ(ブロック)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;							//頂点カラーへのポインタ(ブロック)
D3DXVECTOR3 g_posBlock;													//ブロックの位置
D3DXVECTOR3 g_rotBlock;													//ブロックの角度(向き)
float g_fAngleBlock;													//ブロックの対角線の角度
float g_fLengthBlock;													//ブロックの対角線の長さ
Block g_aBlock[MAX_BLOCK];												//ブロックの総数情報

//=========================================================================================================
// ブロックの初期化処理
//=========================================================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\block000.jpg",
		&g_pTextureBlock);

	//ブロック情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//ブロックの総数の位置
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//ブロックの総数の移動量
		g_aBlock[nCntBlock].nLife = 100;								//ブロックの総数の寿命(体力)
		g_aBlock[nCntBlock].bUse = false;								//使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロック
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 15.0f, g_aBlock[nCntBlock].pos.y - 15.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 15.0f, g_aBlock[nCntBlock].pos.y - 15.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 15.0f, g_aBlock[nCntBlock].pos.y + 15.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 15.0f, g_aBlock[nCntBlock].pos.y + 15.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;														//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

}

//=========================================================================================================
// ブロックの終了処理
//=========================================================================================================
void UninitBlock(void)
{
	//テクスチャの破棄
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=========================================================================================================
// ブロックの更新処理
//=========================================================================================================
void UpdateBlock(void)
{

}

//=========================================================================================================
// ブロックの描画処理
//=========================================================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice{};
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//ブロックが使用されているとき
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);

		}
	}
}

//=========================================================================================================
// ブロックの設定処理
//=========================================================================================================
void SetBlock(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	int nCntBlock;
	VERTEX_2D* pVtx = 0;

	//頂点バッファをロックする
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//ブロックが使用されていない
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].bUse = true;						//使用されている状態にする

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//=========================================================================================================
// ブロックの当たり判定
//=========================================================================================================
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
	bool bLanding = false;	//着地しているかどうか

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//左右の当たり判定
			if (pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth
				&& pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{
				//上の当たり判定
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight
					&& pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
					pMove->y = 0.0f;
				}
				//下の当たり判定
				else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
					&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + fHeight;
					pMove->y = 0.0f;
					bLanding = false;
				}
			}
			//プレイヤーのy(Old)の範囲がブロックに重なっている時の当たり判定
			if (pPosOld->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight
				&& pPosOld->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{
				//Xが左から右のブロックにめり込んだ
				if (pPosOld->x + fWidth / 2 <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth
					&& pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - fWidth / 2;
					pMove->x = 0.0f;
				}
				//Xが右から左のブロックにめり込んだ
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