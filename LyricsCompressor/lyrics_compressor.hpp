#ifndef LYRICS_COMPRESSOR_HPP
#define LYRICS_COMPRESSOR_HPP
#include "hash_map.hpp"
using data_structures::HashMap;
static const size_t table_size_ = 53;

class LyricsCompressor
{
public:
	LyricsCompressor() = delete;
	~LyricsCompressor() = default;
	LyricsCompressor(const function<int(const string& key)>& hash_function);
	LyricsCompressor(const LyricsCompressor& copy);
	LyricsCompressor& operator=(const LyricsCompressor& rhs);
	LyricsCompressor(LyricsCompressor&& copy);
	LyricsCompressor& operator=(LyricsCompressor&& rhs);

	void Start();
private:
	HashMap<string, list<int>> map_;
	function<int(const string&)> hash_function_{ nullptr };
	int output_word_counter_{ 0 };
	int num_words_{ 0 };
	
	void ReadFile();
	void OutputFile();
	void Print();
};



#endif
