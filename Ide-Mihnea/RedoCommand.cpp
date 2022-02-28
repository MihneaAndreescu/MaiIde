#pragma once
#include "RedoCommand.h"
#include "IDE.h"

bool RedoCommand::triggered(sf::Event event) {
	return event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
}
RedoCommand::RedoCommand(IDE& ide) : ide(ide) {

}

bool RedoCommand::execute(sf::Event event) {
	ide.redo();
	return true;
}
