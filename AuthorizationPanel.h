#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"
#include "Frame.h"
#include "InputField.h"
#include "Button.h"
#include "DataBaseClassRoomTeachers.h"
#include "StatusBar.h"


class AuthorizationPanel
{
public:
	AuthorizationPanel();
	bool getStatusDemostration();
	void Draw();
	void SelectSection(KEY_EVENT_RECORD key, DataBaseClassRoomTeachers& dbClassRoomTeachers);
private:
	void setOrigin();
	void setSection(int activeSection);
	void setTextSection(string text);
	void InputAuthorizationData(WCHAR ch);
	void ChangeViewPanel(int activeSection, PressedKey key);
	void ChecInputedAutorizationData(DataBaseClassRoomTeachers& dbClassRoomTeachers);
	void ClearInputedAutorizationData();
	void DispalayTip();
	void Clear();

private:
	Demonstration demonstration;
	COORD origin;
	Frame frame;
	vector<Object*> objects;
	enum Sections { LOGIN, PASSWORD, GROUP, SINGIN };
	Sections section = LOGIN;
	string textSection;
};

AuthorizationPanel::AuthorizationPanel() : frame{}
{
	demonstration = Demonstration::On;
	objects = { new InputField("LOGIN"), new InputField("PASSWORD"),  new InputField("GROUP"), new Button("SINGIN") };
	textSection = objects[section]->getText();
	Draw();
}

void AuthorizationPanel::SelectSection(KEY_EVENT_RECORD key, DataBaseClassRoomTeachers& dbClassRoomTeachers)
{
	int activeSection = section;
	if (!key.bKeyDown)
	{

		switch (key.wVirtualKeyCode)
		{
		case UP:
			ChangeViewPanel(activeSection, UP);
			break;
		case DOWN:
			ChangeViewPanel(activeSection, DOWN);
			break;
		case ENTER:
			ChecInputedAutorizationData(dbClassRoomTeachers);
			break;
		case BACKSPACE:
			ClearInputedAutorizationData();
			break;
		default:
			InputAuthorizationData(key.uChar.AsciiChar);
		}
	}
}

bool AuthorizationPanel::getStatusDemostration() { return bool(demonstration); }

void AuthorizationPanel::setOrigin()
{
	GetConsoleScreenBufferInfo(ServiceVariables::hOutputBuffer, &ServiceVariables::cScrBufferInfo);
	short originX = ServiceVariables::cScrBufferInfo.dwSize.X / 2 - frame.getWidth() / 2;
	short originY = ServiceVariables::cScrBufferInfo.dwSize.Y / 2 - frame.getHeight() / 2;
	origin = { originX, originY };
}

void AuthorizationPanel::Draw()
{
	if (bool(demonstration))
	{
		setOrigin();
		frame.Draw(origin);
		objects[LOGIN]->Draw(origin, { 3, 3 }, textSection);
		objects[PASSWORD]->Draw(origin, { 3, 6 }, textSection);
		objects[GROUP]->Draw(origin, { 3, 9 }, textSection);
		objects[SINGIN]->Draw(origin, { 16, 13 }, textSection);
		DispalayTip();

		if (section == LOGIN || section == PASSWORD || section == GROUP)
		{
			SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { (dynamic_cast<InputLabel*>(objects[section]))->getOrigin() });
		}
	}
}

void AuthorizationPanel::setSection(int activeSection) { section = Sections(activeSection); }

void AuthorizationPanel::setTextSection(string text) { textSection = text; }

void AuthorizationPanel::ChangeViewPanel(int activeSection, PressedKey key)
{
	if (key == UP)
	{
		if (section < objects.size() && section > 0)
		{
			setSection(--activeSection);
			setTextSection(objects[section]->getText());
		}
	}
	if (key == DOWN)
	{
		if (activeSection > -1 && activeSection < objects.size() - 1)
		{
			setSection(++activeSection);
			setTextSection(objects[section]->getText());
		}
	}
	Draw();
}

void AuthorizationPanel::InputAuthorizationData(WCHAR ch)
{
	if (section == LOGIN || section == PASSWORD || section == GROUP)
	{
		(dynamic_cast<InputLabel*>(objects[section]))->InputLineText(ch);
	}
}

void AuthorizationPanel::ChecInputedAutorizationData(DataBaseClassRoomTeachers& dbClassRoomTeachers)
{
	if (section == SINGIN)
	{
		string login = dynamic_cast<InputLabel*>(objects[LOGIN])->getInputedLine();
		string password = dynamic_cast<InputLabel*>(objects[PASSWORD])->getInputedLine();
		string group = dynamic_cast<InputLabel*>(objects[GROUP])->getInputedLine();

		if (login == "" || password == "" || group == "")
		{
			StatusBar::Draw("Error");
			return;
		}

		map<string, map<string, string>> inputedTeachersAutorizationData;
		inputedTeachersAutorizationData[group].insert({ login,password });
		if (dbClassRoomTeachers.ReadInputAuthorizationData(inputedTeachersAutorizationData))
		{
			StatusBar::Draw("Autorization Data inputed sucsessful");
			Clear();
		}
		else
		{
			StatusBar::Draw("Error");
		}
	}
}

void AuthorizationPanel::ClearInputedAutorizationData()
{
	if (section == LOGIN || section == PASSWORD || section == GROUP)
	{
		dynamic_cast<InputLabel*>(objects[section])->Clear();
	}
}

void AuthorizationPanel::DispalayTip()
{
	switch (section)
	{
	case LOGIN:
		StatusBar::Draw("Section selected " + objects[LOGIN]->getText() + ". By pressing ENTER, you can input " + objects[LOGIN]->getText());
		break;
	case PASSWORD:
		StatusBar::Draw("Section selected " + objects[PASSWORD]->getText() + ". By pressing ENTER, you can input " + objects[PASSWORD]->getText());
		break;
	case GROUP:
		StatusBar::Draw("Section selected " + objects[GROUP]->getText() + ". By pressing ENTER, you can input " + objects[GROUP]->getText());
		break;
	case SINGIN:
		StatusBar::Draw("Section selected " + objects[SINGIN]->getText() + ". By pressing ENTER, you can enter your personal account");
		break;
	}
}

void AuthorizationPanel::Clear()
{
	for (int i = 0; i < frame.getHeight(); i++)
	{
		SetConsoleCursorPosition(ServiceVariables::hOutputBuffer, { origin.X, short(origin.Y + i) });
		for (int j = 0; j < frame.getWidth(); j++)
		{
			cout << " ";
		}
		cout << endl;
	}
	demonstration = Demonstration::Off;
}
