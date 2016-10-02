// Declarations and functions for the Sudoku project

#include "board.h"


int numSolutions = 0;

int main()
{
	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "sudoku.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b1(SquareSize);
		ValueType val = 9;
		long nCount = 0;
		int n = 1;
		while (fin && fin.peek() != 'Z')
		{
			b1.initialize(fin);
			b1.print();
			//b1.printConflicts();
			b1.Solve2();
			cout << b1.recursiveCount << " Attempts Taken" << endl;
			nCount += b1.recursiveCount;
			n++;
			if (b1.checkIfSolved())
				cout << "Board Solved" << endl;
			else
				cout << "Board Not Solved" << endl;


		}
		cout << endl << endl << nCount / n << " Average Attempts";
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}
