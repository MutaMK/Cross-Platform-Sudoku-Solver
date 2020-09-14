#include "cMain.h"
int static_sudo[9][9];

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(100, btnSolveClicked)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr,wxID_ANY,"Main Page",wxPoint(30,30), wxSize(800,600))
{
	int x_shift = 20, y_shift = 20;
	btn_solve = new wxButton(this, 100, "Solve", wxPoint(100, 500), wxSize(300, 50));
	//test = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(50, 50));
	txt_grid = new wxTextCtrl * [9 * 9];
	
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (x<6 && x>2) x_shift += 3;
			else if (x >= 6) x_shift += 6;

			if (y>2 && y<6) y_shift += 3;
			else if (y >= 6) y_shift += 6;

			txt_grid[y * 9 + x] = new wxTextCtrl(this, 101 + (y * 9 + x), "", wxPoint(x_shift + 50 * x, y_shift + 50 * y), wxSize(50, 50));
			

			x_shift = 20;
			y_shift = 20;
		}
	}
}


cMain::~cMain()
{
	delete[]txt_grid;
}

void cMain::btnSolveClicked(wxCommandEvent &evt)
{
	int sudoku[9][9] = { 0 };

	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			sudoku[y][x] = wxAtoi(txt_grid[y * 9 + x]->GetValue());
			static_sudo[y][x] = sudoku[y][x];
		}
	}

	my_solve_sudoku(sudoku, highest_weight(sudoku));

	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			wxString mystring;
			mystring << sudoku[y][x];
			txt_grid[y * 9 + x]->Clear();
			txt_grid[y * 9 + x]->AppendText(mystring);
		}
	}
	evt.Skip(); //means event is done
}

int is_valid(int sudoku[9][9], int depth, int num)
{
	int col = depth % 9;
	if (col == 0) col = 9;
	int row = (depth + 9 - col) / 9;
	int position;

	for (int i = 0; i < 9; i++)
	{
		if (num == sudoku[row - 1][i]) return 0;
		if (num == sudoku[i][col - 1]) return 0;

	}

	row = (row - 1) / 3; //row as in 3x3 box
	col = (col - 1) / 3; //col as in 3x3 box
	position = ((row * 27) + 1) + (col * 3); //position of edge of 3x3

	col = position % 9;
	if (col == 0) col = 9;
	row = (position + 9 - col) / 9;

	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			if (num == sudoku[row + a - 1][col + b - 1]) return 0;
		}
	}

	return 1;
}

int my_solve_sudoku(int sudoku[9][9], int depth)
{
	if (depth == -1) return 1;

	int col = depth % 9;
	if (col == 0) col = 9;
	int row = (depth + 9 - col) / 9;


	for (int i = 1; i < 10; i++)
	{
		if (is_valid(sudoku, depth, i) == 1)
		{
			sudoku[row - 1][col - 1] = i;
			//print_sudoku(sudoku);
			if (my_solve_sudoku(sudoku, highest_weight(sudoku)) == 1) return 1;
			else
			{
				sudoku[row - 1][col - 1] = static_sudo[row - 1][col - 1];
			}
		}
	}
	return 0;
}

int get_weight(int sudoku[9][9], int row, int col)
{
	int weight = 0;
	if (sudoku[row + 1][col + 1] != 0) weight += 1;
	if (sudoku[row + 1][col - 1] != 0) weight += 1;
	if (sudoku[row - 1][col + 1] != 0) weight += 1;
	if (sudoku[row - 1][col - 1] != 0) weight += 1;

	for (int j = 0; j < 6; j++)
	{
		if (sudoku[row][j] != 0) weight += 1;
	}

	for (int j = 0; j < 9; j++)
	{
		if (sudoku[j][col] != 0) weight += 1;
	}
	return weight;
}

int highest_weight(int sudoku[9][9])
{
	int depth = 0;
	int max[2] = { -1,-1 };
	int current;

	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			depth += 1;
			if (sudoku[j][i] == 0)// row collum
			{
				current = get_weight(sudoku, j, i);
				if (current > max[0])
				{
					max[0] = current;
					max[1] = depth;
				}
			}
		}
	}
	return max[1];
}