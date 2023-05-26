#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "AuthorizationPanel.h"

class Frame
{
public:
	Frame();
public:
	void Draw(const COORD& origin);
	int getWidth();
	int getHeight();
private:
	char symbolFrame;
	int width;
	int height;
};

Frame::Frame()
{
	symbolFrame = '*';
	width = 40;
	height = 16;
}

int Frame::getWidth() { return width; }
int Frame::getHeight() { return height; }



void Frame::Draw(const COORD& origin)
{
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { origin.X, origin.Y });

	for (int i = 0; i < width; i++)
	{
		cout << symbolFrame;
	}

	for (short i = 0; i < height; i++)
	{
		short newCoordY = origin.Y + i;
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { origin.X,  newCoordY });
		cout << symbolFrame;
	}

	for (short i = 0; i < height; i++)
	{
		short newCoordX = origin.X + width - 1;
		short newCoordY = origin.Y + i;
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { newCoordX , newCoordY });
		cout << symbolFrame;
	}

	short newCoordY = origin.Y + height - 1;
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { origin.X, newCoordY });

	for (short i = 0; i < width; i++)
	{
		cout << symbolFrame;
	}
}
