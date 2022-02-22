#pragma once

#include <SFML/Window.hpp>

class Command {
private:
  virtual bool triggered(sf::Event event) = 0;
public:
  virtual bool execute(sf::Event event) = 0;
  bool handleEvent(sf::Event event);
};