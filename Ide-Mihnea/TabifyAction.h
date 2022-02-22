#pragma once

class IDE; // forward declaration
#include "Action.h"

class TabifyAction : public Action {
private:
	long long init_hash;
	IDE& m_state;
	int shiftBy;
public:
	TabifyAction(IDE& state);
	void doAction() override;
	void undoAction() override;
};