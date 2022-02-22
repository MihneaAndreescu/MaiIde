#pragma once
#include "MoveCaretRightAction.h"
#include "IDE.h"
#include <cassert>



MoveCaretRightAction::MoveCaretRightAction(IDE& state) :
	m_state(state) {

}
void MoveCaretRightAction::doAction() {
	init_hash = m_state.getDebugHash();
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	init_row = currentRowCaretPosition;
	init_col = currentColCaretPosition;

	currentColCaretPosition++;
	if (currentColCaretPosition == m_state.getRowSize(currentRowCaretPosition) + 1) {
		if (currentRowCaretPosition + 1 == m_state.getTotalNumberOfRows()) {
			currentColCaretPosition--;
		}
		else {
			currentRowCaretPosition++;
			currentColCaretPosition = 0;
		}
	}


	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}
void MoveCaretRightAction::undoAction() {

	m_state.setCurrentRowPosition(init_row);
	m_state.setCurrentColPosition(init_col);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}