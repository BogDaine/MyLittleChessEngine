#include "util.h"

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