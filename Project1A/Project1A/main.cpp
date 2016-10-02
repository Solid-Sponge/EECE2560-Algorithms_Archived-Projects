/**
* @file Projct #1a
* @author  Michael Rossi <rossisantomauro.m@husky.neu.edu>
* @version 1.0
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details at
* https://www.gnu.org/copyleft/gpl.html
*
*/

#include "code.h"
#include "response.h"
#include "mastermind.h"

int main()
{
	mastermind game;
	std::cout << "Welcome to Mastermind. Type 0 to play as the codebreaker, or 1 to play\n as the codemaker." << std::endl;
	int response;
	try
	{
		if (std::cin >> response)
		{
		}
		else
		{
			throw 1;
		}
	}
	catch (int e)
	{
		std::cout << "INVALID INPUT (NOT 0 OR 1)" << std::endl;
		exit(0);
	}
	if (response == 0)
	{
		game.playGame();
	}
	else if (response == 1)
	{
		game.playGame2();
	}
	else
	{
		std::cout << "INVALID INPUT (NOT 0 or 1)" << std::endl;
	}
}