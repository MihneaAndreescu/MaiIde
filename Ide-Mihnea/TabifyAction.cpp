#pragma once
#include "TabifyAction.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;

TabifyAction::TabifyAction(IDE& state) :
	m_state(state) {
}

void TabifyAction::doAction() {
	init_hash = m_state.getDebugHash();
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();
	int tabSize = m_state.getTabSize();

	shiftBy = tabSize - currentColCaretPosition % tabSize;

	m_state.insert(currentRowCaretPosition, currentColCaretPosition, string(shiftBy, ' '));
	currentColCaretPosition += shiftBy;

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}

void TabifyAction::undoAction() {
	int currentRowCaretPosition = m_state.getCurrentRowPosition();
	int currentColCaretPosition = m_state.getCurrentColPosition();

	currentColCaretPosition -= shiftBy;
	for (int iter = 1; iter <= shiftBy; iter++) {
		m_state.eraseChar(currentRowCaretPosition, currentColCaretPosition);
	}

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}