// Declarations and functions for the Sudoku project

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <algorithm>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;





int squareNumber(int, int);

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print(); //Prints Board
	void printConflicts(); //Prints conflict in Board
	bool isBlank(int, int); //Checks if cell i,j is empty
	ValueType getCell(int, int); //Returns value of cell

	void setCell(int i, int j, ValueType val); //Sets cell i,j equal to val
	void clearCell(int i, int j); //Clear cell at i,j
	bool checkConflict(int, int, ValueType); //Checks if val placed at cell i,j creates a conflict
	bool checkIfSolved(); //Checks if board is solved

	void findFirstBlank(int& i, int& j);
	void findBestBlank(int& i, int& j);
	void Solve();
	bool Solve2();

	int recursiveCount = 0;
private:

	// The following matrices go from 1 to BoardSize in each
	// dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)

	matrix<ValueType> value;
	bool row[10][10]; //!< Conflict row array of arrays
	bool col[10][10]; //!< Conflict column array of arrays
	bool square[10][10]; //!< Conflict square array of arrays
	bool SolvedStatus = false;
};

#endif