#pragma once
#include "InsertCharacterAction.h"
#include "IDE.h"
#include <cassert>

using namespace std;

InsertCharacterAction::InsertCharacterAction(IDE& state, char charToInsert) :
	m_state(state),
	m_charToInsert(charToInsert) {

}
void InsertCharacterAction::doAction() {
	init_hash = m_state.getDebugHash();

	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	m_state.insert(currentRowCaretPosition, currentColCaretPosition, m_charToInsert);
	currentColCaretPosition++;

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}

void InsertCharacterAction::undoAction() {
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	currentColCaretPosition--;
	m_state.eraseChar(currentRowCaretPosition, currentColCaretPosition);

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}

