#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Label.h"
#include "InputLabel.h"

class InputField : public Label, public InputLabel
{
public:
	InputField();
	InputField(string text, int maxLength = 10, string indicator = ":");
	void Draw(const COORD& origin, COORD offset, string textSection) override;
};

InputField::InputField()
{

}

InputField::InputField(string text, int maxLength, string indicator) : Object(text), Label(text, maxLength, indicator), InputLabel()
{

}

void InputField::Draw(const COORD& origin, COORD offset, string textSection)
{
	short pointX = origin.X + offset.X;
	short pointY = origin.Y + offset.Y;
	Label::Draw({pointX, pointY}, textSection);
	InputLabel::Draw({ short(pointX + size(line) + 2),  pointY });
}





