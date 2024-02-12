#pragma once
#include "Yut.h"
#include <iostream>

class Stone
{
public:
	Stone();
	~Stone();
	int move_check();
	
	int move_piece(Yut* yut);
public:
	// 말의 위치를 정할 변수들
	int x, y = 10;
	int _area=0;
	int _number=0;
	//이전 위치 지우기 위함
	int pre_x = 10;
	int pre_y = 10;
	std::string shape; // 말의 모양

};