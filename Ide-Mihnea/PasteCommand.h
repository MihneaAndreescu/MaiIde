#pragma once

class IDE; // forward declaration
#include "Command.h"


class PasteCommand : public Command {
private:
	IDE& ide;
	bool triggered(sf::Event event) override;
public:
	PasteCommand(IDE& ide);
	bool execute(sf::Event event);

};