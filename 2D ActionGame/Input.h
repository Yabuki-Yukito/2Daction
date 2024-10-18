//=========================================================================================================
//
// ���͂̏��� [Input.h]
// Author : yabuki yukito
//
//=========================================================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�W���C�p�b�h(�L�[)�̎��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	JOYKEY_PADUP = 0,				//�\���L�[(��)
	JOYKEY_PADDOWN,					//�\���L�[(��)
	JOYKEY_PADLEFT,					//�\���L�[(��)
	JOYKEY_PADRIGHT,				//�\���L�[(�E)
	JOYKEY_START,					//�X�^�[�g�{�^��
	JOYKEY_BACK,					//BACK�{�^��
	JOYKEY_L3,						//L3�{�^��
	JOYKEY_R3,						//R3�{�^��
	JOYKEY_L1,						//L1�{�^��
	JOYKEY_R1,						//R1�{�^��
	JOYKEY_L2,						//L2�{�^��
	JOYKEY_R2,						//R2�{�^��
	JOYKEY_A,						//A�{�^��
	JOYKEY_B,						//B�{�^��
	JOYKEY_X,						//X�{�^��
	JOYKEY_Y						//Y�{�^��

}JOYKEY;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�L�[�{�[�h�̃v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardReleace(int nKey);
bool KeyboardRepeat(int nKey);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�W���C�p�b�h�̃v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool JoypadPress(JOYKEY key);

#endif // !_INPUT_H_
