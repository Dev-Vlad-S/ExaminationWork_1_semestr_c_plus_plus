#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "DataBaseClassRoomTeachers.h"
#include "DataBaseStudents.h"

class DataBase
{
public:
	DataBase();
	DataBaseClassRoomTeachers& getDataBaseClassRoomTeachers();
	DataBaseStudents& getDataBaseStudents();
private:
	DataBaseClassRoomTeachers dbClassRoomTeachers;
	DataBaseStudents dbStudents;
};

DataBase::DataBase() : dbClassRoomTeachers{}, dbStudents{} {}

DataBaseClassRoomTeachers& DataBase::getDataBaseClassRoomTeachers() { return dbClassRoomTeachers; }

DataBaseStudents& DataBase::getDataBaseStudents() { return dbStudents; }
