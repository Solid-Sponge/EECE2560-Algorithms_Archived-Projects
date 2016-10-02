/**
* \class card
*
*
* \brief Stores a Set card with 4 parameters (Number, Symbol, Shading, Color)
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

#ifndef CARD_H
#define CARD_H
#include <iostream>

class card
{
	public:
		//! Empty card constructor that sets all parameters = 1111
		card();
		//! Copy constructor for cards
		/*!
		* \param const card& Card object being set equal to
		*/
		card(const card&);

		//! Constructor for card with preset values for each parameter
		/*!
		* \param int Number parameter
		* \param int Symbol parameter
		* \param int Shading parameter
		* \param int color parameter
		*/
		card(int, int, int, int);

		//! Sets number parameter equal to passed value
		/*!
		* \param int Value to set number parameter to
		*/
		void setNumber(int);

		//! Gets number parameter from card object
		/*!
		* \return int Value of number parameter
		*/
		int getNumber() const;
		


		//! Sets symbol parameter equal to passed value
		/*!
		* \param int Value to set symbol parameter to
		*/
		void setSymbol(int);

		//! Gets symbol parameter from card object
		/*!
		* \return int Value of symbol parameter
		*/
		int getSymbol() const;



		//! Sets shading parameter equal to passed value
		/*!
		* \param int Value to set shading parameter to
		*/
		void setShading(int);

		//! Gets shading parameter from card object
		/*!
		* \return int Value of shading parameter
		*/
		int getShading() const;



		//! Sets color parameter equal to passed value
		/*!
		* \param int Value to set color parameter to
		*/
		void setColor(int);

		//! Gets color parameter from card object
		/*!
		* \return int Value of color parameter
		*/
		int getColor() const;

		//! Increases the value of a card by one when called. (Think of cards as a 4-digit base3 number from 1111-3333. 
		//!													   Each time card++ is called, it goes to the next possible combination. 1113->1121. Overflows back to 1111)
		/*!
		* \return card object
		*/
		card& operator++();

		//! Sets value of this object equal to passed card 
		/*!
		* \param const card Card object being set equal to
		* \return card object
		*/
		card& operator=(const card&);

	private:
		int number; //!< Parameter from 1-3 representing number
		int symbol; //!< Parameter from 1-3 representing symbol
		int shading; //!< Parameter from 1-3 representing shading
		int color; //!< Parameter from 1-3 representing color
};

//! Prints all 4 parameters of card object to console
/*!
* \param ostream& ostream object
* \param const card& Card object being printed
* \return ostream&
*/
std::ostream& operator<<(std::ostream&, const card&);

#endif // !CARD_H