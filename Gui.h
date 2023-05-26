#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "MainWindow.h"
#include "WorkSpace.h"

class Gui
{
public:
	Gui();
	MainWindow& getMainWindow();
	WorkSpace& getWorkSpace();
	void Draw();
private:
	MainWindow mainWindow;
	WorkSpace workSpace;

};

Gui::Gui() : mainWindow{}, workSpace{}
{

}

MainWindow& Gui::getMainWindow() { return mainWindow; }

WorkSpace& Gui::getWorkSpace() { return workSpace; }

void Gui::Draw()
{
	workSpace.Draw();
}

