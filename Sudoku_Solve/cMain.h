#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxButton* btn_solve = nullptr;
	wxTextCtrl **txt_grid;

	void btnSolveClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

int my_solve_sudoku(int sudoku[9][9], int depth);
int is_valid(int sudoku[9][9], int depth, int num);
int get_weight(int sudoku[9][9], int row, int col);
int highest_weight(int sudoku[9][9]);