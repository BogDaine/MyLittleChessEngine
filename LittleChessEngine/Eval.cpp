#include "Eval.h"

Move random_move()
{
	auto moves = legal_moves();
	int moveIndex = random_int(0, moves.size()-1);
	return moves[moveIndex];
}

float eval()
{
	float whiteMat = 0, blackMat = 0;
	float e = material(whiteMat, blackMat);
	return e;
}

float piece_val(const int& piece)
{
	//TODO: array these

	switch (piece) {
	case WP:
		return 1.f;
	case WN:
		return 3.f;
	case WB:
		return 3.f;
	case WR:
		return 10.f;
	case WQ:
		return 20.f;
	case WK:
		return 500.f;


	case BP:
		return -1.f;
	case BN:
		return -3.f;
	case BB:
		return -3.f;
	case BR:
		return -10.f;
	case BQ:
		return -20.f;
	case BK:
		return -500.f;
	default:
		return 0.0f;
	}
}

float material(float& white, float& black)
{
	float mat = white = black = 0.f;

	for (int i = 0; i < 128; i++) {
		if (!(i & 0x88)) {
			int pv = piece_val(board[i]);
			mat += pv;
			if (board[i] < BP)
				white += pv;
			else black -= pv;
		}
		else i += 7;
	}
	return mat;
}
