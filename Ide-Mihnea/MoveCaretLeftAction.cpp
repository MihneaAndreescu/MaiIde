#pragma once
#include "MoveCaretLeftAction.h"
#include "IDE.h"
#include <cassert>


MoveCaretLeftAction::MoveCaretLeftAction(IDE& state) :
	m_state(state) {

}
void MoveCaretLeftAction::doAction() {
	init_hash = m_state.getDebugHash();
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	init_row = currentRowCaretPosition;
	init_col = currentColCaretPosition;

	currentColCaretPosition--;
	if (currentColCaretPosition < 0) {
		if (currentRowCaretPosition == 0) {
			currentColCaretPosition++;
		}
		else {
			currentRowCaretPosition--;
			currentColCaretPosition = m_state.getRowSize(currentRowCaretPosition);
		}
	}

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}
void MoveCaretLeftAction::undoAction() {
	m_state.setCurrentRowPosition(init_row);
	m_state.setCurrentColPosition(init_col);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}
