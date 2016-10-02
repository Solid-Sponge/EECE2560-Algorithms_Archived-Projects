/**
* \class response
*
*
* \brief Stores a response to a code (num of correct digits and incorrect digits)
*
* \author $Author: Michael Rossi
*
* \version $Revision: 1.0 $
*
* \date $Date: 2015/09/18 09:45:20 $
*
* Contact: rossisantomauro.m@husky.neu.edu
*
*/


#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include "code.h"

class response
{
public:
	//! Empty code() constructor
	response();

	//! code() constructor that stores two int parameters into numCorrect and numIncorrect
	response(const int, const int);

	//! Returns private member numCorrect
	/*!
	 * \return int numCorrect
	 */
	int get_numCorrect() const;

	//! Returns private member numIncorrect
	/*!
	 * \return int numIncorrect
	 */
	int get_numIncorrect() const;

	//! Sets private member numCorrect = value passed
	/*!
	 * \param int Value to set numCorrect to
	 */
	void set_numCorrect(const int);

	//! Sets private member numIncorrect = value passed
	/*!
	* \param int Value to set numIncorrect to
	*/
	void set_numIncorrect(const int);

	//! Compares response with passed object.
	/*!
	* \param reponse& Response object being compared with calling object
	* \return True if calling object == passed object. False otherwise.
	*/
	bool compareResponse(const response&) const;

	//! Prints to console values of numCorrect and numIncorrect;
	void printResponse() const;

	//! Sets calling object's private members equal to passed object's private members
	/*!
	* \param reponse& Response object being set to the calling object
	* \return reponse& Pointer of calling object
	*/
	response& operator=(const response&);

	friend std::ostream& operator<<(std::ostream&, const response); //!< Sets operator << in ostream class as friend
	friend bool operator== (response&, response&); //!< Sets operator == as friend
private:
	int numCorrect; //!< Number of correct digits in code objects comparison
	int numIncorrect;//!< Number of correct digits in incorrect spot in code objects comparison
};

std::ostream& operator<<(std::ostream& os, const response res);
#endif // !RESPONSE_H