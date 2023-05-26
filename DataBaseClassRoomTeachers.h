#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"

class DataBaseClassRoomTeachers
{
public:
	DataBaseClassRoomTeachers();
	bool ReadInputAuthorizationData(map < string, map<string, string>> inputedTeachersAutorizationData);
	
private:
	map < string, map<string, string>> teachersAutorizationData;
};

DataBaseClassRoomTeachers::DataBaseClassRoomTeachers()
{
	teachersAutorizationData["10a"].insert({ "annaivanovna", "cool10a" });
	teachersAutorizationData["9b"].insert({ "lizapetrovna", "cool9b" });
	teachersAutorizationData["8d"].insert({ "irinaviktorovna", "cool8d" });
}

bool DataBaseClassRoomTeachers::ReadInputAuthorizationData(map<string, map<string, string>> inputedTeachersAutorizationData)
{
	string group = inputedTeachersAutorizationData.begin()->first;
	if (teachersAutorizationData.find(group) != teachersAutorizationData.end())
	{
		if (teachersAutorizationData[group] == inputedTeachersAutorizationData[group])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
