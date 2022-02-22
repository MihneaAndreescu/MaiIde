#pragma once
#include "PasteAction.h"
#include "IDE.h"
#include <cassert>
#include <string>

using namespace std;

PasteAction::PasteAction(IDE& state, vector<string> paste) :
	m_state(state),
	paste(paste) {

}
void PasteAction::doAction() {
	init_hash = m_state.getDebugHash();

	int row = m_state.getCurrentRowPosition();
	int col = m_state.getCurrentColPosition();

	init_row = row;
	init_col = col;

	if (paste.empty()) return;

	init = m_state.getRow(row);
	if ((int)paste.size() == 1) {
		m_state.insert(row, col, paste[0]);
		col += (int)paste[0].size();
	}
	else {
		string aftercol = "";
		for (int j = col; j < m_state.getRowSize(row); j++) {
			aftercol += m_state.getChar(row, j);
		}

		assert(m_state.getRowSize(row) - col >= 0);
		m_state.resizeRow(row, col);
		m_state.insert(row, col, paste[0]);

		for (int i = 1; i < (int)paste.size() - 1; i++) {
			m_state.insert(row + 1, paste[i]);
			row++;
		}
		row++;
		m_state.insert(row, paste.back() + aftercol);
		col = m_state.getRowSize(row);
	}
	mn = row - (int)paste.size() + 1;
	mx = row;
	m_state.setCurrentRowPosition(row);
	m_state.setCurrentColPosition(col);
}
void PasteAction::undoAction() {

	int row = m_state.getCurrentRowPosition();
	int col = m_state.getCurrentColPosition();

	assert(0 <= mn && mn <= mx && mx < m_state.getTotalNumberOfRows());

	m_state.eraseRows(mn, mx + 1);
	m_state.insert(mn, init);


	m_state.setCurrentRowPosition(init_row);
	m_state.setCurrentColPosition(init_col);

	long long hashnow = m_state.getDebugHash();
	assert(hashnow == init_hash);
}