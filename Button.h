#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"

class Button : public Object
{
public:
	Button();
	Button(string text);
	void Draw(const COORD& origin, COORD offset, string textSection) override;
	void Draw(const COORD origin, string textSection) override;

};

Button::Button() {}

Button::Button(string text) : Object(text) { }

void Button::Draw(const COORD& origin, COORD offset, string textSection)
{
	short leftUpPointXLogin = origin.X + offset.X;
	short leftUpPointYLogin = origin.Y + offset.Y;
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { leftUpPointXLogin, leftUpPointYLogin });
	if (textSection == text)
	{
		SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << text;
	}
	else
	{
		SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << text;
	}
	SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

inline void Button::Draw(const COORD origin, string textSection)
{
}

