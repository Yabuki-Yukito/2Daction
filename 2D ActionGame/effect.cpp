////=========================================================================================================
////
//// エフェクトの処理 [effect.cpp]
//// Author : yabuki yukito
////
////=========================================================================================================
//
////#include "bullet.h"
////#include "explosion.h"
//#include "enemy.h"
//#include "player.h"
//
////=========================================================================================================
////メイン関数
////=========================================================================================================
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////マクロ定義
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define MAX_EFFECT (4096)											//エフェクトの最大数
//#define MAX_SCREENWIDTH	(1280)										//横幅
//#define MAX_SCREENHEIGHT (720)										//高さ
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////エフェクト弾構造体の定義
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//typedef struct
//{
//	D3DXVECTOR3 pos;												//位置
//	D3DXVECTOR3 move;												//移動量
//	D3DXCOLOR col;													//色
//	float fRadius;													//半径(大きさ)
//	int nLife;														//寿命
//	bool bUse;														//使用しているかどうか
//}Effect;
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////グローバル変数
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;							//テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;					//頂点バッファへのポインタ
//D3DXVECTOR3 g_posEffect;											//エフェクトの位置
//D3DXVECTOR3 g_rotEffect;											//エフェクトの角度(向き)
//float g_fAngleEffect;												//エフェクトの対角線の角度
//float g_fLengthEffect;												//エフェクトの対角線の長さ
//Effect g_aEffect[MAX_EFFECT];										//エフェクトの総数情報
//
////=========================================================================================================
////エフェクトの初期化処理
////=========================================================================================================
//void InitEffect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntEffect;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\texture\\effect000.jpg",
//		&g_pTextureEffect);
//
//	//エフェクト情報の初期化
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{
//		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//エフェクトの位置
//		g_aEffect[nCntEffect].nLife = 0;							//エフェクトの寿命(体力)
//		g_aEffect[nCntEffect].bUse = false;							//エフェクトを使用していない状態にする
//	}
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffEffect,
//		NULL);
//
//	VERTEX_2D* pVtx;
//	//頂点バッファをロック
//	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{
//		//頂点座標の設定(エフェクト)
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//
//		//rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//頂点カラーの設定
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.01f);
//
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;													//頂点データのポインタを4つ分進める
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffEffect->Unlock();
//
//}
//
////=========================================================================================================
////エフェクトの終了処理
////=========================================================================================================
//void UninitEffect(void)
//{
//	//テクスチャの破棄
//	if (g_pTextureEffect != NULL)
//	{
//		g_pTextureEffect->Release();
//		g_pTextureEffect = NULL;
//	}
//	//頂点バッファの破棄
//	if (g_pVtxBuffEffect != NULL)
//	{
//		g_pVtxBuffEffect->Release();
//		g_pVtxBuffEffect = NULL;
//	}
//}
//
////=========================================================================================================
////エフェクトの更新処理
////=========================================================================================================
//void UpdateEffect(void)
//{
//	int nCntEffect;
//	VERTEX_2D* pVtx = 0;
//
//	//頂点バッファをロック
//	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{//エフェクトが使用されている
//		if (g_aEffect[nCntEffect].bUse == true)
//		{
//			//頂点座標の更新
//			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//
//			if (g_aEffect[nCntEffect].pos.x <= 0.0f || g_aEffect[nCntEffect].pos.x >= MAX_SCREENWIDTH
//				|| g_aEffect[nCntEffect].pos.y <= 0.0f || g_aEffect[nCntEffect].pos.y >= MAX_SCREENHEIGHT)
//			{
//				g_aEffect[nCntEffect].bUse = false;			//使用していない状態にする
//			}
//
//			g_aEffect[nCntEffect].nLife--;
//
//			if (g_aEffect[nCntEffect].nLife <= 0)			//寿命が0に
//			{
//				g_aEffect[nCntEffect].bUse = false;			//使用していない状態にする
//			}
//		}
//		pVtx += 4;
//	}
//	//頂点バッファをアンロック
//	g_pVtxBuffEffect->Unlock();
//}
//
////=========================================================================================================
////エフェクトの描画処理
////=========================================================================================================
//void DrawEffect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice{};
//	int nCntEffect;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//aブレンディングを加算合成に設定
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{//エフェクトを使用している時
//		if (g_aEffect[nCntEffect].bUse == true)
//		{
//			//テクスチャの設定
//			pDevice->SetTexture(0, g_pTextureEffect);
//
//			//ポリゴンの描画
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
//		}
//	}
//
//	//aブレンディングを元に戻す
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//}
//
////=========================================================================================================
////エフェクトの設定処理
////=========================================================================================================
//void SetEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col, float fRadius,int nLife)
//{
//	int nCntEffect;
//	VERTEX_2D* pVtx = 0;
//
//	//頂点バッファをロック
//	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
//	{//エフェクトを使用していない時
//		if (g_aEffect[nCntEffect].bUse == false)
//		{
//			//エフェクトが使用されていない
//			g_aEffect[nCntEffect].pos = pos;
//			g_aEffect[nCntEffect].col = col;
//			g_aEffect[nCntEffect].fRadius = fRadius;
//			g_aEffect[nCntEffect].nLife = nLife;
//
//			//頂点座標の設定
//			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y - 20.0f, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 20.0f, g_aEffect[nCntEffect].pos.y + 20.0f, 0.0f);
//
//			//頂点カラーの設定
//			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col);
//
//			g_aEffect[nCntEffect].bUse = true;							//使用されている状態にする
//			break;
//		}
//		pVtx += 4;
//	}
//	//頂点バッファをアンロック
//	g_pVtxBuffEffect->Unlock();
//}