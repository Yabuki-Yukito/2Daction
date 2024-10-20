//=========================================================================================================
//
// フェードの処理 [fade.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "fade.h"

//=========================================================================================================
//メイン関数
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;			//頂点バッファへのポインタ
FADE g_fade;											//フェードの状態
MODE g_modeNext;										//次の画面(モード)
D3DXCOLOR g_colorFade;									//ポリゴン(フェード)の色

//=========================================================================================================
//フェードの初期化処理
//=========================================================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_fade = FADE_IN;									//フェード状態に
	g_modeNext = modeNext;								//次の画面(モード)を選択
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒いポリゴン(不透明)にしておく


		//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D* pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(フェード)
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
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);


	//頂点情報をアンロック
	g_pVtxBuffFade->Unlock();

	//モードの設定
	SetMode(g_modeNext);
}

//=========================================================================================================
//フェードの終了処理
//=========================================================================================================
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=========================================================================================================
//フェードの更新処理
//=========================================================================================================
void UpdateFade(void)
{
	VERTEX_2D* pVtx{};									//頂点情報へのポインタ

	if (g_fade != FADE_NONE)
	{//フェードイン状態
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= 0.03f;						//ポリゴンを透明に
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;						//何もしていない状態
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorFade.a += 0.03f;						//ポリゴンを不透明に
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;						//フェードイン状態

				//モードの設定
				SetMode(g_modeNext);
			}
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);

		//頂点情報をアンロック
		g_pVtxBuffFade->Unlock();
	}
	pVtx += 4;
}

//=========================================================================================================
//フェードの描画処理
//=========================================================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = 0;						//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=========================================================================================================
//フェードの設定処理
//=========================================================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;									//フェードアウト状態に
	g_modeNext = modeNext;								//次の画面(モード)に設定
}

//=========================================================================================================
//フェードの取得処理
//=========================================================================================================
FADE GetFade(void)
{
	return g_fade;										//フェードの状態を返す
}