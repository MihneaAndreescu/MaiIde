#include "IDE.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <functional>
#include <random>
#include <chrono>
#include "InsertCharacterAction.h"
#include "TabifyAction.h"
#include "MoveCaretLeftAction.h"
#include "MoveCaretRightAction.h"
#include "MoveCaretUpAction.h"
#include "MoveCaretDownAction.h"
#include "NewLineAction.h"
#include "DeleteBeforeAction.h"
#include "MoveCaretToMouseAction.h"
#include "PasteAction.h"
#include "DuplicateLineAction.h"
#include "IndentAction.h"

#include "CopyCommand.h"
#include "ZoomCommand.h"
#include "PasteCommand.h"
#include "InsertCharacterCommand.h"
#include "RunCommand.h"
#include "IndentCommand.h"
#include "RunCommand.h"
#include "RedoCommand.h"
#include "DuplicateLineCommand.h"
#include "TabCommand.h"
#include "DeleteBeforeCommand.h"
#include "NewLineCommand.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "MoveCaretToCommand.h"
#include "UndoCommand.h"

using namespace std;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<> distrib256(0, 255);
uniform_real_distribution<> distrib01(0, 1);

void IDE::addToHash(long long x) {
	hash = 79623423432 * hash + x;
}

void IDE::fixCameraCenter() {
	sf::Vector2f coef = scale * sf::Vector2f(fontCharSize.x, fontCharSize.y);
	sf::Vector2f myPosition = sf::Vector2f(currentColCaretPosition * coef.x, currentRowCaretPosition * coef.y);
	sf::Vector2f maximal = sf::Vector2f((float)rows[currentRowCaretPosition].size() * coef.x, (float)rows.size() * coef.y);
	sf::Vector2f sz = sf::Vector2f(coef.x * 0.15, coef.y);

	cameraCenter = myPosition;
	if (maximal.y >= 1) {
		if (cameraCenter.y < 0.5) cameraCenter.y = 0.5;
		else {
			if (cameraCenter.y > maximal.y - 0.5) {
				cameraCenter.y = maximal.y - 0.5;
			}
		}
	}
	else {
		cameraCenter.y = 0.5;
	}

	if (maximal.x >= 1) {
		if (cameraCenter.x < 0.5) cameraCenter.x = 0.5;
		else {
			if (cameraCenter.x > maximal.x - 0.5) {
				cameraCenter.x = maximal.x - 0.5;
			}
		}
	}
	else {
		cameraCenter.x = 0.5;
	}

}

bool IDE::ends_here(int row, int col, string what) {
	for (int i = (int)what.size() - 1; i >= 0; i--) {
		if (col < 0) return false;
		if (rows[row][col] != what[i]) return false;
		col--;
	}
	return true;
}

void IDE::initCommands() {

	commands.push_back(make_unique<ZoomCommand>(*this));
	commands.push_back(make_unique<CopyCommand>(*this));
	commands.push_back(make_unique<PasteCommand>(*this));
	commands.push_back(make_unique<InsertCharacterCommand>(*this));
	commands.push_back(make_unique<RunCommand>(*this));
	commands.push_back(make_unique<IndentCommand>(*this));
	commands.push_back(make_unique<UndoCommand>(*this));
	commands.push_back(make_unique<RedoCommand>(*this));
	commands.push_back(make_unique<DuplicateLineCommand>(*this));
	commands.push_back(make_unique<TabCommand>(*this));
	commands.push_back(make_unique<DeleteBeforeCommand>(*this));
	commands.push_back(make_unique<NewLineCommand>(*this));
	commands.push_back(make_unique<MoveLeftCommand>(*this));
	commands.push_back(make_unique<MoveRightCommand>(*this));
	commands.push_back(make_unique<MoveUpCommand>(*this));
	commands.push_back(make_unique<MoveDownCommand>(*this));
	commands.push_back(make_unique<MoveCaretToCommand>(*this));
}

