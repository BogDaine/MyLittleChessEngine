#include "Eval.h"

Move random_move()
{
	auto moves = legal_moves();
	int moveIndex = random_int(0, moves.size()-1);
	return moves[moveIndex];
}

int eval()
{
	float whiteMat = 0, blackMat = 0;
	//float e = material(whiteMat, blackMat);
	int e = get_material(WHITE)+get_material(BLACK);
	return e;
}



//float material(float& white, float& black)
//{
//	float mat = white = black = 0.f;
//
//	for (int i = 0; i < 128; i++) {
//		if (!(i & 0x88)) {
//			int pv = piece_val(board[i]);
//			mat += pv;
//			if (board[i] < BP)
//				white += pv;
//			else black -= pv;
//		}
//		else i += 7;
//	}
//	return mat;
//}
