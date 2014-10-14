#include "Solver.h"
using namespace std;

Solver::Solver(Sudoku* s)
{
	sudoku = s;
	vector<int> domain;
	vector<vector<int>> tempCols;
	for (int i=1; i<10; i++)
		domain.push_back(i);
	for (int j=0; j<9; j++)
		tempCols.push_back(domain);
	for (int k=0; k<9; k++)
		possibleValues.push_back(tempCols);
}

void Solver::solve()
{
	for (int i=1; i<10; i++)
		constrainRowDomains(i);
	for (int i=1; i<10; i++)
		constrainColumnDomains(i);

	guess();
	
	while (!solved()) {
		cout << "NOT SOLVED" << endl;
	}
	cout << "SOLVED" << endl;
}

bool Solver::solved()
{
	int count = 0;
	for (int i=1; i<10; i++) {
		if (sudoku->isColFull(i))
			count++;
	}
	if (count == 9)
		return true;
	return false;
}

void Solver::constrainRowDomains(int row)
{
	for (int i=0; i<9; i++) {
		int temp = sudoku->getGrid()[row][i+1];
		if (sudoku->getGrid()[row][i+1] != 0) {
			for (auto j=possibleValues[row-1][i].begin(); j<possibleValues[row-1][i].end(); j++) {
				if (*j == sudoku->getGrid()[row][i+1]) {
					possibleValues[row-1][i].erase(j);
					break;
				}
			}
		}
	}
}

void Solver::constrainColumnDomains(int col)
{
	for (int i=0; i<9; i++) {
		if (sudoku->getGrid()[i+1][col] != 0) {
			for (int j=0; j<possibleValues[i][col-1].size(); j++) {
				if (possibleValues[i][col-1][j] == sudoku->getGrid()[i+1][col]) {
					swap(possibleValues[i][col-1][j],possibleValues[i][col-1][possibleValues[i][col-1].size()-1]);
					possibleValues[i][col-1].pop_back();
					break;
				}
			}
		}
	}
}

void Solver::constrainLocalBlock(int row, int col)
{
	//int sq = sudoku->getSqNumber(row,col);
	//vector<vector<int>>squares = sudoku->getSquares();
	//for (int i=0; i<18; i+=2) {
	//	for (int j=0; j<3; j++) {
	//		if (sudoku->getGrid[squares[sq][i]][squares[sq][i+1]] == possibleValues[i])
	//	}
	//}
}