#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"
#include "IPainter.h"


class InputLabel : public Object
{
public:
	void Draw() override;
	void InputLineText(WCHAR ch);
	string getInputedLine();
	void setInputedLine(string line);
	COORD getOrigin();
	void ClearSymbol();
	void ClearAll();
	InputLabel(int maxLength = 20);
	InputLabel();
private:
	void SetOrigin(COORD origin);
	void OffsetOrigin(short offsetX, short offsetY);
private:
	int maxLength;
	string inputedLine;
};

InputLabel::InputLabel(int maxLength)
{
	this->maxLength = maxLength;
	inputedLine = "";
}

InputLabel::InputLabel() : Object()
{
	inputedLine = "";
	maxLength = 20;
}

void InputLabel::setInputedLine(string line)
{
	inputedLine = line;
}

void InputLabel::Draw()
{
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
	cout << inputedLine;
	if (inputedLine.size() > 0 && inputedLine.size() < maxLength)
	{
		OffsetOrigin(inputedLine.size(), 0);
	}
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
}

void InputLabel::ClearSymbol()
{
	if (inputedLine.size() > 0)
	{
		OffsetOrigin(inputedLine.size() * (-1), 0);
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
		for (int i = 0; i < maxLength; i++)
		{
			cout << " ";
		}
		string temp = "";
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
		for (int i = 0; i < inputedLine.size() - 1; i++)
		{
			temp += inputedLine[i];
		}
		inputedLine = temp;
		cout << inputedLine;
		OffsetOrigin(inputedLine.size(), 0);
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
	}
}

void InputLabel::ClearAll()
{
	if (inputedLine.size() > 0)
	{
		OffsetOrigin(inputedLine.size() * (-1), 0);
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
		for (int i = 0; i < maxLength; i++)
		{
			cout << " ";
		}
		inputedLine = "";
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
	}
}

void InputLabel::InputLineText(WCHAR ch)
{
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, this->origin);
	if (isalpha(ch) || isdigit(ch) || ch == ' ' || ch == '-')
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
