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
	bool ReadFromFile(DataBaseStudents& dbStudents, vector<string>& commandLine);
	void PrintStudents(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool AddStudent(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool DeleteByID(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool WriteToFile(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool ReNameLastName(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool ReNameFirstName(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool ReNameMiddleName(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool AddMarksEvery(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool AddMark(DataBaseStudents& dbStudents, vector<string>& commandLine);
	bool UpdateMark(DataBaseStudents& dbStudents, vector<string>& commandLine);
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
	if (key.bKeyDown || key.wVirtualKeyCode == SHIFT_PRESSED)
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
			StatusBar::Draw("Success add student");
		}
		if (ReadFromFile(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success read from file");
		}
		if (DeleteByID(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success delete student");
		}
		if (CallHelp(commandLine))
		{
			StatusBar::Draw("Success called help");
		}
		if (WriteToFile(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success write to file help");
		}
		if (ReNameLastName(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success rename");
		}
		if (ReNameFirstName(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success rename");
		}
		if (ReNameMiddleName(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success rename");
		}
		if (AddMarksEvery(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success add marks all");
		}
		if (AddMark(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success add mark");
		}
		if (UpdateMark(dbStudents, commandLine))
		{
			PrintStudents(dbStudents, commandLine);
			StatusBar::Draw("Success update mark");
		}

	}
	ClearInputedCommand();
	commandPanel.getCommandsHistoryPanel().resetPosition();
	Draw();
}

bool PersonalAccount::UpdateMark(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (commandLine[0] == "change")
	{
		if (commandLine.size() > 1)
		{
			if (commandLine[1] == "mark")
			{
				if (commandLine.size() > 2)
				{
					if (commandLine[2] == "-id")
					{
						if (commandLine.size() > 3)
						{
							if (dbStudents.getStudents().empty())
							{
								return isReady;
							}
							if (commandLine.size() > 4)
							{
								if (commandLine[4] == "-s")
								{
									if (commandLine.size() > 5)
									{
										string subject = dbStudents.getStudents().find(stoi(commandLine[3]))->second.getSubjects()[stoi(commandLine[5])];

										if (commandLine.size() > 6)
										{
											if (commandLine[6] == "-m")
											{
												if (commandLine.size() > 7)
												{
													string mark = commandLine[7];
													if (commandLine.size() > 8)
													{
														if (commandLine[8] == "-n")
														{
															if (commandLine.size() > 9)
															{
																for (auto& item : dbStudents.getStudents().find(stoi(commandLine[3]))->second.getMarks().find(subject)->second)
																{
																	if (item == mark)
																	{
																		item = commandLine[9];
																		isReady = true;
																		break;
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
					}

				}
			}
		}
	}
	return isReady;
}

bool PersonalAccount::AddMark(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (commandLine[0] == "add")
	{
		if (commandLine.size() > 1)
		{
			if (commandLine[1] == "mark")
			{
				if (commandLine.size() > 2)
				{
					if (commandLine[2] == "-id")
					{
						if (commandLine.size() > 3)
						{
							if (dbStudents.getStudents().empty())
							{
								return isReady;
							}
							if (commandLine.size() > 4)
							{
								if (commandLine[4] == "-s")
								{
									if (commandLine.size() > 5)
									{
										string subject = dbStudents.getStudents().find(stoi(commandLine[3]))->second.getSubjects()[stoi(commandLine[5])];

										if (commandLine.size() > 6)
										{
											if (commandLine[6] == "-m")
											{
												if (commandLine.size() > 7)
												{
													dbStudents.getStudents().find(stoi(commandLine[3]))->second.getMarks().find(subject)->second.push_back(commandLine[7]);
													isReady = true;
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
	return isReady;
}

bool PersonalAccount::AddMarksEvery(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (commandLine[0] == "add")
	{
		if (commandLine.size() > 1)
		{
			if (commandLine[1] == "marks")
			{
				if (commandLine.size() > 2)
				{
					if (commandLine[2] == "-all")
					{
						if (commandLine.size() > 3)
						{
							if (!dbStudents.getStudents().empty())
							{
								for (auto& itemid : dbStudents.getStudents())
								{
									for (auto& itemsubject : itemid.second.getSubjects())
									{
										itemid.second.setMarksEverySubject(commandLine[3]);
										break;
									}
								}
								isReady = true;;
							}
							

						}
					}

				}
			}
		}
	}
	return isReady;
}


bool PersonalAccount::ReNameMiddleName(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (commandLine[0] == "rename")
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
							if (dbStudents.getStudents().empty())
							{
								return isReady;
							}
							if (commandLine.size() > 4)
							{
								if (commandLine[4] == "-m")
								{
									if (commandLine.size() > 5)
									{
										dbStudents.getStudents().find(stoi(commandLine[3]))->second.setMiddleName(commandLine[5]);
										isReady = true;
									}
								}
							}

						}
					}

				}
			}
		}
	}
	return isReady;
}

bool PersonalAccount::ReNameFirstName(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (commandLine[0] == "rename")
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
							if (dbStudents.getStudents().empty())
							{
								return isReady;
							}
							if (commandLine.size() > 4)
							{
								if (commandLine[4] == "-f")
								{
									if (commandLine.size() > 5)
									{
										dbStudents.getStudents().find(stoi(commandLine[3]))->second.setFirstName(commandLine[5]);
										isReady = true;
									}
								}
							}

						}
					}

				}
			}
		}
	}
	return isReady;
}

bool PersonalAccount::ReNameLastName(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (commandLine[0] == "rename")
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
							if (dbStudents.getStudents().empty())
							{
								return isReady;
							}
							if (commandLine.size() > 4)
							{
								if (commandLine[4] == "-l")
								{
									if (commandLine.size() > 5)
									{
										dbStudents.getStudents().find(stoi(commandLine[3]))->second.setLastName(commandLine[5]);
										isReady = true;
									}
								}
							}

						}
					}

				}
			}
		}
	}
	return isReady;
}

bool PersonalAccount::WriteToFile(DataBaseStudents& dbStudents, vector<string>& commandLine)
{
	bool isReady = false;
	if (!dbStudents.getStudents().empty())
	{
		if (commandLine[0] == "write")
		{
			if (commandLine.size() > 1)
			{
				if (dbStudents.ExportDataBaseStudents(commandLine[1]))
				{

					isReady = true;
				}
				else
				{
					isReady = false;
				}
			}
		}
	}
	return isReady;
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
					if (commandLine[2] == "-l")
					{
						if (commandLine.size() > 3)
						{
							isReady = true;
							if (!dbStudents.getStudents().empty())
							{
								int id = dbStudents.getStudents().rbegin()->second.getId();
								student.setId(++id);
							}
							else
							{
								student.setId(0);
							}
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
		dbStudents.getStudents()[student.getId()] = student;
	}
	return isReady;
}

bool PersonalAccount::ReadFromFile(DataBaseStudents& dbStudents, vector<string>& commandLine)
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
	if (commandLine[commandLine.size() - 1] == "print")
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

