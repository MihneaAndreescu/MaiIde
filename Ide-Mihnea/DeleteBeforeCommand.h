#pragma once

class IDE; // forward declaration
#include "Command.h"


class DeleteBeforeCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	DeleteBeforeCommand(IDE& ide);

	bool execute(sf::Event event) override;
};