void IDE::indent() {
	vector<bool> skipped((int)rows.size(), false);
	for (int row = 0; row < (int)rows.size(); row++) {
		string nwrow;
		int p = 0;
		while (0 <= p && p < (int)rows[row].size() && rows[row][p] == ' ') {
			p++;
		}
		if (p + 4 < (int)rows[row].size() && rows[row][p] == '#') {
			skipped[row] = true;
			continue;
		}
		if (p + 4 < (int)rows[row].size() && rows[row][p + 0] == 'u' && rows[row][p + 1] == 's' && rows[row][p + 2] == 'i' && rows[row][p + 3] == 'n' && rows[row][p + 4] == 'g') {
			skipped[row] = true;
			continue;
		}
		bool differentfromspace = false;
		bool inside_string = false;
		for (int col = 0; col < (int)rows[row].size(); col++) {

			if (rows[row][col] == 34 || rows[row][col] == 39) {
				inside_string ^= 1;
			}
			if (inside_string) {
				nwrow += rows[row][col];
				continue;
			}

			if (rows[row][col] == ' ') {
				if (!ends_here(row, col - 1, "int") && !ends_here(row, col - 1, "long") && !ends_here(row, col - 1, "double") && !ends_here(row, col - 1, "float") && !ends_here(row, col - 1, ">")) {
					continue;
				}
			}
			nwrow += rows[row][col];
		}
		rows[row] = nwrow;
	}

	int delta_bracket = 0;



	for (int row = 0; row < (int)rows.size(); row++) {
		if (skipped[row]) {
			continue;
		}
		string nwrow;

		function<bool(char)> isop = [&](char ch) {
			if (ch == '<') return true;
			if (ch == '=') return true;
			if (ch == '>') return true;
			if (ch == '+') return true;
			if (ch == '-') return true;
			if (ch == '*') return true;
			if (ch == '/') return true;
			if (ch == '&') return true;
			if (ch == '|') return true;
			if (ch == '^') return true;
			if (ch == '!') return true;
			return false;
		};

		function<void()> request_space = [&]() {

			if (!nwrow.empty() && nwrow.back() == ' ') return;
			nwrow += " ";
		};

		bool differentfromspace = false;
		bool inside_string = false;

		if (!rows[row].empty()) {

			delta_bracket += (rows[row][0] == '{');
			delta_bracket -= (rows[row][0] == '}');
		}

		for (int j = 1; j <= delta_bracket * tabSize; j++) {
			nwrow += " ";
		}

		for (int col = 0; col < (int)rows[row].size(); col++) {

			if (col > 0) {
				delta_bracket += (rows[row][col] == '{');
				delta_bracket -= (rows[row][col] == '}');
			}
			if (rows[row][col] == 34 || rows[row][col] == 39) {
				inside_string ^= 1;
			}
			if (inside_string) {
				nwrow += rows[row][col];
				continue;
			}

			if (rows[row][col] == ' ') {
				nwrow += rows[row][col];
				continue;
			}

			if (isop(rows[row][col])) {
				if (col == 0) {
					request_space();
				}
				else {
					if (isop(rows[row][col - 1])) {}
					else {
						request_space();
					}
				}
			}
			if (rows[row][col] == '(') {
				if (ends_here(row, col - 1, "if") || ends_here(row, col - 1, "while") || ends_here(row, col - 1, "for")) {
					if (col == 0) {
						request_space();
					}
					else {
						if (rows[row][col - 1] == '>' || rows[row][col - 1] == '<' || rows[row][col - 1] == '=') {}
						else {
							request_space();
						}
					}
				}
			}
			if (rows[row][col] == '{') {
				if (col > 0 && rows[row][col - 1] == ')') {
					request_space();
				}
			}
			nwrow += rows[row][col];
			if (isop(rows[row][col]) || rows[row][col] == ',' || rows[row][col] == ';') {
				if (col == (int)rows[row].size() - 1) {
					request_space();
				}
				else {
					if (isop(rows[row][col + 1])) {}
					else {
						request_space();
					}
				}
			}
		}
		rows[row] = nwrow;
	}
}



