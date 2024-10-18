//=========================================================================================================
//
// �u���b�N�̏��� [Block.h]
// Author : yabuki yukito
//
//=========================================================================================================

#ifndef _Block_H_
#define _Block_H_

#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�u���b�N�̎��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	BlockTYPE_PLAYER = 0,					//�v���C���[�̃u���b�N
	BlockTYPE_ENEMY,						//�G�̃u���b�N
	BlockTPE_MAX
}BlockTYPE;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�v���g�^�C�v�錾	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fHeight, float fWidth/*, D3DXVECTOR3 move,int nLife,BlockTYPE type*/);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);

#endif // !_Block_H_
