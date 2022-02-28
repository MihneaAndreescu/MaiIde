#pragma once

class IDE; // forward declaration
#include "Command.h"


class MoveLeftCommand : public Command {
private:
  IDE& ide;
  bool triggered(sf::Event event);
public:
  MoveLeftCommand(IDE& ide);
  bool execute(sf::Event event);
};
