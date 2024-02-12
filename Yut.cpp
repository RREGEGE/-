#include "Yut.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include"setting.h"

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


using namespace std;;
// 윷을 던지는 함수
void Yut::Throw() {
	sum = 0;
	srand(time(NULL));
	
	for (int i = 0; i < 4; i++) {
		gotoxy(i * 4+2, 16);
		num = rand() % 2;
		if (num == 0) {
			cout << "앞" << endl;

			sum++;
		}
		else {
			cout << "뒤" << endl;

		}
	}
	cout << endl;
}

// 윷을 던진 결과를 반환해주는 함수
int Yut::Result() {
	if (sum == 0) {
		result = 5;
		return result;
	}
	else if (sum == 1) {
		result = 1;
		return result;
	}
	else if (sum == 2) {
		result = 2;
		return result;
	}
	else if (sum == 3) {
		result = 3;
		return result;
	}
	else {
		result = 4;
		return result;
	}
	return 0;
}

// 윷을 던진 결과를 출력해주는 함수
void Yut::Speak() {
	gotoxy(2, 17);
	if (sum == 0) {
		cout << "모" << endl;
		
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
		cout << "┃ ■×■ ■×■ ■×■ ■×■\n";
		cout << "┃ ■×■ ■×■ ■×■ ■×■\n";
		cout << "┃ ■×■ ■×■ ■×■ ■×■\n";
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";

	}
	else if (sum == 1) {
		cout << "도" << endl;
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
		cout << "┃ ■□■ ■×■ ■×■ ■×■\n";
		cout << "┃ ■□■ ■×■ ■×■ ■×■\n";
		cout << "┃ ■□■ ■×■ ■×■ ■×■\n";
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
	}
	else if (sum == 2) {
		cout << "개" << endl;
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
		cout << "┃ ■□■ ■□■ ■×■ ■×■\n";
		cout << "┃ ■□■ ■□■ ■×■ ■×■\n";
		cout << "┃ ■□■ ■□■ ■×■ ■×■\n";
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
	}
	else if (sum == 3) {
		cout << "걸" << endl;
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
		cout << "┃ ■□■ ■□■ ■□■ ■×■\n";
		cout << "┃ ■□■ ■□■ ■□■ ■×■\n";
		cout << "┃ ■□■ ■□■ ■□■ ■×■\n";
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
	}
	else {
		cout << "윷" << endl;
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
		cout << "┃ ■□■ ■□■ ■□■ ■□■\n";
		cout << "┃ ■□■ ■□■ ■□■ ■□■\n";
		cout << "┃ ■□■ ■□■ ■□■ ■□■\n";
		cout << "┃ ■■■ ■■■ ■■■ ■■■\n";
	}
}