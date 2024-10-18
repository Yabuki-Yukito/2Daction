////=========================================================================================================
////
//// 背景の処理 [backgraund.cpp]
//// Author : yabuki yukito
////
////=========================================================================================================
//
//#include "backgraund.h"
//
////=========================================================================================================
////メイン関数
////=========================================================================================================
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////マクロ定義
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define NUM_BACKGURAUND (3)												//背景の枚数
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////グローバル変数
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//LPDIRECT3DTEXTURE9 g_apTexturebackgraund[NUM_BACKGURAUND] = {};			//テクスチャ(3枚分）へのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbackgraund = NULL;					//頂点バッファへのポインタ
//float g_aPosTexU[NUM_BACKGURAUND];										//テクスチャ座標の開始位置(U値)
//
////=========================================================================================================
////背景の初期化処理
////=========================================================================================================
//void Initbackgraund(void)
//{
//	LPDIRECT3DDEVICE9 pDevice2;
//	int nCntbackgraund;
//
//	//デバイスの取得
//	pDevice2 = GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice2,
//		"data\\texture\\bg100.png",
//		&g_apTexturebackgraund[0]);
//
//	//テクスチャの読み込み2
//	D3DXCreateTextureFromFile(pDevice2,
//		"data\\texture\\Galaxy.png",
//		&g_apTexturebackgraund[1]);
//
//	//テクスチャの読み込み3
//	D3DXCreateTextureFromFile(pDevice2,
//		"data\\texture\\bg102.png",
//		&g_apTexturebackgraund[2]);
//
//
//	//テクスチャ座標の開始位置(U値)の初期値
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		g_aPosTexU[nCntbackgraund] = 0.0f;
//	}
//
//	//頂点バッファの生成
//	pDevice2->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*NUM_BACKGURAUND,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffbackgraund,
//		NULL);
//
//	VERTEX_2D* pVtx;													//頂点情報へのポインタ
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffbackgraund->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		//頂点座標の設定(背景)
//		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
//
//		//rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//頂点カラーの設定
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 1.0f);
//
//		pVtx += 4;															//頂点データのポインタを4つ分を進める
//	}
//	//頂点情報をアンロック
//	g_pVtxBuffbackgraund->Unlock();
//}
//
////=========================================================================================================
////背景の終了処理
////=========================================================================================================
//void Uninitbackgraund(void)
//{
//	int nCntbackgraund;													//背景カウント
//
//	//テクスチャ(3枚分)の破棄
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		if (g_apTexturebackgraund[nCntbackgraund] != NULL)
//		{
//			g_apTexturebackgraund[nCntbackgraund]->Release();
//			g_apTexturebackgraund[nCntbackgraund] = NULL;
//		}
//
//	}
//	//頂点バッファの破棄
//	if (g_pVtxBuffbackgraund != NULL)
//	{
//		g_pVtxBuffbackgraund->Release();
//		g_pVtxBuffbackgraund = NULL;
//	}
//}
//
////=========================================================================================================
////背景の更新処理
////=========================================================================================================
//void Updatebackgraund(void)
//{
//	int nCntbackgraund;
//
//	VERTEX_2D* pVtx;													//頂点情報へのポインタ
//
//	//背景テクスチャ
//	g_aPosTexU[0] -= 0.0030f;											//1枚目の移動スピード
//	g_aPosTexU[1] -= 0.0030f;											//2枚目の移動スピード
//	g_aPosTexU[2] -= 0.0030f;											//3枚目の移動スピード
//
////頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffbackgraund->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund], 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntbackgraund] + 1.0f, 1.0f);
//
//		pVtx += 4;														//4つ分
//	}
//	//頂点情報をアンロック
//	g_pVtxBuffbackgraund->Unlock();
//}
//
////=========================================================================================================
////背景の描画処理
////=========================================================================================================
//void Drawbackgraund(void)
//{
//	LPDIRECT3DDEVICE9 pDevice2;
//	int nCntbackgraund;
//
//	//デバイスの取得
//	pDevice2 = GetDevice();
//
//	//頂点バッファをデータストリームに設定
//	pDevice2->SetStreamSource(0, g_pVtxBuffbackgraund, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice2->SetFVF(FVF_VERTEX_2D);
//
//	for (nCntbackgraund = 0; nCntbackgraund < NUM_BACKGURAUND; nCntbackgraund++)
//	{
//		//テクスチャの設定
//		pDevice2->SetTexture(0,	g_apTexturebackgraund[nCntbackgraund]);				
//
//		//背景の描画
//		pDevice2->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntbackgraund*4, 2);
//
//	}
//}
//