vector<string> IDE::getSelected() {
	vector<string> sol;
	for (auto& h : selectedHighlighting) {
		sol.push_back(getSubstr(h.row, h.firstCol, h.lastCol - 1)); /////////////////////// 108
	}
	cout << " = " << (int)sol.size() << "\n";
	return sol;
}

float IDE::getScale() {
	return scale;
}

void IDE::setScale(float newScale) {
	scale = min(maxScale, max(minScale, newScale));
}

float IDE::getScaleChangeFactor() {
	return scaleChangeFactor;
}

void IDE::update() {
	fixCameraCenter();

	selectedHighlighting.clear();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i pos = getMouseEditorPosition();
		int r1 = pos.x, c1 = pos.y;
		int r2 = currentRowCaretPosition, c2 = currentColCaretPosition;
		if (r1 > r2) {
			swap(r1, r2);
			swap(c1, c2);
		}
		if (r1 == r2 && c1 > c2) {
			swap(r1, r2); // useless but cool!
			swap(c1, c2);
		}

		for (int i = r1; i <= r2; i++) {
			int st = 0, dr = (int)rows[i].size();
			if (i == r1) {
				st = c1;
			}
			if (i == r2) {
				dr = c2;
			}
			selectedHighlighting.push_back({ i, st, dr });
		}
	}
	constantHighlighting.clear();
	for (int r = 0; r < (int)rows.size(); r++) {
		for (int c = 0; c < (int)rows[r].size(); c++) {
			for (auto& s : keyWords) {
				if (c + (int)s.first.size() - 1 < (int)rows[r].size()) {
					bool match = true;
					for (int i = 0; i < (int)s.first.size(); i++) {
						match &= (s.first[i] == rows[r][c + i]);
					}
					if (match) {
						Highlighter h;
						h.row = r;
						h.firstCol = c;
						h.lastCol = c + (int)s.first.size() - 1;
						h.color = s.second;
						constantHighlighting.push_back(h);
					}
				}
			}
		}
	}
	sort(constantHighlighting.begin(), constantHighlighting.end());
}

sf::Vector2i IDE::getMouseEditorPosition() {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f position = sf::Vector2f(pixelPos.x, pixelPos.y);

	position.x /= resolution.x;
	position.y /= resolution.y;
	sf::Vector2f start = cameraCenter - sf::Vector2f(0.5, 0.5);
	position += start;

	sf::Vector2f coef = scale * sf::Vector2f(fontCharSize.x, fontCharSize.y);

	position.x /= coef.x;
	position.y /= coef.y;

	int r = position.y;
	int c = position.x;

	assert(!rows.empty());

	if (r < 0) r = 0;
	if (r >= (int)rows.size()) r = (int)rows.size() - 1;
	if (c < 0) c = 0;
	if (c >= (int)rows[r].size()) c = (int)rows[r].size();

	assert(0 <= r && r < (int)rows.size() && 0 <= c && c <= (int)rows[r].size());

	return sf::Vector2i(r, c);
}

