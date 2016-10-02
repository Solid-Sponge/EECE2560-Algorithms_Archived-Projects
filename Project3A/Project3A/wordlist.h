/**
* \class wordlist
*
*
* \brief Stores a dictionary into a vector of strings, then sorts it according to 1 of 3 algorithms. Provides a binary search as well
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

#ifndef WORDLIST_H
#define WORDLIST_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "heap.h"

class wordlist{
	public:
		//! Empty wordlist constructor. Loads wordlist.txt into ListOfWords
		wordlist();

		//! Performs an InsertionSort on ListOfWords
		void InsertionSort();




		//! Performs a QuickSort on ListOfWords
		/*!
		* \param int first element
		* \param int last element
		*/
		void QuickSort(int, int);
		//! QuickSort Pivot function. Used in QuickSort
		/*!
		* \param int first element
		* \param int last element
		*/
		int QSPivot(int, int);



		//! Performs a MergeSort on passed vector of strings (ListOfWords)
		/*!
		* \param std::vector<std::string>& ListOfWords passed to this function
		* \param int low element
		* \param int high element
		*/
		void MergeSort(std::vector<std::string>&, int, int);
		
		//! Merge function to merge two subarrays together. Used in Mergesort
		/*!
		* \param std::vector<std::string>& ListOfWords passed to this function
		* \param int low element
		* \param int mid element
		* \param int high element
		*/
		void Merge(std::vector<std::string>&, int, int, int);


		//! Performs a HeapSort on ListOfWords
		void HeapSort();

		
		//! Performs a BinarySearch on a vector of strings
		/*!
		* \param std::vector<std::string>& vector of strings to search through
		* \param std::string string to search for
		* \param int first element
		* \param int last element
		* \return int index of element if found. -1 otherwise.
		*/
		int BinarySearch(std::vector<std::string>&, std::string, int, int);


		//! Returns size of ListOfWords
		/*!
		* \return int size of ListOfWords
		*/
		int returnSizeOfWords();


		//! Returns SizeOfList
		/*!
		* \return std::vector<std::string>& SizeOfList
		*/
		std::vector<std::string>& returnList();


		friend std::ostream& operator<<(std::ostream&, const wordlist);
	private:
		std::vector<std::string> ListOfWords;
};

//! Checks how many digits in the code object being passed are in the right spot compared to the code object calling this method
/*!
* \param std::ostream& Ostream object passed
* \param int low element
* \return std::ostream& Ostream object
*/
std::ostream& operator<<(std::ostream&, const wordlist);

#endif // !WORDLIST_H