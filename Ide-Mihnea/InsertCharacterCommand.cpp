#pragma once
#include "InsertCharacterCommand.h"
#include "InsertCharacterAction.h"
#include "IDE.h"

using namespace std;

bool InsertCharacterCommand::triggered(sf::Event event) {
	return (event.type == sf::Event::TextEntered && isprint(event.text.unicode));
}
InsertCharacterCommand::InsertCharacterCommand(IDE& ide) : ide(ide) {

}

bool InsertCharacterCommand::execute(sf::Event event) {
	char charToInsert = event.text.unicode;
	ide.doAction(make_unique<InsertCharacterAction>(ide, charToInsert));
	return true;
}