long long IDE::getDebugHash() {
	hash = 0;
	addToHash(currentRowCaretPosition);
	addToHash(currentColCaretPosition);
	addToHash(rows.size());
	for (int i = 0; i < (int)rows.size(); i++) {
		addToHash(rows[i].size());
	}
	for (auto& s : rows) {
		for (auto& ch : s) {
			addToHash(ch);
		}
	}
	return hash;
}
int IDE::getTotalNumberOfRows() {
	return (int)rows.size();
}
vector<string> IDE::getRows() {
	return rows;
}
void IDE::setRows(vector<string> newRows) {
	rows = newRows;
}
string IDE::getRow(int currentRowCaretPosition) {
	return rows[currentRowCaretPosition];
}
int IDE::getRowSize(int currentRowCaretPosition) {
	return (int)rows[currentRowCaretPosition].size();
}
void IDE::doAction(unique_ptr<Action> action) {
	action->doAction();
	positionInTimeline++;
	actionTimeline.resize(positionInTimeline);
	actionTimeline.push_back(move(action));
}
void IDE::undoAction() {
	if (positionInTimeline >= 0) {
		actionTimeline[positionInTimeline]->undoAction();
		positionInTimeline--;
	}
}
void IDE::redo() {
	if (positionInTimeline + 1 < (int)actionTimeline.size()) {
		positionInTimeline++;
		actionTimeline[positionInTimeline]->doAction();
	}
}
int IDE::getTabSize() {
	return tabSize;
}
int IDE::getCurrentRowPosition() {
	return currentRowCaretPosition;
}
int IDE::getCurrentColPosition() {
	return currentColCaretPosition;
}
void IDE::setCurrentRowPosition(int newRow) {
	currentRowCaretPosition = newRow;
}
void IDE::setCurrentColPosition(int newCol) {
	currentColCaretPosition = newCol;
}
void IDE::resizeRow(int currentRowCaretPosition, int newSize) {
	rows[currentRowCaretPosition].resize(newSize);
}
void IDE::setRow(int currentRowCaretPosition, string newRowValue) {
	rows[currentRowCaretPosition] = newRowValue;
}
void IDE::insert(int currentRowCaretPosition, int currentColCaretPosition, string stringToInsert) {
	rows[currentRowCaretPosition].insert(rows[currentRowCaretPosition].begin() + currentColCaretPosition, stringToInsert.begin(), stringToInsert.end());
}
void IDE::insert(int currentRowCaretPosition, int currentColCaretPosition, char charToInsert) {
	rows[currentRowCaretPosition].insert(rows[currentRowCaretPosition].begin() + currentColCaretPosition, charToInsert);
}
void IDE::eraseChar(int currentRowCaretPosition, int currentColCaretPosition) {
	rows[currentRowCaretPosition].erase(rows[currentRowCaretPosition].begin() + currentColCaretPosition);
}
void IDE::insert(int currentRowCaretPosition, string newRow) {
	rows.insert(rows.begin() + currentRowCaretPosition, newRow);
}
void IDE::erase(int currentRowCaretPosition) {
	rows.erase(rows.begin() + currentRowCaretPosition);
}
void IDE::eraseRows(int r1, int r2) {
	rows.erase(rows.begin() + r1, rows.begin() + r2);
}
char IDE::getChar(int currentRowCaretPosition, int currentColCaretPosition) {
	return rows[currentRowCaretPosition][currentColCaretPosition];
}

IDE::IDE(sf::Window& window, sf::Vector2i resolution) :
	window(window),
	resolution(resolution),
	rows({ "" }),
	unhighlightedColor(sf::Color(255, 255, 255))
{
	initCommands();
	if (!font.loadFromFile("font.ttf")) {
		cout << "error\n";
		exit(0);
	}

	unhighlightedColor = sf::Color(distrib256(rng), distrib256(rng), distrib256(rng));
	highlightingBackgroundColor = sf::Color(distrib256(rng), distrib256(rng), distrib256(rng));

	vector<vector<string>> categories;

	categories.push_back({ "int", "long", "double", "float" });
	categories.push_back({ "if" });
	categories.push_back({ "for" });
	categories.push_back({ "do", "while" });
	categories.push_back({ "=" });
	categories.push_back({ ";" });
	categories.push_back({ "0" });
	categories.push_back({ "1" });
	categories.push_back({ "2" });
	categories.push_back({ "3" });
	categories.push_back({ "4" });
	categories.push_back({ "5" });
	categories.push_back({ "6" });
	categories.push_back({ "7" });
	categories.push_back({ "8" });
	categories.push_back({ "9" });

	categories.push_back({ "using", "namespace", "std" });
	categories.push_back({ "#include" });
	categories.push_back({ "<", ">" });
	categories.push_back({ "iostream" });
	categories.push_back({ "vector" });
	categories.push_back({ "random" });
	categories.push_back({ "chrono" });
	categories.push_back({ "set" });
	categories.push_back({ "map" });

	for (auto& category : categories) {
		sf::Color color = sf::Color(distrib256(rng), distrib256(rng), distrib256(rng));
		for (auto& keyWord : category) {
			keyWords[keyWord] = color;
		}
	}
}

