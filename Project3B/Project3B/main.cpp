/**
* @file Project #3a
* @author  Michael Rossi <rossisantomauro.m@husky.neu.edu>
* @version 1.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details at
* https://www.gnu.org/copyleft/gpl.html
*
*/

#include "wordlist.h"
#include "grid.h" //!< GRID FILENAME TO LOAD IS A MACRO IN GRID.H. EDIT GRID.H TO CHANGE FILE LOCATION
#include "Index.h"
#include "time.h"
#include <exception>
#include <stdexcept>
#include <cstdlib>

//! Given a SORTED wordlist and a grid of chars, finds all possible words
/*!
* \param wordlist& SORTED wordlist passed
* \param grid& grid of chars passed
*/
void findMatches(wordlist&, grid&);

//! Instantiates a wordlist object and grid object and returns words found in grid.
//! Sorting algorithm used depends on passed integer parameter
/*!
* \param int Sorting algorithm used. 0 = InsertionSort (30 min)  1 = QuickSort (2.418 sec)  2 = MergeSort (10.362 sec)
*/
void search(int);

int main()
{
	try{
		search(1);
	}
	catch (std::invalid_argument &s)
	{
		std::cout << "INVALID VALUE: searchType must be equal to 0,1,or 2" << std::endl;
		exit(0);
	}
}

void findMatches(wordlist& dictionary, grid& file)
{
	int size = file.getSize();
	matrix<char>* charMatrix = &(file.getMatrix());

	if (charMatrix->rows() != charMatrix->cols())
	{
		throw std::invalid_argument("INVALID VALUE: Matrix dimensions not equal to each other");
	}

	std::vector<std::string> WordsFound;
	std::string testWord[8] = {"","","","","","","",""}; //!< Vector of strings, each containing a test word facing each cardinal direction
	index a(size);
	index b(size);

	for (int i = 0; i < size; i++) //!< Goes through each column of the array
	{
		for (int j = 0; j < size; j++) //!< Goes throw each row of the array
		{
			a.setnum(i); //!< Sets index objects equal to current index
			b.setnum(j); //!< Sets index objects equal to current index
			for (int k = 0; k < size || k < 12; k++) //!< Goes through each possible combination of words in a line until either the dimension of the matrix is reached or k > 12
			{										 //!< as there are very few words in the english alphabet that are greater than 11 words, this speeds up the algorithm
				int x = 0; //!< Each while loop from here on out will check each cardinal direction for a word, for instance, if f o o d, was part of the sequence facing east
						   //!<	it would first try f, then fo, then foo, then food. It keeps going up until k is reached, so the word size is capped by either the dimension or by 11.
			
				while (x <= k) //NORTH
				{
					testWord[0] = testWord[0] + (*charMatrix)[a.getnum()][b.getnum()]; //!< Adds each attempt into a testing vector of strings. NORTH corresponds to 0, NORTHEAST to 1, etc
					x++;
					++a; //!< Increments only a. The index will move upwards
					//--b;
				}

				x = 0; //!< Reset x back to 0
				a.setnum(i); //!< Reset indices back to original position (i, j)
				b.setnum(j);
				while (x <= k) //NORTHEAST
				{
					testWord[1] = testWord[1] + (*charMatrix)[a.getnum()][b.getnum()];
					x++;
					++a; //! Increments a and b. The index will move upright
					++b;
				}

				x = 0;
				a.setnum(i);
				b.setnum(j);
				while (x <= k) //EAST
				{
					testWord[2] = testWord[2] + (*charMatrix)[a.getnum()][b.getnum()];
					x++;
					++b; //! Increments only b. The index will move right
				}

				x = 0;
				a.setnum(i);
				b.setnum(j);
				while (x <= k) //SOUTHEAST
				{
					testWord[3] = testWord[3] + (*charMatrix)[a.getnum()][b.getnum()];
					x++;
					--a; //!< Decrements a, increments b. The index will move down right
					++b;
				}

				x = 0;
				a.setnum(i);
				b.setnum(j);
				while (x <= k) //SOUTH
				{
					testWord[4] = testWord[4] + (*charMatrix)[a.getnum()][b.getnum()];
					x++;
					--a; //!< Decrements only a. The index will move down
				}

				x = 0;
				a.setnum(i);
				b.setnum(j);
				while (x <= k) //SOUTHWEST
				{
					testWord[5] = testWord[5] + (*charMatrix)[a.getnum()][b.getnum()];
					x++;
					--a; //!< Decrements a and b. The index will move downleft
					--b;
				}

				x = 0;
				a.setnum(i);
				b.setnum(j);
				while (x <= k) //WEST
				{
					testWord[6] = testWord[6] + (*charMatrix)[a.getnum()][b.getnum()];
					x++;
					--b; //!< Decrements only b. The index will move left
				}

				x = 0;
				a.setnum(i);
				b.setnum(j);
				while (x <= k) //NORTHWEST
				{
					testWord[7] = testWord[7] + (*charMatrix)[a.getnum()][b.getnum()];
					x++;
					++a; //!< Increments a, decrements b. The index will move upleft
					--b;
				}

				if (x >= 4) //!Checks if test words are greater than 4 letters
				{

					for (int direction = 0; direction < 8; direction++) //!< Tests each element in the test vector of strings against the dictionary via Binary search.
					{

						if (dictionary.BinarySearch(dictionary.returnList(), testWord[direction], 0, dictionary.returnSizeOfWords() - 1) != -1 && testWord[direction].length() > 4)
						{
							WordsFound.push_back(testWord[direction]); //!< If word found, pushes it onto WordsFound vector
						}
						testWord[direction] = ""; //!< Resets test vector of strings
					}
				}
				a.setnum(i); //!< Resets position
				b.setnum(j); //!< Resets position
			}

		}
	}
	for (int i = 0; i < WordsFound.size(); i++)
	{
		std::cout << WordsFound[i] << std::endl; //!< Prints out each element in WordsFound
	}
}

void search(int searchType)
{
	if (searchType != 0 && searchType != 1 && searchType != 2)
	{
		throw std::invalid_argument("INVALID VALUE: searchType must be equal to 0,1,or 2");
	}
	
	wordlist dictionary;
	std::vector<std::string>* list = &dictionary.returnList();
	clock_t startTime, endTime;
	grid file;
	double sorttime;
	double searchtime;

	switch (searchType)
	{
	case 0: //!< Insertion Sort
		startTime = clock();
		dictionary.InsertionSort();
		sorttime = double(clock() - startTime) / CLOCKS_PER_SEC;
		std::cout << "INSERTION SORT: " <<  sorttime << " Seconds" << std::endl;
		break;
	case 1: //!< Quick Sort
		startTime = clock();
		dictionary.QuickSort(0, dictionary.returnSizeOfWords() - 1);
		sorttime = double(clock() - startTime) / CLOCKS_PER_SEC;
		std::cout << "QUICK SORT: " << sorttime << " Seconds" << std::endl;
		break;
	case 2: //! Merge Sort
		startTime = clock();
		dictionary.MergeSort(*list, 0, list->size() - 1);
		sorttime = double(clock() - startTime) / CLOCKS_PER_SEC;
		std::cout << "MERGE SORT: " << sorttime << " Seconds" << std::endl;
		break;
	}
	startTime = clock();
	findMatches(dictionary, file);
	searchtime = double(clock() - startTime) / CLOCKS_PER_SEC;
	std::cout << "Time taken to find words in grid: " << searchtime << " Seconds" << std::endl;
	std::cout << "Time Overall: " << sorttime + searchtime << " Seconds" << std::endl;
}