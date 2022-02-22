#pragma once

class IDE; // forward declaration
#include "Action.h"
#include <vector>
#include <string>

class IndentAction : public Action {
private:
	long long init_hash;
	IDE& m_state;
	int init_row;
	int init_col;
	std::vector<std::string> init_rows;

public:
	IndentAction(IDE& state);

	void doAction() override;

	void undoAction() override;
};
