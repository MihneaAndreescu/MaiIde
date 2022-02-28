#pragma once

class IDE; // forward declaration
#include "Command.h"


class UndoCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	UndoCommand(IDE& ide);

	bool execute(sf::Event event) override;
};


