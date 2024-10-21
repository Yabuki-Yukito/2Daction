//=========================================================================================================
//
// ゲームの処理 [game.cpp]
// Author : yabuki yukito
//
//=========================================================================================================

#include "game.h"
#include "player.h"
#include "Input.h"
#include "Block.h"
#include "fade.h"
#include "enemy.h"
#include "result.h"
//#include "backgraund.h"
//#include "bullet.h"
//#include "score.h"
//#include "pause.h"
//#include "ranking.h"
//#include "effect.h
//#include "wave.h"

//=========================================================================================================
//メイン関数
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
bool g_bPause = false;													//ポーズ中かどうか

//=========================================================================================================
// ゲーム画面の初期化処理
//=========================================================================================================
void InitGame(void)
{
	//ブロックの初期化処理
	InitBlock();

	//X座標,Y座標,Z座標,高さの座標,幅の座標
	SetBlock(D3DXVECTOR3(640.0f, 695.0f, 0.0f), 20.0f, 700.0f);			//ブロック1個目(地面)の座標
	SetBlock(D3DXVECTOR3(300.0f, 490.0f, 0.0f), 30.0f, 180.0f);			//ブロック2個目(左側)の座標
	SetBlock(D3DXVECTOR3(1000.0f, 490.0f, 0.0f), 30.0f, 180.0f);		//ブロック3個目(右側)の座標
	SetBlock(D3DXVECTOR3(650.0f, 270.0f, 0.0f), 30.0f, 170.0f);			//ブロック4個目(真ん中)の座標

	//プレイヤーの初期化処理
	InitPlayer();

	//弾の初期化処理
	//InitBullet();

	//敵の初期化処理
	InitEnemy();

	//X座標,Y座標,Z座標
	SetEnemy(D3DXVECTOR3(750.0f, 200.0f, 0.0f), 0.0f, 10.0f);					//敵の座標(上)
	SetEnemy(D3DXVECTOR3(300.0f, 420.0f, 0.0f), 0.0f, 10.0f);					//敵の座標(左)
	SetEnemy(D3DXVECTOR3(1000.0f, 420.0f, 0.0f), 0.0f, 10.0f);					//敵の座標(右)
	SetEnemy(D3DXVECTOR3(660.0f, 640.0f, 0.0f), 0.0f, 10.0f);					//敵の座標(下)


	////ウェーブの初期化処理
	//InitWave();

	//エフェクトの初期化処理
	//InitEffect();

	//スコアの初期化処理
	//InitScore();
	//SetScore(0);

	//背景の初期化処理
	//Initbackgraund();

	//爆発の初期化処理
	//InitExplosion();

	g_gameState = GAMESTATE_NORMAL;									//通常状態
	g_nCounterGameState;
	//g_bPause = false;												//ポーズ解除

	////読込処理
	//LoadWave();
}

//=========================================================================================================
// ゲーム画面の終了処理
//=========================================================================================================
void UninitGame(void)
{
	//ブロックの終了処理
	UninitBlock();

	//プレイヤーの終了処理
	UninitPlayer();


	//弾の終了処理
	//UninitBullet();

	//敵の終了処理
	UninitEnemy();

	//エフェクトの終了処理
	//UninitEffect();

	//スコアの終了処理
	//UninitScore();

	//背景の終了処理
	//Uninitbackgraund();

	//爆発の終了処理
	//UninitExplosion();
}

//=========================================================================================================
// ゲーム画面の更新処理
//=========================================================================================================
void UpdateGame(void)
{
	//ブロックの更新処理
	UpdateBlock();

	//プレイヤーの更新処理
	UpdatePlayer();


	//弾の更新処理
	//UpdateBullet();

	//敵の更新処理
	UpdateEnemy();

	//エフェクトの更新処理
	//UpdateEffect();

	//スコアの更新処理
	//UpdateScore();

	//背景の更新処理
	//Updatebackgraund();

	//爆発の更新処理
	//UpdateExplosion();

	Player* pPlayer = GetPlayer();										//プレイヤー情報へのポインタ
	Enemy* pEnemy = GetEnemy();											//敵情報へのポインタ

	//敵数の取得
	int NumEnemy = GetEnemyNum();
	bool bfinish = false;

	if (NumEnemy <= 0)
	{
		SetResult(RESULT_WIN);
		SetGameState(GAMESTATE_END);
		//LoadWave();
	}

	if (pPlayer->bUse == false)										//プレイヤーが使用されていない時の処理
	{
		g_gameState = GAMESTATE_END;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:

		//bfinish = GetFinish();

		if (bfinish == true)
		{
			//モード設定
			SetResult(RESULT_WIN);
			SetGameState(GAMESTATE_END);
		}
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//フェードの設定
			SetFade(MODE_RESULT);

		}
	}
}

//=========================================================================================================
// ゲーム画面の描画処理
//=========================================================================================================
void DrawGame(void)
{
	//背景の描画処理
	//Drawbackgraund();

	//ブロックの描画処理
	DrawBlock();

	//プレイヤーの描画処理
	DrawPlayer();


	//弾の描画処理
	//DrawBullet();

	//敵の描画処理
	DrawEnemy();

	//エフェクトの描画処理
	//DrawEffect();

	//スコアの描画処理
	//DrawScore();

	//爆発の描画処理
	//DrawExplosion();


	//if (g_bPause == true)												//ポーズをしている時
	//{												
	//	//ポーズの描画処理
	//	//DrawPause();
	//}
}

//=========================================================================================================
// ゲーム画面の状態処理
//=========================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}

//=========================================================================================================
// ゲーム画面の状態取得処理
//=========================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=========================================================================================================
// ポーズの有効無効設定処理
//=========================================================================================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}
