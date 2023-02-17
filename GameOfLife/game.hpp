#ifndef GAME_HPP
#define GAME_HPP

#include "array2d.hpp"
using data_structures::Array2D;
#include "array.hpp"
using data_structures::Array;

class Game
{
public:
	Game();
	~Game();
	Game(const Game& copy);
	Game& operator=(const Game& rhs);
	Game(Game&& copy);
	Game& operator=(Game&& rhs);
	

	void Start();
private:
	Array2D<char> board_;
	Array2D<char>* board_storage_ = new Array2D<char>[5];
	size_t board_storage_counter_{ 0 };
	
	void CreateBoard(const size_t& row, const size_t& col);
	void CreateBoard();
	void DisplayBoard();
	void PlayGame(const bool& manual);
	void Generation();
	bool InBounds(const int& x, const int& y) const;
	bool CheckDuplicates() const;
};



#endif 
