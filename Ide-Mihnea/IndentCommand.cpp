#pragma once
#include "IndentCommand.h"
#include "IndentAction.h"
#include "IDE.h"

using namespace std;
bool IndentCommand::triggered(sf::Event event) {
	return event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
}
IndentCommand::IndentCommand(IDE& ide) : ide(ide) {

}

bool IndentCommand::execute(sf::Event event) {
	ide.doAction(make_unique<IndentAction>(ide));
	return true;
}