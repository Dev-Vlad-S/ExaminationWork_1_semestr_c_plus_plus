#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"

class MainWindow
{
public:
	MainWindow();
	void ResizeBufferWindow(WINDOW_BUFFER_SIZE_RECORD wbsr);
};


MainWindow::MainWindow()
{
	ShowWindow(ServiceVariables::consoleWindow, SW_MAXIMIZE);
}

void MainWindow::ResizeBufferWindow(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);

	short winWidth = ServiceVariables::cScrBufferInfo.srWindow.Right - ServiceVariables::cScrBufferInfo.srWindow.Left + 1;
	short winHeight = ServiceVariables::cScrBufferInfo.srWindow.Bottom - ServiceVariables::cScrBufferInfo.srWindow.Top + 1;
	COORD newSize;
	newSize.X = winWidth;
	newSize.Y = winHeight;

	SetConsoleScreenBufferSize(ServiceVariables::hOutputBuffer, newSize);
}