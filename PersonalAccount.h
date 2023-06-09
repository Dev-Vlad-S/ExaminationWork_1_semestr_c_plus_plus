#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "CommandPanel.h"
#include "OutPutPanel.h"
#include "SplitLine.h"

class PersonalAccount
{
public:
	void InputCommands(KEY_EVENT_RECORD key, DataBaseStudents& dbStudents);
	void Draw();
	bool getStatusDemostration();
	void setStatusDemostration(bool isDemonstaration);
	PersonalAccount();
private:
	void ClearInputedSymbol();
	void ClearInputedCommand();
	void ImplementCommands(DataBaseStudents& dbStudents);
	void UpdateHistoryPanel();
	bool ReadFile(DataBaseStudents& dbStudents, vector<string>& commandLine);
	void PrintStudents(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool AddStudent(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool DeleteByID(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool CallHelp(vector<string>& commandLine);
	void ListUpHistory();
	void ListDownHistory();
private:
	SplitLine splitLine;
	Demonstration demonstration;
	CommandPanel commandPanel;
	OutPutPanel outPutPanel;
};

void PersonalAccount::ListUpHistory()
{
	int	position = commandPanel.getCommandsHistoryPanel().getPosition();
	if (commandPanel.getCommandsHistoryPanel().getHistory()[position] != "")
	{
		commandPanel.getInputField().getInputLabel()->ClearAll();
		commandPanel.getInputField().getInputLabel()->setInputedLine(commandPanel.getCommandsHistoryPanel().getHistory()[position]);
		commandPanel.getCommandsHistoryPanel().setPosition(--position);
	}
	Draw();
}

void PersonalAccount::ListDownHistory()
{
	int	position = commandPanel.getCommandsHistoryPanel().getPosition();
	if (commandPanel.getCommandsHistoryPanel().getHistory()[position] == "")
	{
		++position;

	}
	commandPanel.getCommandsHistoryPanel().setPosition(++position);
	if (commandPanel.getCommandsHistoryPanel().getHistory()[commandPanel.getCommandsHistoryPanel().getPosition()] != "")
	{
		commandPanel.getInputField().getInputLabel()->ClearAll();
		commandPanel.getInputField().getInputLabel()->setInputedLine(commandPanel.getCommandsHistoryPanel().getHistory()[commandPanel.getCommandsHistoryPanel().getPosition()]);
	}
	Draw();
}

void PersonalAccount::InputCommands(KEY_EVENT_RECORD key, DataBaseStudents& dbStudents)
{
	if (!key.bKeyDown)
	{
		switch (key.wVirtualKeyCode)
		{
		case UP:
			ListUpHistory();
			break;
		case DOWN:
			ListDownHistory();
			break;
		case ENTER:
			ImplementCommands(dbStudents);
			break;
		case BACKSPACE:
			ClearInputedSymbol();
			break;
		default:
			commandPanel.getInputField().getInputLabel()->InputLineText(key.uChar.AsciiChar);
			commandPanel.getCommandsHistoryPanel().resetPosition();
		}
	}
}

void PersonalAccount::ImplementCommands(DataBaseStudents& dbStudents)
{
	UpdateHistoryPanel();
	vector<string> commandLine = commandPanel.ParsingCommandLine();
	if (!commandLine.empty())
	{
		if (AddStudent(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
		}
		if (ReadFile(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
		}
		if (DeleteByID(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
		}
		if (CallHelp(commandLine))
		{
			
		}
	}
	ClearInputedCommand();
	commandPanel.getCommandsHistoryPanel().resetPosition();
	Draw();
}

bool PersonalAccount::DeleteByID(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (commandLine[0] == "delete")
	{
		if (commandLine.size() > 1)
		{
			if (commandLine[1] == "student")
			{
				if (commandLine.size() > 2)
				{
					if (commandLine[2] == "-id")
					{
						if (commandLine.size() > 3)
						{
							dbStudents.getStudents().erase(dbStudents.getStudents().find(stoi(commandLine[3])));
							return true;
						}
					}


				}
			}
		}

	}

	return isReady;
}



bool PersonalAccount::AddStudent(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	Student student;
	if (commandLine[0] == "add")
	{
		if (commandLine.size() > 1)
		{
			if (commandLine[1] == "student")
			{
				if (commandLine.size() > 2)
				{
					isReady = true;

					if (commandLine[2] == "-l")
					{
						if (commandLine.size() > 3)
						{
							student.setLastName(commandLine[3]);
							isReady = true;

							if (commandLine.size() > 4)
							{
								if (commandLine[4] == "-f")
								{
									if (commandLine.size() > 5)
									{
										student.setFirstName(commandLine[5]);

										if (commandLine.size() > 6)
										{
											if (commandLine[6] == "-m")
											{
												if (commandLine.size() > 7)
												{
													student.setMiddleName(commandLine[7]);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}


	if (isReady)
	{
		student.id = dbStudents.getStudents().size();
		dbStudents.getStudents()[student.id] = student;
	}
	return isReady;
}

bool PersonalAccount::ReadFile(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	if (dbStudents.getStudents().empty())
	{
		if (commandLine[0] == "read")
		{
			if (commandLine.size() > 1)
			{
				if (dbStudents.ImportDataBaseStudents(commandLine[1]))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
	return false;
}

void PersonalAccount::PrintStudents(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	if (commandLine[commandLine.size()-1] == "print")
	{
		outPutPanel.Display(dbStudents);
	}
}

bool PersonalAccount::CallHelp(vector<string>& commandLine)
{
	if (commandLine[commandLine.size() - 1] == "help")
	{
		outPutPanel.DisplayHelp();
		return true;
	}
	return false;
}

void PersonalAccount::ClearInputedSymbol()
{
	commandPanel.getInputField().getInputLabel()->ClearSymbol();
}

void PersonalAccount::ClearInputedCommand()
{
	commandPanel.getInputField().getInputLabel()->ClearAll();
}

void PersonalAccount::UpdateHistoryPanel()
{
	if (commandPanel.getInputField().getInputLabel()->getInputedLine() != "")
	{
		commandPanel.getCommandsHistoryPanel().getHistory().erase(commandPanel.getCommandsHistoryPanel().getHistory().begin());
		commandPanel.getCommandsHistoryPanel().getHistory().push_back(commandPanel.getInputField().getInputLabel()->getInputedLine());
	}
}


void PersonalAccount::Draw()
{
	splitLine.Draw();
	commandPanel.Draw();
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, commandPanel.getInputField().getInputLabel()->getOrigin());
}

bool PersonalAccount::getStatusDemostration() { return bool(demonstration); }

void PersonalAccount::setStatusDemostration(bool isDemonstaration)
{
	if (isDemonstaration)
	{
		demonstration = Demonstration::On;
	}
	else
	{
		demonstration = Demonstration::Off;
	}
}

PersonalAccount::PersonalAccount() : commandPanel{}
{
	splitLine = SplitLine(COORD(0, commandPanel.getHeight() + StatusBar::getOrigin().Y + 1));
	outPutPanel = OutPutPanel(COORD(0, commandPanel.getHeight() + StatusBar::getOrigin().Y + 3));
	demonstration = Demonstration::Off;
}

