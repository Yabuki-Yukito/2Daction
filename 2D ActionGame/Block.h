//=========================================================================================================
//
// ブロックの処理 [Block.h]
// Author : yabuki yukito
//
//=========================================================================================================

#ifndef _Block_H_
#define _Block_H_

#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ブロックの種類
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	BlockTYPE_PLAYER = 0,					//プレイヤーのブロック
	BlockTYPE_ENEMY,						//敵のブロック
	BlockTPE_MAX
}BlockTYPE;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fHeight, float fWidth/*, D3DXVECTOR3 move,int nLife,BlockTYPE type*/);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);

#endif // !_Block_H_
