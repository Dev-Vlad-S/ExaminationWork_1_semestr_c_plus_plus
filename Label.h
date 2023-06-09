#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"
#include "IPainter.h"

class Label : public Object
{
public:
	void Draw();
	void SetColor(Colors color);
	string getLine();
	Label(string text, COORD origin, int maxLength, string indicator);
	Label();
protected:
	string line;
private:
	void Fill();
private:
	Colors color;
	int maxLength;
	string indicator;
};

Label::Label()
{
	color = Colors::Normal;
	maxLength = 20;
	string indicator = ":";
	line = "";
}


Label::Label(string text, COORD origin, int maxLength, string indicator) : Object(text, origin)
{
	color = Colors::Normal;
	this->maxLength = maxLength;
	this->indicator = indicator;
	Fill();
}

string Label::getLine() { return line; }

void Label::SetColor(Colors color)
{
	this->color = color;
}

 void Label::Draw()
{
	 SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { origin.X, origin.Y });
	 SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, color);
	 cout << line;
	 SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, Normal);
}

void Label::Fill()
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

