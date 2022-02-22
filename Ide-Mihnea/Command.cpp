#pragma once
#include "Command.h"

bool Command::handleEvent(sf::Event event) {
  if (!triggered(event)) {
    return false;
  }
  return execute(event);
  // true = vreau sa nu se mai execute celelalte comenzi
  // false = nu e problema daca se mai executa celelalte comenzi
}
