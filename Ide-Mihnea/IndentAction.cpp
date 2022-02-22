#pragma once
#include "IndentAction.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;



IndentAction::IndentAction(IDE& state) :
	m_state(state) {

}
void IndentAction::doAction() {
	init_hash = m_state.getDebugHash();

	init_row = m_state.getCurrentRowPosition();
	init_col = m_state.getCurrentColPosition();
	init_rows = m_state.getRows();

	m_state.indent();
}
void IndentAction::undoAction() {
	int row = m_state.getCurrentRowPosition();
	int col = m_state.getCurrentColPosition();

	m_state.setRows(init_rows);
	m_state.setCurrentRowPosition(init_row);
	m_state.setCurrentColPosition(init_col);
	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}
