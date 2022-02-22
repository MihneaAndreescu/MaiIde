#pragma once
#include "CopyCommand.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;

bool CopyCommand::triggered(sf::Event event) {
	return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl));
}
CopyCommand::CopyCommand(IDE& ide) : ide(ide) {

}

bool CopyCommand::execute(sf::Event event) {
	vector<string> all = ide.getSelected();
	string s = "";

	for (auto& sub : all) {
		s += sub + "\n";
	}
	if (!s.empty()) {
		assert(s.back() == '\n');
		s.pop_back();
	}
	sf::Clipboard::setString(s);
	return true;
}
