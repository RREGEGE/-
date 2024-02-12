#pragma once
#include"setting.h"
#include<iostream>
#include<cstdlib>
#include<windows.h>
#include <conio.h>

#ifndef __COLOR_LIST_
#define __COLOR_LIST_//사용할 색상을 미리 열거형으로 지정

enum
{
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};

#endif


int MAP_X_MAX = 75; //콘솔의 최대 크기 X,Y를 정의
int MAP_Y_MAX = 30;

//콘솔 창의 크기와 제목을 지정하는 함수 , 콘솔창의 x,y값은 그래프의 제2사분면이라고 생각하면 쉽다.
void set_console() {
	system("title 윷놀이 게임"); // 콘솔창 이름 설정
	system("mode con:cols=75 lines=30"); // 콘솔창 크기설정;

}
//제목 그리기
void title_draw()
{
	
	set_color(white, brown);
	cout << "□□□■■■■■■■□□□□□■□□□□□□□□□□□□□□□□□□□■□\n";
	cout << "□□■■□□□□□■■□□□□■□□□□□□□□□□□■■■■□□□□■□\n";
	cout << "□□■■□□□□□■■□□□□■□□□□□□□□□□■■□□■■□□□■□\n";
	cout << "□□□■■■■■■■□□□□□■■■■■■■■■□□■□□□□■□□□■□\n";
	cout << "□□□□□□□□□□□□□□□□□□□■□□□□□□■□□□□■□□□■□\n";
	cout << "■■■■■■■■■■■■■□■■■■■■■■■■■□■□□□□■□□□■□\n";
	cout << "□□□■■□□□■■□□□□□□□□□□□□□□□□■□□□□■□□□■□\n";
	cout << "□□□□■□■□■□□□□□□■■■■■■■■□□□■■□□■■□□□■□\n";
	cout << "□□■■■■■■■■■□□□□□□□□□□□■□□□□■■■■□□□□■□\n";
	cout << "□□□□□■■■□□□□□□□■■■■■■■■□□□□□□□□□□□□■□\n";
	cout << "□□□□■■□■■□□□□□□■□□□□□□□□□□□□□□□□□□□■□\n";
	cout << "□□■■■□□□■■■□□□□■■■■■■■■■□□□□□□□□□□□■□\n";
	set_color(white, black);

}


//커서 이동, 해당 위치로 커서를 이동시켜 원하는 위치에 출력을 할 수 있게 한다.
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//콘솔의 핸들값 (ID)
	COORD Cur{}; //선언되어 있는 x, y 값을 저장하는 구조체
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(consoleHandle, Cur);//"콘솔의 핸들 값"과 "좌표값"을 받아서, 해당 위치로 콘솔의 커서를 이동시킴!
}

//메뉴 그리기 1.게임시작 2.게임정보 3.게임종료
int menu_draw() //사용자에게 입력값을 받아 3가지 선택지중 실행되도록 한다.
{
	int x = (MAP_X_MAX / 2) - 7;
	int y = (MAP_Y_MAX / 2) + 2;
	int temp;
	gotoxy(x - 2, y);
	cout << "> 1. 게임 시작";
	gotoxy(x, y + 2);
	cout << "0. 게임 종료  \n";
	cin >> temp;
	return temp;
}

void set_color(int forground, int background)//콘솔창의 색상을 변경하는데 쓰이는 함수, 앞 파라미터로 글자색, 뒤 파라미터로 배경색이 된다
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}
