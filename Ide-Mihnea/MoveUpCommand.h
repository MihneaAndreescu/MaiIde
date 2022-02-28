#pragma once

class IDE; // forward declaration
#include "Command.h"


class MoveUpCommand : public Command {
private:
  IDE& ide;
  bool triggered(sf::Event event);
public:
  MoveUpCommand(IDE& ide);
  bool execute(sf::Event event);
};
