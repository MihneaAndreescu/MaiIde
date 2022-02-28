#pragma once
#include "NewLineCommand.h"
#include "NewLineAction.h"
#include "IDE.h"

using namespace std;

bool NewLineCommand::triggered(sf::Event event) {
	return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return);
}
NewLineCommand::NewLineCommand(IDE& ide) : ide(ide) {

}

bool NewLineCommand::execute(sf::Event event) {
	ide.doAction(make_unique<NewLineAction>(ide));
	return true;
}
