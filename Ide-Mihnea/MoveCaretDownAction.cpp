#pragma once
#include "MoveCaretDownAction.h"
#include "IDE.h"
#include <cassert>
#include <algorithm>

using namespace std;


MoveCaretDownAction::MoveCaretDownAction(IDE& state) :
	m_state(state) {

}
void MoveCaretDownAction::doAction() {
	init_hash = m_state.getDebugHash();
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	init_row = currentRowCaretPosition;
	init_col = currentColCaretPosition;

	currentRowCaretPosition++;
	if (currentRowCaretPosition == (int)m_state.getTotalNumberOfRows()) {
		currentRowCaretPosition--;
	}
	else {
		currentColCaretPosition = min(currentColCaretPosition, m_state.getRowSize(currentRowCaretPosition));
	}

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}
void MoveCaretDownAction::undoAction() {

	m_state.setCurrentRowPosition(init_row);
	m_state.setCurrentColPosition(init_col);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}
