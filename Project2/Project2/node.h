/**
* \class node
*
*
* \brief Stores an object T in a node with a pointer to the next object T, used in linked lists
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

#ifndef NODE_H
#define NODE_H

#include <cstddef>

template<typename T>
class node{
	public:
		//! Node constructor with passed object T. Automatically sets next pointer equal to NULL
		/*!
		* \param const T& Object being passed to construct node with
		*/
		node(const T &item, node<T> *nextNode = NULL)
			: nodeValue(item), next(nextNode) {};
		//! Default constructor for node. Automatically sets next pointer equal to NULL
		node(node<T> *nextNode = NULL) 
			: next(nextNode) {};

		T nodeValue; //!< Value of object T
		node <T> *next; //!< Pointer to next object T
};

#endif // !NODE_H


