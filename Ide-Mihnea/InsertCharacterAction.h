#pragma once

class IDE; // forward declaration
#include "Action.h"

class InsertCharacterAction : public Action {
private:
	long long init_hash;
	char m_charToInsert;
	IDE& m_state;
public:
	InsertCharacterAction(IDE& state, char charToInsert);

	void doAction() override;
	void undoAction() override;

};