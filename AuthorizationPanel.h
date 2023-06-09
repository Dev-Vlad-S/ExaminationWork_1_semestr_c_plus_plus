#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Object.h"
#include "Frame.h"
#include "InputField.h"
#include "Button.h"
#include "DataBaseClassRoomTeachers.h"
#include "StatusBar.h"
#include "IPainter.h"

class AuthorizationPanel
{
public:
	void Draw();
	void SelectSection(KEY_EVENT_RECORD key, DataBaseClassRoomTeachers& dbClassRoomTeachers);
	bool getStatusDemostration();
	AuthorizationPanel();
private:
	void DrawSections();
	void setOrigin();
	void InputAuthorizationData(WCHAR ch);
	void SetSection(int activeSection, PressedKey key);
	void ChecInputedAutorizationData(DataBaseClassRoomTeachers& dbClassRoomTeachers);
	void ClearInputedAutorizationData();
	void DispalayTip();
	void Clear();

private:
	Demonstration demonstration;
	COORD origin;
	Frame frame;
	vector<IPainter*> objects;
	enum Sections { LOGIN, PASSWORD, GROUP, SINGIN };
	Sections section = LOGIN;
};

AuthorizationPanel::AuthorizationPanel() : frame{}
{
	demonstration = Demonstration::On;
	objects = { new InputField("LOGIN"), new InputField("PASSWORD"), new InputField("GROUP"), new Button("SINGIN") };
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
			SetSection(activeSection, UP);
			break;
		case DOWN:
			SetSection(activeSection, DOWN);
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
		DrawSections();
		DispalayTip();
	}
}

void AuthorizationPanel::DrawSections()
{
	if (section == LOGIN)
	{
		COORD offsetLogin = { origin.X + 3, origin.Y + 3 };
		dynamic_cast<InputField*>(objects[LOGIN])->getLabel()->setOrigin(offsetLogin);
		dynamic_cast<InputField*>(objects[LOGIN])->getLabel()->SetColor(Highlighted);
		dynamic_cast<InputField*>(objects[LOGIN])->Draw();
	}
	else
	{
		COORD offsetLogin = { origin.X + 3, origin.Y + 3 };
		dynamic_cast<InputField*>(objects[LOGIN])->getLabel()->setOrigin(offsetLogin);
		dynamic_cast<InputField*>(objects[LOGIN])->getLabel()->SetColor(Normal);
		dynamic_cast<InputField*>(objects[LOGIN])->Draw();
	}

	if (section == PASSWORD)
	{
		COORD offsetPassword = { origin.X + 3, origin.Y + 6 };
		dynamic_cast<InputField*>(objects[PASSWORD])->getLabel()->setOrigin(offsetPassword);
		dynamic_cast<InputField*>(objects[PASSWORD])->getLabel()->SetColor(Highlighted);
		dynamic_cast<InputField*>(objects[PASSWORD])->Draw();
	}
	else
	{
		COORD offsetPassword = { origin.X + 3, origin.Y + 6 };
		dynamic_cast<InputField*>(objects[PASSWORD])->getLabel()->setOrigin(offsetPassword);
		dynamic_cast<InputField*>(objects[PASSWORD])->getLabel()->SetColor(Normal);
		dynamic_cast<InputField*>(objects[PASSWORD])->Draw();
	}

	if (section == GROUP)
	{
		COORD offsetGroup = { origin.X + 3, origin.Y + 9 };
		dynamic_cast<InputField*>(objects[GROUP])->getLabel()->setOrigin(offsetGroup);
		dynamic_cast<InputField*>(objects[GROUP])->getLabel()->SetColor(Highlighted);
		dynamic_cast<InputField*>(objects[GROUP])->Draw();

	}
	else
	{
		COORD offsetGroup = { origin.X + 3, origin.Y + 9 };
		dynamic_cast<InputField*>(objects[GROUP])->getLabel()->setOrigin(offsetGroup);
		dynamic_cast<InputField*>(objects[GROUP])->getLabel()->SetColor(Normal);
		dynamic_cast<InputField*>(objects[GROUP])->Draw();
	}

	if (section == SINGIN)
	{
		COORD offsetSingIn = { origin.X + 18, origin.Y + 13 };
		dynamic_cast<Button*>(objects[SINGIN])->setOrigin(offsetSingIn);
		dynamic_cast<Button*>(objects[SINGIN])->SetColor(Highlighted);
		dynamic_cast<Button*>(objects[SINGIN])->Draw();
	}
	else
	{
		COORD offsetSingIn = { origin.X + 18, origin.Y + 13 };
		dynamic_cast<Button*>(objects[SINGIN])->setOrigin(offsetSingIn);
		dynamic_cast<Button*>(objects[SINGIN])->SetColor(Normal);
		dynamic_cast<Button*>(objects[SINGIN])->Draw();
	}

	if (section == LOGIN || section == PASSWORD || section == GROUP)
	{
		(dynamic_cast<InputField*>(objects[section]))->Draw();
	}
}

void AuthorizationPanel::SetSection(int activeSection, PressedKey key)
{
	if (key == UP)
	{
		if (section < objects.size() && section > 0)
		{
			section = Sections(--activeSection);
		}
	}
	if (key == DOWN)
	{
		if (activeSection > -1 && activeSection < objects.size() - 1)
		{
			section = Sections(++activeSection);;
		}
	}
	Draw();
}

void AuthorizationPanel::InputAuthorizationData(WCHAR ch)
{
	if (section == LOGIN || section == PASSWORD || section == GROUP)
	{
		(dynamic_cast<InputField*>(objects[section]))->getInputLabel()->InputLineText(ch);
	}
}

void AuthorizationPanel::ChecInputedAutorizationData(DataBaseClassRoomTeachers& dbClassRoomTeachers)
{
	if (section == SINGIN)
	{
		string login = dynamic_cast<InputField*>(objects[LOGIN])->getInputLabel()->getInputedLine();
		string password = dynamic_cast<InputField*>(objects[PASSWORD])->getInputLabel()->getInputedLine();
		string group = dynamic_cast<InputField*>(objects[GROUP])->getInputLabel()->getInputedLine();

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
		dynamic_cast<InputField*>(objects[section])->getInputLabel()->ClearSymbol();
	}
}

void AuthorizationPanel::DispalayTip()
{
	switch (section)
	{
	case LOGIN:
		//StatusBar::Draw("Section selected " + objects[LOGIN]->getText() + ". By pressing ENTER, you can input " + objects[LOGIN]->getText());
		break;
	case PASSWORD:
		//StatusBar::Draw("Section selected " + objects[PASSWORD]->getText() + ". By pressing ENTER, you can input " + objects[PASSWORD]->getText());
		break;
	case GROUP:
		//StatusBar::Draw("Section selected " + objects[GROUP]->getText() + ". By pressing ENTER, you can input " + objects[GROUP]->getText());
		break;
	case SINGIN:
		//StatusBar::Draw("Section selected " + objects[SINGIN]->getText() + ". By pressing ENTER, you can enter your personal account");
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
