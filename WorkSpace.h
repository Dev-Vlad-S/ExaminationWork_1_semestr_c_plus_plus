#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "AuthorizationPanel.h"
#include "PersonalAccount.h"

class WorkSpace
{
public:
	void Draw();
	AuthorizationPanel& getAuthorizationPanel();
	PersonalAccount& getPersonalAccount();
	WorkSpace();

private:
	AuthorizationPanel authorizationPanel;
	PersonalAccount personalAccount;
};

WorkSpace::WorkSpace() : authorizationPanel{}
{

}

AuthorizationPanel& WorkSpace::getAuthorizationPanel() { return authorizationPanel; }

PersonalAccount& WorkSpace::getPersonalAccount() { return personalAccount; }

void WorkSpace::Draw()
{
	system("cls");
	if (authorizationPanel.getStatusDemostration())
	{
		authorizationPanel.Draw();
	}
	else if (personalAccount.getStatusDemostration())
	{
		personalAccount.Draw();
	}
}
