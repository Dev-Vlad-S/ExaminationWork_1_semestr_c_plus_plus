#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"

class Label : virtual public Object
{
protected:
	Label();
	Label(string text, int maxLength, string indicator);
	void Draw(const COORD origin, string textSection) override;
	void Draw(const COORD& origin, COORD offset, string textSection) override;
protected:
	string line;
private:
	void InitializeLine();
private:
	int maxLength;
	string indicator;
};

Label::Label()
{
	maxLength = 0;
	string indicator = ":";
	line = "";
}


Label::Label(string text, int maxLength, string indicator) : Object(text)
{
	this->maxLength = maxLength;
	this->indicator = indicator;
	InitializeLine();
}

void Label::InitializeLine()
{
	for (int i = 0, j = 0; i < maxLength; i++)
	{
		if (j < size(text))
		{
			line += text[i];
			j++;
		}
		else
		{
			line += " ";
		}
	}
	line += indicator;
}


void Label::Draw(const COORD origin, string textSection)
{
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { origin.X, origin.Y });
	if (textSection == text)
	{
		SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << line;
	}
	else
	{
		SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << line;
	}
	SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

inline void Label::Draw(const COORD& origin, COORD offset, string textSection)
{
}


