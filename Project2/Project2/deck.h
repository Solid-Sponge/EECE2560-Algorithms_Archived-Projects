/**
* \class deck
*
*
* \brief Stores a deck of objects in a linked list format
*
* \author $Author: Michael Rossi
*
* \version $Revision: 1.0 $
*
* \date $Date: 2015/09/17 23:16:20 $
*
* Contact: rossisantomauro.m@husky.neu.edu
*
*/


#ifndef DECK_H
#define DECK_H

#include "node.h"
#include "card.h"
#include <cstddef>
#include <vector>

template<typename T>
class deck{
	public:
		//! Default constructor for deck object. Stores 81 objects incremented into the linked list
		deck();

		//! Default destructor for deck object. Destroys all objects in the linked list to prevent memory leaking
		~deck();

		//! Adds an object T at a specific point in the linked list
		/*!
		* \param object T Object being added
		* \param int Index to store object
		*/
		void addNode(T&, int);

		//! Adds an object T at the end of the linked list
		/*!
		* \param object T Object being added
		*/
		void addNodeAtEnd(T&);

		//! Deletes an object T at a specific point in the linked list
		/*!
		* \param int Index of object to delete
		*/
		void deleteNode(int);

		//! Retrieves object T at a specific index list
		/*!
		* \param int Index of object to retrieve
		* \return T Object being retrieved
		*/
		T getNode(int);

		//! Retrives pointer ot object T at specific index in linked list
		/*!
		* \param int Index of object to retrieve pointer of
		* \return node<T>* Pointer of objet
		*/
		node<T>* getNodePtr(int); //node<T>

		//! Swaps 2 objects in the linked list
		/*!
		* \param int First index
		* \param int Second index
		*/
		void swapNode(int, int);

		//! Shuffles contents of Linked List around (PRNG MUST BE SEEDED ELSEWHERE)
		void shuffle();

		//! Prints out each object in linked list
		void printAll();

		//! Returns size of linked list
		/*!
		* \return int Size of linked list
		*/
		int getSizeOfList();
		
		//! Removes int cards from linked list and pushes them onto empty vector of objects
		/*!
		* \param int Num of cards to deal
		* \param vector<T>& Vector to deal cards to
		*/
		void deal(int, std::vector<T>&);

		//! Removes objects from vector of objects and pushes them onto the linked list
		/*!
		* \param vector<T>& Vector to remove cards from
		*/
		void replace(std::vector<T>&);

	private:
		node<T> *pHead; //!< Head of Linked List
		int SizeOfList = 0; //!< Size of Linked List
};


#endif // !DECK_H
