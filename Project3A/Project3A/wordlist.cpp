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

#include "wordlist.h"

wordlist::wordlist()
{
	std::ifstream readfile;
	readfile.open("wordlist.txt");
	std::string temp;
	if (readfile.is_open())
	{
		while (!readfile.eof())
		{
			readfile >> temp;
			ListOfWords.push_back(temp); //!< Reads all words from wordlist into ListOfWords
		}
	}
}

void wordlist::InsertionSort()
{
	std::string key;
	int i, j;

	for (i = 1; i < ListOfWords.size(); i++)
	{
		key = ListOfWords[i];
		for (j = i - 1; (j >= 0) && (ListOfWords[j] > key); j--)
		{
			ListOfWords[j + 1] = ListOfWords[j];
		}
		ListOfWords[j + 1] = key;
	}
}

void wordlist::QuickSort(int first, int last)
{
	int pivotElement;
	if (first < last)
	{
		pivotElement = QSPivot(first, last); //Sets the pivot element equal to function return of QSPivot, with first and last passed
		QuickSort(first, pivotElement - 1); //Recursively calls QuickSort for bounds from first to pivotElement - 1
		QuickSort(pivotElement + 1, last); //Recursively calls Quicksort for bounds pivotElement + 1 to last
	}
}

int wordlist::QSPivot(int first, int last)
{
	int p = first;
	std::string pivotElement = ListOfWords[first];
	std::string temp;
	for (int i = first + 1; i <= last; i++)
	{
		if (ListOfWords[i] <= pivotElement)
		{
			p++;
			temp = ListOfWords[i];
			ListOfWords[i] = ListOfWords[p];
			ListOfWords[p] = temp;
		}
	}

	temp = ListOfWords[p];
	ListOfWords[p] = ListOfWords[first];
	ListOfWords[first] = temp;
	return p;
}


void wordlist::MergeSort(std::vector<std::string>& arr, int low, int high)
{
	if (low < high) //!<Recursively called until low < high
	{
		int mid = (low + high) / 2; 
		MergeSort(arr, low, mid); //!< Recursively calls MergeSort with boundaries from low to mid
		MergeSort(arr, mid + 1, high); //!< Recursively calls Mergesort with boundaries from mid+1 to high
		Merge(arr, low, mid, high); //!< Merges arr with low, mid, and high
	}
}

void wordlist::Merge(std::vector<std::string>& arr, int low, int mid, int high)
{
	std::vector<std::string> temp;
	for (int i = 0; i < (high - low + 1); i++)
	{
		temp.push_back(""); //!< Allocates empty space equal to high - low + 1
	}

	int left = low;
	int right = mid + 1;
	int current = 0;

	while (left <= mid && right <= high) //!< Essentially checks both arrays from left to right and adds each corresponding element from lowest to highest back to the array
	{
		if (arr[left] <= arr[right])
		{
			temp[current] = arr[left];
			left++;
		}
		else
		{
			temp[current] = arr[right];
			right++;
		}
		current++;
	}

	if (left > mid)
	{
		for (int i = right; i <= high; i++)
		{
			temp[current] = arr[i];
			current++;
		}
	}
	else
	{
		for (int i = left; i <= mid; i++)
		{
			temp[current] = arr[i];
			current++;
		}
	}

	for (int i = 0; i <= high - low; i++)
	{
		arr[i + low] = temp[i];
	}
}


void wordlist::HeapSort()
{
	heap<std::string> h;
	h.heapsort(ListOfWords);
	for (int i = 0; i < ListOfWords.size(); i++)
	{
		ListOfWords[i] = h.getItem(i);
	}
}

int wordlist::BinarySearch(std::vector<std::string>& arr, std::string key, int first, int last)
{
	int index;

	if (first > last) //!< If search fails, return -1
	{
		index = -1;
	}
	else
	{
		int mid = (first + last) / 2; 
		if (key == arr[mid]) //!< Checks if the middle element is equal to the key
		{
			index = mid;
		}
		else
		{
			if (key < arr[mid]) //!< Checks if the key is smaller than the middle element in array.
			{
				index = BinarySearch(arr, key, first, mid-1); //!< Recursively calls BinarySearch with altered bounds from first to mid-1
			}
			else
			{
				index = BinarySearch(arr, key, mid + 1, last); //!< Recursively calls BinarySearch with altered bounds from mid + 1 to last
			}
		}
	}
	return index;
}



int wordlist::returnSizeOfWords()
{
	return ListOfWords.size();
}

std::vector<std::string>& wordlist::returnList()
{
	return ListOfWords;
}

std::ostream& operator<<(std::ostream& os, const wordlist w)
{
	for (int i = 0; i < w.ListOfWords.size(); i++)
	{
		os << w.ListOfWords[i] << std::endl;
	}
	return os;
}