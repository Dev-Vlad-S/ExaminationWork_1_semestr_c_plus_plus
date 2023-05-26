#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"


class InputLabel : virtual public Object
{
public:
	void InputLineText(WCHAR ch);
	string getInputedLine();
	COORD getOrigin();
	void Clear();
protected:
	InputLabel();
	void Draw(COORD origin);
	void Draw(const COORD& origin, COORD offset, string textSection) override;
private:
	void SetOrigin(COORD origin);
	void OffsetOrigin(short offsetX, short offsetY);
private:
	int maxLength;
	string inputedLine;
	COORD origin;
};

InputLabel::InputLabel()
{
	inputedLine = "";
	maxLength = 20;
}

void InputLabel::Draw(COORD origin)
{

	SetOrigin(origin);
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
	cout << inputedLine;
	if (inputedLine.size() > 0 && inputedLine.size() < maxLength)
	{
		OffsetOrigin(inputedLine.size(), 0);
	}
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
}

void InputLabel::Draw(const COORD& origin, COORD offset, string textSection)
{
}

void InputLabel::Clear()
{
	if (inputedLine.size() > 0)
	{
		OffsetOrigin(inputedLine.size()*(-1), 0);
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
		for (int i = 0; i < maxLength; i++)
		{
			cout << " ";
		}
		inputedLine = "";
	}
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
}

void InputLabel::InputLineText(WCHAR ch)
{
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
	if (isalpha(ch) || isdigit(ch))
	{
		if (inputedLine.size() < maxLength)
		{
			cout << char(ch);
			inputedLine += char(ch);
			OffsetOrigin(1, 0);
			SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { this->origin });
		}
	}
}

string InputLabel::getInputedLine() { return inputedLine; }


void InputLabel::SetOrigin(COORD origin) { this->origin = origin; }

void InputLabel::OffsetOrigin(short offsetX, short offsetY)
{
	origin.X += offsetX;
	origin.Y += offsetY;
}



COORD InputLabel::getOrigin() { return origin; }
