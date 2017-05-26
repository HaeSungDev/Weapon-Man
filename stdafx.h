// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma comment(lib, "msimg32.lib")     //transparentBlt�� �������ִ� ���̺귯�� ����
#pragma comment(lib, "winmm.lib")       //MMSystem.h�� timeGetTime�� ������ �ִ� ���̺귯���� ����

#include "targetver.h"

#define RANKMODE 1      //��ũ��� ����
#define BATTLEMODE 2    //��Ʋ��� ����

#define WINSIZE 650      //������ ������

#define MAXLIFE 3       //��� ����

#define WICHAR 40        //ĳ������ �ʺ� ����
#define HECHAR 60       //ĳ������ ���� ����

#define WMON 70         //������ �ʺ� ����
#define HMON 70         //������ ���� ����

#define XMON 6          //�� �迭���� ������ x���
#define YMON 6          //�� �迭���� ������ y���

#define MAXSPEED 5     //ĳ���� �ְ� �ӵ�

#define MAXBOMB 7       //�ִ� �������ִ� ��ź ����
#define MAXPOW  5       //�ִ� �������ִ� ��ź �Ŀ�

#define BOMBTIME 250      //��ź Ÿ�̸� ȣ�� �ð�

#define MAPSIZE 50  //���� ũ��

#define WIMENU 144  //�޴��� �ʺ� ����
#define HEMENU 39  //�޴��� ���� ����

#define XMAP 13     //x�� ������
#define YMAP 13     //y�� ������

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <MmSystem.h>
#include "resource.h"
#include "Ranking.h"
#include "Userinterface.h"
#include "Bomb.h"
#include "Weapon.h"
#include "Character.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Manage.h"

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
