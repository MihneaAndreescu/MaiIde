#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "Command.h"
#include "Action.h"

class IDE : public sf::Drawable {
private:
  struct Highlighter {
    int row, firstCol, lastCol;
    sf::Color color;
    bool operator < (Highlighter other) {
      if (row != other.row) {
        return row < other.row;
      }
      else {
        return firstCol < other.firstCol;
      }
    }
  };

  sf::Color unhighlightedColor;
  std::map<std::string, sf::Color> keyWords;

  sf::Vector2i resolution;
  const sf::Vector2f fontCharSize = sf::Vector2f(160, 288);
  std::vector<std::string> rows;
  int currentRowCaretPosition = 0;
  int currentColCaretPosition = 0;
  sf::Window& window;
  sf::Font font;

  int tabSize = 4;


  float scale = 0.0001;

  float minScale = 0.00007;
  float maxScale = 0.001;

  sf::Color highlightingBackgroundColor = sf::Color(61, 202, 74);
  std::vector<Highlighter> selectedHighlighting;

  float scaleChangeFactor = 0.9;

  std::vector<std::unique_ptr<Action>> actionTimeline;
  int positionInTimeline = -1;
  sf::Vector2f cameraCenter;

  long long hash;

  void addToHash(long long x);


  void fixCameraCenter();

  std::vector<Highlighter> constantHighlighting;

  bool ends_here(int row, int col, std::string what);
  
  std::vector<std::unique_ptr<Command>> commands;

  void initCommands();

public:


  void indent();

  std::vector<std::string> getSelected();

  float getScale();

  void setScale(float newScale);

  float getScaleChangeFactor();

  void update();

  sf::Vector2i getMouseEditorPosition();
 

  long long getDebugHash();

  int getTotalNumberOfRows();

  std::vector<std::string> getRows();

  void setRows(std::vector<std::string> newRows);

  std::string getRow(int currentRowCaretPosition);

  int getRowSize(int currentRowCaretPosition);

  void doAction(std::unique_ptr<Action> action);
  void undoAction();
  void redo();

  int getTabSize();

  int getCurrentRowPosition();

  int getCurrentColPosition();

  void setCurrentRowPosition(int newRow);

  void setCurrentColPosition(int newCol);

  void resizeRow(int currentRowCaretPosition, int newSize);

  void setRow(int currentRowCaretPosition, std::string newRowValue);

  void insert(int currentRowCaretPosition, int currentColCaretPosition, std::string stringToInsert);

  void insert(int currentRowCaretPosition, int currentColCaretPosition, char charToInsert);

  void eraseChar(int currentRowCaretPosition, int currentColCaretPosition);

  void insert(int currentRowCaretPosition, std::string newRow);

  void erase(int currentRowCaretPosition);

  void eraseRows(int r1, int r2);

  char getChar(int currentRowCaretPosition, int currentColCaretPosition);

  IDE(sf::Window& window, sf::Vector2i resolution);

  void handleEvent(sf::Event event);


private:
  std::string getSubstr(int r, int c1, int c2) const;


  void highlightBackground(sf::RenderTarget& renderTarget, sf::Color color, int r, int c1, int c2) const;


  void drawConstantColorString(int r, int c1, int c2, sf::Color color, sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;

  void drawText(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;

  void drawCaret(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;

public:
  void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;

};
