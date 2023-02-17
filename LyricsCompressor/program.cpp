#include <iostream>
#include "lyrics_compressor.hpp"
using std::cout;
using std::cin;
using std::endl;

function<int(const string& key)> ascii_hash_functions_ = [&](const string& key) -> int
{
	auto sum = 0;
	for (const auto& ch : key)
	{
		sum += ch;
	}
	return static_cast<int>(sum % table_size_);
};


int main()
{
	LyricsCompressor compressor(ascii_hash_functions_);
	auto choice{ 0 };
	auto error{ false };
	do
	{
		if (!error)
			compressor.Start();
		
		cout << "\nContinue Running?" << std::endl;
		cout << "1: Yes\n2: No" << std::endl;
		error = false;
		std::cin >> choice;
		if (cin.fail())
		{
			cout << "Error: Integer Input Required" << endl;;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			error = true;
			choice = 1;
		}
	} while (choice == 1);
	
	cout << "\nExiting Program" << std::endl;
	return 0;
}

