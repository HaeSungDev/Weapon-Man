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

            GetDlgItemText(hDlg, IDC_EDIT1, str[0], 40);           //각각 에디트로부터 정보를 받아옴
            GetDlgItemText(hDlg, IDC_EDIT2, str[1], 40);
            GetDlgItemText(hDlg, IDC_EDIT3, str[2], 40);
            GetDlgItemText(hDlg, IDC_EDIT4, str[3], 40);
            GetDlgItemText(hDlg, IDC_EDIT5, str[4], 40);
            
            for(int i = 0;i < 5;++i)
            {
                WideCharToMultiByte(CP_ACP, 0, str[i], -1, str_a[i], 40, NULL, NULL);       //유니코드를 아스키코드로 변경
            }

            fopen_s(&fp, ".\\Ranking\\Ranking.lhs", "at");
            if(fp == NULL)
            {
                if(MessageBox(hDlg, L"외부에서 Load 되는 맵 파일이 없습니다.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
                {
                    DestroyWindow(hDlg);        //로드 실패시 프로그램 종료
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
        if(MessageBox(hWnd, L"외부에서 Load 되는 맵 파일이 없습니다.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
        {
            DestroyWindow(hWnd);        //로드 실패시 프로그램 종료
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

    map.saveMap(iMap);      //맵 파일 저장
    map.saveBitmap(hWnd);   //맵 및 배경화면 비트맵 저장

    player_1.setIPlayer(1);     //플레이어 번호 설정
    player_1.setMap(iMap);      //맵 파일 저장
    player_1.saveBitmap(hWnd);  //캐릭터 비트맵 저장
    player_1.saveWeaponBitmap(hWnd);    //무기 비트맵 저장
    
    player_2.setIPlayer(2);
    player_2.setMap(iMap);      //맵 파일 저장
    player_2.saveBitmap(hWnd);  //캐릭터 비트맵 저장
    player_2.saveWeaponBitmap(hWnd);    //무기 비트맵 저장

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

    map.printBack(hdc);         //배경화면 출력
    map.printMap(hdc);          //맵 출력
    
    player_1.bombPrint(hdc);    //폭탄 출력
    player_2.bombPrint(hdc);    //폭탄 출력
    mon.bombPrint(hdc);     //폭탄 출력

    player_1.popPrint(hdc);     //폭파 출력
    player_2.popPrint(hdc);     //폭파 출력

    mon.popPrint(hdc);

    mon.monsterPrint(hdc);      //몬스터 출력
    
    if( player_1.getILife() )
    {
        player_1.charPrint(hdc);    //캐릭터 출력
    }
    if( player_2.getILife() )
    {
        player_2.charPrint(hdc);    //캐릭터 출력
    }
}

void Manage::manageCol(Player &player, int iDirection)
{
    /* 캐릭터가 아이템을 먹었는지 충돌체크 */

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
    
    /* map과 캐릭터 충돌체크 */

    for(int i = 0;i < YMAP;++i)
    {
        for(int j = 0;j < XMAP;++j)
        {
            if(iMap[i][j] != 0 && iMap[i][j] != 3 && iMap[i][j] != 4 && iMap[i][j] != 5)
            {
                switch(iDirection)
                {
                case VK_UP:

                    if( !player.rectCol(player.getICharX(), player.getICharY()+player.getISpeed(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //충돌체크 전 겹쳐있는지 체크
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //충돌체크
                        {
                            return;
                        }
                    }
                    break;

                case VK_DOWN:

                    if( !player.rectCol(player.getICharX(), player.getICharY()-player.getISpeed(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //충돌체크 전 겹쳐있는지 체크
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //충돌체크
                        {
                            return;
                        }
                    }
                    break;

                case VK_LEFT:

                    if( !player.rectCol(player.getICharX()+player.getISpeed(), player.getICharY(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //충돌체크 전 겹쳐있는지 체크
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //충돌체크
                        {
                            return;
                        }
                    }
                    break;

                case VK_RIGHT:

                    if( !player.rectCol(player.getICharX()-player.getISpeed(), player.getICharY(), WICHAR, HECHAR, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )     //충돌체크 전 겹쳐있는지 체크
                    {
                        if( player.charCol(iDirection, j*MAPSIZE+5, i*MAPSIZE+5, MAPSIZE-10, MAPSIZE-30) )      //충돌체크
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
        /* 캐릭터가 이동하지 않을 때 변수를 초기화시켜줌 */
        if( !(GetKeyState('W') & 0x8000) && !(GetKeyState('S') & 0x8000) &&
            !(GetKeyState('A') & 0x8000) && !(GetKeyState('D') & 0x8000) )
        {
            bTimer_1 = true;
        }

        if( GetKeyState('W') & 0x8000 )       //VK_UP이 눌렸는지 안눌렸는지 확인
        {
            player_1.charMove(VK_UP);       //이동
            manageCol(player_1, VK_UP);       //충돌체크
        }

        if( GetKeyState('S') & 0x8000 )     //VK_DOWN이 눌렸는지 안눌렸는지 확인
        {
            player_1.charMove(VK_DOWN);     //이동
            manageCol(player_1, VK_DOWN);       //충돌체크
        }

        if( GetKeyState('A') & 0x8000 )     //VK_LEFT이 눌렸는지 안눌렸는지 확인
        {
            player_1.charMove(VK_LEFT);     //이동
            manageCol(player_1, VK_LEFT);       //충돌체크
        }

        if( GetKeyState('D') & 0x8000 )     //VK_RIGHT이 눌렸는지 안눌렸는지 확인
        {
            player_1.charMove(VK_RIGHT);        //이동
            manageCol(player_1, VK_RIGHT);        //충돌체크
        }

        if( GetKeyState(VK_TAB) & 0x8000 )     //폭탄설치
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
        /* 캐릭터가 이동하지 않을 때 변수를 초기화시켜줌 */
        if( !(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_DOWN) & 0x8000) &&
            !(GetKeyState(VK_LEFT) & 0x8000) && !(GetKeyState(VK_RIGHT) & 0x8000) )
        {
            bTimer_2 = true;
        }

        if( GetKeyState(VK_UP) & 0x8000 )       //VK_UP이 눌렸는지 안눌렸는지 확인
        {
            player_2.charMove(VK_UP);       //이동
            manageCol(player_2, VK_UP);       //충돌체크
        }

        if( GetKeyState(VK_DOWN) & 0x8000 )     //VK_DOWN이 눌렸는지 안눌렸는지 확인
        {
            player_2.charMove(VK_DOWN);     //이동
            manageCol(player_2, VK_DOWN);       //충돌체크
        }

        if( GetKeyState(VK_LEFT) & 0x8000 )     //VK_LEFT이 눌렸는지 안눌렸는지 확인
        {
            player_2.charMove(VK_LEFT);     //이동
            manageCol(player_2, VK_LEFT);       //충돌체크
        }

        if( GetKeyState(VK_RIGHT) & 0x8000 )     //VK_RIGHT이 눌렸는지 안눌렸는지 확인
        {
            player_2.charMove(VK_RIGHT);        //이동
            manageCol(player_2, VK_RIGHT);        //충돌체크
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

            MessageBox(hWnd, L"Game Over!\n다시 도전해주세요!", L"System", MB_OK);
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
            manageCtrl_1();       //키입력타이머
        }
        
        if( player_2.getBDead() )
        {   
            player_2.dead();
        }
        else if( !player_2.getBDead() && player_2.getILife() > 0 )
        {
            manageCtrl_2();     //키입력 타이머
        }

        break;

    case 2:

        if(bTimer_1)        //움직였을떄 제자리 모습으로 돌아오게해주는 타이머
        {
            player_1.setIBitX(1);

            bTimer_1 = false;
        }
        if(bTimer_2)        //움직였을떄 제자리 모습으로 돌아오게해주는 타이머
        {
            player_2.setIBitX(1);

            bTimer_2 = false;
        }
        
        break;

    case 3:     //폭탄 애니메이션 타이머

        player_1.bombAni();
        player_1.bombTimer();

        player_2.bombAni();
        player_2.bombTimer();

        mon.bombAni();
        mon.bombTimer();

        break;

    case 4:     //폭파 애니메이션 타이머
        
        player_1.popAni(player_2.getBomb(), mon.getBomb(), player_2.getIBombNum(), mon.getIBombNum());
        if( !bPower_1 )
        {
            player_1.playerDead(player_1);      //플레이어가 죽었는지 체크
            player_1.playerDead(player_2);
            playerDead(mon, player_1);      //몬스터의 폭탄과 충돌체크
        }

        player_2.popAni(player_1.getBomb(), mon.getBomb(), player_1.getIBombNum(), mon.getIBombNum());
        if( !bPower_2 )
        {
            player_2.playerDead(player_2);      //플레이어가 죽었는지 체크
            player_2.playerDead(player_1);
            playerDead(mon, player_2);  //몬스터 폭탄과 충돌체크
        }

        mon.popAni(player_1.getBomb(), player_2.getBomb(), player_1.getIBombNum(), player_2.getIBombNum());

        mon.decreaseHP(iMap, player_1);     //몬스터의 HP가 폭탄에 맞았을때 HP 감소
        mon.decreaseHP(iMap, player_2);     //몬스터의 HP가 폭탄에 맞았을떄 HP 감소

        break;

    case 5:

        mon.attack();       //몬스터가 공격을 함

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

                /* 캐릭터가 폭파에 맞았는지 충돌체크 */
                for(int j = 0;j <= bomb[i].getIBombPow();++j)
                {
                    /* 캐릭터가 폭파에 맞았는지 충돌체크 */
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
        if(MessageBox(hWnd, L"외부에서 Load 되는 맵 파일이 없습니다.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
        {
            DestroyWindow(hWnd);        //로드 실패시 프로그램 종료
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