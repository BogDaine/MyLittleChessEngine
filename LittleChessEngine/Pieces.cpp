#include "Pieces.h"

static const char* pieces_ascii = ".PNBRQKpnbrqkO";

static std::unordered_map<int, PieceProps> pieceP =
{
	//-----------------------------------------------------------------------------------------------------------
	std::make_pair<int, PieceProps>(WP, {P_PAWN, WHITE}),

	std::make_pair<int, PieceProps>(WN, {P_KNIGHT, WHITE}),

	std::make_pair<int, PieceProps>(WB, {P_SLIDING | P_MOVE_DIAG, WHITE}),

	std::make_pair<int, PieceProps>(WR, {P_SLIDING | P_MOVE_STRAIGHT, WHITE}),

	std::make_pair<int, PieceProps>(WQ, {	P_SLIDING | P_MOVE_DIAG | P_MOVE_STRAIGHT, WHITE}),

	std::make_pair<int, PieceProps>(WK, {P_MOVE_DIAG | P_MOVE_STRAIGHT, WHITE}),
	//-----------------------------------------------------------------------------------------------------------
	std::make_pair<int, PieceProps>(BP, {P_PAWN, BLACK}),

	std::make_pair<int, PieceProps>(BN, {P_KNIGHT, BLACK}),

	std::make_pair<int, PieceProps>(BB, {P_SLIDING | P_MOVE_DIAG, BLACK}),

	std::make_pair<int, PieceProps>(BR, {P_SLIDING | P_MOVE_STRAIGHT, BLACK}),

	std::make_pair<int, PieceProps>(BQ, {	P_SLIDING | P_MOVE_DIAG | P_MOVE_STRAIGHT, BLACK}),

	std::make_pair<int, PieceProps>(BK, {P_MOVE_DIAG | P_MOVE_STRAIGHT, BLACK}),
	//-----------------------------------------------------------------------------------------------------------
	std::make_pair<int, PieceProps>(E, {0, -1}),
	std::make_pair<int, PieceProps>(O, {0, -1})
};

PieceProps piece_props(const int& piece) {
	return pieceP[piece];
}

bool is_piece(const int& piece)
{
	return pieceP.find(piece) != pieceP.end();
}

bool is_piece(const char& piece)
{
	return strchr("PNBRQKpnbrqk", piece);
}

char piece_ascii(const int& piece)
{
	_ASSERT(piece >= 0 && piece < 14);
	return pieces_ascii[piece];
}

int fen_piece_to_piece(const char& piece)
{
	int value;
	switch (piece) {
	case 'P':
		value = WP;
		break;
	case 'N':
		value = WN;
		break;
	case 'B':
		value = WB;
		break;
	case 'R':
		value = WR;
		break;
	case 'Q':
		value = WQ;
		break;
	case 'K':
		value = WK;
		break;

	case 'p':
		value = BP;
		break;
	case 'n':
		value = BN;
		break;
	case 'b':
		value = BB;
		break;
	case 'r':
		value = BR;
		break;
	case 'q':
		value = BQ;
		break;
	case 'k':
		value = BK;
		break;

	default:value = -1;
	}
	return value;
}
