/**
* \class heap
*
*
* \brief Stores a heap into a vector of T objects
*
* \author $Author: Michael Rossi
*
* \version $Revision: 1.0 $
*
* \date $Date: 2015/10/18 23:16:20 $
*
* Contact: rossisantomauro.m@husky.neu.edu
*
*/

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <cstring>

template<typename T>
class heap
{
	public:
		///Default constructor
		heap();
		///Constructor that assigns HeapArr equal to passed object
		heap(std::vector<T> &);

		//! Returns index of parent at int index
		/*!
		* \param int index to check
		* \return index of parent
		*/
		int parent(int);

		//! Returns index of left node at int index
		/*!
		* \param int index to check
		* \return index of right node
		*/
		int left(int);

		//! Returns index of right node at int index
		/*!
		* \param int index to check
		* \return index of right node
		*/
		int right(int);

		//! Returns object T at inde
		/*!
		* \param int index to check
		* \return object T at index
		*/
		T getItem(int);

		//! Fixes heap property at index
		/*!
		* \param vector<T>& Vector to check
		* \param int index,
		* \param int heap_size
		*/
		void maxHeapify(std::vector<T>&, int, int);

		//! Creates a heap out of an array
		/*!
		* \param vector<T>& Vector to change
		*/
		void buildMaxHeap(std::vector<T>&);

		//! Creates a max heap, calls buildMaxHeap, which calls maxHeapify recursively
		/*!
		* \param int index to check
		*/
		void initializeMaxHeap(std::vector<T>&);

		//! Returns index of parent at int index
		/*!
		* \param int index to check
		*/


		//! Fixes heap property at index MINHEAP edition
		/*!
		* \param vector<T>& Vector to check
		* \param int index,
		* \param int heap_size
		*/
		void minHeapify(std::vector<T>&, int, int);

		//! Creates a heap out of an array MINHEAP edition
		/*!
		* \param vector<T>& Vector to change
		*/
		void buildMinHeap(std::vector<T>&);

		//! Creates a min heap, calls buildMinHeap, which calls minHeapify recursively
		/*!
		* \param int index to check
		*/
		void initializeMinHeap(std::vector<T>&);

		//! Sorts an array using a heapsort
		/*!
		* \param vector<T>& array to sort
		*/
		void heapsort(std::vector<T>&);
	private:
		std::vector<T> HeapArr; //!< Heap
};

#endif