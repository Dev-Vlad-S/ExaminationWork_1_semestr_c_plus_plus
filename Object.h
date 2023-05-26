#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"

class Object
{
public:
	string getText();
	virtual void Draw(const COORD& origin, COORD offset, string textSection) = 0;
protected:
	Object();
	Object(string text);
	virtual void Draw(const COORD origin, string textSection) = 0;
protected:
	string text;
	COORD origin;
};

string Object::getText() { return text; }


Object::Object()
{
	this->text = "666655";
	origin = { 0,0 };
}

Object::Object(string text)
{
	this->text = text;
}

