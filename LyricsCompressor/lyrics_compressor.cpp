#define _CRT_SECURE_NO_WARNINGS
#include "lyrics_compressor.hpp"
#include <iostream>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::cin;

function<list<int>()> create_function = [&]() -> list<int>
{
	return list<int>();
};

LyricsCompressor::LyricsCompressor(const function<int(const string& key)>& hash_function)
	:map_(table_size_, hash_function), hash_function_(hash_function)
{
	
}

LyricsCompressor::LyricsCompressor(const LyricsCompressor& copy)
	: map_(copy.map_), hash_function_(copy.hash_function_),
	output_word_counter_(copy.output_word_counter_), num_words_(copy.num_words_)
{
	
}

LyricsCompressor& LyricsCompressor::operator=(const LyricsCompressor& rhs)
{
	if (this != &rhs)
	{
		map_ = rhs.map_;
		hash_function_ = rhs.hash_function_;
		num_words_ = rhs.num_words_;
		output_word_counter_ = rhs.output_word_counter_;
	}
	return *this;
}

LyricsCompressor::LyricsCompressor(LyricsCompressor&& copy)
	: map_(std::move(copy.map_)), hash_function_(std::move(copy.hash_function_)),
	output_word_counter_(copy.output_word_counter_), num_words_(copy.num_words_)
{
	
}

LyricsCompressor& LyricsCompressor::operator=(LyricsCompressor&& rhs)
{
	if (this != &rhs)
	{
		map_ = std::move(rhs.map_);
		hash_function_ = std::move(rhs.hash_function_);
		rhs.hash_function_ = nullptr;
		num_words_ = rhs.num_words_;
		output_word_counter_ = rhs.output_word_counter_;
	}
	return *this;
}

void LyricsCompressor::Start()
{
	int choice{};
	cout << "Lyrics Compressor" << endl;
	do
	{
		cout << "1: Compress File" << endl;
		cout << "2: Print Words and Positions" << endl;
		cout << "3: Decompress to Output File" << endl;
		cin >> choice;

		if (cin.fail())
		{
			cout << "Error: Integer Input Required" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
	} while (choice > 4 | choice < 1);

	
	switch (choice)
	{
	case 1:
		ReadFile();
		break;
	case 2:
		Print();
		break;
	case 3:
		OutputFile();
	}
}

void LyricsCompressor::ReadFile()
{
	// Create a new LyricsCompressor object in case the user decides to read the same file in
	// multiple times in a row
	*this = LyricsCompressor(hash_function_);
	string file_name;
	ifstream file;
	cout << "Enter File Name to Compress: " << endl;
	cout << "Default File Name is song.txt" << endl << "File Name:";
	cin >> file_name;
	
	file.open(file_name);
	
	cout << "\nReading Input File" << endl;

	if (file.is_open())
	{
		while (!file.eof())
		{
			list<string> list;
			char buffer[256];
			char buffer_test[] = { "" };
			file.getline(buffer, 256);

			char* temp = strtok(buffer, " ");

			while (temp != nullptr)
			{
				list.emplace_back(temp);
				temp = strtok(nullptr, " ");
			}

			if (file.peek() == '\n')
			{
				const string s = "\n";
				list.emplace_back(s);
			}
			for (auto i : list)
			{
				if (i == list.back())
				{
					auto temp = -num_words_;
					map_.GetOrAdd(i, create_function);
					map_[i].emplace_back(temp);
					num_words_++;
				}
				else
				{
					map_.GetOrAdd(i, create_function);
					map_[i].emplace_back(num_words_++);
				}
			}
		}
	}
	else
	{
		cout << "Error: Invalid File Name" << endl;
	}

}

void LyricsCompressor::OutputFile()
{
	ofstream output;
	string file_name;
	
	const auto output_function = [&](const string& key, const list<int>& list)
	{
		for (auto i : list)
		{
			if (i == output_word_counter_)
			{
				output << key << ' ';
				++output_word_counter_;
			}
			else if (i == -output_word_counter_)
			{
				output << key << "\n";
				++output_word_counter_;
			}
		}
	};

	if (map_.Count() == 0)
		cout << "Error: No Song Compressed Into Memory" << endl;
	else
	{
		cout << "Enter Name of File to Decompress: ";
		cin >> file_name;
		output.open(file_name);
		while (output_word_counter_ < num_words_)
			map_.Traverse(output_function);

		output.close();
		output_word_counter_ = 0;
	}
}

void LyricsCompressor::Print()
{
	const auto print_function = [&](const string& key, const list<int>& list)
	{
		cout << "Word: " << key << "\nPosition: ";
		for (auto i : list)
		{
			cout << i << ' ';
		}
		cout << std::endl;
	};

	if (map_.Count() == 0)
		cout << "Error: No Song Compressed Into Memory" << endl;
	else
		map_.Traverse(print_function);
}
