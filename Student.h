#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"


class Student
{
public:
	void AddMarks(string line);
	string getFirstName();
	string getLastName();
	string getMiddleName();
	void setMiddleName(string middleName);
	void setLastName(string lastName);
	void setFirstName(string firstName);
	vector<string>& getSubjects();
	map<string, vector<string>>& getMarks();
	void setMarksEverySubject(string mark);
	int getId();
	void setId(int id);
	Student(string line);
	Student();
private:
	int id;
	string firstName;
	string lastName;
	string middleName;
	vector<string> subjects;
	map<string, vector<string>> marks;
};


void Student::setMiddleName(string middleName)
{
	this->middleName = middleName;
}

void Student::setLastName(string lastName)
{
	this->lastName = lastName;
}

void Student::setFirstName(string firstName)
{
	this->firstName = firstName;
}

vector<string>& Student::getSubjects() {	return subjects;}

string Student::getFirstName() {	return firstName; }

string Student::getLastName() {	return lastName; }

string Student::getMiddleName() {return middleName;}

map<string, vector<string>>& Student::getMarks()
{
	return marks;
}

void Student::setMarksEverySubject(string mark)
{
	for (auto& idSubject : marks)
	{
		idSubject.second.push_back(mark);
	}
}


Student::Student()
{
	id = 0;
	firstName = "";
	lastName = " ";
	middleName = " ";
	subjects = { "English language", "Russian language", "Geography", "Mathematics", "Literature", "Geometry", "Informatics" };
	marks = {};
}

int Student::getId() {	return id; }

void Student::setId(int id)
{
	this->id = id;
}

Student::Student(string line) : Student()
{
	int position = line.find(";");
	id = stoi(line.substr(0, position));

	line = line.substr(++position);
	position = line.find(";");
	lastName = line.substr(0, position);

	line = line.substr(++position);
	position = line.find(";");
	firstName = line.substr(0, position);

	line = line.substr(++position);
	position = line.find(";");
	middleName = line.substr(0, position);

	line = line.substr(++position);
	position = line.find(";");
}

void Student::AddMarks(string line)
{

	int position = line.find(";");
	line = line.substr(++position);

	position = line.find(";");
	string subject = line.substr(0, position);
	line = line.substr(++position);

	vector<string> listMarks;

	string markstr;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] != ';')
		{
			markstr = line[i];
		}
		else
		{
			listMarks.push_back(markstr);
			markstr = "";
		}
	}

	for (int i = 0; i < subjects.size(); i++)
	{
		if (subject == subjects[i])
		{

			marks[subject] = listMarks;
			break;
		}
	}
}
