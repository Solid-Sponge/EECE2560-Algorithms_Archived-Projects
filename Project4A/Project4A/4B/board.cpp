#include "board.h"


board::board(int sqSize)
	: value(BoardSize + 1, BoardSize + 1)
	// Board constructor
{
}

void board::clear()
// Clear the entire board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			value[i][j] = 0;
			row[i][j] = true;
			col[i][j] = true;
			square[i][j] = true;
			//clearCell(i,j);
		}
	}
}

void board::setCell(int i, int j, ValueType val)
// set cell i,j to val and update conflicts
{
	value[i][j] = val;
	if (val != 0)
	{
		row[i][val] = false;
		col[j][val] = false;
		square[squareNumber(i, j)][val] = false;
	}

}

void board::clearCell(int i, int j)
// clears cell i,j and update conflicts
{
	ValueType oldval = value[i][j];
	value[i][j] = 0;
	row[i][oldval] = true;
	col[j][oldval] = true;
	square[squareNumber(i, j)][oldval] = true;
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
	char ch;
	recursiveCount = 0;
	SolvedStatus = false;
	clear();
	for (int i = 1; i <= BoardSize; i++)
		for (int j = 1; j <= BoardSize; j++)
		{
		fin >> ch;

		// If the read char is not Blank
		if (ch != '.')
		{
			setCell(i, j, ch - '0');   // Convert char to int
		}
		}
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	ostr << endl;
	return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
		return value[i][j];
	else
		throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
		throw rangeError("bad value in setCell");
	ValueType val = getCell(i, j);
	if (val != 0)
	{
		return false;
	}
	return true;

}

void board::print()
// Prints the current board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		if ((i - 1) % SquareSize == 0)
		{
			cout << " -";
			for (int j = 1; j <= BoardSize; j++)
				cout << "---";
			cout << "-";
			cout << endl;
		}
		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j - 1) % SquareSize == 0)
				cout << "|";
			if (!isBlank(i, j))
				cout << " " << getCell(i, j) << " ";
			else
				cout << "   ";
		}
		cout << "|";
		cout << endl;
	}

	cout << " -";
	for (int j = 1; j <= BoardSize; j++)
		cout << "---";
	cout << "-";
	cout << endl;
}

void board::printConflicts()
//Print all conflicts in Board
{
	for (int i = 1; i <= BoardSize; i++)
	{
		cout << "Row " << i << " Placed Elements: ";
		for (int j = 1; j <= BoardSize; j++)
		{
			if (!row[i][j])
				cout << j << " ";
		}
		cout << endl;
	}

	for (int i = 1; i <= BoardSize; i++)
	{
		cout << "Column " << i << " Placed Elements: ";
		for (int j = 1; j <= BoardSize; j++)
		{
			if (!col[i][j])
				cout << j << " ";
		}
		cout << endl;
	}

	for (int i = 1; i <= BoardSize; i++)
	{
		cout << "Square " << i << " Placed Elements: ";
		for (int j = 1; j <= BoardSize; j++)
		{
			if (!square[i][j])
				cout << j << " ";
		}
		cout << endl;
	}
}

bool board::checkConflict(int i, int j, ValueType val)
//Checks if val can be placed in i,j without creating a conflict
{
	if (row[i][val] == true && col[j][val] == true && square[squareNumber(i, j)][val] == true)
		return true;
	return false;
}

bool board::checkIfSolved()
//Checks if board is solved
{
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			if (value[i][j] == 0)
				return false;
			if (row[i][j] == true || col[i][j] == true || square[i][j] == true)
				return false;
		}
	}
	return true;
}

void board::findFirstBlank(int& i, int& j)
// Sets int i and int j equal to the position of the first blank found (in sequential order)
{
	ValueType testcell;
	for (int a = 1; a <= BoardSize; a++) 
	{

		for (int b = 1; b <= BoardSize; b++)
		{
			testcell = getCell(a, b);
			if (testcell == 0)
			{
				i = a;
				j = b;
				return;
			}
		}
	}
	i = 0;
	j = 0;
	return;
}

void board::findBestBlank(int& i, int& j)
//Improved version of findFirstBlank. Sets int i and int j equal to the position of the blank with the lowest score (first blank found is lowest score is tied)
//A position's score is determined by the amount of valid values that can be placed in that position.
//The smallest score is then picked as the Best "Blank", because that position has the smallest amount of valid values that can be placed, optimizing the backtrack search
{
	ValueType testcell;
	vector<int> xValue;
	vector<int> yValue;
	vector<int> Value;

	for (int a = 1; a <= BoardSize; a++)
	{

		for (int b = 1; b <= BoardSize; b++)
		{
			testcell = getCell(a, b);
			if (testcell == 0)
			{
				xValue.push_back(a);
				yValue.push_back(b);
				int score = 0;
				for (int z = 1; z <= BoardSize; z++)
				{
					if (row[a][z] == true)
						score++;
					if (col[b][z] == true)
						score++;
					if (square[squareNumber(a, b)][z] == true)
						score++;
				}
				Value.push_back(score);

			}
		}
	}
	int index = std::min_element(Value.begin(), Value.end()) - Value.begin();
	i = xValue[index];
	j = yValue[index];
}

void board::Solve()
//This version of Solve() solves a sudoku puzzle via backtracking search, using an object's parameter SolvedStatus to indicate when to stop the recursion
//findFirstBlank() is used in this version, which finds the first blank it sees.
{
	recursiveCount++;
	if (checkIfSolved())
	{
		print();
		SolvedStatus = true;
		return;
	}
	else
	{
		int i = 1;
		int j = 1;
		findFirstBlank(i, j);
		if (i == 0 || j == 0)
		{
		}
		else if (!SolvedStatus)
		{
			for (int a = 1; a <= 9; a++)
			{
				if (checkConflict(i, j, a))
				{
					setCell(i, j, a);
					Solve();
					if (SolvedStatus)
					{
						return;
					}
					else
					{
						clearCell(i, j);
					}
				}
			}
		}
	}
}

bool board::Solve2()
//This version of Solve() solves a sudoku puzzle via a more optimized version of backtracking search, returning true when the board is solved.
//findBestBlank() is used in this version, which finds the blank with the least amount of possible choices
{
	if (checkIfSolved())
	{
		print();
		SolvedStatus = true;
		return true;
	}
	else
	{
		int i = 0;
		int j = 0;
		findBestBlank(i, j);
		if (i == 0 || j == 0)
		{
			return false;
		}
		else if (!SolvedStatus)
		{
			for (int a = 1; a <= 9; a++)
			{
				if (checkConflict(i, j, a))
				{
					setCell(i, j, a);
					if (Solve2())
						return true;
					else
					{
						recursiveCount++;
						clearCell(i, j);
					}
				}
			}
		}
	}

	return false;
}