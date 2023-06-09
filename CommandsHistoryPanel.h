#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"

class CommandsHistoryPanel
{
public:
	void Draw();
	short getHeight();
	COORD getOrigin();
	vector <string>& getHistory();
	CommandsHistoryPanel();
	void setPosition(int pos);
	int getPosition();
	void resetPosition();
private:
	void Clear();
private:
	int position;
	vector <string> history;
	string indicator;
	unsigned int height;
	COORD origin;
};

void CommandsHistoryPanel::resetPosition()
{
	position = history.size() - 1;
}

void CommandsHistoryPanel::setPosition(int pos)
{
	if (pos > -1 && pos < history.size())
	{
		position = pos;
		if (position == history.size())
		{
			--position;
		}
		if (position == -1)
		{
			++position;
		}
	}
}

int CommandsHistoryPanel::getPosition() { return position; }

void CommandsHistoryPanel::Draw()
{
	Clear();
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
	for (int i = 0; i < history.size(); i++)
	{
		cout << indicator << " " << history[i] << endl;
	}
}

void CommandsHistoryPanel::Clear()
{
	GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
	for (int i = 0; i < history.size(); i++)
	{
		cout << indicator << " ";
		for (int j = 0; j < ServiceVariables::cScrBufferInfo.dwSize.X - 3; j++)
		{
			cout << " ";
		}
		cout << endl;
	}
}


short CommandsHistoryPanel::getHeight() { return height; };

COORD CommandsHistoryPanel::getOrigin() { return COORD(); }

vector<string>& CommandsHistoryPanel::getHistory() { return history; }

CommandsHistoryPanel::CommandsHistoryPanel()
{

	indicator = "-";
	origin = { 0, 1 };
	height = 7;
	history = { height, "" };
	position = history.size() - 1;
}