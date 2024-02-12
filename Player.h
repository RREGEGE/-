#pragma once
#include <vector>
#include <iostream>
#include "Stone.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();
	void Make_stone(Stone* stone);
	void Together();
	int Eat(Player* opponent);
	void Location_share(int num);
	int End();

public:
	vector<Stone*> life; // 벡터안에 각 말들을 받음
	string _name; // 플레이어의 이름
	vector<bool> isTogether; // 위치가 같은지 저장하는 벡터 trur라면 위치가 같음
	int check; // 상대방의 말과 위치가 같다면 반환할 변수
};

