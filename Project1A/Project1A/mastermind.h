/**
* \class mastermind
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

#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "code.h"
#include "response.h"

class mastermind
{
public:
	//! Empty constructor for mastermind
	mastermind();

	//! Prints out code key object's values
	void printSecretCode() const;

	//! Prompts user to enter guess
	void humanGuess();
	//! Prompts user to set keycode
	void humanSetKey();
	

	//! Gets response from codes passed
	/*!
	* \param code& Code object designated as key
	* \param const code& Code object designated as guess
	* \return Response Response of key and guess
	*/
	response getResponse(code&, const code&) const;
	
	//! Checks if response passed is solved
	/*!
	* \param const reponse& Response object being checked
	* \return True if response& is (4,0)/Solved. False otherwise.
	*/
	bool isSolved(const response&) const;

	/*
	code getCodeFromStoredVector(int) const;
	void setCodeFromStoredVector(const code&, int);

	response getResponseFromStoredVector(int) const;
	void setResponseFromStoredVector(const response&, int);*/

	//! Checks if code passed is consistent with previous codes stored in storedGuesses
	/*!
	* \param code& Code being checked against previous guesses
	* \return True if guess is consistent with previous guesses. False otherwise.
	*/
	bool consistentWithPreviousGuesses(code&);

	//! Checks if code passed is consistent with previous codes stored in storedGuesses, EXCEPT it checks for a specific response passed to it
	/*!
	* \param code& Code being checked against previous guesses
	* \return True if guess is consistent with previous guesses. False otherwise.
	*/
	//bool consistentWithPreviousGuesses(code&, response&);

	//! Initialises all possible responses in first vector, and its respective storage vector (amount of guesses per response)
	/*!
	* \param vector<response>& Vector of all possible responses
	* \param vector<int>& Vector of amount of guesses per each response
	*/
	void SetListOfResponses(std::vector<response> &, std::vector<int> &);

	//! Returns computer's next guess
	/*!
	* \return code Computer's next guess
	*/
	code agentGuess();


	//! Plays a game of mastermind where the user cracks the computer's code
	void playGame();
	//! Plays a game of mastermind where the computer cracks the user's code
	void playGame2();
private:
	code key; //!< Code object where the key is stored
	code guess; //!< Code object where the user's guess is stored
	response keyR; //!< Response object where the correct key response is stored
	response guessR; //!< Response object where the user's response is stored

	std::vector<code> S; //!< Set of all possible code objects ( initialized in playGame2() )
	std::vector<code> storedGuesses; //!< Stored vector of all previous computer guesses
	std::vector<response> storedResponses; //!< Stored vector of all previous computer guesses' responses
};
#endif // !MASTERMIND_H