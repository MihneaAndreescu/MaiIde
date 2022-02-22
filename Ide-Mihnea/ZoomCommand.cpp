#pragma once
#include "ZoomCommand.h"
#include "IDE.h"

ZoomCommand::ZoomCommand(IDE& ide) : ide(ide) {}

bool ZoomCommand::triggered(sf::Event event) {
  return (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::MouseWheelMoved);
}

bool ZoomCommand::execute(sf::Event event) {
  ide.setScale(ide.getScale() * pow(ide.getScaleChangeFactor(), -event.mouseWheel.delta));
  return true;
}

