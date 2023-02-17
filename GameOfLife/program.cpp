#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using std::cout;

#include "game.hpp"
#include "adt_exception.hpp"
using data_structures::AdtException;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	auto choice{ 0 };
	auto done{ false };
	Game game;
	try
	{
		
		while (!done)
		{
			game.Start();
			do
			{
				cout << "\nPlay again?" << std::endl;
				cout << "1) Yes" << std::endl;
				cout << "2) No" << std::endl;
				std::cin >> choice;
			} while (choice != 1 && choice != 2);
			if (choice == 1)
				done = false;
			else
				done = true;
		}
	}
	catch(AdtException& err)
	{
		cout << err.what();
	}
}

