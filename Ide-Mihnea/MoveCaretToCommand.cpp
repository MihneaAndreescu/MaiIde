#pragma once
#include "MoveCaretToCommand.h"
#include "MoveCaretToMouseAction.h"
#include "IDE.h"

using namespace std;

bool MoveCaretToCommand::triggered(sf::Event event) {
	return (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left);
}

MoveCaretToCommand::MoveCaretToCommand(IDE& ide) : ide(ide) {

}

bool MoveCaretToCommand::execute(sf::Event event) {
	ide.doAction(make_unique<MoveCaretToMouseAction>(ide));
	return true;
}