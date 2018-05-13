#include "stdafx.h"
#include "KMain.h"
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include <Windows.h>

#define RECT_WIDTH 100
#define RECT_HEIGHT 100

int mx;
int my;
int turn = 0; 
int com_bingo=0;
int user_bingo=0;

HWND mHwnd;


#pragma warning(disable:4996)


#define MAX 5
int user[MAX][MAX] = { 0 };
int com[MAX][MAX] = { 0 };

int flag = 1;

void GameStart();
void InitArray(int arr[][MAX]);
void UserInput(int n);
void ComInput();
int Check(int arr[][MAX]);
void Choose(int n);
void ChooseItem(int arr[][MAX], int v);
void CheckAll();
void OnDraw(HDC hdc);
void OnLButtonDown(HWND hWnd, LPARAM lParam);
void OnKeyDown(HWND hWnd, WPARAM wParam);



void GameStart()
{
	InitArray(user);

	InitArray(com);
}


void InitArray(int arr[][MAX])
{
	int temp[MAX*MAX];

	for (int i = 0; i < MAX*MAX; i++)
	{
		int ran = rand() % (MAX*MAX * 2) + 1;

		temp[i] = ran;

		for (int j = 0; j < i; j++)
		{
			if (temp[j] == ran)
			{
				i--;
				break;
			}
		}
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			arr[y][x] = temp[MAX * y + x];
		}
	}

	arr[MAX / 2][MAX / 2] = -1;
}


void ChooseItem(int arr[][MAX], int v)
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (arr[y][x] == v)
			{
				arr[y][x] = -1;
				break;
			}
		}
	}
}



void UserInput(int n)
{
	Choose(n);
	// user 빙고 체크
	CheckAll();
	// com 값 입력
	turn = 1;
	// com, user 아이템 선택
	ComInput();
	// 빙고 체크
	CheckAll();
	turn = 0;
}


void CheckAll()
{
	user_bingo = Check(user);
	com_bingo = Check(com);
}


void ComInput()
{
	int ran = 0;

	int y, x;

	for (;;)
	{
		ran = rand() % (MAX*MAX) + 1;
		y = ran / MAX;
		x = ran % MAX;

		if (com[y][x] == -1)
			continue;
		else
			break;
	}



	Choose(com[y][x]);
}


int Check(int arr[][MAX])
{
	int temp = 0;

	for (int y = 0; y < MAX; y++)
	{
		int cmd = 0;

		for (int x = 0; x < MAX; x++)
		{
			if (arr[y][x] == -1)
			{
				cmd++;
			}
		}
		if (cmd == MAX)
		{
			temp++;
		}
	}

	for (int x = 0; x < MAX; x++)
	{
		int cmd = 0;

		for (int y = 0; y < MAX; y++)
		{
			if (arr[y][x] == -1)
			{
				cmd++;
			}
		}
		if (cmd == MAX)
		{
			temp++;
		}
	}


	int cmd = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (arr[i][MAX - i - 1] == -1)
		{
			cmd++;
		}
		if (cmd == MAX)
		{
			temp++;
		}
	}


	cmd = 0;
	for (int i = 0; i < MAX; i++)
	{

		if (arr[i][i] == -1)
		{
			cmd++;
		}
		if (cmd == MAX)
		{
			temp++;
		}
	}

	return temp;
}


void Choose(int n)
{
	ChooseItem(user, n);
	ChooseItem(com, n);
}


void PrintAPI(HDC hdc, int arr[][MAX],int sx,int sy)
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			int dx = x*RECT_WIDTH+sx;
			int dy = y*RECT_HEIGHT+sy;

			if (arr[y][x] != -1)
			{
				char msg[20];
				wsprintf(msg, "%d", arr[y][x]);
				TextOutA(hdc, dx + 40, dy + 40, msg, strlen(msg));
			}
		}
	}
}


//int main()
//{
//	srand(time(NULL));
//	GameStart(hdc);
//}

void OnCreate(HWND hWnd)
{
	mHwnd = hWnd;
	srand(time(NULL));
	GameStart();
}


void OnDraw(HDC hdc)
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (-1 == user[y][x])
			{
				HBRUSH hBrush,oBrush;
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, 100 * x, 100 * y, 100 * x + 100, 100 * y + 100);
				SelectObject(hdc, oBrush);
				DeleteObject(hBrush);
			}
			else
			{
				Rectangle(hdc, 100 * x, 100 * y, 100 * x + 100, 100 * y + 100);
			}
			
		}
	}

	PrintAPI(hdc, user,0,0);
	PrintAPI(hdc, com, 700, 0);
	
	char msg[20];
	wsprintf(msg, "%d,%d", mx, my);
	TextOutA(hdc, 600, 10, msg, strlen(msg));

	wsprintf(msg, "user bingo : %d",user_bingo);
	TextOutA(hdc, 600, 40, msg, strlen(msg));

	wsprintf(msg, "com bingo : %d",com_bingo);
	TextOutA(hdc, 600, 70, msg, strlen(msg));

	wsprintf(msg, "turn : %d", turn);
	TextOutA(hdc, 600, 100, msg, strlen(msg));
}

void OnLButtonDown(HWND hWnd,LPARAM lParam)
{
	int lx = LOWORD(lParam);
	int ly = HIWORD(lParam);

	mx = lx;
	my = ly;

	int n = user[my / RECT_WIDTH][mx / RECT_HEIGHT];


	UserInput(n);

	InvalidateRect(hWnd,NULL,true);
}

void OnKeyDown(HWND hWnd,WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		break;
	case VK_RIGHT:
		break;
	case VK_DOWN:
		break;
	case VK_UP:
		break;
	}
}