#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"

class StatusBar
{
private:
	static void Clear();

public:
	static COORD getOrigin();
	static void Draw(string text = "");

private:
	static COORD origin;
	static string indicator;
	static COORD cursorPosition;

};

COORD StatusBar::origin = { 0,0 };
string StatusBar::indicator = ": ";
COORD StatusBar::cursorPosition = { short(size(indicator)), 0 };

COORD StatusBar::getOrigin() { return origin; }

void StatusBar::Draw(string text)
{
	GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);
	COORD currentCursorPosition = ServiceVariables::cScrBufferInfo.dwCursorPosition;

	Clear();

	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
	cout << indicator;
	cout << text;

	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, currentCursorPosition);
}

void StatusBar::Clear()
{
	GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
	for (int i = short(size(indicator)) - 1; i < ServiceVariables::cScrBufferInfo.dwSize.X; i++)
	{
		cout << " ";
	}
}



