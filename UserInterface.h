#pragma once
class UserInterface     //인터페이스를 만들기위한 클래스 
{
    bool bMenu[3];    //메뉴 위에 마우스가 있는지 체크
    
    RECT menu[3];    //게임 메뉴 좌표
    
    HBITMAP uiBit;      //인터페이스 비트맵
    HBITMAP menuBit;    //메뉴 비트맵
 
public:
    UserInterface(void);
    ~UserInterface(void);

    void saveBitmap(HWND &hWnd);        //비트맵들을 저장 

    void interfacePrint(HDC &hdc);      //비트맵을 출력해줌

    void checkMouse(int iX, int iY);    //마우스의 위치 및 클릭 확인
    int checkClick(HWND &hWnd);    //마우스가 어디를 클릭 했을때 체크
};