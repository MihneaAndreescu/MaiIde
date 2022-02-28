#pragma once

class IDE; // forward declaration
#include "Command.h"


class DuplicateLineCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	DuplicateLineCommand(IDE& ide);
	bool execute(sf::Event event) override;
};