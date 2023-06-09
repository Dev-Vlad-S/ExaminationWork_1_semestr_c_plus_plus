#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "CommandsHistoryPanel.h"
#include "InputField.h"
#include "DataBaseStudents.h"

class CommandPanel
{
public:
	vector<string> ParsingCommandLine();
	void Draw();
	short getHeight();
	InputField& getInputField();
	CommandsHistoryPanel& getCommandsHistoryPanel();
	CommandPanel();
private:
	vector<string> inputedCommand;
	short height;
	COORD origin;
	CommandsHistoryPanel commandsHistoryPanel;
	InputField inputField;
};


vector<string> CommandPanel::ParsingCommandLine()
{
	inputedCommand = {};
	string temp = "";
	string inputedLine = inputField.getInputLabel()->getInputedLine();
	for (int i = 0; i < inputedLine.size(); i++)
	{
		if (inputedLine[i] != ' ')
		{
			temp += inputedLine[i];
		}
		else if (temp.size() > 0)
		{
			inputedCommand.push_back(temp);
			temp = "";
		}
	}
	if (temp.size() > 0)
	{
		inputedCommand.push_back(temp);
		temp = "";
	}
	if (!inputedCommand.empty())
	{
		return inputedCommand;
	}
	return {};
}

void CommandPanel::Draw()
{
	commandsHistoryPanel.Draw();
	inputField.Draw();
}

short CommandPanel::getHeight() { return height; }

InputField& CommandPanel::getInputField() { return inputField; }

CommandsHistoryPanel& CommandPanel::getCommandsHistoryPanel() {	return commandsHistoryPanel; }

CommandPanel::CommandPanel() : commandsHistoryPanel{}
{
	origin = commandsHistoryPanel.getOrigin();
	height = commandsHistoryPanel.getHeight() + 1;
	inputField = InputField("Input Command", 14, ">", 100);
	inputField.getLabel()->setOrigin({ origin.X, short(origin.Y + height) });
}

