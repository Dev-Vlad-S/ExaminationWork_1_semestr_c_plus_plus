#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Student.h"

class DataBaseStudents
{
public:
	bool ImportDataBaseStudents(string path);
	bool ExportDataBaseStudents(string path);
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
        }
        if (line[0] == ';')
        {
            student.AddMarks(line);
            students[student.getId()] = student;
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

bool DataBaseStudents::ExportDataBaseStudents(string path)
{
    ofstream file;
    path = path + ".txt";
    file.open(path, ios::trunc);
    if (!file.is_open()) {
        file.close();
        return false;
    }

    for (auto& itemid : students)
    {
        string indicator = ";";
        file << itemid.first << indicator;
        file << itemid.second.getLastName() << indicator;
        file << itemid.second.getFirstName() << indicator;
        file << itemid.second.getMiddleName() << indicator;
        file << endl;

        for (auto& itemsubject : itemid.second.getSubjects())
        {
            file << indicator;
            file << itemsubject << indicator;
            for (auto& itemmark : itemid.second.getMarks()[itemsubject])
            {
                file << itemmark << indicator;
            }
            file << endl;
        }
        file << "-" << endl;
    }
   
}



DataBaseStudents::DataBaseStudents(){}