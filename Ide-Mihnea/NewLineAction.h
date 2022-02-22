#pragma once

class IDE; // forward declaration
#include "Action.h"

class NewLineAction : public Action {
private:
	long long init_hash;
	IDE& m_state;
	int init_col;
public:
	NewLineAction(IDE& state);
	void doAction() override;
	void undoAction() override;
};