#pragma once

class IDE; // forward declaration
#include "Command.h"


class MoveDownCommand : public Command {
private:
  IDE& ide;
  bool triggered(sf::Event event);
public:
  MoveDownCommand(IDE& ide);
  bool execute(sf::Event event);
};
