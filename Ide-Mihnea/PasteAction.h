#pragma once

class IDE; // forward declaration
#include "Action.h"
#include <vector>
#include <string>

class PasteAction : public Action {
private:
	long long init_hash;
	std::vector<std::string> paste;
	IDE& m_state;
	int mn;
	int mx;
	int init_row;
	int init_col;
	std::string init;

public:
	PasteAction(IDE& state, std::vector<std::string> paste);

	void doAction() override;
	void undoAction() override;
};
