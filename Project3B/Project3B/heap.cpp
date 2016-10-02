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

#include "heap.h"


template <class T>
heap<T>::heap()
{

}

template <class T>
heap<T>::heap(std::vector<T>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		HeapArr.push_back(arr[i]);
}

template <class T>
int heap<T>::parent(int n)
{
	return ( (n + 1) / 2) - 1;
}

template <class T>
int heap<T>::left(int n)
{
	return (2*(n+1)) - 1;
}

template <class T>
int heap<T>::right(int n)
{
	return 2 * (n+1);
}

template <class T>
T heap<T>::getItem(int n)
{
	return HeapArr[n];
}

template <class T>
void heap<T>::maxHeapify(std::vector<T>& arr, int i, int size)
{
	int l = left(i);
	int r = right(i);
	int largest;
	if (l <= size-1 && arr[l] > arr[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}

	if (r <= size-1 && arr[r] > arr[largest])
	{
		largest = r;
	}

	if (largest != i)
	{
		T temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		maxHeapify(arr,largest,size);
	}
}

template <class T>
void heap<T>::buildMaxHeap(std::vector<T>& arr)
{
	for (int i = (arr.size() / 2) - 1; i >= 0; i--)
		maxHeapify(arr, i, arr.size());
}

template <class T>
void heap<T>::initializeMaxHeap(std::vector<T>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		HeapArr.push_back(arr[i]);
	}
	buildMaxHeap(HeapArr);
}


template <class T>
void heap<T>::minHeapify(std::vector<T>& arr, int i, int size)
{
	int l = left(i);
	int r = right(i);
	int smallest;
	if (l <= size - 1 && arr[l] < arr[i])
	{
		smallest = l;
	}
	else
	{
		smallest = i;
	}

	if (r <= size - 1 && arr[r] < arr[smallest])
	{
		smallest = r;
	}

	if (smallest != i)
	{
		T temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
		minHeapify(arr, smallest, size);
	}
}

template <class T>
void heap<T>::buildMinHeap(std::vector<T>& arr)
{
	for (int i = (arr.size() / 2) - 1; i >= 0; i--)
		minHeapify(arr, i, arr.size());
}

template <class T>
void heap<T>::initializeMinHeap(std::vector<T>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		HeapArr[i] = arr[i];
	}
	buildMinHeap(HeapArr);
}


template <class T>
void heap<T>::heapsort(std::vector<T>& arr)
{
	initializeMaxHeap(arr);
	int size = HeapArr.size();
	for (int i = HeapArr.size() - 1; i >= 1; i--)
	{
		T temp = HeapArr[0];
		HeapArr[0] = HeapArr[i];
		HeapArr[i] = temp;
		size--;
		maxHeapify(HeapArr, 0, size);

	}
}

template class heap <std::string>;
template class heap <int> ;