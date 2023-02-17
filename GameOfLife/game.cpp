#include "game.hpp"
#include <random>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
#include <conio.h>
#include <chrono>
using std::chrono::system_clock;
#include <thread>
using namespace std::this_thread;
//#include <Windows.h>
#include "adt_exception.hpp"
using data_structures::AdtException;

static const int NUM_BOARDS = 5;

Game::Game()
{
	
}

Game::~Game()
{
	delete[] board_storage_;
}

Game::Game(const Game& copy)
{
	*this = copy;
}

Game& Game::operator=(const Game& rhs)
{
	if (this != &rhs)
	{
		board_ = rhs.board_;
		
		delete[] board_storage_;
		board_storage_ = nullptr;

		board_storage_ = new Array2D<char>[NUM_BOARDS];
		for (auto i{ 0 }; i < NUM_BOARDS; ++i)
			board_storage_[i] = rhs.board_storage_[i];
		
		board_storage_counter_ = rhs.board_storage_counter_;
		
	}
	return *this;
}

Game::Game(Game&& copy)
{
	*this = std::move(copy);
}

Game& Game::operator=(Game&& rhs)
{
	if (this != &rhs)
	{
		board_ = std::move(rhs.board_);
		board_storage_counter_ = rhs.board_storage_counter_;
		
		delete[] board_storage_;
		board_storage_ = rhs.board_storage_;

		rhs.board_storage_ = nullptr;
		
	}
	return *this;
}

void Game::Start()
{
	auto rows{ 0 };
	auto cols{ 0 };
	int choice{};
	auto manual{ false };
	auto file{ false };

	system("cls");
	cout << "Game of Life" << endl;

	do
	{
		cout << "Read Grid from File?: " << endl;;
		cout << "1) Yes" << endl;
		cout << "2) No" << endl;
		cin >> choice;
	} while (choice != 1 && choice != 2);
	
	if (choice == 1)
		file = true;

	if (file)
		CreateBoard();
	else
	{
		cout << "Enter the number of Rows: ";
		cin >> rows;
		cout << "Enter the number of Columns: ";
		cin >> cols;

		if (rows < 1 | cols < 1)
			throw AdtException("Error: Rows and Columns must be greater than zero");
		CreateBoard(rows, cols);
	}

	// reset choice since it is used for previous menu
	choice = 0;
	do
	{
		
		cout << "Manual or Automatic Mode:" << endl;
		cout << "1) Manual" << endl;
		cout << "2) Automatic" << endl;
		cin >> choice;
	} while (choice != 1 && choice != 2);
	
	if (choice == 1)
		manual = true;
	

	PlayGame(manual);
	
}

void Game::CreateBoard(const size_t& row, const size_t& col)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_int_distribution<int> dis(0, 1);

	board_ = Array2D<char>{ row, col };

	for (size_t i{ 0 }; i < row; ++i)
	{
		for (size_t k{ 0 }; k < col; ++k)
		{
			const int random_number = dis(gen);
			if (random_number == 0)
				board_[i][k] = '-';
			else 
				board_[i][k] = 'X';

		}
	}
}

void Game::CreateBoard()
{
	size_t row{};
	size_t col{};
	size_t row_counter{};
	size_t col_counter{};
	char storage{};
	ifstream data_file;
	data_file.open("grid.txt");
	
	
	if (data_file.is_open())
	{
		data_file >> row >> col;
		board_ = Array2D<char>{ row, col };


		for (size_t i{}; i < row; ++i)
			for (size_t k{}; k < col; ++k)
			{
				data_file >> storage;
				if (storage == 'X')
					board_[i][k] = 'X';
				else if (storage == '-')
					board_[i][k] = '-';
				else
					throw AdtException("Error: Failure reading data from file");
			}
		data_file.close();
		
	}
	else
	{
		throw AdtException("Error: Unable to open file");
	}
}


void Game::DisplayBoard()
{
	for (size_t i{ 0 }; i < board_.Rows(); ++i)
	{
		for (size_t k{ 0 }; k < board_.Columns(); ++k)
		{
			cout << board_[i][k] << " ";
		}
		cout << endl;
	}	
}

void Game::PlayGame(const bool& manual)
{
	auto iteration{1};
	auto game_over{ false };
	auto simulation_speed{ 0 };

	if (!manual)
	{
		do
		{
			cout << "Enter Simulation Speed in Milliseconds: ";
			cin >> simulation_speed;
		} while (simulation_speed < 0);
	}
	
	while (!game_over)
	{
		auto num{ 0 };
		
		cout << "Generation #" << iteration++ << endl;
		
		DisplayBoard();

		if (manual)
		{
			do
			{
				cout << "1) Continue: ";
				cin >> num;
			} while (num != 1);
			
		}
		
		// Creates a new board based on the prior one
		Generation();

		if (CheckDuplicates())
		{
			cout << "Repeating Generations found. Exiting game.";
			game_over = true;
		}
		
		if (_kbhit() != 0)
		{
			cout << "STOPPING LOOP" << endl;
			cout << "Press C to continue or E to end simulation" << endl;
			switch (cin.get())
			{
			case 'C':
				system("cls");
				continue;
			case 'E':
				game_over = true;
			}
		}

		if (!manual && !game_over)
			sleep_until(system_clock::now() + std::chrono::milliseconds(simulation_speed));

		if (!game_over)
			system("cls");
	}
}

void Game::Generation()
{
	// Store current board
	auto temp = board_;
	
	for (auto i{ 0 }; i < temp.Rows(); ++i)
	{
		for (auto k{ 0 }; k < temp.Columns(); ++k)
		{
			auto count{ 0 };
			// position diagonal above and left
			if (InBounds(i - 1 , k - 1 ))
			{
				if (temp[i - 1][k - 1 ] == 'X')
					count++;
			}

			// position above
			if (InBounds(i - 1, k))
			{
				if (temp[i - 1][k] == 'X')
					count++;
			}

			// position diagonal above and right
			if (InBounds(i - 1, k + 1))
			{
				if (temp[i - 1][k + 1] == 'X')
					count++;
			}

			// position right
			if (InBounds(i, k + 1))
			{
				if (temp[i][k + 1] == 'X')
					count++;
			}

			// position diagonal right and below
			if (InBounds(i + 1, k + 1))
			{
				if (temp[i + 1][k + 1] == 'X')
					count++;
			}

			// position below
			if (InBounds(i + 1, k))
			{
				if (temp[i + 1][k] == 'X')
					count++;
			}

			// position diagonal below and left
			if (InBounds( i + 1, k - 1))
			{
				if (temp[i + 1][k - 1] == 'X')
					count++;
			}

			// position left
			if (InBounds(i, k - 1))
			{
				if (temp[i][k - 1] == 'X')
					count++;
			}

			// modify current board based on stored temp board
			if (temp[i][k] == 'X')
			{
				// lonely or overcrowded
				if (count < 2 || count > 3 && count < 9)
					board_[i][k] = '-';
			}
			else
			{
				// cell is born if three neighbors
				if (count == 3)
					board_[i][k] = 'X';
			}
		}
	}
	board_storage_[board_storage_counter_ % NUM_BOARDS] = temp;
	board_storage_counter_++;
}

bool Game::InBounds(const int& x, const int& y) const
{
	return x >= 0 && x < board_.Rows() && y >= 0 && y < board_.Columns();
}

bool Game::CheckDuplicates() const
{
	for (auto i{ 0 }; i < NUM_BOARDS; ++i)
		if (board_ == board_storage_[i])
			return true;
	// duplicate was not found
	return false;
}



