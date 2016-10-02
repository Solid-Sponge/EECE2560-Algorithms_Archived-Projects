/**
* \class grid
*
*
* \brief Stores a word grid in a matrix
*
* \author $Author: Michael Rossi
*
* \version $Revision: 1.0 $
*
* \date $Date: 2015/10/13 23:16:20 $
*
* Contact: rossisantomauro.m@husky.neu.edu
*
*/

#include "grid.h"

grid::grid()
{
	std::ifstream readfile;
	char temp;
	readfile.open(FILENAME); //!< Reads FILENAME in grid.h
	if (readfile.is_open())
	{
		int rows, cols;
		readfile >> rows;
		readfile >> cols;
		charMatrix.resize(rows, cols);
		for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					readfile >> temp;
					charMatrix[i][j] = temp;
					//std::cout << temp << " ";
				}
				//std::cout << std::endl;
			}
	}
}

matrix<char>& grid::getMatrix()
{
	return charMatrix;
}

int grid::getSize()
{
	return charMatrix.rows();
}