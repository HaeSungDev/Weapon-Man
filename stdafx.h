// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(lib, "msimg32.lib")     //transparentBlt을 가지고있는 라이브러리 연결
#pragma comment(lib, "winmm.lib")       //MMSystem.h의 timeGetTime을 가지고 있는 라이브러리에 연결

#include "targetver.h"

#define RANKMODE 1      //랭크모드 게임
#define BATTLEMODE 2    //배틀모드 게임

#define WINSIZE 650      //윈도우 사이즈

#define MAXLIFE 3       //목숨 개수

#define WICHAR 40        //캐릭터의 너비 길이
#define HECHAR 60       //캐릭터의 높이 길이

#define WMON 70         //몬스터의 너비 길이
#define HMON 70         //몬스터의 높이 길이

#define XMON 6          //맵 배열에서 몬스터의 x요소
#define YMON 6          //맵 배열에서 몬스터의 y요소

#define MAXSPEED 5     //캐릭터 최고 속도

#define MAXBOMB 7       //최대 가질수있는 폭탄 개수
#define MAXPOW  5       //최대 가질수있는 폭탄 파워

#define BOMBTIME 250      //폭탄 타이머 호출 시간

#define MAPSIZE 50  //맵의 크기

#define WIMENU 144  //메뉴의 너비 길이
#define HEMENU 39  //메뉴의 높이 길이

#define XMAP 13     //x축 블럭개수
#define YMAP 13     //y축 블럭개수

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
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

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
