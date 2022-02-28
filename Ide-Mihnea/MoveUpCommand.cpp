#pragma once
#include "MoveUpCommand.h"
#include "MoveCaretUpAction.h"
#include "IDE.h"


using namespace std;

bool MoveUpCommand::triggered(sf::Event event) {
	return  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up);
}
MoveUpCommand::MoveUpCommand(IDE& ide) : ide(ide) {

}

bool MoveUpCommand::execute(sf::Event event) {
	ide.doAction(make_unique<MoveCaretUpAction>(ide));
	return true;
}