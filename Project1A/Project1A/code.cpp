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

#include "code.h"

//! Empty code() constructor
code::code()
{
	for (int i = 0; i < 5; i++)
	{
		vCode.push_back(0); //!< Creates 4 zero-value elements in vCode vector
	}
}


code::code(const int a, const int b, const int c, const int d)
{
	vCode.push_back(a); //!<Creates 4 values in vCode vector equal to a, b, c, d. Note that the only time push back is used is when calling any constructor of code
	vCode.push_back(b); //!<This prevents more than 4 elements in vCode
	vCode.push_back(c);
	vCode.push_back(d);
}
void code::setCode(const int a, const int b, const int c, const int d)
{
	vCode[0] = a; //!<Sets first 4 elements in vCode vector equal to a, b, c, d
	vCode[1] = b;
	vCode[2] = c;
	vCode[3] = d;
}
void code::randomizeCode()
{
	for (int i = 0; i < 4; i++)
		vCode[i] = (rand() % 6); //!<Randomizes first 4 elements in vCode vector. PRNG must be seeded in another function
}
void code::printCode() const
{
	for (int i = 0; i < 4; i++) //!<Prints first 4 elements in vCode Vector
		std::cout << vCode[i];
}
int code::checkCorrect(const code &c)
{
	try
	{
		if (c.vCode.size() < 4)
		{
			throw 1;
		}
	}
	catch (int e)
	{
		std::cout << "EXCEPTION THROWN: CODE HAS NO VALID CODE VECTOR";
		exit(0);
	}
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (vCode[i] == c.vCode[i]) //!<Checks if each value in each position in vCode is equal to the passed code object
		{
			count++;
			switch (i)
			{
			case 0:
				firstPosition = true; //!<If the first position is equal in both cases, a boolean is set to true. This is used in the checkIncorrect function to ignore specific positions
				break;
			case 1:
				secondPosition = true; //!<If the second position is equal in both cases, a boolean is set to true. This is used in the checkIncorrect function to ignore specific positions
				break;
			case 2:
				thirdPosition = true; //!<If the second position is equal in both cases, a boolean is set to true. This is used in the checkIncorrect function to ignore specific positions
				break;
			case 3:
				fourthPosition = true; //!<If the second position is equal in both cases, a boolean is set to true. This is used in the checkIncorrect function to ignore specific positions
				break;
			}
		}
	}
	return count;
}
int code::checkIncorrect(const code &c)
{
	try
	{
		if (c.vCode.size() < 4)
		{
			throw 1;
		}
	}
	catch (int e)
	{
		std::cout << "EXCEPTION THROWN: CODE HAS NO VALID CODE VECTOR";
		exit(0);
	}
	
	int count = 0;
	int values_incorrect[2][6] = { 0 }; /*!<Instantiates a 2x6 matrix of arrays. Each element in this array stands for each number present in both vCode and passed object's vCode. */
										/*!<The first row is for vCode [numof0's,numof1's,numof2's,#3,#4,#5]. The second row is for passed object's vCode [#0,#1,#2,#3,#4,#5] */
	
	for (int a = 0; a < 6; a++) //!< Essentially this entire nested for loop counts the amount of times each number appears in vCode
	{
		for (int b = 0; b < 4; b++)
			if (vCode[b] == a)
			{
			switch (b)
			{
			case 0:
				if (firstPosition) {} //!< If the loop finds a digit in a position that has already been marked as "correct" by the checkCorrect function, it ignores it.
				else
				{
					values_incorrect[0][a]++; //!< Otherwise, it increments it in the corresponding position of values_incorrect (first row, 'a' position)
				}
				break;
			case 1:
				if (secondPosition) {}
				else
				{
					values_incorrect[0][a]++;
				}
				break;
			case 2:
				if (thirdPosition) {}
				else
				{
					values_incorrect[0][a]++;
				}
				break;
			case 3:
				if (fourthPosition) {}
				else
				{
					values_incorrect[0][a]++;
				}
				break;
			}
			}
	}

	for (int a = 0; a < 6; a++) //!< This for loop does the exact same thing as the previous nested for loop, only for the passed code object's vCode.
	{
		for (int b = 0; b < 4; b++)
			if (c.vCode[b] == a)
			{
			switch (b)
			{
			case 0:
				if (firstPosition) {} //!< Once again, a check to see if the Position can be ignored due to it satisfying the numbersCorrect function
				else
				{
					values_incorrect[1][a]++; //!< The results are unsurprisingly placed in the 2nd row of the values_incorrect matrix.
				}
				break;
			case 1:
				if (secondPosition) {}
				else
				{
					values_incorrect[1][a]++;
				}
				break;
			case 2:
				if (thirdPosition) {}
				else
				{
					values_incorrect[1][a]++;
				}
				break;
			case 3:
				if (fourthPosition) {}
				else
				{
					values_incorrect[1][a]++;
				}
				break;
			}
			}
	}

	for (int a = 0; a < 5; a++)
	{
		count += std::min(values_incorrect[0][a], values_incorrect[1][a]); /*!< At the end of it all, it finally compares the number of times each number appears in both vCode and c.vCode.
																		    * It then takes the minimum of the two, and appends it to count variable. This is the algorithm responsible
																		    * for correctly returning the number of incorrect digits. Taking the min of both values ensures that duplicates
																		    * aren't counted in the answer. Ex: Key=2211 Guess=1222. The second position is marked as ignored so the codes
																		    * are reduced to 2[]11 and 1[]22. We see that 2 appears once in the key, or #2key = 1. In the answer,
																		    * 2 appears twice. So #2ans = 2. The min between #2key and #2ans is 1, which is correct, as there is only one 2 in
																		    * the key. The extra 2 in the ans is not duplicatedSame thing with 1. #1key = 2, #1ans = 1. Min(#1key,#1ans) = 1.
																			* There's two 1's in the key, but only one 1 in the answer. Overall, the total that would be returned is 2 digits incorrect*/
	}
	firstPosition = false; /*Each positional variable in the calling code object is reset back to default variables*/
	secondPosition = false;
	thirdPosition = false;
	fourthPosition = false;
	return count;
}

