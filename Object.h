#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "IPainter.h"

class Object : public IPainter
{
public:
	void setOrigin(COORD origin);
	COORD getOrigin();
	void setText(string text);
	string getText();
protected:
	Object(string text, COORD origin);
	Object();
protected:
	string text;
	COORD origin;
private:
	void Draw() override = 0;
};

string Object::getText() { return text; }

void Object::setText(string text) { this->text = text; }

void Object::setOrigin(COORD origin)
{
	this->origin = origin;
}

COORD Object::getOrigin() {	return origin; }

Object::Object()
{
	this->text = "";
	origin = { 0,0 };
}

Object::Object(string text, COORD origin = { 0,0 })
{
	this->text = text;
}

