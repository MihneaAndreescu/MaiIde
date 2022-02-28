#pragma once

class IDE; // forward declaration
#include "Command.h"

class IndentCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	IndentCommand(IDE& ide);

	bool execute(sf::Event event) override;
};