string IDE::getSubstr(int r, int c1, int c2) const {
	if (c1 > c2) {
		return "";
	}
	else {
		assert(0 <= c1 && c1 <= c2 && c2 < (int)rows[r].size());
		return rows[r].substr(c1, c2 - c1 + 1);
	}
}

void IDE::highlightBackground(sf::RenderTarget& renderTarget, sf::Color color, int r, int c1, int c2) const {

	if (c1 >= c2) return;


	sf::Vector2f coef = scale * sf::Vector2f(fontCharSize.x, fontCharSize.y);


	sf::Vector2f p1 = sf::Vector2f(c1 * coef.x, r * coef.y);
	sf::Vector2f p2 = sf::Vector2f(c2 * coef.x, r * coef.y);

	sf::RectangleShape shp;
	shp.setFillColor(color);
	shp.setPosition(p1);
	shp.setSize(sf::Vector2f(p2.x - p1.x, coef.y));
	renderTarget.draw(shp);
}


void IDE::drawConstantColorString(int r, int c1, int c2, sf::Color color, sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
	if (c1 > c2) {
		return;
	}
	string s = getSubstr(r, c1, c2);
	sf::Vector2f coef = scale * sf::Vector2f(fontCharSize.x, fontCharSize.y);
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(240);
	text.setFillColor(color);
	text.setScale(sf::Vector2f(1, 1) * scale);
	text.setPosition(sf::Vector2f(coef.x * c1, coef.y * r));
	text.setString(getSubstr(r, c1, c2));
	renderTarget.draw(text);
}
void IDE::drawText(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
	string allLines;

	for (auto& h : selectedHighlighting) {
		highlightBackground(renderTarget, highlightingBackgroundColor, h.row, h.firstCol, h.lastCol);
	}

	int r = 0, c = 0;
	for (auto& h : constantHighlighting) {

		while (r < h.row) {
			drawConstantColorString(r, c, (int)rows[r].size() - 1, unhighlightedColor, renderTarget, renderStates);

			r++;
			c = 0;
		}
		assert(r == h.row);
		assert(c <= h.firstCol);
		drawConstantColorString(r, c, h.firstCol - 1, unhighlightedColor, renderTarget, renderStates);
		drawConstantColorString(r, h.firstCol, h.lastCol, h.color, renderTarget, renderStates);
		c = h.lastCol + 1;
	}
	while (r < (int)rows.size()) {
		drawConstantColorString(r, c, (int)rows[r].size() - 1, unhighlightedColor, renderTarget, renderStates);
		r++;
		c = 0;
	}

}
void IDE::drawCaret(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
	sf::RectangleShape caret;
	caret.setFillColor(sf::Color(0, 255, 0, 255));

	sf::Vector2f coef = scale * sf::Vector2f(fontCharSize.x, fontCharSize.y);
	sf::Vector2f myPosition = sf::Vector2f(currentColCaretPosition * coef.x, currentRowCaretPosition * coef.y);
	sf::Vector2f sz = sf::Vector2f(coef.x * 0.15, coef.y);

	caret.setPosition(myPosition);
	caret.setSize(sz);
	renderTarget.draw(caret);
}

void IDE::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
	sf::View camera;
	camera.setCenter(cameraCenter);
	camera.setSize(sf::Vector2f(1, 1));
	renderTarget.setView(camera);
	drawText(renderTarget, renderStates);
	drawCaret(renderTarget, renderStates);
};



void IDE::handleEvent(sf::Event event) {

	for (auto& command : commands) {
		if (command->handleEvent(event)) {
			break;
		}
	}
}