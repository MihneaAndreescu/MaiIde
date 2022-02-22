#pragma once
class Action {
public:

  virtual void doAction() = 0;
  virtual void undoAction() = 0;
};
