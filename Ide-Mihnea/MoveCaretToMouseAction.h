#pragma once

class IDE; // forward declaration
#include "Action.h"

class MoveCaretToMouseAction : public Action {
private:
	long long init_hash;
	IDE& m_state;
	int init_row, init_col;

public:
	MoveCaretToMouseAction(IDE& state);
	void doAction() override;
	void undoAction() override;
};