//=========================================================================================================
//
// 入力の処理 [Input.h]
// Author : yabuki yukito
//
//=========================================================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ジョイパッド(キー)の種類
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	JOYKEY_PADUP = 0,				//十字キー(上)
	JOYKEY_PADDOWN,					//十字キー(下)
	JOYKEY_PADLEFT,					//十字キー(左)
	JOYKEY_PADRIGHT,				//十字キー(右)
	JOYKEY_START,					//スタートボタン
	JOYKEY_BACK,					//BACKボタン
	JOYKEY_L3,						//L3ボタン
	JOYKEY_R3,						//R3ボタン
	JOYKEY_L1,						//L1ボタン
	JOYKEY_R1,						//R1ボタン
	JOYKEY_L2,						//L2ボタン
	JOYKEY_R2,						//R2ボタン
	JOYKEY_A,						//Aボタン
	JOYKEY_B,						//Bボタン
	JOYKEY_X,						//Xボタン
	JOYKEY_Y						//Yボタン

}JOYKEY;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//キーボードのプロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardReleace(int nKey);
bool KeyboardRepeat(int nKey);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ジョイパッドのプロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool JoypadPress(JOYKEY key);

#endif // !_INPUT_H_
