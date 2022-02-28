#pragma once
#include "DuplicateLineCommand.h"
#include "DuplicateLineAction.h"
#include "IDE.h"

using namespace std;

bool DuplicateLineCommand::triggered(sf::Event event) {
	return event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
}
DuplicateLineCommand::DuplicateLineCommand(IDE& ide) : ide(ide) {

}

bool DuplicateLineCommand::execute(sf::Event event) {
	ide.doAction(make_unique<DuplicateLineAction>(ide));
	return true;
}
