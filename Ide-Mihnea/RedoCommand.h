#pragma once

class IDE; // forward declaration
#include "Command.h"

class RedoCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	RedoCommand(IDE& ide);

	bool execute(sf::Event event) override;
};