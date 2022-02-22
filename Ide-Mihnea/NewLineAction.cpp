#pragma once
#include "NewLineAction.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;


NewLineAction::NewLineAction(IDE& state) :
	m_state(state) {

}
void NewLineAction::doAction() {
	init_hash = m_state.getDebugHash();
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	init_col = currentColCaretPosition;

	string after = "";

	for (int i = currentColCaretPosition; i < m_state.getRowSize(currentRowCaretPosition); i++) {
		after += m_state.getChar(currentRowCaretPosition, i);
	}
	m_state.resizeRow(currentRowCaretPosition, currentColCaretPosition);
	m_state.insert(currentRowCaretPosition + 1, after);
	currentColCaretPosition = 0;
	currentRowCaretPosition++;

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}
void NewLineAction::undoAction() {
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	currentRowCaretPosition--;
	currentColCaretPosition = init_col;
	string after = m_state.getRow(currentRowCaretPosition + 1);
	m_state.erase(currentRowCaretPosition + 1);
	m_state.setRow(currentRowCaretPosition, m_state.getRow(currentRowCaretPosition) + after);


	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}
