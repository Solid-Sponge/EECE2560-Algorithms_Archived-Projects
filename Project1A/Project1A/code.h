/**
 * \class code
 *
 *
 * \brief Stores a 4-dight code (ranging from 0-4)
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

#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>


class code
{
	public:
		//! Empty code() constructor
		code();

		//! code() constructor that stores the four int parameters into vector vCode as seperate elements
		code(const int, const int, const int, const int);

		//! Sets first 4 elements of vCode equal to the 4 ints passed 
		/*!
		 * \param int Position 1 of vCode to be set
		 * \param int Position 2 of vCode to be set
		 * \param int Position 3 of vCode to be set
		 * \param int Position 4 of vCode to be set
		 */
		void setCode(int, int, int, int);

		/** Randomizes the first 4 elements of vCode based of a pseudo-random number generator.
		  * IMPORTANT: This function does NOT seed the PRNG. The PRNG must be seeded by another
		  * function
		  */
		void randomizeCode();

		//! Checks how many digits in the code object being passed are in the right spot compared to the code object calling this method
		/*!
		* \param code Code object being compared to
		* \return int number of correct digits
		*/
		int checkCorrect(const code&);

		//! Checks how many digits in the code object being passed are digits that appear in the object calling this method but in the wrong position
		/*!
		* \param code Code object being compared to
		* \return int number of correct digits in icorrect spot
		*/
		int checkIncorrect(const code&);

		//! Prints out the first 4 values of the object calling this method's vCode to the console
		void printCode() const;

		//! Increments the value of vCode to the next possible Value (stops when 
		void increment();

		//! Sets calling code object equal to passed code object (via operator =)
		/*!
		* \param code Code object being passed
		* \return code& pointer to Code
		*/
		code& operator=(const code&);

		//! Sets operator<< in ostream class as a friend
		friend std::ostream& operator<<(std::ostream&, const code); 
	private:
		std::vector<int> vCode; //!< Vector used to store 4-digit code
		bool firstPosition = false; //!< Bool used to determine if first position is matched up with another code
		bool secondPosition = false; //!< Bool used to determine if second position is matched up with another code
		bool thirdPosition = false; //!< Bool used to determine if third position is matched up with another code
		bool fourthPosition = false; //!< Bool used to determine if fourth position is matched up with another code
};

//! Outputs values in vCode to console
/*!
* \param ostream& pointer to ostream object
* \return code& pointer to Code
*/
std::ostream& operator<<(std::ostream&, const code);
#endif // !CODE_H