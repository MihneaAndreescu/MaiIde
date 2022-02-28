#pragma once
#include "PasteCommand.h"
#include "PasteAction.h"
#include "IDE.h"
#include <string>
#include <vector>

using namespace std;


bool PasteCommand::triggered(sf::Event event) {
	return event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
}
PasteCommand::PasteCommand(IDE& ide) : ide(ide) {

}

bool PasteCommand::execute(sf::Event event) {
	string s = sf::Clipboard::getString();
	vector<string> paste;
	for (auto& ch : s) {
		if (ch == '\n') {
			paste.push_back("");
			continue;
		}
		if (paste.empty()) paste.push_back("");
		paste.back() += ch;
	}
	ide.doAction(make_unique<PasteAction>(ide, paste));
	return true;
}
