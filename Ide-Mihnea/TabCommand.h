#pragma once

class IDE; // forward declaration
#include "Command.h"


class TabCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	TabCommand(IDE& ide);
	bool execute(sf::Event event) override;
};
