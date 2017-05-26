// Weapon Man.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Weapon Man.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WEAPONMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WEAPONMAN));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDC_WEAPONMAN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
      CW_USEDEFAULT, 0, WINSIZE+36, WINSIZE+28, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

CRITICAL_SECTION critical;      //��Ƽ�������� �Ӱ迵�� ��������(�޸��� ������ ���Ͼ�� ��)
HANDLE hThread;     //�����带 �����Ҽ��ִ� �ڵ�

DWORD WINAPI MusicThread(LPVOID prc)
{
    EnterCriticalSection(&critical);

    while(1)
    {
        PlaySound(L".\\Sound\\music1.wav", NULL, SND_FILENAME);
        PlaySound(L".\\Sound\\music2.wav", NULL, SND_FILENAME);
        PlaySound(L".\\Sound\\music3.wav", NULL, SND_FILENAME);
        PlaySound(L".\\Sound\\music4.wav", NULL, SND_FILENAME);
    }

    LeaveCriticalSection(&critical);

    return 0;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

HBITMAP hBit = NULL;    //������۸��� ���� ��Ʈ���ڵ�
Manage game;        //������ ���� Ŭ����
UserInterface ui;   //���� ���� Ŭ����
Ranking rank;       //���� ��ŷ Ŭ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
    HDC hdc, memDC;
    HBITMAP oldBitmap;  //�޸� ������ ���� �ӽ������
    RECT rt;    //�������� ũ�⸦ �����ϱ����� ����

	switch (message)
	{
    case WM_CREATE:
        
        InitializeCriticalSection(&critical);

        hThread = CreateThread(NULL, 0, MusicThread, NULL, NULL, NULL);
        
        ui.saveBitmap(hWnd);
        game.manageCreate(hWnd);
        
        SetTimer(hWnd, 1, 10, NULL);     //Ű �Է¹޴� Ÿ�̸� �� ���
        SetTimer(hWnd, 2, 250, NULL);   //ĳ���� ���ڸ� ������� ���ƿ����ϴ� Ÿ�̸�
        SetTimer(hWnd, 3, BOMBTIME, NULL);   //��ź �ִϸ��̼� �� �ð�üũ
        SetTimer(hWnd, 4, 75, NULL);    //���� �ִϸ��̼�
        SetTimer(hWnd, 5, 6000, NULL);      //���� ��ź ��ġ ���� �ִϸ��̼�

        break;

    case WM_MOUSEMOVE:

        if( !game.getBGame() && !rank.getBRank() )
        {
            ui.checkMouse(LOWORD(lParam), HIWORD(lParam));
        }
        break;

    case WM_LBUTTONDOWN:

        if( !game.getBGame() && !rank.getBRank() )
        {
            if( ui.checkClick(hWnd) == 0 )
            {
                MessageBox(hWnd, L"    �Ѹ����б� ��ǻ�Ͱ��а�\n              20125169\n                ���ؼ�", L"INFORMATION", MB_OK);
            }
            else if( ui.checkClick(hWnd) == 1 )
            {
                game.allClear(hWnd);
                game.startGame();
            }
            else if ( ui.checkClick(hWnd) == 2 )
            {
                rank.setBRank(true);
                rank.rankRead(hWnd);
            }
        }
        else if( rank.getBRank() )
        {
            rank.setBRank(false);
        }
        break;

    case WM_TIMER:

        if( game.getBGame() )
        {
            game.manageTimer(hWnd, hInst, wParam);
        }

        InvalidateRect(hWnd, NULL, FALSE);
        break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

        GetClientRect(hWnd, &rt);   //�������� ũ�� ����

        if( hBit == NULL )
        {
            hBit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);    //hBit�� hdc�� ȣȯ�Ǵ� ������ ũ���� ��Ʈ������ �������
        }
        memDC = CreateCompatibleDC(hdc);    //hdc�� ȣȯ�Ǵ� �޸� dc�� �������

        oldBitmap = (HBITMAP)SelectObject(memDC, hBit);   //�޸� dc�� ��Ʈ���� hBit�� �ٲ���

        FillRect(memDC, &rt, WHITE_BRUSH);      //hBit�� �Ͼ�� ������� ä��
        
        /* �׸��� ���� */
        
        if( !game.getBGame() )
        {
            ui.interfacePrint(memDC);       //�������̽��� �׸�
        }

        if( game.getBGame() )
        {
            game.managePrint(memDC);        //������ �׸�
        }
        else if( rank.getBRank() )
        {
            rank.rankPrint(memDC);      //��ũ�� �׸�
        }

        /* �׸��� �� */

        BitBlt(hdc, 0, 0, rt.right, rt.bottom, memDC, 0, 0, SRCCOPY);   //ȭ�鿡 hBit�� ���

        SelectObject(memDC, oldBitmap);     //�޸� DC ������ ���� ��Ʈ���� ������� �ٲ���
        DeleteDC(memDC);    //�޸� dc�� ��������

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
        
        DeleteObject(hBit);     //���α׷� ����� hBit�޸� ����
        
        /* Ÿ�̸� ���� */
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        KillTimer(hWnd, 3);
        KillTimer(hWnd, 4);
        KillTimer(hWnd, 5);

        DeleteCriticalSection(&critical);       //ũ��Ƽ�� ���� ����
        CloseHandle(hThread);

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}