#pragma once

class IDE; // forward declaration
#include "Command.h"


class MoveCaretToCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	MoveCaretToCommand(IDE& ide);

	bool execute(sf::Event event) override;
};