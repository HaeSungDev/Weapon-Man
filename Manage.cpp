#include "StdAfx.h"
#include "Manage.h"

static double DRecord;

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    FILE *fp;
    char str_a[5][40];
    TCHAR str[5][40];

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:

        DRecord = (timeGetTime()-DRecord)*0.001;

        SetDlgItemInt(hDlg, IDC_EDIT5, DRecord, true);

		return (INT_PTR)TRUE;

	case WM_COMMAND:

        switch(LOWORD(wParam))
        {
        case IDOK:

            GetDlgItemText(hDlg, IDC_EDIT1, str[0], 40);           //���� ����Ʈ�κ��� ������ �޾ƿ�
            GetDlgItemText(hDlg, IDC_EDIT2, str[1], 40);
            GetDlgItemText(hDlg, IDC_EDIT3, str[2], 40);
            GetDlgItemText(hDlg, IDC_EDIT4, str[3], 40);
            GetDlgItemText(hDlg, IDC_EDIT5, str[4], 40);
            
            for(int i = 0;i < 5;++i)
            {
                WideCharToMultiByte(CP_ACP, 0, str[i], -1, str_a[i], 40, NULL, NULL);       //�����ڵ带 �ƽ�Ű�ڵ�� ����
            }

            fopen_s(&fp, ".\\Ranking\\Ranking.lhs", "at");
            if(fp == NULL)
            {
                if(MessageBox(hDlg, L"�ܺο��� Load �Ǵ� �� ������ �����ϴ�.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
                {
                    DestroyWindow(hDlg);        //�ε� ���н� ���α׷� ����
                }
            }


            fprintf_s(fp, "%s ", str_a[4]);
            for(int i = 0;i < 4;++i)
            {
                if( i == 3 )
                {
                    fprintf_s(fp, "|%s ", str_a[i]);
                }
                else
                {
                    fprintf_s(fp, "%s ", str_a[i]);
                }
            }
            fprintf_s(fp, "\n");

            fclose(fp);

			EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            
            break;

        case IDCANCEL:

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

            break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

Manage::Manage(void)
{
    bTimer_1 = false;
    bTimer_2 = false;

    bPush_1 = false;
    bPush_2 = false;

    bPower_1 = false;
    bPower_2 = false;
}
Manage::~Manage(void)
{
}

bool Manage::getBGame()
{
    return bGame;
}
void Manage::startGame()
{
    bGame = true;

    DRecord = timeGetTime();
}

void Manage::manageCreate(HWND &hWnd)
{   
    FILE* fp = NULL;

    fopen_s(&fp, ".\\Map\\map.txt", "rt");
    if(fp == NULL)
    {
        if(MessageBox(hWnd, L"�ܺο��� Load �Ǵ� �� ������ �����ϴ�.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
        {
            DestroyWindow(hWnd);        //�ε� ���н� ���α׷� ����
        }
    }

    for(int i = 0;i < YMAP;++i)
    {
        for(int j = 0;j < XMAP;++j)
        {
            fscanf_s(fp, "%d", &iMap[i][j]);
        }
    }

    fclose(fp);

    map.saveMap(iMap);      //�� ���� ����
    map.saveBitmap(hWnd);   //�� �� ���ȭ�� ��Ʈ�� ����

    player_1.setIPlayer(1);     //�÷��̾� ��ȣ ����
    player_1.setMap(iMap);      //�� ���� ����
    player_1.saveBitmap(hWnd);  //ĳ���� ��Ʈ�� ����
    player_1.saveWeaponBitmap(hWnd);    //���� ��Ʈ�� ����
    
    player_2.setIPlayer(2);
    player_2.setMap(iMap);      //�� ���� ����
    player_2.saveBitmap(hWnd);  //ĳ���� ��Ʈ�� ����
    player_2.saveWeaponBitmap(hWnd);    //���� ��Ʈ�� ����

    mon.saveBitmap(hWnd);
    mon.saveWeaponBitmap(hWnd);
    mon.setMap(iMap);

    for(int i = 0;i < MAXBOMB;++i)
    {
        if( mon.getIBombNum() < MAXBOMB )
        {
            mon.increaseNum();
        }
        if( mon.getIBombPow() < MAXPOW-3 )
        {
            mon.increasePow();
        }
    }
}

void Manage::managePrint(HDC hdc)
{
    mon.energyPrint(hdc);

    map.printBack(hdc);         //���ȭ�� ���
    map.printMap(hdc);          //�� ���
    
    player_1.bombPrint(hdc);    //��ź ���
    player_2.bombPrint(hdc);    //��ź ���
    mon.bombPrint(hdc);     //��ź ���

    player_1.popPrint(hdc);     //���� ���
    player_2.popPrint(hdc);     //���� ���

    mon.popPrint(hdc);

    mon.monsterPrint(hdc);      //���� ���
    
    if( player_1.getILife() )
    {
        player_1.charPrint(hdc);    //ĳ���� ���
    }
    if( player_2.getILife() )
    {
        player_2.charPrint(hdc);    //ĳ���� ���
    }
}

void Manage::manageCol(Player &player, int iDirection)
{
    /* ĳ���Ͱ� �������� �Ծ����� �浹üũ */

    int tempX = (player.getICharX()+WICHAR/2)/MAPSIZE;
    int tempY = (player.getICharY()+HECHAR/2)/MAPSIZE;

    switch(iMap[tempY][tempX])
    {
    case 3:

        player.eatBombPow();
        iMap[tempY][tempX] = 0;

        break;

    case 4:

        player.eatBombNum();
        iMap[tempY][tempX] = 0;

        break;

    case 5:

        player.eatSpeed();
        iMap[tempY][tempX] = 0;

        break;
    }
    
    /* map�� ĳ���� �浹üũ */

    for(int i = 0;i < YMAP;++i)
    {
        for(int j = 0;j < XMAP;++j)
        {
            if(iMap[i][j] != 0 && iMap[i][j] != 3 && iMap[i][j] != 4 && iMap[i][j] != 5)
            {
                switch(iDirection)
                {
                case VK_UP:

                    if( !player.rectCol(player.getICharX(), player.getICharY()+player.getISpeed(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //�浹üũ �� �����ִ��� üũ
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //�浹üũ
                        {
                            return;
                        }
                    }
                    break;

                case VK_DOWN:

                    if( !player.rectCol(player.getICharX(), player.getICharY()-player.getISpeed(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //�浹üũ �� �����ִ��� üũ
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //�浹üũ
                        {
                            return;
                        }
                    }
                    break;

                case VK_LEFT:

                    if( !player.rectCol(player.getICharX()+player.getISpeed(), player.getICharY(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //�浹üũ �� �����ִ��� üũ
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //�浹üũ
                        {
                            return;
                        }
                    }
                    break;

                case VK_RIGHT:

                    if( !player.rectCol(player.getICharX()-player.getISpeed(), player.getICharY(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //�浹üũ �� �����ִ��� üũ
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //�浹üũ
                        {
                            return;         
                        }
                    }
                    break;
                }
            }
        }
    }
}
void Manage::manageCtrl_1()
{
    if( !player_1.getBDead() )
    {
        /* ĳ���Ͱ� �̵����� ���� �� ������ �ʱ�ȭ������ */
        if( !(GetKeyState('W') & 0x8000) && !(GetKeyState('S') & 0x8000) &&
            !(GetKeyState('A') & 0x8000) && !(GetKeyState('D') & 0x8000) )
        {
            bTimer_1 = true;
        }

        if( GetKeyState('W') & 0x8000 )       //VK_UP�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_1.charMove(VK_UP);       //�̵�
            manageCol(player_1, VK_UP);       //�浹üũ
        }

        if( GetKeyState('S') & 0x8000 )     //VK_DOWN�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_1.charMove(VK_DOWN);     //�̵�
            manageCol(player_1, VK_DOWN);       //�浹üũ
        }

        if( GetKeyState('A') & 0x8000 )     //VK_LEFT�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_1.charMove(VK_LEFT);     //�̵�
            manageCol(player_1, VK_LEFT);       //�浹üũ
        }

        if( GetKeyState('D') & 0x8000 )     //VK_RIGHT�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_1.charMove(VK_RIGHT);        //�̵�
            manageCol(player_1, VK_RIGHT);        //�浹üũ
        }

        if( GetKeyState(VK_TAB) & 0x8000 )     //��ź��ġ
        {
            if( bPush_1 )
            {
                int tempX = (player_1.getICharX()+WICHAR/2)/MAPSIZE;
                int tempY = (player_1.getICharY()+HECHAR/2)/MAPSIZE;

                player_1.bombPut(tempX, tempY);

                bPush_1 = false;
            }
        }
        else
        {
            bPush_1 = true;
        }
    }
}
void Manage::manageCtrl_2()
{
    if( !player_2.getBDead() )
    {
        /* ĳ���Ͱ� �̵����� ���� �� ������ �ʱ�ȭ������ */
        if( !(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_DOWN) & 0x8000) &&
            !(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000) )
        {
            bTimer_2 = true;
        }

        if( GetKeyState(VK_UP) & 0x8000 )       //VK_UP�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_2.charMove(VK_UP);       //�̵�
            manageCol(player_2, VK_UP);       //�浹üũ
        }

        if( GetKeyState(VK_DOWN) & 0x8000 )     //VK_DOWN�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_2.charMove(VK_DOWN);     //�̵�
            manageCol(player_2, VK_DOWN);       //�浹üũ
        }

        if( GetKeyState(VK_LEFT) & 0x8000 )     //VK_LEFT�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_2.charMove(VK_LEFT);     //�̵�
            manageCol(player_2, VK_LEFT);       //�浹üũ
        }

        if( GetKeyState(VK_RIGHT) & 0x8000 )     //VK_RIGHT�� ���ȴ��� �ȴ��ȴ��� Ȯ��
        {
            player_2.charMove(VK_RIGHT);        //�̵�
            manageCol(player_2, VK_RIGHT);        //�浹üũ
        }

        if( GetKeyState(VK_RSHIFT) & 0x8000 )
        {
            if( bPush_2 )
            {
                int tempX = (player_2.getICharX()+WICHAR/2)/MAPSIZE;
                int tempY = (player_2.getICharY()+HECHAR/2)/MAPSIZE;

                player_2.bombPut(tempX, tempY);

                bPush_2 = false;
            }
        }
        else
        {
            bPush_2 = true;
        }
    }
}

void Manage::manageTimer(HWND& hWnd, HINSTANCE &hInst, WPARAM &wParam)
{
    switch(wParam)
    {
    case 1:

        reviveChar();

        if( player_1.getILife() <= 0 && player_2.getILife() <= 0 )
        {
            player_1.dead();
            player_2.dead();

            bGame = false;

            MessageBox(hWnd, L"Game Over!\n�ٽ� �������ּ���!", L"System", MB_OK);
        }
        else if( player_1.getILife() <= 0 && mon.getBDead() )
        {
            allClear(hWnd);

            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
        }
        else if( player_2.getILife() <= 0 && mon.getBDead() )
        {
            allClear(hWnd);

            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
        }
        
        if( player_1.getBDead() )
        {   
            player_1.dead();
        }
        else if( !player_1.getBDead() && player_1.getILife() > 0 )
        {
            manageCtrl_1();       //Ű�Է�Ÿ�̸�
        }
        
        if( player_2.getBDead() )
        {   
            player_2.dead();
        }
        else if( !player_2.getBDead() && player_2.getILife() > 0 )
        {
            manageCtrl_2();     //Ű�Է� Ÿ�̸�
        }

        break;

    case 2:

        if(bTimer_1)        //���������� ���ڸ� ������� ���ƿ������ִ� Ÿ�̸�
        {
            player_1.setIBitX(1);

            bTimer_1 = false;
        }
        if(bTimer_2)        //���������� ���ڸ� ������� ���ƿ������ִ� Ÿ�̸�
        {
            player_2.setIBitX(1);

            bTimer_2 = false;
        }
        
        break;

    case 3:     //��ź �ִϸ��̼� Ÿ�̸�

        player_1.bombAni();
        player_1.bombTimer();

        player_2.bombAni();
        player_2.bombTimer();

        mon.bombAni();
        mon.bombTimer();

        break;

    case 4:     //���� �ִϸ��̼� Ÿ�̸�
        
        player_1.popAni(player_2.getBomb(), mon.getBomb(), player_2.getIBombNum(), mon.getIBombNum());
        if( !bPower_1 )
        {
            player_1.playerDead(player_1);      //�÷��̾ �׾����� üũ
            player_1.playerDead(player_2);
            playerDead(mon, player_1);      //������ ��ź�� �浹üũ
        }

        player_2.popAni(player_1.getBomb(), mon.getBomb(), player_1.getIBombNum(), mon.getIBombNum());
        if( !bPower_2 )
        {
            player_2.playerDead(player_2);      //�÷��̾ �׾����� üũ
            player_2.playerDead(player_1);
            playerDead(mon, player_2);  //���� ��ź�� �浹üũ
        }

        mon.popAni(player_1.getBomb(), player_2.getBomb(), player_1.getIBombNum(), player_2.getIBombNum());

        mon.decreaseHP(iMap, player_1);     //������ HP�� ��ź�� �¾����� HP ����
        mon.decreaseHP(iMap, player_2);     //������ HP�� ��ź�� �¾����� HP ����

        break;

    case 5:

        mon.attack();       //���Ͱ� ������ ��

        break;
    }
}

void Manage::playerDead(Monster &mon, Player &player)
{
    if( !player.getBDead() )
    {
        Bomb *bomb = mon.getBomb();

        int iX = (player.getICharX()+WICHAR/2)/MAPSIZE;
        int iY = (player.getICharY()+HECHAR/2)/MAPSIZE;

        int tempX;
        int tempY;

        for(int i = 0;i < mon.getIBombNum();++i)
        {
            if( bomb[i].getIUse() == 2 && bomb[i].getIPopAni() < 3 )
            {
                tempX = bomb[i].getIBombX();
                tempY = bomb[i].getIBombY();

                /* ĳ���Ͱ� ���Ŀ� �¾Ҵ��� �浹üũ */
                for(int j = 0;j <= bomb[i].getIBombPow();++j)
                {
                    /* ĳ���Ͱ� ���Ŀ� �¾Ҵ��� �浹üũ */
                    for(int j = 0;j <= bomb[i].getIBombPow();++j)
                    {
                        if( j <= bomb[i].getICol()[0] )
                        {
                            if( (iY == tempY-j) && (iX == tempX) )
                            {
                                player.setBDead(true);
                                player.setITime(timeGetTime());

                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[1] )
                        {
                            if( (iY == tempY+j) && (iX == tempX) )
                            {
                                player.setBDead(true);
                                player.setITime(timeGetTime());

                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[2] )
                        {
                            if( (iX == tempX-j) && (iY == tempY) ) 
                            {
                                player.setBDead(true);
                                player.setITime(timeGetTime());

                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[3] )
                        {
                            if( (iX == tempX+j) && (iY == tempY) ) 
                            {
                                player.setBDead(true);
                                player.setITime(timeGetTime());

                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Manage::allClear(HWND &hWnd)
{
    bGame = false;

    player_1.allClear();
    player_1.playerClear();
    player_1.setBDead(false);

    player_2.allClear();
    player_2.playerClear();
    player_2.setBDead(false);

    mon.monsterClear(iMap);

    FILE* fp = NULL;

    ZeroMemory(iMap, sizeof(iMap));

    fopen_s(&fp, ".\\Map\\map.txt", "rt");
    if(fp == NULL)
    {
        if(MessageBox(hWnd, L"�ܺο��� Load �Ǵ� �� ������ �����ϴ�.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
        {
            DestroyWindow(hWnd);        //�ε� ���н� ���α׷� ����
        }
    }

    for(int i = 0;i < YMAP;++i)
    {
        for(int j = 0;j < XMAP;++j)
        {
            fscanf_s(fp, "%d", &iMap[i][j]);
        }
    }

    fclose(fp);
}

void Manage::reviveChar()
{
    if( timeGetTime()-player_1.getITime() >= 3500 )
    {
        if( bPower_1 )
        {
            bPower_1 = false;
        }

        if( player_1.getBDead() && player_1.getILife() )
        {
            player_1.playerClear();
            player_1.setILife(player_1.getILife()-1);

            player_1.setITime(timeGetTime());

            bPower_1 = true;
        }
    }
    if( timeGetTime()-player_2.getITime() >= 3500)
    {
        if( bPower_2 )
        {
            bPower_2 = false;
        }

        if( player_2.getBDead() && player_2.getILife() )
        {
            player_2.playerClear();
            player_2.setILife(player_2.getILife()-1);

            player_2.setITime(timeGetTime());
            
            bPower_2 = true;
        }
    }
}