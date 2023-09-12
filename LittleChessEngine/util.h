#pragma once

#include <vector>
#include <iostream>
#include <random>

template <typename T>
void vector_to_stream(std::vector<T> v, std::ostream& flow){
	for (auto x : v)
		flow << x << ' ';
	flow << std::endl;
}
int random_int(const int& a, const int& b);