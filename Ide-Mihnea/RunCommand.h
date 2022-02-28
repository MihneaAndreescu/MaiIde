#pragma once

class IDE; // forward declaration
#include "Command.h"


class RunCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	RunCommand(IDE& ide);

	bool execute(sf::Event event) override;
};