#pragma once
#include "ConnectedLibraries.h"
#include "ServiceVariables.h"
#include "Label.h"
#include "InputLabel.h"

class InputField : public IPainter
{
public:

	void Draw() override;
	Label* getLabel();
	InputLabel* getInputLabel();
	InputField(string text, int maxLengthLabel, string indicator, int maxLengthInputLabel);
	InputField();
private:
	Label* label;
	InputLabel* inputLabel;
};

InputField::InputField() {}

InputField::InputField(string text, int maxLengthLabel = 10, string indicator = ":", int maxLengthInputLabel = 20)
{
	label = new Label(text, { 0,0 }, maxLengthLabel, indicator);
	inputLabel = new InputLabel(maxLengthInputLabel);
}

void InputField::Draw()
{
	label->Draw();
	COORD originInputLabel = { label->getOrigin().X + label->getLine().size() + 2, label->getOrigin().Y };
	inputLabel->setOrigin(originInputLabel);
	inputLabel->Draw();
}

Label* InputField::getLabel() { return label; }

InputLabel* InputField::getInputLabel() { return inputLabel; }





