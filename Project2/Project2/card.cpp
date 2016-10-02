/**
* \class card
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

#include "card.h"
#include <string>

card::card()
{
	number = 1; //!< Default values for card
	symbol = 1;
	shading = 1;
	color = 1;
}


card::card(const card &rhs)
{
	number = rhs.number; //Copy constructor
	symbol = rhs.symbol;
	shading = rhs.shading;
	color = rhs.color;
}

card::card(int a, int b, int c, int d) //!< Assigns each parameter in object equal to each int
{
	number = a;
	symbol = b;
	shading = c;
	color = d;
}

void card::setNumber(int a) { number = a; } //!< Sets parameter number equal to int a
int card::getNumber() const //!< Gets parameter number
{
	return number; 
}

void card::setSymbol(int a) { symbol = a; } //!< Sets parameter symbol equal to int a
int card::getSymbol() const  //!< Gets parameter symbol
{
	return symbol;
}

void card::setShading(int a) { shading = a; } //!< Sets parameter shading equal to int a
int card::getShading() const //!< Gets parameter shading
{
	return shading;
}

void card::setColor(int a) { color = a; } //!< Sets parameter color equal to int a;
int card::getColor() const //!< Gets parameter color
{
	return color; 
}



card& card::operator++()
{
	if (color == 3) //! Essentially checks each overflow case. Overflow is caused when a parameter contains a value greater than 3
	{				//! For example, 1223++ overflows, and turns into 1231. The most significant bit's overflow is dropped,
		color = 1; //! 3333++ overflows, and turns into 1111
		if (shading == 3)
		{
			shading = 1;
			if (symbol == 3)
			{
				symbol = 1;
				if (number == 3)
				{
					number = 1;
				}
				else
				{
					number++;
				}
			}
			else
			{
				symbol++;
			}
		}
		else
		{
			shading++;
		}
	}
	else
	{
		color++;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& ostr, const card& c)
{
	std::string number;
	std::string symbol;
	std::string shading;
	std::string color;

	switch (c.getNumber()) //!< Converts numerical parameters into words (Symbol 1 = Diamond, Symbol 2 = Squiggle, etc)
	{
	case 1:
		number = "1";
		break;
	case 2:
		number = "2";
		break;
	case 3:
		number = "3";
		break;
	}

	switch (c.getSymbol())
	{
	case 1:
		symbol = "Diamond ";
		break;
	case 2:
		symbol = "Squiggle";
		break;
	case 3:
		symbol = "Oval    ";
		break;
	}

	switch (c.getShading())
	{
	case 1:
		shading = "Solid  ";
		break;
	case 2:
		shading = "Striped";
		break;
	case 3:
		shading = "Open   ";
		break;
	}

	switch (c.getColor())
	{
	case 1:
		color = "Red   ";
		break;
	case 2:
		color = "Green ";
		break;
	case 3:
		color = "Purple";
		break;
	}
	ostr << number << " " << symbol << " " << shading << " " << color;
	return ostr;
}

card& card::operator=(const card& rhs)
{
	number = rhs.number; //Assignment operator overloaded
	symbol = rhs.symbol;
	shading = rhs.shading;
	color = rhs.color;
	return *this;
}
