//=========================================================================================================
//
// 2D�A�N�V���� [main.cpp]
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
//���C���֐�
//=========================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�O���[�o���ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MODE g_mode = MODE_TITLE;												//���݂̃��[�h	
LPD3DXFONT g_pFont = NULL;												//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;													//FPS�ւ̃J�E���^

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;

//=========================================================================================================
//����������
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
	HWND hWnd;															//�E�B���h�E�n���h��(���ʎq)
	MSG msg;															//���b�Z�[�W���i�[
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };						//�E�B���h�E�N���X�̓o�^

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	RegisterClassEx(&wcex);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,														//�g���E�B���h�E�X�^�C��
		WINDOW_NAME,													//�E�B���h�E�N���X�̖��O
		WS_OVERLAPPEDWINDOW,											//�E�B���h�E�̖��O		
		CW_USEDEFAULT,													//�E�B���h�E����X���W
		CW_USEDEFAULT,													//�E�B���h�E����Y���W
		(rect.right - rect.left),										//�E�B���h�E����̕�
		(rect.bottom - rect.top),										//�E�B���h�E����̍���
		NULL,															//�e�E�B���h�E�̃n���h��
		NULL,															//���j���[�n���h��
		hInstance,														//�C���X�^���X�n���h��
		NULL);															//�E�B���h�E�쐬�f�[�^

	DWORD dwCurrentTime;												//���ݎ���
	DWORD dwExecLastTime;												//�Ō�ɏ�����������
	DWORD dwFrameCount;													//�t���[���ւ̃J�E���^
	DWORD dwFPSLastTime;												//�Ō��FPS���v����������

	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		//�����������s������
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;													//���ݎ���������������
	dwExecLastTime = timeGetTime();										//���ݎ������擾(�Ō�)
	dwFrameCount = 0;													//�t���[���J�E���^������������
	dwFPSLastTime = timeGetTime();										//FPS���擾��������(�Ō�)

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdshow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;						//FPS�𑪒肵��������ۑ�

				dwFrameCount = 0;									//�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//60����1�b�o��
				dwExecLastTime = dwCurrentTime;						//�����J�n�̎���(���ݎ���)��ۑ�

				//�X�V�ݒ�
				Update();

				//�`��ݒ�
				Draw();
				dwFrameCount++;										//�t���[���J�E���g�����Z
			}
		}
	}

	//����\��߂�
	timeEndPeriod(1);

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=========================================================================================================
//�E�B���h�E�v���V�[�W���̏���
//=========================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
	int nID;															//�Ԃ�l���i�[

	switch (umsg)
	{
	case WM_DESTROY:
		//WM_QUIT�̃��b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);
			if (nID == IDYES)
			{
				//�͂���I�񂾏ꍇ
				MessageBox(NULL, "�I��", "�I�����b�Z�[�W", MB_OK);
				DestroyWindow(hWnd);									//�E�B���h�E��j������(WM_DESTROY�ɑ���)
				break;
			}
			else if (nID == IDNO)
			{
				//��������I�񂾏ꍇ
				MessageBox(NULL, "���s", "�I�����b�Z�[�W", MB_OK);
			}
			break;
		}
	}
	return DefWindowProc(hWnd, umsg, wParam, lParam);					//�K��̏������J��Ԃ�
}

//=========================================================================================================
//����������
//=========================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//�Q�[����ʂ̃T�C�Y(���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//����
	d3dpp.BackBufferFormat = d3ddm.Format;								//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;											//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;								//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//�C���^�[�o��

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


	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�N�\���p�̃t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Teminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//���[�h�̐ݒ�
	SetMode(g_mode);

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}

//=========================================================================================================
//�v���C���[�̏���������
//=========================================================================================================
void Uninit(void)
{

	switch (g_mode)
	{
		//�^�C�g�����
	case MODE_TITLE:
		UninitTitle();
		break;

		//�Q�[�����
	case MODE_GAME:
		UninitGame();
		break;

		//���U���g���
	case MODE_RESULT:
		UninitResult();
		break;
	}

	//�t�F�[�h�̏I������
	UninitFade();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�Q�[���p�b�h�̏I������
	UninitJoypad();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();

		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();

		g_pD3D = NULL;
	}

	//�f�o�b�N�\���p�̃t�H���g�̐ݒ�
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�Q�[���p�b�h�̍X�V����
	UpdateJoypad();

	switch (g_mode)
	{
		//�^�C�g����ʂ̍X�V����
	case MODE_TITLE:
		UpdateTitle();
		break;

		//�Q�[����ʂ̍X�V����
	case MODE_GAME:
		UpdateGame();
		break;

		//���U���g��ʂ̍X�V����
	case MODE_RESULT:
		UpdateResult();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A�j
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
			//�^�C�g����ʂ̕`�揈��
		case MODE_TITLE:
			DrawTitle();
			break;

			//�Q�[����ʂ̕`�揈��
		case MODE_GAME:
			DrawGame();
			break;

			//���U���g��ʂ̕`�揈��
		case MODE_RESULT:
			DrawResult();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//FPS�̕\��
		DrawFPS();

		//�`��I��
		g_pD3DDevice->EndScene();

	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//=========================================================================================================
//FPS�̕\������
//=========================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//�f�o�C�X�̎擾
//=========================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================
//���[�h��ݒ�
//=========================================================================================================
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
		//�^�C�g�����
	case MODE_TITLE:
		UninitTitle();
		break;

		//�Q�[�����
	case MODE_GAME:
		UninitGame();
		break;

		//���U���g���
	case MODE_RESULT:
		UninitResult();
		break;
	}

	//���[�h�ݒ�(���)�̏���������
	switch (mode)
	{
		//�^�C�g�����
	case MODE_TITLE:
		InitTitle();
		break;

		//�Q�[�����
	case MODE_GAME:
		InitGame();
		break;

		//���U���g���
	case MODE_RESULT:
		InitResult();
		break;
	}

	//���݂̉��(���[�h)��؂�ւ���
	g_mode = mode;
}

//=========================================================================================================
//���[�h�̎擾
//=========================================================================================================
MODE GetMode(void)
{
	return g_mode;														//���݂̃��[�h��Ԃ�
}
