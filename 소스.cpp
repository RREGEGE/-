#include <iostream>
#include "Yut.h"
#include "Player.h"
#include "Stone.h"
#include "n_page.h"
#include"setting.h"
#include <Windows.h>
#include<iomanip>

using namespace std;;

int turn = 0;
int flag = 0;

string board[11][11]; //윷놀이 판을 출력할 2차원 string 배열 선언
int ctn = 48;//임시 말

#ifndef __COLOR_LIST_  //사용할 색상을 미리 열거형으로 지정
#define __COLOR_LIST_

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
void start_point(Player*); //출발하지 않은 말을 출력해주는 함수
void finish_point(Player*); //결승점을 통과한 말을 출력해주는 함수
void Watch_together(Player*); //업기 상태인 말을 출력해주는 함수
void Number_stone(Player*); // 말의 모양을 출력해주는 함수
int End_check(Player*); //게임이 끝나면 실행될 함수 = 말 3개가 모두 결승점을 통과

void Run(Player* player, Player* opponent) {
	Yut a;
	int stone_num;
	int count = 0;
	int j = 0;
	gotoxy(2, 14);
	cout << player->_name << "님 턴입니다.";
	a.Throw();
	a.Speak();
	a.Result();
	gotoxy(2, 28);
	cout << "움직일 말을 고르세요.(0,1,2 중에) :";
	cin >> stone_num;
	gotoxy(45, 18);
	cout << "                      ";
	while (true) {
		if (stone_num > 2) {
			gotoxy(2, 29);
			cout << "잘못 입력하셨습니다. 다시 입력하세요: ";
			cin >> stone_num;
		}
		else if (player->life[stone_num]->_area == 6) {
			gotoxy(2, 29);
			cout << "이미 도착한 말입니다. 다시 입력하세요: ";
			cin >> stone_num;
		}
		else {
			gotoxy(2, 29);
			cout << "                                         ";
			break;
		}
	}
	player->life[stone_num]->move_piece(&a);
	player->life[stone_num]->move_check();
	piece_location(player->life[stone_num], board);
	End_check(player);
	gotoxy(26, flag % 2 + 1);
	start_point(player);
	finish_point(player);
	player->Location_share(stone_num);
	gotoxy(2, 21);
	player->Together();
	gotoxy(26, flag % 2 + 4);
	Watch_together(player);
	player->Eat(opponent);
	if (a.Result() == 5 || a.Result() == 4 || player->check == 1) {
		if (a.Result() == 5 && player->Eat(opponent) || a.Result() == 4 && player->Eat(opponent)) {
			count += 2;
		}
		else {
			count++;
		}
	}
	gotoxy(26, (++flag) % 2 + 1);
	start_point(opponent);
	finish_point(opponent);
	gotoxy(26, (flag) % 2 + 4);
	Watch_together(opponent);

	while (count != 0) {
		gotoxy(45, 18);
		cout << "                      ";
		int j = 0;
		gotoxy(45, 16);
		cout << "한번 더 던집니다.";
		a.Throw();
		a.Speak();
		a.Result();
		gotoxy(2, 28);
		cout << "움직일 말을 고르세요.(0,1,2 중에) :";
		cin >> stone_num;
		while (true) {
			gotoxy(45, 18);
			cout << "                      ";
			if (stone_num > 2) {
				gotoxy(2, 29);
				cout << "잘못 입력하셨습니다. 다시 입력하세요: ";
				cin >> stone_num;
			}
			else if (player->life[stone_num]->_area == 6) {
				gotoxy(2, 29);
				cout << "이미 도착한 말입니다. 다시 입력하세요: ";
				cin >> stone_num;
			}
			else {
				gotoxy(2, 29);
				cout << "                                         ";
				break;
			}
		}
		player->life[stone_num]->move_piece(&a);
		player->life[stone_num]->move_check();
		piece_location(player->life[stone_num], board);
		End_check(player);
		gotoxy(26, (++flag) % 2 + 1);
		start_point(player);
		finish_point(player);
		gotoxy(26, (flag) % 2 + 4);
		Watch_together(player);
		player->Location_share(stone_num);
		player->Together();
		player->Eat(opponent);
		if (a.Result() == 5 || a.Result() == 4 || player->check == 1) {
			if (a.Result() == 5 && player->Eat(opponent) || a.Result() == 5 && player->Eat(opponent)) {
				count += 2;
			}
			else {
				count++;
			}
		}
		gotoxy(26, (++flag) % 2 + 1);
		start_point(opponent);
		finish_point(opponent);
		gotoxy(26, (flag) % 2 + 4);
		Watch_together(opponent);
		count--;
		gotoxy(45, 16);
		cout << "                              ";
	}

	turn++;
}
//판 세팅, 2차원 배열에 두 칸마다 칸을 표현한 문자를 넣어 간격있게 출력될수 있도록한다.
void set_board() 
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((i % 2 == 0) && (j % 2 == 0))//해당조건
			{
				board[i][j] = "●";
			}
			if (i == 5 && j == 5)
			{
				board[i][j] = "●";
			}
		}
		cout << endl;
	}
	board[2][4] = ""; //짝수칸으로 설정했기때문에 해당칸들은 비워주어야 한다.
	board[2][6] = "";
	board[4][2] = "";
	board[6][2] = "";
	board[8][4] = "";
	board[8][6] = "";
	board[4][8] = "";
	board[6][8] = "";

}
//판 출력 2차원 배열을 이중반복문을 통해 콘솔에 출력하는 함수이다. 
void print_board()
{
	set_color(white, brown);
	for (int i = 0; i < 11; i++)
	{
		gotoxy(2, 1 + i);
		for (int j = 0; j < 11; j++)
		{
			if (board[i][j] == "")
			{
				cout << "  ";
			}
			else
			{
				cout << board[i][j];
			}
		}
		cout << "\n\n";
	}
	set_color(white, black);

}
// 테두리
void Grow_game() { 
	cout << "┏";
	for (int i = 1; i < 24; i++) {
		gotoxy(i, 0);
		cout << "━";
	}
	gotoxy(24, 0);
	cout << "┳";
	for (int i = 25; i < 86; i++) {
		gotoxy(i, 0);
		cout << "━";
	}
	gotoxy(86, 0);
	cout << "┓";
	for (int i = 1; i < 12; i++) {
		gotoxy(0, i);
		cout << "┃" << endl;
	}
	gotoxy(0, 12);
	cout << "┣";
	for (int i = 1; i < 12; i++) {
		gotoxy(24, i);
		cout << "┃" << endl;
	}
	gotoxy(24, 12);
	cout << "┻";
	for (int i = 1; i < 24; i++) {
		gotoxy(i, 12);
		cout << "━";
	}
	for (int i = 25; i < 43; i++) {
		gotoxy(i, 12);
		cout << "━";
	}
	gotoxy(43, 12);
	cout << "┳";
	for (int i = 44; i < 86; i++) {
		gotoxy(i, 12);
		cout << "━";
	}
	for (int i = 1; i < 12; i++) {
		gotoxy(86, i);
		cout << "┃" << endl;
	}
	gotoxy(86, 12);
	cout << "┫" << endl;
	for (int i = 13; i < 30; i++) {
		gotoxy(0, i);
		cout << "┃" << endl;
	}
	gotoxy(0, 30);
	cout << "┗";
	for (int i = 1; i < 43; i++) {
		gotoxy(i, 30);
		cout << "━";
	}
	gotoxy(43, 30);
	cout << "┻";
	for (int i = 13; i < 30; i++) {
		gotoxy(43, i);
		cout << "┃" << endl;
	}
	gotoxy(86, 30);
	cout << "┛";
	for (int i = 44; i < 86; i++) {
		gotoxy(i, 30);
		cout << "━";
	}
	for (int i = 13; i < 30; i++) {
		gotoxy(86, i);
		cout << "┃" << endl;
	}
}
// 대기중인 말 표시 
void start_point(Player* player)
{
	string arr_srt[3]{};

	cout << player->_name << "의 나가지 못한 말 : ";
	for (int i = 0; i < 3; i++)
	{

		if (player->life[i]->_area == 0 && player->life[i]->_number == 0)//말의 상태가 담겨있는 area와 number가 초기상태인 말을 판별
		{
			arr_srt[i] = player->life[i]->shape; //배열에 말의 모양을 넣고 난 후 그 배열을 출력한다. 
		}
		else arr_srt[i] = "  ";//아닌경우 비워둔다
		cout << arr_srt[i] << " ";
	}


}
// 도착한 말 표시
void finish_point(Player* player)//도착한 상태 : area==6으로 지정하여 판별한다.
{
	string arr_fin[3]{};

	cout << player->_name << "의 도착한 말 : ";
	for (int i = 0; i < 3; i++)
	{

		if (player->life[i]->_area == 6)
		{
			arr_fin[i] = player->life[i]->shape;
		}
		else arr_fin[i] = "  ";
		cout << arr_fin[i] << " ";
	}

	cout << endl;

}
// 업은 말 표시
void Watch_together(Player* player) {
	string arr_together[3]{};
	cout << player->_name << "의 업고 있는 말: ";
	for (int i = 0; i < 3; i++) {
		if (player->isTogether[i] == true)
		{
			arr_together[i] = player->life[i]->shape;
		}
		else arr_together[i] = "  ";
		cout << arr_together[i] << " ";
	}
}
// 플레이어마다 말의 번호 출력
void Number_stone(Player* player) {
	cout << player->_name << "님의 말: ";
	for (int i = 0; i < 3; i++) {
		cout << i << '.' << player->life[i]->shape << " ";
	}
}
// 게임시작, 초기화면 1 입력시 실행된다
void game_start()
{
	system("cls");//콘솔화면을 초기화하고 시작
	system("mode con:cols=100 lines=40"); // 콘솔창 크기설정;
	// 플레이어와 말 선언
	Player A;
	Player B;
	Stone blue;
	blue.shape = "ⓐ";
	Stone blue_1;
	blue_1.shape = "ⓑ";
	Stone blue_2;
	blue_2.shape = "ⓒ";
	Stone red;
	red.shape = "①";
	Stone red_1;
	red_1.shape = "②";
	Stone red_2;
	red_2.shape = "③";
	A.Make_stone(&blue);
	B.Make_stone(&red);
	A.Make_stone(&blue_1);
	B.Make_stone(&red_1);
	A.Make_stone(&blue_2);
	B.Make_stone(&red_2);
	system("cls");
	Grow_game();
	gotoxy(26, 7);
	Number_stone(&A);
	gotoxy(26, 8);
	Number_stone(&B);
	gotoxy(26, 1);
	start_point(&A);
	finish_point(&A);
	gotoxy(26, 2);
	start_point(&B);
	finish_point(&B);
	gotoxy(26, 4);
	Watch_together(&A);
	gotoxy(26, 5);
	Watch_together(&B);
	set_board();
	print_board();


	while (true) {//번갈아가면서 턴 진행
		if (turn % 2 == 0) {
			Run(&A, &B);
			if (End_check(&A) == 0) {
				system("cls");
				cout << A._name << "님이 이겼습니다!";
				break;
			}
		}
		else {
			Run(&B, &A);
			if (End_check(&B) == 0) {
				system("cls");
				cout << B._name << "님이 이겼습니다!";
				break;
			}
		}
	}
	Sleep(3000);
	return;
}

