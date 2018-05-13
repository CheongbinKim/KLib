#include "stdafx.h"
#include "KMain.h"
#include <stdio.h>

#define RECT_WIDTH 100
#define RECT_HEIGHT 100

int mx;
int my;

void OnDraw(HDC hdc)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			int dx = x*RECT_WIDTH;
			int dy = y*RECT_HEIGHT;
			Rectangle(hdc, dx,dy,dx+RECT_WIDTH,dy+RECT_HEIGHT);
		}
	}
	
	char msg[20];
	wsprintf(msg, "%d,%d", mx, my);

	TextOutA(hdc, 600, 10, msg, strlen(msg));
}

void OnLButtonDown(HWND hWnd,LPARAM lParam)
{
	int lx = LOWORD(lParam);
	int ly = HIWORD(lParam);

	mx = lx;
	my = ly;

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