#pragma once
#include "MoveDownCommand.h"
#include "MoveCaretDownAction.h"
#include "IDE.h"


using namespace std;

bool MoveDownCommand::triggered(sf::Event event) {
	return  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down);
}
MoveDownCommand::MoveDownCommand(IDE& ide) : ide(ide) {

}

bool MoveDownCommand::execute(sf::Event event) {
	ide.doAction(make_unique<MoveCaretDownAction>(ide));
	return true;
}