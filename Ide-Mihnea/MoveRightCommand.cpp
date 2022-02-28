#pragma once
#include "MoveRightCommand.h"
#include "MoveCaretRightAction.h"
#include "IDE.h"


using namespace std;

bool MoveRightCommand::triggered(sf::Event event) {
	return  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right);
}
MoveRightCommand::MoveRightCommand(IDE& ide) : ide(ide) {

}

bool MoveRightCommand::execute(sf::Event event) {
	ide.doAction(make_unique<MoveCaretRightAction>(ide));
	return true;
}