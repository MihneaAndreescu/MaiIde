#pragma once
#include "UndoCommand.h"
#include "IDE.h"


bool UndoCommand::triggered(sf::Event event) {
	return event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
}
UndoCommand::UndoCommand(IDE& ide) : ide(ide) {

}

bool UndoCommand::execute(sf::Event event) {
	ide.undoAction();
	return true;
}



