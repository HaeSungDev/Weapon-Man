#pragma once
class UserInterface     //�������̽��� ��������� Ŭ���� 
{
    bool bMenu[3];    //�޴� ���� ���콺�� �ִ��� üũ
    
    RECT menu[3];    //���� �޴� ��ǥ
    
    HBITMAP uiBit;      //�������̽� ��Ʈ��
    HBITMAP menuBit;    //�޴� ��Ʈ��
 
public:
    UserInterface(void);
    ~UserInterface(void);

    void saveBitmap(HWND &hWnd);        //��Ʈ�ʵ��� ���� 

    void interfacePrint(HDC &hdc);      //��Ʈ���� �������

    void checkMouse(int iX, int iY);    //���콺�� ��ġ �� Ŭ�� Ȯ��
    int checkClick(HWND &hWnd);    //���콺�� ��� Ŭ�� ������ üũ
};