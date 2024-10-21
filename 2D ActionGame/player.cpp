//=========================================================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "player.h"
#include "Input.h"
#include "Block.h"
#include "game.h"
#include "enemy.h"
//#include "Block.h"
//#include "result.h"

//=========================================================================================================
//メイン関数
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define JP (-45)	//ジャンプ力
#define GB (+3)		//重力

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9 g_pTextureplayer = NULL;						//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;				//頂点バッファへのポインタ
//D3DXVECTOR3 g_player.pos;										//プレイヤーの位置
D3DXVECTOR3 g_movePlayer;										//プレイヤーの移動量
D3DXVECTOR3 g_rotPlayer;										//プレイヤーの向き
Player g_player;												//プレイヤーの情報
int g_nCounterAnimPlayer = 0;									//アニメーションカウンター
int g_nPatternAnimPlayer = 0;									//アニメーションパターン№
float g_fLengthPlayer;											//対角線の長さ
float g_fAnglePlayer;											//対角線の角度

//=========================================================================================================
// プレイヤーの初期化処理
//=========================================================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\player000.png",
		&g_pTextureplayer);

	g_nCounterAnimPlayer = 0;									//アニメーションカウンターの初期化
	g_nPatternAnimPlayer = 0;									//アニメーションパターンの初期化
	g_player.pos = D3DXVECTOR3(50.0f, 670.0f, 0.0f);			//プレイヤーの位置
	g_movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//プレイヤーの移動量
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//プレイヤーの前回の位置
	//g_player.nLife = 2;										//プレイヤーの体力
	g_player.bDisp = true;										//プレイヤーが表示しているとき
	g_player.bUse = true;										//プレイヤーが使用されているとき
	g_player.bRightMove = true;									//プレイヤーが左右を向いているとき
	g_player.bJump = false;										//プレイヤーがジャンプしてないとき
	g_player.bStepOn = false;									//プレイヤーが踏んでいないとき

	//対角線の長さを算出する
	g_fLengthPlayer = sqrtf(200.0f * 350.0f + 200.0f * 200.0f) / 2.0f;

	//対角線の角度を算出する
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x - PLAYER_WIDTH;
	pVtx[0].pos.y = g_player.pos.y - PLAYER_HEIGHT;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + PLAYER_WIDTH;
	pVtx[1].pos.y = g_player.pos.y - PLAYER_HEIGHT;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x - PLAYER_WIDTH;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + PLAYER_WIDTH;
	pVtx[3].pos.y = g_player.pos.y;
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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);


	//頂点情報をアンロック
	g_pVtxBuffplayer->Unlock();

}

//=========================================================================================================
//プレイヤーの終了処理
//=========================================================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTextureplayer != NULL)

		//頂点バッファの破棄
		if (g_pVtxBuffplayer != NULL)
		{
			g_pVtxBuffplayer->Release();
			g_pVtxBuffplayer = NULL;
		}
}

