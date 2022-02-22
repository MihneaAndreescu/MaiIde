#pragma once

class IDE; // forward declaration
#include "Command.h"


class ZoomCommand : public Command { 
private:
  IDE& ide;
  bool triggered(sf::Event event);
public:
  ZoomCommand(IDE& ide);
  bool execute(sf::Event event);
};
