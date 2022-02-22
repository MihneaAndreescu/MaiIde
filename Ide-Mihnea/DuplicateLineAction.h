#pragma once

class IDE; // forward declaration
#include "Action.h"

class DuplicateLineAction : public Action {
private:
	long long init_hash;
	IDE& m_state;

public:
	DuplicateLineAction(IDE& state);

	void doAction() override;
	void undoAction() override;
};
