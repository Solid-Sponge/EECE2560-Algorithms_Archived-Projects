/**
* \class deck
*
*
* \brief Initializes a game of Mastermind to be played against the computer when playGame() is called
*
* \author $Author: Michael Rossi
*
* \version $Revision: 1.0 $
*
* \date $Date: 2015/09/18 18:45:20 $
*
* Contact: rossisantomauro.m@husky.neu.edu
*
*/

#include "deck.h"
#include "card.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>


template<class T>
deck<T>::deck()
{
	pHead = new node < T > ; //!< Creates new head object equal to default value of object
	T object; //!< Creates temporary object
	object++; //!< Increments temporary object
	SizeOfList++; //!< Increments size of linked list
	for (int i = 0; i < 80; i++) //!< Appends 80 elements on top of head object, each element appended
	{
		addNodeAtEnd(object);
		object++;
	}
}

template<class T>
deck<T>::~deck()
{
	node<T> *pDel = pHead; //!< Creates pointer to node of objects equal to the head
	while (pDel != NULL) //!< Loop continues as long as pDel != NULL 
	{
		pHead = pHead->next; //!< Assigns pHead the value of the address in the next element on the list
		delete pDel; //!< Deletes pDel (which will always be 1 element behind pHead
		pDel = pHead; //!< Assigns to pDel the current value of pHead
		SizeOfList--; //!< Decrements the size of the list variable

	}
	pHead = NULL; //!< Sets pHead = NULL
}

template<class T>
void deck<T>::addNode(T& value, int n)
{
	node<T> *cur = pHead; //!< Creates a pointer to a node object equal to head
	node<T> *prev = NULL; //!< Creates a pointer to a node object equal to NULL, whose purpose is to always remain 1 step behind pHead
	int i = 0;
	while ((cur->next != NULL) && (i < n)) //!< Goes through linked list until either element in specific index is found or final element is reached
	{
		prev = cur;
		cur = cur->next;
		i++;
	}
	if (i != n) //!< Checks if index n is out of bounds of array. Throws an out_of_range exception if so
	{
		throw std::out_of_range("Position higher than size of linked list");
	}
	node<T> *target = new node < T > ; //!< Creates space for a new node object T
	target->nodeValue = value; //!< Assigns value of target equal to passed object's value
	if (prev == NULL) //!< Checks if element is to be inserted in front of the linked list
	{
		pHead = target;
		pHead->next = cur;
	}
	else
	{
		prev->next = target;
		target->next = cur;
	}
	SizeOfList++; //!< Increments size of linked list
}


template<class T>
void deck<T>::addNodeAtEnd(T& value)
{
	node<T> *cur = pHead;//!< Creates a pointer to a node object equal to head
	while (cur->next != NULL) //!< Loops through linked list until final element is reached
	{
		cur = cur->next;
	}
	node<T> *target = new node < T > ; //!< Creates space for new node object T
	target->nodeValue = value; //!< Assigns value of new object equal to passed object value
	cur->next = target; //!< Links the new object into the end of the linked list
	SizeOfList++; //!< Increments size of linked list
}


template<class T>
void deck<T>::deleteNode(int n)
{
	node<T> *cur = pHead; //!< Creates a pointer to a node object equal to head
	node<T> *prev = NULL; //!< Creates a pointer to a node object equal to NULL, whose purpose is to always remain 1 step behind pHead
	int i = 0;
	while ((cur->next != NULL) && (i < n)) //!< Goes through linked list until either element in specific index is found or final element is reached
	{
		prev = cur;
		cur = cur->next;
		i++;
	}
	if (i != n) //!< Checks if index n is out of bounds of array. Throws an out_of_range exception if so
	{
		throw std::out_of_range("Position higher than size of linked list");
	}
	if (prev == NULL) //!< Checks if element to be delted is in front of the linked list
	{
		pHead = pHead->next; //!< Points pHead to 2nd element of list
		delete cur; //!< Deletes element in front of linked list
	}
	else
	{
		prev->next = cur->next; //!< Points previous element to element after the deleted node
		delete cur; //!< Deletes element in index n
	}
	SizeOfList--; //!< Decrements size of linked list
}

