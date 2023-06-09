#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"

class SplitLine
{
public:
	void Draw();
	SplitLine(COORD origin);
	SplitLine();
private:
	COORD origin;
};

void SplitLine::Draw()
{
	GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);

	for (int i = 0; i < ServiceVariables::cScrBufferInfo.dwSize.X; i++)
	{
		cout << "-";
	}
}

SplitLine::SplitLine(COORD origin)
{
	this->origin = origin;
}

SplitLine::SplitLine()
{
	origin = { 0, 0 };
}
