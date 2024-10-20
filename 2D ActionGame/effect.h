//=========================================================================================================
//
// エフェクトの処理 [effect.h]
// Author : yabuki yukito
//
//=========================================================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//弾の種類
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//typedef enum
//{
//	EFFECTTYPE_PLAYER = 0,		//プレイヤーの弾
//	EFFECTTYPE_ENEMY,			//敵の弾
//	EFFECTTYPE_MAX
//}EFFECTTYPE;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col,float fRadius, int nLife);

#endif // !_EFFECT_H_
