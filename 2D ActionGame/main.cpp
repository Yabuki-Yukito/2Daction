//=========================================================================================================
//
// 2Dアクション [main.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "main.h"
#include "Player.h"
#include "input.h"
#include "enemy.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
//#include "backgraund.h"
//#include "bullet.h"
//#include "explosion.h"
//#include "sound.h"
//#include "effect.h"

//=========================================================================================================
//メイン関数
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MODE g_mode = MODE_TITLE;												//現在のモード	
LPD3DXFONT g_pFont = NULL;												//フォントへのポインタ
int g_nCountFPS = 0;													//FPSへのカウンタ

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;

//=========================================================================================================
//初期化処理
//=========================================================================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdshow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)

	};
	HWND hWnd;															//ウィンドウハンドル(識別子)
	MSG msg;															//メッセージを格納
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };						//ウィンドウクラスの登録

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	RegisterClassEx(&wcex);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,														//拡張ウィンドウスタイル
		WINDOW_NAME,													//ウィンドウクラスの名前
		WS_OVERLAPPEDWINDOW,											//ウィンドウの名前		
		CW_USEDEFAULT,													//ウィンドウ左上X座標
		CW_USEDEFAULT,													//ウィンドウ左上Y座標
		(rect.right - rect.left),										//ウィンドウ左上の幅
		(rect.bottom - rect.top),										//ウィンドウ左上の高さ
		NULL,															//親ウィンドウのハンドル
		NULL,															//メニューハンドル
		hInstance,														//インスタンスハンドル
		NULL);															//ウィンドウ作成データ

	DWORD dwCurrentTime;												//現在時刻
	DWORD dwExecLastTime;												//最後に処理した時刻
	DWORD dwFrameCount;													//フレームへのカウンタ
	DWORD dwFPSLastTime;												//最後にFPSを計測した時刻

	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		//初期化が失敗した時
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;													//現在時刻を初期化する
	dwExecLastTime = timeGetTime();										//現在時刻を取得(最後)
	dwFrameCount = 0;													//フレームカウンタを初期化する
	dwFPSLastTime = timeGetTime();										//FPSを取得した時刻(最後)

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdshow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;						//FPSを測定した時刻を保存

				dwFrameCount = 0;									//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//60分の1秒経過
				dwExecLastTime = dwCurrentTime;						//処理開始の時刻(現在時刻)を保存

				//更新設定
				Update();

				//描画設定
				Draw();
				dwFrameCount++;										//フレームカウントを加算
			}
		}
	}

	//分解能を戻す
	timeEndPeriod(1);

	//終了処理
	Uninit();

	//ウィンドウクラスの登録解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=========================================================================================================
//ウィンドウプロシージャの処理
//=========================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
	int nID;															//返り値を格納

	switch (umsg)
	{
	case WM_DESTROY:
		//WM_QUITのメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);
			if (nID == IDYES)
			{
				//はいを選んだ場合
				MessageBox(NULL, "終了", "終了メッセージ", MB_OK);
				DestroyWindow(hWnd);									//ウィンドウを破棄する(WM_DESTROYに送る)
				break;
			}
			else if (nID == IDNO)
			{
				//いいえを選んだ場合
				MessageBox(NULL, "続行", "終了メッセージ", MB_OK);
			}
			break;
		}
	}
	return DefWindowProc(hWnd, umsg, wParam, lParam);					//規定の処理を繰り返す
}

//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Directオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータ設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//ゲーム画面のサイズ(幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//高さ
	d3dpp.BackBufferFormat = d3ddm.Format;								//バックバッファの形式
	d3dpp.BackBufferCount = 1;											//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;								//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//インターバル

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}


	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバック表示用のフォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Teminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//モードの設定
	SetMode(g_mode);

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}

//=========================================================================================================
//プレイヤーの初期化処理
//=========================================================================================================
void Uninit(void)
{

	switch (g_mode)
	{
		//タイトル画面
	case MODE_TITLE:
		UninitTitle();
		break;

		//ゲーム画面
	case MODE_GAME:
		UninitGame();
		break;

		//リザルト画面
	case MODE_RESULT:
		UninitResult();
		break;
	}

	//フェードの終了処理
	UninitFade();

	//キーボードの終了処理
	UninitKeyboard();

	//ゲームパッドの終了処理
	UninitJoypad();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();

		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();

		g_pD3D = NULL;
	}

	//デバック表示用のフォントの設定
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();

	//ゲームパッドの更新処理
	UpdateJoypad();

	switch (g_mode)
	{
		//タイトル画面の更新処理
	case MODE_TITLE:
		UpdateTitle();
		break;

		//ゲーム画面の更新処理
	case MODE_GAME:
		UpdateGame();
		break;

		//リザルト画面の更新処理
	case MODE_RESULT:
		UpdateResult();
		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void Draw(void)
{
	//画面クリア（バックバッファ&Zバッファのクリア）
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
			//タイトル画面の描画処理
		case MODE_TITLE:
			DrawTitle();
			break;

			//ゲーム画面の描画処理
		case MODE_GAME:
			DrawGame();
			break;

			//リザルト画面の描画処理
		case MODE_RESULT:
			DrawResult();
			break;
		}

		//フェードの描画処理
		DrawFade();

		//FPSの表示
		DrawFPS();

		//描画終了
		g_pD3DDevice->EndScene();

	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//=========================================================================================================
//FPSの表示処理
//=========================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//デバイスの取得
//=========================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================
//モードを設定
//=========================================================================================================
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
		//タイトル画面
	case MODE_TITLE:
		UninitTitle();
		break;

		//ゲーム画面
	case MODE_GAME:
		UninitGame();
		break;

		//リザルト画面
	case MODE_RESULT:
		UninitResult();
		break;
	}

	//モード設定(画面)の初期化処理
	switch (mode)
	{
		//タイトル画面
	case MODE_TITLE:
		InitTitle();
		break;

		//ゲーム画面
	case MODE_GAME:
		InitGame();
		break;

		//リザルト画面
	case MODE_RESULT:
		InitResult();
		break;
	}

	//現在の画面(モード)を切り替える
	g_mode = mode;
}

//=========================================================================================================
//モードの取得
//=========================================================================================================
MODE GetMode(void)
{
	return g_mode;														//現在のモードを返す
}
