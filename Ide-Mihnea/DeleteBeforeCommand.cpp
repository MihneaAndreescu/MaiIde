#pragma once
#include "DeleteBeforeCommand.h"
#include "DeleteBeforeAction.h"
#include "IDE.h"

using namespace std;

bool DeleteBeforeCommand::triggered(sf::Event event) {
	return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace);
}
DeleteBeforeCommand::DeleteBeforeCommand(IDE& ide) : ide(ide) {

}

bool DeleteBeforeCommand::execute(sf::Event event) {
	ide.doAction(make_unique<DeleteBeforeAction>(ide));
	return true;
}
