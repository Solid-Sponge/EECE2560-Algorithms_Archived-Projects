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

#include "mastermind.h"
#include <algorithm>

mastermind::mastermind() //!< Empty constructor
{

}
void mastermind::printSecretCode() const //!< Prints out key object 
{
	std::cout << "(Secret Code is: ";
	key.printCode();
	std::cout << ")" << std::endl;
}

void mastermind::humanGuess()
{
	int code = 0;
	try
	{
		if (std::cin >> code)//!< Prompts user to enter code exactly as written ([1,2,3,4] would be written to console as 1234)
		{
		}
		else
		{
			throw 1;
		}
	}
	catch (int e)
	{
		std::cout << "INVALID INPUT (NOT AN INT)" << std::endl;
		exit(0);
	}
	int d = code % 10; //!< Seperates each digit entered previously into seperate ints
	int c = code / 10 % 10;
	int b = code / 100 % 10;
	int a = code / 1000 % 10;
	try {
		if ((a > 5 || b > 5 || c > 5 || d > 5) || (a < 0 || b < 0 || c < 0 || d < 0))
		{
			throw 2;
		}
		if ((code / 10000 % 10) != 0)
		{
			throw 3;
		}
	}
	catch (int e)
	{
		std::cout << "INVALID INPUT (CODE VALUES NOT BETWEEN 0 AND 5 OR CODE GREATER THAN 4 DIGITS)" << std::endl;
		exit(0);
	}
	guess.setCode(a, b, c, d); //!< Sets each seperate ints into the code guess object
}
void mastermind::humanSetKey()
{
	int code = 0;
	try
	{
		if (std::cin >> code)//!< Prompts user to enter code exactly as written ([1,2,3,4] would be written to console as 1234)
		{ }
		else
		{
			throw 1;
		}
	}
	catch (int e)
	{
			std::cout << "INVALID INPUT (NOT AN INT)" << std::endl;
			exit(0);
	}
	int d = code % 10; //!< Seperates each digit entered previously into seperate ints
	int c = code / 10 % 10;
	int b = code / 100 % 10;
	int a = code / 1000 % 10;
	try {
		if ( (a > 5 || b > 5 || c > 5 || d > 5) || (a < 0 || b < 0 || c < 0 || d < 0))
		{
			throw 2;
		}
		if ((code / 10000 % 10) != 0)
		{
			throw 3;
		}
	}
	catch (int e)
	{
		std::cout << "INVALID INPUT (CODE VALUES NOT BETWEEN 0 AND 5 OR CODE GREATER THAN 4 DIGITS)" << std::endl;
		exit(0);
	}
	key.setCode(a, b, c, d); //!< Sets each seperate ints into the code guess object
}


response mastermind::getResponse(code &key, const code &guess) const
{
	response key_guess; //!< Instantiates a response object
	int nCorrect = 0; //!< Instantites an int corresponding to the number of digits correct
	int nIncorrect = 0; //!< Instantites an int corresponding to the number of digits correct in incorrect spot
	nCorrect = key.checkCorrect(guess); //!< Sets nCorrect equal to the amount of correct digits in guess compared to key
	nIncorrect = key.checkIncorrect(guess); //!< Sets nIncorrect equal to the amount of correct digits in incorrect spots in guess compared to key
	key_guess.set_numCorrect(nCorrect); //!< Stores value of nCorrect in response object's private member numCorrect
	key_guess.set_numIncorrect(nIncorrect);//!< Stores value of nIncorrect in response object's private member numIncorrect
	return key_guess; //!< Returns response object
}

bool mastermind::isSolved(const response &attempt) const
{
	if (attempt.get_numCorrect() == 4) //!< Returns true if the response object being passed to has a 4 in its private member numCorrect
		return true;
	return false;
}

bool mastermind::consistentWithPreviousGuesses(code& cGuess)
{
	response temp; //!< Creates temporary response object
	for (int i = 0; i < storedGuesses.size(); i++) //!< Goes through list of previously guessed guesses
	{
		temp = getResponse(cGuess, storedGuesses[i]); //!< Compares passed guess with previous guesses and stores response into temp
		if (storedResponses[i] == temp) //!< If the results are equal, the guess has a chance of being consistant with the previous guesses
		{

		}
		else
		return false; //!< The moment the responses aren't equal, the code is considered inconsistant
	}
	return true; //!< If all results are equal, the code is consistant
}

