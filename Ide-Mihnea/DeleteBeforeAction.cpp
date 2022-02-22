#pragma once
#include "DeleteBeforeAction.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;

DeleteBeforeAction::DeleteBeforeAction(IDE& state) :
	m_state(state) {
}

void DeleteBeforeAction::doAction() {
	init_hash = m_state.getDebugHash();
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();
	init_row = currentRowCaretPosition;
	init_col = currentColCaretPosition;
	if (currentColCaretPosition == 0) {
		if (currentRowCaretPosition > 0) {
			iftype = 1;
			currentColCaretPosition = m_state.getRowSize(currentRowCaretPosition - 1);
			sizeOfRow = m_state.getRowSize(currentRowCaretPosition);
			string Joint = m_state.getRow(currentRowCaretPosition - 1) + m_state.getRow(currentRowCaretPosition);
			m_state.setRow(currentRowCaretPosition - 1, Joint);

			m_state.erase(currentRowCaretPosition);
			currentRowCaretPosition--;
		}
	}
	else {
		iftype = 2;
		currentColCaretPosition--;
		deletedChar = m_state.getChar(currentRowCaretPosition, currentColCaretPosition);

		m_state.eraseChar(currentRowCaretPosition, currentColCaretPosition);
	}

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}
void DeleteBeforeAction::undoAction() {
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();
	if (iftype == 1) {
		currentRowCaretPosition++;
		int sz = sizeOfRow;
		string thestr;

		for (int i = m_state.getRowSize(currentRowCaretPosition - 1) - sz; i < m_state.getRowSize(currentRowCaretPosition - 1); i++) {
			thestr += m_state.getChar(currentRowCaretPosition - 1, i);
		}

		m_state.insert(currentRowCaretPosition, thestr);
		m_state.resizeRow(currentRowCaretPosition - 1, m_state.getRowSize(currentRowCaretPosition - 1) - sz);

		currentColCaretPosition = m_state.getRowSize(currentRowCaretPosition - 1);
	}
	if (iftype == 2) {
		m_state.insert(currentRowCaretPosition, currentColCaretPosition, deletedChar);
		currentColCaretPosition++;
	}
	m_state.setCurrentRowPosition(init_row);
	m_state.setCurrentColPosition(init_col);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}