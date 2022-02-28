#pragma once
#include "TabCommand.h"
#include "TabifyAction.h"
#include "IDE.h"

using namespace std;

bool TabCommand::triggered(sf::Event event) {
	return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab);
}
TabCommand::TabCommand(IDE& ide) : ide(ide) {

}

bool TabCommand::execute(sf::Event event) {
	ide.doAction(make_unique<TabifyAction>(ide));
	return true;
}
