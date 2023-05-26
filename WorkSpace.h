#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "AuthorizationPanel.h"

class WorkSpace
{
public:
	WorkSpace();
	AuthorizationPanel& getAuthorizationPanel();
	void Draw();
private:
	AuthorizationPanel authorizationPanel;

};

WorkSpace::WorkSpace() : authorizationPanel{}
{

}

AuthorizationPanel& WorkSpace::getAuthorizationPanel() { return authorizationPanel; }

void WorkSpace::Draw()
{
	system("cls");
	authorizationPanel.Draw();
}
