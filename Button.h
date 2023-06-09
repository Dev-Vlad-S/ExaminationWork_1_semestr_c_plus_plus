#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"

class Button : public Object
{
public:
	void Draw();
	void SetColor(Colors color);
	Button(string text, COORD origin);
	Button();
private:
	Colors color;
};

Button::Button()
{
	color = Colors::Normal;
}

Button::Button(string text, COORD origin = { 0,0 }) : Object(text, origin)
{
	color = Colors::Normal;
}

void Button::Draw()
{
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { origin.X, origin.Y });
	SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, color);
	cout << text;
	SetConsoleTextAttribute(ServiceVariables::hOutputBuffer, Normal);
}

void Button::SetColor(Colors color)
{
	this->color = color;
}


