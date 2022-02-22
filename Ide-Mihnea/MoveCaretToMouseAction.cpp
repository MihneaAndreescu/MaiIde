#pragma once
#include "MoveCaretToMouseAction.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;

MoveCaretToMouseAction::MoveCaretToMouseAction(IDE& state) :
	m_state(state) {

}
void MoveCaretToMouseAction::doAction() {
	init_hash = m_state.getDebugHash();
	int currentRowCaretPosition, currentColCaretPosition;
	init_row = m_state.getCurrentRowPosition();
	init_col = m_state.getCurrentColPosition();

	sf::Vector2i g = m_state.getMouseEditorPosition();
	currentRowCaretPosition = g.x;
	currentColCaretPosition = g.y;

	m_state.setCurrentRowPosition(currentRowCaretPosition);
	m_state.setCurrentColPosition(currentColCaretPosition);
}
void MoveCaretToMouseAction::undoAction() {

	m_state.setCurrentRowPosition(init_row);
	m_state.setCurrentColPosition(init_col);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}