//=========================================================================================================
//
// リザルトの処理 [result.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "result.h"
#include "Input.h"
#include "fade.h"

//=========================================================================================================
//メイン関数
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//テクスチャのポインタ(リザルト)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//頂点バッファへのポインタ(リザルト)
RESULT g_Result = RESULT_LOSE;

//=========================================================================================================
// リザルト画面の初期化処理
//=========================================================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;							//デバイスへのポインタ

	//デバイスの取得
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

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	g_Result = RESULT_LOSE;								//リザルトの初期化

	VERTEX_2D* pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(リザルト)
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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

	//頂点情報をアンロック
	g_pVtxBuffResult->Unlock();
}

//=========================================================================================================
// リザルト画面の終了処理
//=========================================================================================================
void UninitResult(void)
{
	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
		//頂点バッファの破棄
		if (g_pVtxBuffResult != NULL)
		{
			g_pVtxBuffResult->Release();
			g_pVtxBuffResult = NULL;
		}

}

//=========================================================================================================
// リザルト画面の更新処理
//=========================================================================================================
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_TITLE);
	}
}

//=========================================================================================================
// リザルト画面の描画処理
//=========================================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;							//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=========================================================================================================
// リザルト画面の結果処理
//=========================================================================================================
void SetResult(RESULT result)
{
	g_Result = result;
}
