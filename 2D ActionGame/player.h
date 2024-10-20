//=========================================================================================================
//
// プレイヤーの処理 [player.h]
// Author : yabuki yukito
//
//=========================================================================================================

#ifndef _Player_H_				//このマクロ定義がされてなかったら
#define _Player_H_

#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//プレイヤーの状態
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	PLAYERSTATE_APPEAR = 0,		//出現状態(点滅)
	PLAYERSTATE_NORMAL,			//通常状態
	PLAYERSTATE_DAMAGE,			//ダメージ状態
	PLAYERSTATE_DEATH,			//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//プレイヤーの構造体
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 posOld;			//前回の位置
	PLAYERSTATE state;			//プレイヤーの状態
	int nCounterState;			//状態管理カウンター
	int nLife;					//体力
	bool bDisp;					//表示するかしないか
	bool bUse;					//使っているか使っていないか
	bool bJump;					//ジャンプ中かどうか
	bool bRightMove;			//向き(左右)
	bool bStepOn;				//踏んでいるかどうか
}Player;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define PLAYER_WIDTH (80.0f)											//プレイヤーの幅
#define PLAYER_HEIGHT (80.0f)											//プレイヤーの高さ
#define MAX_MAXIMUM  (200.0f)									//大きさ
#define MAX_MINI (200.0f)										//小ささ



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);


#endif // !_player_H_			//このマクロ定義がされてなかったら

