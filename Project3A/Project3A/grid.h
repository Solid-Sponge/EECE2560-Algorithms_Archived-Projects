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

#ifndef GRID_H
#define GRID_H
#define FILENAME "Puzzle1_size10" //!< Filename to load

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "d_matrix.h"

class grid{
	public:
		//! Default grid constructor. Loads FILENAME into matrix charMatri
		grid();

		//! Returns charMatrix
		/*!
		* \return matrix<char>& charMatrix
		*/
		matrix<char>& getMatrix();

		//! Returns N in matrix of size NxN
		/*!
		* \return int dimension of matrix
		*/
		int getSize();
	private:
		matrix<char> charMatrix; //!< Matrix of Word Grid
};

#endif // !WORDLIST_H