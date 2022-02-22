#pragma once

class IDE; // forward declaration
#include "Command.h"
#include <vector>
#include <string>


class CopyCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	CopyCommand(IDE& ide);
	bool execute(sf::Event event) override;
};