void code::increment()
{
	if (vCode[3] == 5) //<! Essentially does an Adhoc check to see if the last element is 5. If so, carry out to next element. (0005 -> 0010)
	{                  //<! The rest of the code accounts for every possible carry out situation
		if (vCode[2] == 5)
		{
			if (vCode[1] == 5)
			{
				if (vCode[0] == 5)
				{
					vCode[3] = 0;
					vCode[2] = 0;
					vCode[1] = 0;
					vCode[0] = 0;
				}
				else
				{
					vCode[3] = 0;
					vCode[2] = 0;
					vCode[1] = 0;
					vCode[0] += 1;
				}
			}
			else
			{
				vCode[3] = 0;
				vCode[2] = 0;
				vCode[1] += 1;
			}
		}
		else
		{
			vCode[3] = 0;
			vCode[2] += 1;
		}
	}
	else
	{
		vCode[3] += 1;
	}
}

code& code::operator=(const code& c)
{
	try
	{
		if (c.vCode.size() < 4)
		{
			throw 1;
		}
	}
	catch (int e)
	{
		std::cout << "EXCEPTION THROWN: CODE HAS NO VALID CODE VECTOR";
		exit(0);
	}
	setCode(c.vCode[0], c.vCode[1], c.vCode[2], c.vCode[3]); //!< Sets calling object's vCode equal to c's vCode
	return *this;
}

std::ostream& operator<<(std::ostream& os, const code c)
{
	os << c.vCode[0] << c.vCode[1] << c.vCode[2] << c.vCode[3]; //!<Outputs vCode to console
	return os;
}