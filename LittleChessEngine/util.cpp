#include "util.h"
#include <sstream>

void vector_to_stream(std::ostream& flow){
	//TODO: maybe implement this idk
}

int random_int(const int& a, const int& b)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(a, b);

	return dist(mt);
}

std::vector<std::string> *tokenize_str(const std::string& str, const char& separator)
{
	auto *tokens = new std::vector<std::string>();
	std::stringstream ss(str);
	std::string word;
	while (!ss.eof()) {
		ss >> word;
		if(word.size())
			tokens->push_back(word);
	}
	return tokens;
}
