#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"

class DataBaseClassRoomTeachers
{
public:
	bool ReadInputAuthorizationData(map < string, map<string, string>> inputedTeachersAutorizationData);
	DataBaseClassRoomTeachers();
	
private:
	map < string, map<string, string>> teachersAutorizationData;
};

DataBaseClassRoomTeachers::DataBaseClassRoomTeachers()
{
	teachersAutorizationData["10A"].insert({ "AnnaIvanovna", "cool10A" });
	teachersAutorizationData["9B"].insert({ "LizaPetrovna", "cool9B" });
	teachersAutorizationData["8D"].insert({ "IrinaViktorovna", "cool8D" });
	teachersAutorizationData["1"].insert({ "1", "1" });
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
