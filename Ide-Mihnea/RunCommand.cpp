#pragma once
#include "RunCommand.h"
#include "IDE.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;



bool RunCommand::triggered(sf::Event event) {
	return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl));
}
RunCommand::RunCommand(IDE& ide) : ide(ide) {

}

bool RunCommand::execute(sf::Event event) {
	ofstream myfile;
	myfile.open("tet.cpp");
	vector<string> rows = ide.getRows();
	for (auto& row : rows) {
		myfile << row << "\n";
	}
	myfile.close();
	system("cls");
	int ret = system("g++ tet.cpp -o outputfile.exe");
	if (ret == 0) {
		system("outputfile.exe");
	}
	else {
		cout << "compilation error my friend\n";
	}
	return true;
}
