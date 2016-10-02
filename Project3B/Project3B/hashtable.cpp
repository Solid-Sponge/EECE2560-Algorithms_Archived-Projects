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

#include "hashtable.h"

template<class T>
hashtable<T>::hashtable(int size)
{
	hashtable_size = size;
	table.resize(size);
}


template<class T>
void hashtable<T>::addItem(T& object)
{
	table[hash(object)].push_back(object);
	//table.push_back.push_back()
}

template<class T>
void hashtable<T>::deleteItem(T& object)
{
	size_t hashnum = hash(object);
	for (int i = 0; i < table[hashnum].size(); i++)
	{
		if (table[hashnum][i] == object)
		{
			table[hashnum].erase(table[hashnum].begin() + i);
		}
	}
}

template<class T>
bool hashtable<T>::inList(T& object)
{
	size_t hashnum = hash(object);
	for (int i = 0; i < table[hashnum].size(); i++)
	{
		if (table[hashnum][i] == object)
		{
			return true;
		}
	}
	return false;
}




template<class T>
std::size_t hashtable<T>::hash(T& object)
{
	return h_func(object) % hashtable_size;
}


template class hashtable <std::string>;