void mastermind::SetListOfResponses(std::vector<response> & ListOfResponses, std::vector<int> & ListOfResponsesCount)
{
	try
	{
		if (ListOfResponses.size() > 0 || ListOfResponsesCount.size() > 0)
		{
			throw 1;
		}
	}
	catch (int e)
	{
		std::cout << "EXCEPTION THROWN: VECTORS NOT EMPTY" << std::endl;
		exit(0);
	}

	response tempR(0, 0); //!< Creates temporary response object with values 0,0
	ListOfResponses.push_back(tempR); //!<Pushes it into a vector of responses

	tempR.set_numCorrect(0); //!< Reassignes temporary response object with values 0,1
	tempR.set_numIncorrect(1); //!< Pushes it into a vector of responses
	ListOfResponses.push_back(tempR);
	
	tempR.set_numCorrect(0); //!< Essentially pushes all possible responses (0,0) - (4,0) into a passed array ListOfResponses
	tempR.set_numIncorrect(2);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(0);
	tempR.set_numIncorrect(3);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(0);
	tempR.set_numIncorrect(4);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(1);
	tempR.set_numIncorrect(0);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(1);
	tempR.set_numIncorrect(1);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(1);
	tempR.set_numIncorrect(2);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(1);
	tempR.set_numIncorrect(3);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(2);
	tempR.set_numIncorrect(0);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(2);
	tempR.set_numIncorrect(1);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(2);
	tempR.set_numIncorrect(2);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(3);
	tempR.set_numIncorrect(0);
	ListOfResponses.push_back(tempR);

	tempR.set_numCorrect(4);
	tempR.set_numIncorrect(0);
	ListOfResponses.push_back(tempR);

	for (int i = 0; i < 14; i++) //!< Initializes empty ListOfResponseCount to fourteen 0's
	{
		ListOfResponsesCount.push_back(0);
	}
}

code mastermind::agentGuess()
{
	int i = 0; 
	std::vector<code> Candidates; //!< List of consistant candidate guesses
	std::vector<int> WorstCaseCandidatesScore; //!< Each possible candidate's "score" as defined in the project 1b pdf
	std::vector<response> ListOfResponses; //!< Empty vector of responses, which will be initalized to contain each possible response
	std::vector<int> ListOfResponsesCount; //!< Empty vector of ints, which correspond to each responses' score, the worst of which will be taken as the individual candidate's score
	SetListOfResponses(ListOfResponses, ListOfResponsesCount); //!< Initialies both ListOfResponses to contain all possible responses, as well as ListOfResponsesCount;
	while (i < S.size()) //!<Checks the entire set of possible codes S from 0000-5555
	{
		if (consistentWithPreviousGuesses(S[i])) //!< If a code is consistant with previous guesses, it gets pushed onto Candidates
		{
			Candidates.push_back(S[i]);
		}
			i++;
	}

	for (int a = 0; a < Candidates.size(); a++) //!< Goes through each candidate guess in order to determine which candidate will remove the most possible guesses
	{
			storedGuesses.push_back(Candidates[a]); //!< Temporarily pushes a candidate onto the storedGuesses vector
			for (int k = 0; k < 14; k++) //!< Goes through each possible response the candidate could have
			{
				storedResponses.push_back(ListOfResponses[k]); //!< Temporarily pushes a response onto the storedResponses vector
				int z = 0;
				while (z < Candidates.size()) //!< Goes through the sample set Candidates testing for how many guesses remain consistant
				{
					if (consistentWithPreviousGuesses(Candidates[z]))
					{
						ListOfResponsesCount[k]++; //!< Pushes # of consistant guesses onto ListOfResponsesCount, each element in ListOfResponsesCount corresponds to a single response
					}
					z++;
				}
				storedResponses.pop_back(); //!< Pops out the response
			}
			int ResponseindexValue = (std::max_element(ListOfResponsesCount.begin(), ListOfResponsesCount.end()) - ListOfResponsesCount.begin()); //!< Finds the index value of the biggest score of
																																				  //!< all responses
			WorstCaseCandidatesScore.push_back(ListOfResponsesCount[ResponseindexValue]); //!< Pushes the score onto WorstCaseCandidatesScore, each element in this vector corresponds to its respective
																						  //!< candidate
			storedGuesses.pop_back(); //!< Pops out the candidate
			for (int clear = 0; clear < 14; clear++) //!< Clears out the score response vector in order to use it with another guess
			{
				ListOfResponsesCount[clear] = 0;
			}
	}

	int indexValue = (std::min_element(WorstCaseCandidatesScore.begin(), WorstCaseCandidatesScore.end()) - WorstCaseCandidatesScore.begin()); //!< Goes through WorstCaseCandidatesScore and finds
																																			  //!< the index value of the guess with the smallest score
	return Candidates[indexValue]; //!< Returns the guess itself with the smallest possible score
}