template<class T>
T deck<T>::getNode(int n)
{
	node<T> *cur = pHead; //!< Creates a pointer to a node object equal to head
	node<T> *prev = NULL; //!< Creates a pointer to a node object equal to NULL, whose purpose is to always remain 1 step behind pHead
	int i = 0;
	while ((cur->next != NULL) && (i < n)) //!< Goes through linked list until either element in specific index is found or final element is reached
	{
		prev = cur;
		cur = cur->next;
		i++;
	}
	if (i != n) //!< Checks if index n is out of bounds of array. Throws an out_of_range exception if so
	{
		throw std::out_of_range("Position higher than size of linked list");
	}
		return cur->nodeValue; //!< Returns object at position n
}

template<class T>
node<T>* deck<T>::getNodePtr(int n)
{
	node<T> *cur = pHead; //!< Creates a pointer to a node object equal to head
	node<T> *prev = NULL;//!< Creates a pointer to a node object equal to NULL, whose purpose is to always remain 1 step behind pHead
	int i = 0;
	while ((cur->next != NULL) && (i < n)) //!< Goes through linked list until either element in specific index is found or final element is reached
	{
		prev = cur;
		cur = cur->next;
		i++;
	}
	if (i != n) //!< Checks if index n is out of bounds of array. Throws an out_of_range exception if so
	{
		throw std::out_of_range("Position higher than size of linked list");
	}
	return cur; //!< Returns pointer to object at position n
}


template<class T>
void deck<T>::swapNode(int a, int b)
{
	
	node<T> *PtrA = getNodePtr(a); //!< Gets pointer to object at position a
	node<T> *PtrB = getNodePtr(b); //!< Gets pointer to object at position b
	T tempobj; //!< Creates a temporary object
	tempobj = PtrA->nodeValue; //!< Temporary object holds value of object at position a
	PtrA->nodeValue = PtrB->nodeValue; //!< Assigns value of object at position a = value of object at position b
	PtrB->nodeValue = tempobj; //!< Assigns value of object at position b = temp object (which contains old value of a)
}

template<class T>
void deck<T>::shuffle()
{
	for (int i = 0; i < SizeOfList; i++)
	{
		swapNode(i, rand() % SizeOfList); //!< SHuffles objects in linked list
	}
}

template<class T>
void deck<T>::printAll()
{
	node<T> *cur = pHead;
	while (cur->next != NULL) //!< Scans through all of linked list
	{
		std::cout << cur->nodeValue << std::endl; //!< Prints each object's value
		cur = cur->next;
	}
	std::cout << cur->nodeValue << std::endl; //!< Prints last object in list's value
	std::cout << "SizeOfList: " << SizeOfList << std::endl;
}

template<class T>
int deck<T>::getSizeOfList()
{
	return SizeOfList; //!< Returns size of linked list
}

template<class T>
void deck<T>::deal(int num, std::vector<T> &v)
{
	if (v.size() != 0) //!< Checks if vector v has any elements in it, throws exception if so
	{
		throw std::length_error("Vector passed is not empty");
	}
	for (int i = 0; i < num; i++)
	{
		v.push_back(getNode(i)); //!< Pushes into vector v the first i objects in linked list
	}
	for (int i = 0; i < num; i++)
	{
		deleteNode(0); //!< Deletes the first i objects from linked list
	}
}

template<class T>
void deck<T>::replace(std::vector<T> &v)
{
	if (v.size() == 0) //!< Checks if vector v is empty, throws exception if so
	{
		throw std::length_error("Vector passed is empty");
	}
	for (int i = 0; i < v.size(); i++)
	{
		addNodeAtEnd(v[i]); //!< Appends to the end of the linked list each object in vector v
	}
	for (int i = 0; i < v.size(); i++)
	{
		v.pop_back(); //!< Pops out each object in vector v
	}
}



template class deck < card > ;