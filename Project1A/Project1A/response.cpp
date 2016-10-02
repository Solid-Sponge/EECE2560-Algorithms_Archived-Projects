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

#include "response.h"

response::response() {} //!<Empty constructor
response::response(const int nCorrect, const int nIncorrect)
{
	numCorrect = nCorrect; //!< Sets private members numCorrect and numIncorrect equal to the passed ints
	numIncorrect = nIncorrect;
}
int response::get_numCorrect() const
{
	return numCorrect; //!< Returns private member numCorrect;
}
int response::get_numIncorrect() const
{
	return numIncorrect; //!< Returnss private member numIncorrect;
}
void response::set_numCorrect(const int n)
{
	numCorrect = n; //!< Sets private member numCorrect equal to passed int
}
void response::set_numIncorrect(const int n)
{
	numIncorrect = n; //!< Sets private member numIncorrect equal to passed int
}
bool response::compareResponse(const response &res) const
{
	if ((numCorrect == res.numCorrect) && (numIncorrect == res.numIncorrect)) //!< Returns true if both private members of the calling object and the passed object are equal to each other
		return true;
	return false;
}
void response::printResponse() const
{
	std::cout << "Number Correct: " << numCorrect << std::endl << "Number Correct in Wrong Spot: " << numIncorrect << std::endl; //!< Prints out private members numCorrect and numIncorrect
}

response& response::operator=(const response& b)
{
	numCorrect = b.numCorrect; //!< Sets each private member of calling object equal to passed object
	numIncorrect = b.numIncorrect;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const response res)
{
	os << res.numCorrect << " Digits Correct/ " << res.numIncorrect << " Digits Incorrect"; //!< Outputs response in console
	return os;
}

bool operator== (response& a, response& b)
{
	if ((a.numCorrect == b.numCorrect) && (a.numIncorrect == b.numIncorrect)) //!< Returns true if response a's private members == response b's private members
		return true;
	return false;
}