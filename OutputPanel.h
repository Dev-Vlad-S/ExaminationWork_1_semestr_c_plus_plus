#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "DataBaseStudents.h"

class OutPutPanel
{
public:
	void Display(DataBaseStudents& dbStudents);
	OutPutPanel();
	OutPutPanel(COORD origin);
	void DisplayHelp();
private:
	void Clear();
private:
	COORD origin;
};


void OutPutPanel::DisplayHelp()
{
	Clear();
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
	cout << "Commands:" << endl;
	cout << "1. " << "read <name>" << " - " << "Load data base of students" << endl;
	cout << "2. " << "print" << " - " << "Display data base of students" << endl;
	cout << "3. " << "add student" << " - " << "Display data base of students" << endl;
	cout << "\t" << " * - " << "\"-l <last name>\"" <<  " - " << "Add last name" << endl;
	cout << "\t" << " * - " << "\"-f <first name>\"" <<  " - " << "Add first name" << endl;
	cout << "\t" << " * - " << "\"-m <middle name>\"" <<  " - " << "Add middle name" << endl;
	cout << "4. " << "delete student" << " - " << "Delete student from data base of students" << endl;
	cout << "\t" << " * - " << "\"-id <id>\"" << " - " << "Delete student from data base of students by ID" << endl;
}

void OutPutPanel::Display(DataBaseStudents& dbStudents)
{
	Clear();
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
	for (auto& itemid : dbStudents.getStudents())
	{
		string indicator = ";";
		cout << itemid.first << indicator;
		cout << itemid.second.getLastName() << indicator;
		cout << itemid.second.getFirstName() << indicator;
		cout << itemid.second.getMiddleName() << indicator;
		cout << endl;

		for (auto& itemsubject : itemid.second.getSubjects())
		{
			cout << indicator;
			cout << itemsubject << indicator;
			for (auto& itemmark : itemid.second.getMarks()[itemsubject])
			{
				cout << itemmark << indicator;
			}
			cout << endl;
		}
	}
}

OutPutPanel::OutPutPanel() {}

OutPutPanel::OutPutPanel(COORD origin)
{
	this->origin = origin;
}

void OutPutPanel::Clear()
{
	GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
	short height = ServiceVariables::cScrBufferInfo.dwSize.Y - origin.Y - 1;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < ServiceVariables::cScrBufferInfo.dwSize.X; j++)
		{
			cout << " ";
		}
		cout << endl;
	}
	SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, origin);
}
