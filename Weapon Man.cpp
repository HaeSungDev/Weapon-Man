// Weapon Man.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Weapon Man.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WEAPONMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WEAPONMAN));

	// 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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

CRITICAL_SECTION critical;      //멀티스레드의 임계영역 설정변수(메모리의 간섭이 안일어나게 함)
HANDLE hThread;     //쓰레드를 제어할수있는 핸들

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//

HBITMAP hBit = NULL;    //더블버퍼링을 위한 비트맵핸들
Manage game;        //게임을 위한 클래스
UserInterface ui;   //게임 실행 클래스
Ranking rank;       //게임 랭킹 클래스

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
    HDC hdc, memDC;
    HBITMAP oldBitmap;  //메모리 해제를 위한 임시저장소
    RECT rt;    //윈도우의 크기를 조사하기위한 변수

	switch (message)
	{
    case WM_CREATE:
        
        InitializeCriticalSection(&critical);

        hThread = CreateThread(NULL, 0, MusicThread, NULL, NULL, NULL);
        
        ui.saveBitmap(hWnd);
        game.manageCreate(hWnd);
        
        SetTimer(hWnd, 1, 10, NULL);     //키 입력받는 타이머 및 사망
        SetTimer(hWnd, 2, 250, NULL);   //캐릭터 제자리 모습으로 돌아오게하는 타이머
        SetTimer(hWnd, 3, BOMBTIME, NULL);   //폭탄 애니메이션 및 시간체크
        SetTimer(hWnd, 4, 75, NULL);    //폭파 애니메이션
        SetTimer(hWnd, 5, 6000, NULL);      //몬스터 폭탄 설치 패턴 애니메이션

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
                MessageBox(hWnd, L"    한림대학교 컴퓨터공학과\n              20125169\n                이해성", L"INFORMATION", MB_OK);
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
		// TODO: 여기에 그리기 코드를 추가합니다.

        GetClientRect(hWnd, &rt);   //윈도우의 크기 조사

        if( hBit == NULL )
        {
            hBit = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);    //hBit를 hdc에 호환되는 윈도우 크기의 비트맵으로 만들어줌
        }
        memDC = CreateCompatibleDC(hdc);    //hdc와 호환되는 메모리 dc를 만들어줌

        oldBitmap = (HBITMAP)SelectObject(memDC, hBit);   //메모리 dc의 비트맵을 hBit로 바꿔줌

        FillRect(memDC, &rt, WHITE_BRUSH);      //hBit를 하얀색 배경으로 채움
        
        /* 그리기 시작 */
        
        if( !game.getBGame() )
        {
            ui.interfacePrint(memDC);       //인터페이스를 그림
        }

        if( game.getBGame() )
        {
            game.managePrint(memDC);        //게임을 그림
        }
        else if( rank.getBRank() )
        {
            rank.rankPrint(memDC);      //랭크를 그림
        }

        /* 그리기 끝 */

        BitBlt(hdc, 0, 0, rt.right, rt.bottom, memDC, 0, 0, SRCCOPY);   //화면에 hBit를 출력

        SelectObject(memDC, oldBitmap);     //메모리 DC 해제를 위해 비트맵을 원래대로 바꿔줌
        DeleteDC(memDC);    //메모리 dc를 해제해줌

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
        
        DeleteObject(hBit);     //프로그램 종료시 hBit메모리 해제
        
        /* 타이머 해제 */
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        KillTimer(hWnd, 3);
        KillTimer(hWnd, 4);
        KillTimer(hWnd, 5);

        DeleteCriticalSection(&critical);       //크리티컬 섹션 제거
        CloseHandle(hThread);

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}