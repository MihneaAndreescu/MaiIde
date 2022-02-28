#pragma once

class IDE; // forward declaration
#include "Command.h"


class NewLineCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	NewLineCommand(IDE& ide);
	bool execute(sf::Event event) override;
};