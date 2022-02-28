#pragma once

class IDE; // forward declaration
#include "Command.h"

class InsertCharacterCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	InsertCharacterCommand(IDE& ide);

	bool execute(sf::Event event) override;
};