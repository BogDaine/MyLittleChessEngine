#include "Search.h"

long perft(const int& maxDepth, const int& depth)
{
	if (depth == maxDepth)
	{
		return 1;
	}

	//std::cout << "DEPTH: " << depth << std::endl;

	int counter = 0;

	auto moves = legal_moves();
	if (moves.size() == 0)
		return 0;
	auto ms = get_moveStack();

	//stiu ca e duplicate code

	if (depth == 0) {
		for (auto& x : moves) {
			x.print(true);
			std::cout << ": ";

			make_move(x);
			int nodes = perft(maxDepth, depth + 1);

			counter += nodes;
			unmake_move();

			std::cout << nodes << std::endl;
		}
	}
	else {
		for (auto& x : moves) {
			make_move(x);
			counter += perft(maxDepth, depth + 1);
			unmake_move();
		}
	}
	return counter;
}