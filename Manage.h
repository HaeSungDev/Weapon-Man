#pragma once
class Manage
{
    bool bGame;     //게임 실행 여부

    int iMap[YMAP][XMAP];       //맵 배열

    Map map;    //맵 선언
    Player player_1;     //캐릭터 선언
    Player player_2;    //2p 선언
    Monster mon;    //몬스터 선언

    bool bTimer_1;      //타이머 실행 여부
    bool bTimer_2;      //타이머 실행 여부

    bool bPush_1;     //폭탄 설치 버튼을 누르는 순간을 확인
    bool bPush_2;     //폭탄 설치 버튼을 누르는 순간을 확인

    bool bPower_1;      //1p가 무적 상태인지 확인
    bool bPower_2;      //2p가 무적 상태인지 확인

public:

    Manage(void);
    ~Manage(void);

    bool getBGame();
    void startGame();

    void manageCreate(HWND &hWnd);    //윈도우 생성시 처리할작업

    void managePrint(HDC hdc);     //출력 관리

    void manageCol(Player &player, int iDirection);       //충돌체크 관리
    void manageCtrl_1();     //1p 컨트롤 관리
    void manageCtrl_2();     //2p 컨트롤 관리

    void manageTimer(HWND& hWnd, HINSTANCE &hInst, WPARAM &wParam);     //타이머 관리

    void playerDead(Monster &mon, Player &player);      //몬스터 폭탄에 맞은 플레이어

    void allClear(HWND &hWnd);        //모든 게임을 초기화

    void reviveChar();      //캐릭터의 목숨이 있을때 부활
};

