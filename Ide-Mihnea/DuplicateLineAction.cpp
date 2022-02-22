#pragma once
#include "DuplicateLineAction.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;


DuplicateLineAction::DuplicateLineAction(IDE& state) :
	m_state(state) {

}
void DuplicateLineAction::doAction() {
	init_hash = m_state.getDebugHash();

	int row = m_state.getCurrentRowPosition();
	int col = m_state.getCurrentColPosition();

	m_state.insert(row + 1, m_state.getRow(row));
	row++;

	m_state.setCurrentRowPosition(row);
	m_state.setCurrentColPosition(col);
}
void DuplicateLineAction::undoAction() {
	int row = m_state.getCurrentRowPosition();
	int col = m_state.getCurrentColPosition();

	row--;
	m_state.erase(row + 1);

	m_state.setCurrentRowPosition(row);
	m_state.setCurrentColPosition(col);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}