//=========================================================================================================
//プレイヤーの更新処理
//=========================================================================================================
void UpdatePlayer(void)
{

	//switch (g_player.state)
	//{
	//case PLAYERSTATE_APPEAR:

	//	break;

	//case PLAYERSTATE_NORMAL:

	//	break;

	//case PLAYERSTATE_DAMAGE:

	//	break;

	//case PLAYERSTATE_DEATH:

	//	break;

	//default:

	//	break;
	//}

	//プレイヤーが使用されている時
	if (g_player.bUse == true)
	{
		if (KeyboardRepeat(DIK_A) == true || JoypadPress(JOYKEY_PADLEFT) == true)
		{//Aキーが押された
			g_movePlayer.x -= 1.0f;
			g_player.bRightMove = false;						//左を向いていたら
		}
		if (KeyboardRepeat(DIK_D) == true || JoypadPress(JOYKEY_PADRIGHT) == true)
		{//Dキーが押された
			g_movePlayer.x += 1.0f;
			g_player.bRightMove = true;							//右を向いていたら
		}
		if (KeyboardTrigger(DIK_SPACE) == true || JoypadPress(JOYKEY_L3) == true || JoypadPress(JOYKEY_START) == true)
		{//SPACEキー
			if (g_player.bJump == false)
			{
				g_movePlayer.y = JP;
				g_player.bJump = true;
			}
		}
		g_movePlayer.y += GB;									//重力加算

		//前回の位置を保存
		g_player.posOld = g_player.pos;

		//位置を更新
		g_player.pos.x += g_movePlayer.x;
		g_player.pos.y += g_movePlayer.y;

		//ブロックの当たり判定
		if (CollisionBlock(
			&g_player.pos,		//現在の位置
			&g_player.posOld,	//前回の位置
			&g_movePlayer,		//プレイヤーの移動量
			PLAYER_WIDTH, PLAYER_HEIGHT) == true)
		{
			g_player.bJump = false;
		}

		//敵の当たり判定
		if (CollisionEnemy(
			&g_player.pos,
			&g_player.posOld,
			&g_movePlayer) == true)
		{
			g_player.bStepOn = false;
			g_player.bJump = false;
		}

		//移動量を更新(減衰)
		g_movePlayer.x += (0.0f - g_movePlayer.x) * 0.08f;
		//g_movePlayer.y += (0.0f - g_movePlayer.y) * 0.09f;

		//画面外の処理
		if (g_player.pos.x >= SCREEN_WIDTH)						//横(右)
		{
			g_player.pos.x = 0;
		}
		else if (g_player.pos.x <= 0)							//横(左)
		{
			g_player.pos.x = SCREEN_WIDTH;
		}
		if (g_player.pos.y >= SCREEN_HEIGHT)					//地面
		{
			g_player.pos.y = SCREEN_HEIGHT;
			g_movePlayer.y = 0.0f;
			g_player.bJump = false;
		}
		else if (g_player.pos.y <= 0 + PLAYER_HEIGHT)			//上
		{
			g_player.pos.y = 0 + PLAYER_HEIGHT;
			g_movePlayer.y = 0;
		}

		//頂点情報へのポインタ
		VERTEX_2D* pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos.x = g_player.pos.x - PLAYER_WIDTH / 2;
		pVtx[0].pos.y = g_player.pos.y - PLAYER_HEIGHT;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_player.pos.x + PLAYER_WIDTH / 2;
		pVtx[1].pos.y = g_player.pos.y - PLAYER_HEIGHT;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_player.pos.x - PLAYER_WIDTH / 2;
		pVtx[2].pos.y = g_player.pos.y;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_player.pos.x + PLAYER_WIDTH / 2;
		pVtx[3].pos.y = g_player.pos.y;
		pVtx[3].pos.z = 0.0f;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

		////テクスチャ座標の設定
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		//pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

		//頂点情報をアンロック
		g_pVtxBuffplayer->Unlock();
	}
	//g_nCounterAnimPlayer++;									//カウンターを加算

	//if ((g_nCounterAnimPlayer % 8) == 0)
	//{
	//	g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 8;
	//	g_nCounterAnimPlayer = 0;								//カウンターを初期値に戻す
	//	g_nPatternAnimPlayer++;									//パターン№.を更新

	//	if (g_nPatternAnimPlayer == 8)
	//	{
	//		g_nPatternAnimPlayer = 0;							//パターン№.を初期値に戻す
	//	}
	//}

}

//=========================================================================================================
//プレイヤーの描画処理
//=========================================================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;									//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーが表示されるとき
	//if (g_player.bDisp == true)
	//{
		//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffplayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureplayer);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//}
}

//=========================================================================================================
//プレイヤーの取得処理
//=========================================================================================================
Player* GetPlayer(void)
{
	return &g_player;											//プレイヤーの情報を返す
}

//=========================================================================================================
//プレイヤーのヒット処理
//=========================================================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	VERTEX_2D* pVtx{};

	if (g_player.nLife <= 0)
	{
		//g_nNumEnemy--;

		g_player.bDisp = false;									//プレイヤーが表示されてない時
		g_player.bUse = false;									//プレイヤーが使用されていない時
		g_player.state = PLAYERSTATE_DEATH;						//死亡状態
		g_player.nCounterState = 60;							//状態管理
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;					//ダメージ状態
		g_player.nCounterState = 5;								//ダメージ状態を保つ時間を設定

		pVtx += 4 * nDamage;									//プレイヤーのヒット処理(4つ分)

		//頂点バッファをロック
		g_pVtxBuffplayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//頂点情報をアンロック
		g_pVtxBuffplayer->Unlock();
	}
}
