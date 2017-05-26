#pragma once
class Manage
{
    bool bGame;     //���� ���� ����

    int iMap[YMAP][XMAP];       //�� �迭

    Map map;    //�� ����
    Player player_1;     //ĳ���� ����
    Player player_2;    //2p ����
    Monster mon;    //���� ����

    bool bTimer_1;      //Ÿ�̸� ���� ����
    bool bTimer_2;      //Ÿ�̸� ���� ����

    bool bPush_1;     //��ź ��ġ ��ư�� ������ ������ Ȯ��
    bool bPush_2;     //��ź ��ġ ��ư�� ������ ������ Ȯ��

    bool bPower_1;      //1p�� ���� �������� Ȯ��
    bool bPower_2;      //2p�� ���� �������� Ȯ��

public:

    Manage(void);
    ~Manage(void);

    bool getBGame();
    void startGame();

    void manageCreate(HWND &hWnd);    //������ ������ ó�����۾�

    void managePrint(HDC hdc);     //��� ����

    void manageCol(Player &player, int iDirection);       //�浹üũ ����
    void manageCtrl_1();     //1p ��Ʈ�� ����
    void manageCtrl_2();     //2p ��Ʈ�� ����

    void manageTimer(HWND& hWnd, HINSTANCE &hInst, WPARAM &wParam);     //Ÿ�̸� ����

    void playerDead(Monster &mon, Player &player);      //���� ��ź�� ���� �÷��̾�

    void allClear(HWND &hWnd);        //��� ������ �ʱ�ȭ

    void reviveChar();      //ĳ������ ����� ������ ��Ȱ
};

