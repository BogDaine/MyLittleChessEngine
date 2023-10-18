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

int search(const int& depth)
{
	if (depth == 0) {
		return eval() * ((get_stm())?-1:1);
	}
	//int bestEval = (get_stm()) ? -99999999 : 99999999;
	int bestEval = -99999999;
	auto moves = legal_moves();
	if (moves.empty()) {
		if (is_checked(get_stm()))
		{
			return bestEval;
			//return bestEval * ((get_stm()) ? -1 : 1);
		}
		return 0;
	}
	for (int i = 0; i < moves.size(); i++){
		make_move(moves[i]);
		int ev = -search(depth - 1);
		if (ev > 90000000) {
			ev -= 900;
		}
		//bestEval = (get_stm()) ? (MIN(ev, bestEval)):(MAX(ev, bestEval));
		bestEval = MAX(ev, bestEval);
		unmake_move();
	}
	return bestEval;
}

int alphabeta_search(const int& depth, int alpha, int beta)
{
	if (depth == 0) {
		return eval() * ((get_stm()) ? -1 : 1);
	}

	int bestEval = -99999999;
	auto moves = legal_moves();
	if (moves.empty()) {
		if (is_checked(get_stm()))
		{
			return bestEval;
		}
		return 0;
	}

	for (int i = 0; i < moves.size(); i++) {
		make_move(moves[i]);
		int ev = -alphabeta_search(depth - 1, -beta, -alpha);
		
		unmake_move();

		if (ev > 90000000) {
			ev -= 900;
		}

		if (ev >= beta) {
			return beta;
		}

		if (ev > alpha)
		{
			alpha = ev;
		}
	}
	return alpha;
}

int alphabeta_root(const int& depth, int alpha, int beta)
{
	if (depth == 0) {
		return eval() * ((get_stm()) ? -1 : 1);
	}

	int bestEval = -99999999;
	auto moves = legal_moves();
	if (moves.empty()) {
		if (is_checked(get_stm()))
		{
			return bestEval;
		}
		return 0;
	}


	for (auto& m : moves) {
		make_move(m);
		int ev = -alphabeta_search(depth - 1, -beta, -alpha);
		
		unmake_move();

		if (ev > 90000000) {
			ev -= 900;
		}

		if (ev >= beta) {
			return beta;
		}

		if (ev > alpha) {
			the_best_move = m;
			alpha = ev;
		}


		m.print(true);
		std::cout << " - ";
		std::cout << ev << std::endl;
	}
	//std::cout << std::endl;
	//std::cout << "best eval: ";
	//bestmove.print(true);
	//std::cout << " - " << bestEval << std::endl;
	return alpha;
}

Move best_move(const int& depth)
{
	Move bestmove;
	auto moves = legal_moves();
	//int bestEval = (get_stm())? 99999999 : -99999999;
	int bestEval = -99999999;

	for (auto& m : moves) {
		make_move(m);
		int ev = -search(depth - 1);
		if (ev > 90000000) {
			ev -= 900;
		}
		if (ev > bestEval) {
			bestmove = m;
			bestEval = ev;
		}
		//bestEval = MAX(ev, bestEval);
		//bestEval = (get_stm()) ? (MIN(ev, bestEval)) : (MAX(ev, bestEval));
		std::cout << "be: " << bestEval << std::endl;
		/*if (bestEval == ev) {
			bestmove = m;
		}*/

		unmake_move();

		m.print(true);
		std::cout << " - ";
		std::cout << ev << std::endl;
	}
	std::cout << std::endl;
	std::cout << "best eval: ";
	bestmove.print(true);
	std::cout << " - " << bestEval << std::endl;
	return bestmove;
}

Move get_best_move()
{
	return the_best_move;
}
