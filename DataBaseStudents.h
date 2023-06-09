#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Student.h"

class DataBaseStudents
{
public:
	bool ImportDataBaseStudents(string path);
    map<int, Student>& getStudents();
    DataBaseStudents();
private:
    map<int, Student> students;
};

map<int, Student>& DataBaseStudents::getStudents() { return students; }
    
bool DataBaseStudents::ImportDataBaseStudents(string path)
{
    ifstream file;
    path = path + ".txt";
    file.open(path);

    if (!file.is_open()) {

        return false;
    }

    string line;
    Student student;
    while (getline(file, line)) {
        if (line == "") {
            return false;
        }
        if (line[0] == '-')
        {
            continue;
        }
        if (line[0] != ';' && line[0] != '-')
        {
            student = Student(line);
            student.id = students.size();
            students.insert(pair<int, Student>(student.id, student));
        }
        if (line[0] == ';')
        {
            student.AddMarks(line);
            student.id = students.size() - 1;
            students[student.id] = student;
        }
        
    }

    if (students.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

DataBaseStudents::DataBaseStudents(){}