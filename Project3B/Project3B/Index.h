/**
* \class Index
*
*
* \brief Acts just like an int, except it can have any radix (defined by carryout)
*	///	Used to access elements in a matrix and have them overflow properly with the ++ overloaded operator
*	/// Ex: With carryout 5, it will go from 0->1->2->3->4->0 when adding + 1,
*	///	or 0->4->3->2->1->0 when adding - 1
* \author $Author: Michael Rossi
*
* \version $Revision: 1.0 $
*
* \date $Date: 2015/10/13 23:16:20 $
*
* Contact: rossisantomauro.m@husky.neu.edu
*
*/

#ifndef INDEX_H
#define INDEX_H

class index{
	public:

		//! Default constructor (sets num = 0 and base = 0)
		index() { carryout = 0; num = 0; }

		//! Constructor that sets the carryout (radix) equal to passed value
		/*!
		* \param int Value passed
		*/
		index(int c) { carryout = c; num = 0; }

		//! \return int Value of num stored
		int getnum() { return num; }
		//! \param int Value to set num equal to
		void setnum(int n) { num = n; }
		//! \return int Value of carryout stored
		int getcarryout() { return carryout; }
		
		//! Increments num+1 until carryout is reached, then overflows back to 0
		/*!
		* \return index& index object
		*/
		index& operator++();

		//! Increments num+1 until carryout is reached, then overflows back to 0
		/*!
		* \return index& index object
		*/
		index& operator--();
	private:
		int num; //!< Value stored
		int carryout; //!< "Radix" or "base" of number
};

index& index::operator++()
{
	num++;
	if (num == carryout)
	{
		num = 0;
	}
	return *this;
}

index& index::operator--()
{
	num--;
	if (num < 0)
	{
		num = carryout - 1;
	}
	return *this;
}

index& operator+(index i, int n)
{
	for (int a = 0; a < n; a++)
	{
		++i;
	}
	return i;
}

#endif