void mastermind::playGame()
{
	srand(time(NULL)); //!< Seeds the PRNG
	keyR.set_numCorrect(4); //!< Sets the correct win condition values (key Response must have 4 numbers correct and 0 numbers incorrect)
	keyR.set_numIncorrect(0);
	int a = 0, b = 0, c = 0, d = 0; //!< Instantiates a bunch of ints used as a sort of "multiplexor" to convert a 4-digit int into 4 int components
	int code = 0; //!< Instantiates int code used to store user's guess as a 4-digit int
	int attempts = 10; //!< Sets the ammount of attempts given to crack code
	std::cout << "Welcome to the game of Mastermind. The object is to crack a 4-digit code with " << std::endl;
	std::cout << "each digit from 0-5.You get 10 attempts, but you're not going in completely " << std::endl;
	std::cout << "blind. Each time you enter a code, the computer returns the number of digits " << std::endl;
	std::cout << "you got correct in the right spot, as well as the amount of digits you got " << std::endl;
	std::cout << "that were in the code but were in the wrong spot. Keep in mind that " << std::endl;
	std::cout << "duplicates don't count. For instance, if the secret code is [1234], and your " << std::endl;
	std::cout << "guess is [2122], you would get 0 digits correct, and 2 digits in the wrong " << std::endl;
	std::cout << "spot(the extra 2's don't count). With that said, the game will now begin!" << std::endl << std::endl;
	while (true) //!< Infinite loop to keep the game playing
	{
		attempts = 10; //!< Resets the attempts to 10 each time the game is replayed
		key.randomizeCode(); //!< Randomizes key code
		printSecretCode(); //!< Prints the key code in order to test program
		std::cout << "CODE RANDOMIZED: GAME START" << std::endl;
		while (attempts != 0) //!< Checks if user has any attempts left
		{
			humanGuess();
			guessR = getResponse(key, guess); //!< Sets response guessR object equal to the response object returned from getResponse, after passing both the key and guess to it
			if (isSolved(guessR)) //!< Passes the guessR object to isSolved. Returns true if guessR has a 4 in numCorrect
			{
				std::cout << "YOU CRACKED IT!" << std::endl << std::endl; //!< Celeberatory message indicating the user has cracked the code
				attempts = 0; //!< Sets the attempt to 0 in order to restart the loop with a new key
			}
			else
			{
				if (attempts == 1) //!< If this was the last user attempt, a demeaning message plays indicating the user has failed in cracking the code
				{
					guessR.printResponse(); //!< Prints out how many digits they got right
					std::cout << "GAME OVER" << std::endl << std::endl;
					attempts--;
				}
				else //!< Otherwise, it outputs how many attempts the user has left after printing out how many digits they got right
				{
					guessR.printResponse();
					attempts--;
					std::cout << attempts << " attempts left." << std::endl;
				}
			}
		}
	}
}
void mastermind::playGame2()
{
	code temp(0, 0, 0, 0); //!< Creates a temporary code object
	response test(0, 0); //!< Creates test response
	response cracked(4, 0); //!< Creates code cracked response to compare against

	for (int i = 0; i < 1296; i++) //!< Initialises Set S of all possible code combinations
	{
		
		S.push_back(temp);
		temp.increment();
	}
	while (true) {
		std::cout << "Enter the secret code for the computer to crack: ";
		humanSetKey(); //!< Gets user's input and stores it as secret code
		
		guess.setCode(0, 0, 1, 1); //!< Computer's first initial guess will always be 0011
		test = getResponse(key, guess); //!< Stores response to initial guess into test
		storedGuesses.push_back(guess); //!< Pushes guess into previously stored guesses's storage
		storedResponses.push_back(test); //!< Pushes test response into previously stored response's storage
		std::cout << guess; //!< Outputs computer's guess (always 0011 in this case)
		std::cout << "   " << test << std::endl; //!< Outputs response to computer's guess

		while (!isSolved(test)) //!< Checks if test response is correct
		{
			guess = agentGuess(); //!< Calles agentGuess(), the function responsible for calculating the computer's next guess
			std::cout << guess; //!< Outputs computer's guess to console

			test = getResponse(key, guess); //!< Stores response of guess into test
			std::cout << "   " << test << std::endl; //!< Outputs response to computer's guess
			if (!isSolved(test)) //!< Checks if code is cracked with test response
			{
				storedGuesses.push_back(guess); //!< If code isn't cracked, adds guess to list of previous guesses
				storedResponses.push_back(test); //!< If code isn't cracked, adds response to list of previous responses
			}
		}
		std::cout << "CODE CRACKED" << std::endl;
		storedGuesses.clear(); //!< Clears list of previous guesses
		storedResponses.clear(); //!< Clears list of previous responses
	}
}
