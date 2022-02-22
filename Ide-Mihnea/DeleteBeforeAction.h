#pragma once

class IDE; // forward declaration
#include "Action.h"


class DeleteBeforeAction : public Action {
private:
	long long init_hash;
	IDE& m_state;
	int iftype = 0;
	int sizeOfRow;
	char deletedChar;
	int init_row;
	int init_col;

public:
	DeleteBeforeAction(IDE& state);

	void doAction() override;
	void undoAction() override;

};