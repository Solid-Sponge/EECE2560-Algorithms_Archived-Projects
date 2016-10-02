/**
* \class hashtable
*
*
* \brief Stores a hashtable of generic objects
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

#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <vector>
#include <functional>
#include <cstring>

template<typename T>
class hashtable
{
	public:
		///Default constructor
		hashtable();
		/// Constructor that takes an int, which becomes the size of the hash_table
		hashtable(int);

		//! Adds object T to hashtable
		/*!
		* \param T& Item to add
		*/
		void addItem(T&);

		//! Deletes object T in hashtable
		/*!
		* \param T& Item to delete
		*/
		void deleteItem(T&);

		//! Checks if object T is in hashtable
		/*!
		* \param T& Item to check
		* \return true if T is in hashtable, false if otherwise
		*/
		bool inList(T&);

		//! Generates a hash for object T
		/*!
		* \param T& Item to generate hash
		* \return size_t hash value
		*/
		std::size_t hash(T&);
	private:
		std::vector<std::vector<T>> table; //!< Hash table
		std::hash<T> h_func; //!< Hash function
		int hashtable_size; //!< Hash table size
};

#endif