#ifndef display_H
#define display_h
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;


void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;

	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


class progressBar
{
private:
	int topLeftX, topLeftY;
	int progressBarX, progressBarY;
	int width, height;
	string title;
	float progress;
	int updates;
	int printed;

public:
	void setTitle(string y)
	{
		title = y;
	}
	progressBar(int width, int height, int topLeftX, int topLeftY)
	{
		printed = 0;
		progress = 0;
		this->topLeftY = topLeftY;
		this->topLeftX = topLeftX;
		this->width = width;
		this->height = height;
	}

	void setProgress(int done, int total)
	{
		progress = (float)((float)done / (float)total) * 100;
		gotoxy(topLeftX + 1, topLeftY + 1);
		updates = progress * (width - 1) / 100;

	}
	void update()
	{
		for (int i = printed; i <= printed + updates; i++)
		{
			cout << (char)219;

		}
		printed += updates;

	}
	void drawOutline()
	{
		gotoxy(topLeftX + (width / 2) - 1, topLeftY - 1);
		cout << title;
		gotoxy(topLeftX, topLeftY);
		char topLeft = 218, topRight = 191, bottomLeft = 192, bottomRight = 217, horizontal = 196, vertical = 179;
		cout << topLeft;
		for (int i = topLeftX; i < (topLeftX + width); i++)
		{

			cout << horizontal;

		}
		gotoxy(topLeftX, topLeftY + height);
		cout << bottomLeft;
		for (int i = topLeftX; i < (topLeftX + width); i++)
		{

			cout << horizontal;

		}

		gotoxy(topLeftX, topLeftY);
		for (int i = topLeftY; i < topLeftY + height; i++)
		{
			gotoxy(topLeftX, i);
			cout << vertical;

		}


		gotoxy(topLeftX + width, topLeftY);
		cout << topRight;
		for (int i = topLeftY; i < topLeftY + height; i++)
		{
			gotoxy(topLeftX + width, i);
			cout << vertical;

		}


		gotoxy(topLeftX, topLeftY);
		cout << topLeft;
		gotoxy(topLeftX + width, topLeftY);
		cout << topRight;
		gotoxy(topLeftX + width, topLeftY + height);
		cout << bottomRight;
		gotoxy(topLeftX, topLeftY + height);
		cout << bottomLeft;




	}
	void clearProgress()
	{
		progress = 0;
		updates = 0;
		gotoxy(topLeftX + 1, topLeftY + 1);
		for (int i = 0; i < width - 1; i++)
			cout << " ";
	}
	void clearAll()
	{
		clearTitle();
		clearProgress();
		clearOutline();
	}
	void clearOutline()
	{


		gotoxy(topLeftX, topLeftY);
		char topLeft, topRight, bottomLeft, bottomRight, horizontal, vertical;
		topLeft = topRight = bottomLeft = bottomRight = horizontal = vertical = ' ';
		cout << topLeft;
		for (int i = topLeftX; i < (topLeftX + width); i++)
		{

			cout << horizontal;

		}
		gotoxy(topLeftX, topLeftY + height);
		cout << bottomLeft;
		for (int i = topLeftX; i < (topLeftX + width); i++)
		{

			cout << horizontal;

		}

		gotoxy(topLeftX, topLeftY);
		for (int i = topLeftY; i < topLeftY + height; i++)
		{
			gotoxy(topLeftX, i);
			cout << vertical;

		}


		gotoxy(topLeftX + width, topLeftY);
		cout << topRight;
		for (int i = topLeftY; i < topLeftY + height; i++)
		{
			gotoxy(topLeftX + width, i);
			cout << vertical;

		}


		gotoxy(topLeftX, topLeftY);
		cout << topLeft;
		gotoxy(topLeftX + width, topLeftY);
		cout << topRight;
		gotoxy(topLeftX + width, topLeftY + height);
		cout << bottomRight;
		gotoxy(topLeftX, topLeftY + height);
		cout << bottomLeft;
	}
	void clearTitle()
	{

		gotoxy(topLeftX + (width / 2) - 1, topLeftY - 1);
		for (int i = 0; i < title.length(); i++)
		{
			cout << " ";
		}
	}


};

#endif