void game_exit()//초기화면에서 0 입력시 실행
{
	system("cls");
	cout << "게임 종료";
	Sleep(3000);
	return;
}

void piece_location(Stone* s, string arr[11][11])//배열(판)상의 말의 위치(x,y)를 지정해주는 함수, 끝나면 배열 출력으로 이어진다.
{
	if (ctn > 48)	arr[s->pre_x][s->pre_y] = "●";//말이 존재하던 이전 위치를 지운다.
	switch (s->_area)
	{
	case 0://각 케이스에 맞게 x,y 변경
	{	//0 area = x값 10에서 칸당 2씩 감소, y값 고정
		s->x = 10 - (2 * (s->_number));
		s->y = 10;
		arr[s->x][s->y] = s->shape;
		++ctn;
		s->pre_x = s->x;//다음 위치로 갈때 현 위치를 삭제하기 위함
		s->pre_y = s->y;
		break;
	}
	case 1://1 area = x값 0고정, y값 10에서 칸당 2씩 감소
	{
		s->x = 0;
		s->y = 10 - (2 * (s->_number));
		arr[s->x][s->y] = s->shape;
		++ctn;
		s->pre_x = s->x;
		s->pre_y = s->y;
		break;

	}
	case 2://2 area = x값 0부터 칸당 2씩 증가, y값 0 고정
	{
		s->x = (2 * (s->_number));
		s->y = 0;
		arr[s->x][s->y] = s->shape;
		++ctn;
		s->pre_x = s->x;
		s->pre_y = s->y;
		break;

	}
	case 3://3 area = x값 10고정, y값 0부터 칸당 2씩 증가
	{
		s->x = 10;
		s->y = (2 * (s->_number));
		arr[s->x][s->y] = s->shape;
		++ctn;
		s->pre_x = s->x;
		s->pre_y = s->y;
		break;

	}
	case 4://4 area = x값 , y값 0부터 칸당 2씩 증가 , 우하향하는 부분
	{
		s->x = (2 * (s->_number));
		s->y = (2 * (s->_number));
		if (s->_number > 3) //가운데 칸이 5,5라서 그 뒤부분 칸은 값조절 필요
		{
			s->x = s->x - 2;
			s->y = s->y - 2;
		}
		else if (s->_number == 3)//가운데 칸이 5,5라서 그 칸은 값조절 필요
		{
			s->x = s->x - 1;
			s->y = s->y - 1;
		}
		arr[s->x][s->y] = s->shape;
		++ctn;
		s->pre_x = s->x;
		s->pre_y = s->y;
		break;

	}
	case 5://5 area = x값 0부터 칸당 2씩 증가 y값 10부터 칸당 2씩 감소 , 좌하향하는 부분
	{
		s->x = (2 * (s->_number));
		s->y = 10 - (2 * (s->_number));
		if (s->_number > 3) //가운데 칸이 5,5라서 그 뒤부분 칸은 값조절 필요
		{
			s->x = s->x - 2;
			s->y = s->y + 2;
		}
		arr[s->x][s->y] = s->shape;
		++ctn;
		s->pre_x = s->x;
		s->pre_y = s->y;
		break;
	}
	default:
		break;
	}
	print_board();//말을 이동시킨 후 출력하도록

}
int End_check(Player* player) {//게임 종료 조건 만족 판별
	if (player->End() == 1) {
		return 0;
	}
}


int main()
{

	set_console();//콘솔 창 세팅
	while (1)
	{
		title_draw();//윷놀이 띄우기 위함
		int temp = menu_draw();//1.2.3 선택지
		switch (temp)
		{
		case 1:
			game_start();//게임 시작
			break;
		case 0:
			game_exit();//게임 종료
			break;
		default:
			break;
		}
		system("cls");
		if (temp == 0) break;
	}

	return 0;
}