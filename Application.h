#pragma once
#include "ConnectedLibraries.h"
#include "StatusBar.h"
#include "Gui.h"
#include "DataBase.h"

class Application
{
public:
	Application();
	void Run();
private:
	DataBase db;
	Gui gui;
};

Application::Application() : gui{}, db{}
{

}

void Application::Run()
{
	INPUT_RECORD lpBufferInputData[128];
	DWORD sizeBufferInputData = 128;
	DWORD consoleInputMode;
	DWORD lpNumberBufferInputRecords;

	while (true)
	{
		if (ReadConsoleInput(ServiceVariables::hInputBuffer, lpBufferInputData, sizeBufferInputData, &lpNumberBufferInputRecords))
		{

			for (int i = 0; i < lpNumberBufferInputRecords; i++)
			{
				if (lpBufferInputData[i].EventType == WINDOW_BUFFER_SIZE_EVENT)
				{
					gui.getMainWindow().ResizeBufferWindow(lpBufferInputData[i].Event.WindowBufferSizeEvent);
					gui.Draw();
					GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);
					StatusBar::Draw("The window size has changed [" + to_string(ServiceVariables::cScrBufferInfo.dwSize.X) + ":" + to_string(ServiceVariables::cScrBufferInfo.dwSize.Y) + "]");
				}
				if (lpBufferInputData[i].EventType == KEY_EVENT)
				{

					if (gui.getWorkSpace().getAuthorizationPanel().getStatusDemostration() == bool(Demonstration::On))
					{
						gui.getWorkSpace().getAuthorizationPanel().SelectSection(lpBufferInputData[i].Event.KeyEvent, db.getDataBaseClassRoomTeachers());
					}
					/*if (gui.getWorkspace().getLoginPanel().getVisible())
					{
						gui.getWorkspace().getLoginPanel().SelectContent(lpBufferInputData[i].Event.KeyEvent, dataBase.getDataBaseClassRoomTeachers());
						if (gui.getWorkspace().getLoginPanel().getVisible())
						{
							gui.getWorkspace().getLoginPanel().Draw();

						}
					}
					if (gui.getWorkspace().getPersonalAccountWindow().getVisible())
					{
						gui.getWorkspace().getPersonalAccountWindow().InputCommands(lpBufferInputData[i].Event.KeyEvent, dataBase.getDataBaseStudents());
					}*/
				}
			}


		}
	}
}



