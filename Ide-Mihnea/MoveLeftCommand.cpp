#pragma once
#include "MoveLeftCommand.h"
#include "MoveCaretLeftAction.h"
#include "IDE.h"


using namespace std;

bool MoveLeftCommand::triggered(sf::Event event) {
	return  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left);
}
MoveLeftCommand::MoveLeftCommand(IDE& ide) : ide(ide) {

}

bool MoveLeftCommand::execute(sf::Event event) {
	ide.doAction(make_unique<MoveCaretLeftAction>(ide));
	return true;
}