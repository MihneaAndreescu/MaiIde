#pragma once

class IDE; // forward declaration
#include "Action.h"

class MoveCaretLeftAction : public Action {
private:
	long long init_hash;
	IDE& m_state;
	int init_row, init_col;

public:
	MoveCaretLeftAction(IDE& state);
	void doAction() override;
	void undoAction() override;
};