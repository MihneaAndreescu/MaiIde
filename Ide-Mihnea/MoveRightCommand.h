#pragma once

class IDE; // forward declaration
#include "Command.h"


class MoveRightCommand : public Command {
private:
  IDE& ide;
  bool triggered(sf::Event event);
public:
  MoveRightCommand(IDE& ide);
  bool execute(sf::Event event);
};
