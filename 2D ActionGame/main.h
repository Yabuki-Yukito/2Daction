//=========================================================================================================
//
// 2D�V���[�e�B���O [main.h]
// Author : yabuki yukito
//
//=========================================================================================================

#ifndef _MAIN_H_												//���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_												//2�d�C���N���[�h�h�~�̃}�N����`

#include <windows.h> 
#include "d3dx9.h"												//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)							//�r���h���̌x���Ώ����p�}�N��
#include "dinput.h"												//���͏����ɕK�v
#include "Xinput.h"												//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//���C�u�����̃����N
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma comment(lib,"d3d9.lib")									//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")								//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")								//�W���C�p�b�h�����ɕK�v

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CLASS_NAME "windowClass"								//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "Score Run"							//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280)										//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)										//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define ID_BUTTON_FINISH (101)								//�I���{�^����ID
#define ID_BUTTON_COPY (102)									//�R�s�[�{�^����ID
#define ID_EDIT_INPUT (111)									//���̓E�B���h�E��ID
#define ID_EDIT_OUTPUT (121)									//�o�̓{�^����ID
#define ID_TIMER (122)										//�^�C�}�[��ID
#define ID_TIMER_INTERVAL (1000/60)							//�^�C�}�[�̔������ԊԊu(�~���b)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//���_���{2D}�̍\���̂̒�`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;											//���_���W
	float rhw;													//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;												//���_�J���[
	D3DXVECTOR2 tex;											//�e�N�X�`���̍��W
}VERTEX_2D;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//���(���[�h)�̎��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	MODE_TITLE = 0,												//�^�C�g�����
	MODE_GAME,													//�Q�[�����
	MODE_RESULT,												//���U���g���
	MODE_MAX
}MODE;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
void DrawFPS(void);
MODE GetMode(void);

#endif

