#pragma once
#include <sstream>

#include "board.h"


std::pair<std::vector<Piece>, std::vector<Piece>> pieces;
static int emptyboard[128] = {
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E, O,O,O,O,O,O,O,O,
};
int board[128] = {
	WR, WN, WB, WQ, WK, WB, WN, WR, O,O,O,O,O,O,O,O,
	WP, WP, WP, WP, WP, WP, WP, WP, O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E,  O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E,  O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E,  O,O,O,O,O,O,O,O,
	E,  E,  E,  E,  E,  E,  E,  E,  O,O,O,O,O,O,O,O,
	BP, BP, BP, BP, BP, BP, BP, BP, O,O,O,O,O,O,O,O,
	BR, BN, BB, BQ, BK, BB, BN, BR, O,O,O,O,O,O,O,O,
};
 
void board_init() {
	load_from_fen(startfen);
}

bool make_move(const Move& m)
{
	//castles
	//White
	if (castle_rights & CASTLERIGHTS_WK || castle_rights & CASTLERIGHTS_WQ) {
		if (board[E1] != WK) {
			castle_rights = castle_rights & ~(CASTLERIGHTS_WK | CASTLERIGHTS_WQ);
		}
		if ((m.from == E1) || ((m.flags & MOVEFLAG_CASTLE_WK) || (m.flags & MOVEFLAG_CASTLE_WQ)))
		{
			if (m.flags & MOVEFLAG_CASTLE_WK) {
				board[H1] = E;
				board[F1] = WR;
			}
			if (m.flags & MOVEFLAG_CASTLE_WQ) {
				board[A1] = E;
				board[D1] = WR;
			}
			castle_rights = castle_rights & ~(CASTLERIGHTS_WK | CASTLERIGHTS_WQ);

		}
		if (m.from == H1 || m.to == H1) {
			castle_rights = castle_rights & ~(CASTLERIGHTS_WK);
		}
		if (m.from == A1 || m.to == A1) {
			castle_rights = castle_rights & ~(CASTLERIGHTS_WQ);
		}
	}

	//Black

	if (castle_rights & CASTLERIGHTS_BK || castle_rights & CASTLERIGHTS_BQ)
	{
		if (board[E8] != BK) {
			castle_rights = castle_rights & ~(CASTLERIGHTS_BK | CASTLERIGHTS_BQ);
		}
		if ((m.from == E8) && ((m.flags & MOVEFLAG_CASTLE_BK) || (m.flags & MOVEFLAG_CASTLE_BQ)))
		{
			if (m.flags & MOVEFLAG_CASTLE_BK) {
				board[H8] = E;
				board[F8] = BR;
			}
			if (m.flags & MOVEFLAG_CASTLE_BQ) {
				board[A8] = E;
				board[D8] = BR;
			}
			castle_rights = castle_rights & ~(CASTLERIGHTS_BK | CASTLERIGHTS_BQ);

		}
		if (m.from == H8 || m.to == H8) {
			castle_rights = castle_rights & ~CASTLERIGHTS_BK;
		}
		if (m.from == A8 || m.to == A8) {
			castle_rights = castle_rights & ~CASTLERIGHTS_BQ;
		}
	}
	stm = !stm;
	if (m.flags & MOVEFLAG_CAPTURE) {
		material[stm] -= piece_val(m.capt);
	}

	//en-passant

	if (m.flags & MOVEFLAG_EP) {
		switch (m.side) {
		case WHITE:
			board[m.ep + SOUTH] = E;
			material[BLACK] -= piece_val(BP);
			break;
		case BLACK:
			board[m.ep + NORTH] = E;
			material[WHITE] -= piece_val(WP);
			break;
		}
	}
	if (m.flags & MOVEFLAG_PAWNX2) {
		switch (m.side) {
		case WHITE:
			en_passant = m.from + NORTH;
			break;
		case BLACK:
			en_passant = m.from + SOUTH;
			break;
		}
	}
	else en_passant = -1;

	//promotions
	if (m.flags & MOVEFLAG_PROMOTION) {
		board[m.to] = m.promote;
		
		material[m.side] -= piece_val(board[m.from]);
		material[m.side] += piece_val(m.promote);

		board[m.from] = 0;

	}
	else {
		board[m.to] = board[m.from];
		board[m.from] = E;
	}

	if (board[m.to] == WK)
		WK_pos = m.to;
	if (board[m.to] == BK)
		BK_pos = m.to;

	
	moveStack.push(m);
	return true;
}

void unmake_move()
{
	Move m = moveStack.top();

	if (m.flags & MOVEFLAG_PROMOTION) {
		switch (m.side) {
		case WHITE:
			board[m.from] = WP;
			material[WHITE] -= piece_val(m.promote);
			material[WHITE] += piece_val(WP);
			break;
		case BLACK:
			board[m.from] = BP;
			material[BLACK] -= piece_val(m.promote);
			material[BLACK] += piece_val(BP);
			break;
		}
	}

	else {
		board[m.from] = board[m.to];
	}

	if (m.flags & MOVEFLAG_CAPTURE) {
		board[m.to] = m.capt;
		material[stm] += piece_val(m.capt);
	}
	else board[m.to] = E;

	if (m.flags & MOVEFLAG_CASTLE_WK) {
		board[F1] = E;
		board[H1] = WR;
	}
	if (m.flags & MOVEFLAG_CASTLE_WQ) {
		board[D1] = E;
		board[A1] = WR;
	}
	if (m.flags & MOVEFLAG_CASTLE_BK) {
		board[F8] = E;
		board[H8] = BR;
	}
	if (m.flags & MOVEFLAG_CASTLE_BQ) {
		board[D8] = E;
		board[A8] = BR;
	}

	if (m.flags & MOVEFLAG_EP) {
		switch (m.side) {
		case WHITE:
			board[m.ep + SOUTH] = m.capt;
			break;
		case BLACK:
			board[m.ep + NORTH] = m.capt;
			break;
		}
		material[stm] += piece_val(m.capt);
	}

	stm = m.side;

	castle_rights = m.castle_rights;
	en_passant = m.ep;
	if (board[m.from] == WK)
		WK_pos = m.from;
	if (board[m.from] == BK)
		BK_pos = m.from;
	//board_to_stream(std::cout);
	//std::cout << "-----------------------------------------------" << std::endl;

	moveStack.pop();
}

void add_pawn_moves(const int& index, const int& color, std::vector<Move>& moves, const bool& capturesOnly) {
	Move m = { 0,
					0, 0,
					en_passant,
					stm,
					E,
					E,
					castle_rights };

		if (color == WHITE) {
			int left = index + NW, forward = index + NORTH, forwardx2 = index + NORTH + NORTH, right = index + NE;
			int promotionPieces[4] = { WN, WB, WR, WQ };

			if (!(left & 0x88)) {
				if (piece_props(board[left]).color == BLACK) {
					m.from = index;
					m.to = left;
					m.flags = MOVEFLAG_CAPTURE;
					m.capt = board[left];

					if (rank_of(m.to) == 8) {
						m.flags = m.flags | MOVEFLAG_PROMOTION;
						for (int i = 0; !(i & 4); ++i)
						{
							m.promote = promotionPieces[i];
							moves.push_back(m);
						}
					}
					else {
						moves.push_back(m);
					}
				}
				if (!(en_passant & 0x88) && en_passant == left) {
					m.from = index;
					m.to = left;
					m.flags = MOVEFLAG_EP;
					m.capt = board[index - 1];
					moves.push_back(m);
				}
			}
			if (!(right & 0x88)) {
				if (piece_props(board[right]).color == BLACK) {
					m.from = index;
					m.to = right;
					m.flags = MOVEFLAG_CAPTURE;
					m.capt = board[right];

					if (rank_of(m.to) == 8) {
						m.flags = m.flags | MOVEFLAG_PROMOTION;
						for (int i = 0; !(i & 4); ++i)
						{
							m.promote = promotionPieces[i];
							moves.push_back(m);
						}
					}
					else {
						moves.push_back(m);
					}
				}
				if (!(en_passant & 0x88) && en_passant == right) {
					m.from = index;
					m.to = right;
					m.flags = MOVEFLAG_EP;
					m.capt = board[index + 1];
					moves.push_back(m);
				}
			}
			if (capturesOnly)
				return;

			bool fwdFree = false;
			if (!(forward & 0x88) && piece_props(board[forward]).color == -1) {
				fwdFree = true;
				m.from = index;
				m.to = forward;

				//std::cout << "RANK OF FORWARD: " << rank_of(forward) << std::endl;;
				if (rank_of(m.to) == 8) {
					m.flags = MOVEFLAG_PROMOTION;
					for (int i = 0; !(i & 4); ++i)
					{
						m.promote = promotionPieces[i];
						moves.push_back(m);
					}
				}
				else {
					m.flags = 0;
					moves.push_back(m);
				}
			}
			if (rank_of(index) == 2 && fwdFree && piece_props(board[forwardx2]).color == -1) {
				m.from = index;
				m.to = forwardx2;
				m.flags = MOVEFLAG_PAWNX2;
				moves.push_back(m);
			}
		}
		else if (color == BLACK) {
			int left = index + SW, forward = index + SOUTH, forwardx2 = index + SOUTH + SOUTH, right = index + SE;
			int promotionPieces[4] = { BN, BB, BR, BQ };

			if (!(left & 0x88)) {
				if (piece_props(board[left]).color == WHITE) {
					m.from = index;
					m.to = left;
					m.flags = MOVEFLAG_CAPTURE;
					m.capt = board[left];

					if (rank_of(m.to) == 1) {
						m.flags = m.flags | MOVEFLAG_PROMOTION;
						for (int i = 0; !(i & 4); ++i)
						{
							m.promote = promotionPieces[i];
							moves.push_back(m);
						}
					}
					else {
						moves.push_back(m);
					}
				}
				if (!(en_passant & 0x88) && en_passant == left) {
					m.from = index;
					m.to = left;
					m.flags = MOVEFLAG_EP;
					m.capt = board[index - 1];
					moves.push_back(m);
				}
			}
			if (!(right & 0x88)) {
				if (piece_props(board[right]).color == WHITE) {
					m.from = index;
					m.to = right;
					m.flags = MOVEFLAG_CAPTURE;
					m.capt = board[right];

					if (rank_of(m.to) == 1) {
						m.flags = m.flags | MOVEFLAG_PROMOTION;
						for (int i = 0; !(i & 4); ++i)
						{
							m.promote = promotionPieces[i];
							moves.push_back(m);
						}
					}
					else {
						moves.push_back(m);
					}
				}
				if (!(en_passant & 0x88) && en_passant == right) {
					m.from = index;
					m.to = right;
					m.flags = MOVEFLAG_EP;
					m.capt = board[index + 1];
					moves.push_back(m);
				}
			}
			if (capturesOnly)
				return;

			bool fwdFree = false;
			if (!(forward & 0x88) && piece_props(board[forward]).color == -1) {
				fwdFree = true;
				m.from = index;
				m.to = forward;

				if (rank_of(m.to) == 1) {
					m.flags = MOVEFLAG_PROMOTION;
					for (int i = 0; !(i & 4); ++i)
					{
						m.promote = promotionPieces[i];
						moves.push_back(m);
					}
				}
				else {
					m.flags = 0;
					moves.push_back(m);
				}
			}
			if (rank_of(index) == 7 && fwdFree && piece_props(board[forwardx2]).color == -1) {
				m.from = index;
				m.to = forwardx2;
				m.flags = MOVEFLAG_PAWNX2;
				moves.push_back(m);
			}
		}
	
}
void add_knight_moves(const int& index, const int& color, std::vector<Move>& moves, const bool& capturesOnly) {
	Move m = { 0,
					0, 0,
					en_passant,
					stm,
					E,
					E,
					castle_rights };

	//int dir[8] = { -33, -31, -14, 18, 33, 31, 14, -18 };
	for (int i = 0; !(i & 8); i++) {
		int to = index + knight_dir[i];
		if (to & 0x88)
			continue;
		PieceProps dest = piece_props(board[to]);
		m.from = index;
		m.to = to;
		if (dest.color == -1) {
			if (!capturesOnly)
			{
				m.flags = 0;
				moves.push_back(m);
			}
		}
		else {
			if (dest.color != color) {
				m.flags = MOVEFLAG_CAPTURE;
				m.capt = board[to];
				moves.push_back(m);
			}
		}


	}
}
void add_sliding_moves(const int& index, const int& color, const int* directions, const int& size, std::vector<Move>& moves, const bool& capturesOnly) {
	Move m = { 0,
					0, 0,
					en_passant,
					stm,
					E,
					E,
					castle_rights };

	m.from = index;
	for (int i = 0; i < size; ++i) {

		for (int to = index + directions[i]; !(to & 0x88); to += directions[i]) {
			PieceProps dest = piece_props(board[to]);
			m.to = to;
			if (dest.color == -1) {
				if (!capturesOnly) {
					m.flags = 0;
					moves.push_back(m);
				}
			}
			else {
				if (dest.color != color) {
					m.flags = MOVEFLAG_CAPTURE;
					m.capt = board[to];
					moves.push_back(m);
				}
				break;
			}
		}
	}
}
void add_king_moves(const int& index, const int& color, std::vector<Move>& moves, const bool& capturesOnly) {
	Move m = { 0,
					0, 0,
					en_passant,
					stm,
					E,
					E,
					castle_rights };

	for (int i = 0; !(i & 8); i++) {
		int to = index + king_dir[i];
		if (to & 0x88)
			continue;
		PieceProps dest = piece_props(board[to]);
		m.from = index;
		m.to = to;
		if (dest.color == -1) {
			if (!capturesOnly) {
				m.flags = 0;
				moves.push_back(m);
			}
		}
		else {
			if (dest.color != color) {
				m.flags = MOVEFLAG_CAPTURE;
				m.capt = board[to];
				moves.push_back(m);
			}
		}
	}

}
void add_castle_moves(const int& color, std::vector<Move>& moves) {

	Move m = { 0,
					0, 0,
					en_passant,
					stm,
					E,
					E,
					castle_rights };

	switch (color) {
	case WHITE:
		m.from = E1;
		if (castle_rights & CASTLERIGHTS_WK) {
			int squares[2] = { F1, G1 };
			if (check_squares_equal(squares, 2, E)) {
				if (!check_squares_attacked(squares, 2, WHITE) && !is_attacked_simple(E1, WHITE) && board[H1] == WR) {
					m.flags = MOVEFLAG_CASTLE_WK;
					m.to = G1;
					moves.push_back(m);
				}
			}

		}
		if (castle_rights & CASTLERIGHTS_WQ) {
			int squares[3] = { D1, C1, B1 };
			if (check_squares_equal(squares, 3, E)) {
				if (!check_squares_attacked(squares, 2, WHITE) && !is_attacked_simple(E1, WHITE) && board[A1] == WR) {
					m.flags = MOVEFLAG_CASTLE_WQ;
					m.to = C1;
					moves.push_back(m);
				}
			}
		}

		break;
	case BLACK:
		m.from = E8;
		if (castle_rights & CASTLERIGHTS_BK) {
			if (is_checked(BLACK))
				break;
			int squares[2] = { F8, G8 };
			if (check_squares_equal(squares, 2, E)) {
				if (!check_squares_attacked(squares, 2, BLACK) && !is_attacked_simple(E8, BLACK) && board[H8] == BR) {
					m.flags = MOVEFLAG_CASTLE_BK;
					m.to = G8;
					moves.push_back(m);
				}
			}
		}
		if (castle_rights & CASTLERIGHTS_BQ) {
			int squares[3] = { D8, C8, B8 };
			if (check_squares_equal(squares, 3, E)) {
				if (!check_squares_attacked(squares, 2, BLACK) && !is_attacked_simple(E8, BLACK) && board[A8] == BR) {
					m.flags = MOVEFLAG_CASTLE_BQ;
					m.to = C8;
					moves.push_back(m);
				}
			}
		}
		break;
	default:
		break;
	}
}

void add_piece_moves_beta(const PieceProps& piece, const int& index, std::vector<Move>& moves, const bool& capturesOnly = false) {
	if (piece.movedir & P_PAWN)
	{
		add_pawn_moves(index, piece.color, moves, capturesOnly);
		return;
	}
	if (piece.movedir & P_KNIGHT)
	{
		add_knight_moves(index, piece.color, moves, capturesOnly);
		return;
	}
	if (piece.movedir & P_SLIDING) {
		{	if (piece.movedir & P_MOVE_DIAG)
			add_sliding_moves(index, piece.color, bishop_dir, 4, moves, capturesOnly);
		if (piece.movedir & P_MOVE_STRAIGHT)
			add_sliding_moves(index, piece.color, rook_dir, 4, moves, capturesOnly);
		}
		return;
	}
	if (piece.movedir & (P_MOVE_DIAG + P_MOVE_STRAIGHT)) {
		add_king_moves(index, piece.color, moves, capturesOnly);
	}
}

std::vector<Move> generate_moves(const bool& capturesOnly)
{
	std::vector<Move> mvs;

	for (int i = 0; !(i & 128); i++) {
		if (i & 0x88) {
			i += 7;
			continue;
		}
		PieceProps piece = piece_props(board[i]);

		if (piece.color == stm) {
			//add_piece_moves(piece, i, mvs);
			add_piece_moves_beta(piece, i, mvs, capturesOnly);
			
		}
	}
	if(!capturesOnly)
		add_castle_moves(stm, mvs);

	return mvs;
}

std::vector<Move> legal_moves(const bool& capturesOnly)
{
	std::vector<Move> allMoves, legalMoves;
	allMoves = generate_moves(capturesOnly);
	for (const auto& m : allMoves) {
		make_move(m);
		if (!is_checked(m.side)) {
			legalMoves.push_back(m);
		}
		unmake_move();
	}
	return legalMoves;
}

int get_castle_rights()
{
	return castle_rights;
}

int get_stm()
{
	return stm;
}

int get_en_passant()
{
	return en_passant;
}

int get_material(const int& color)
{
	return material[color];
}

std::stack<Move>* get_moveStack()
{
	return &moveStack;
}

int* get_board()
{
	return board;
}

int color(const int& piece) {
	if (!piece) return 2;
	if (piece < BP) return 0;
	return 1;
}

int rank_of(const int& index)
{
	return (index >> 4)+1;
}

int is_attacked(const int& square, const int& color, const bool& check, std::vector<int>& attackers)
{
	//color - color of the hypothetical piece on square
	//TODO: Separate attacks!
	//TODO: Change this entirely because it's rather slow

	if (square & 0x88 || !(color == 0 || color == 1))
		return 0;
	std::vector<int> squares;
	//check for pawn
	int from;
	if (color == 0) {
		from = square + NW;
		if (!((from) & 0x88) && board[from] == BP) {
			attackers.push_back(from);
			if (check)
				goto stop_attackers_search;
		}
		from = square + NE;
		if (!((from) & 0x88) && board[from] == BP) {
			attackers.push_back(from);
			if (check)
				goto stop_attackers_search;
		}
	}
	else
	{
		from = square + SW;
		if (!((from) & 0x88) && board[from] == WP) {
			attackers.push_back(from);
			if (check)
				goto stop_attackers_search;
		}
		from = square + SE;
		if (!((from) & 0x88) && board[from] == WP) {
			attackers.push_back(from);
			if (check)
				goto stop_attackers_search;
		}
	}
	//check for knight
	{
		int dir[8] = { -33, -31, -14, 18, 33, 31, 14, -18 };
		for (int i = 0; !(i & 8); i++) {
			int from = square + dir[i];

			if (!(from & 0x88)) {
				auto pieceProps = piece_props(board[from]);
				if (pieceProps.movedir & P_KNIGHT && pieceProps.color != color) {
					attackers.push_back(from);
					if (check)
						goto stop_attackers_search;
				}
			}
		}
	}
	//other pieces
	// 
	{
		int dir[4] = { NORTH, EAST, SOUTH, WEST };
		for (int i = 0; !(i & 4); ++i) {
			int currentSq = square;
			for (int counter = 0; !(counter & 8); counter++) {
				currentSq += dir[i];
				if ((currentSq & 0x88))
					break;
				auto pieceProps = piece_props(board[currentSq]);
				if (pieceProps.color != color && (pieceProps.movedir & P_MOVE_STRAIGHT) && ((pieceProps.movedir & P_SLIDING) || counter == 0)) {
					attackers.push_back(currentSq);
					goto stop_attackers_search;
				}
				else {
					if (pieceProps.color != -1)
						break;
				}
			}
		}
	}
	{
		int dir[4] = { NW, NE, SE, SW };
		for (int i = 0; !(i & 4); ++i) {
			int currentSq = square;
			for (int counter = 0; !(counter & 8); counter++) {
				currentSq += dir[i];
				if ((currentSq & 0x88))
					break;
				auto pieceProps = piece_props(board[currentSq]);

				if (pieceProps.color != color && (pieceProps.movedir & P_MOVE_DIAG) && ((pieceProps.movedir & P_SLIDING) || counter == 0)) {
					attackers.push_back(currentSq);
					goto stop_attackers_search;
				}
				else {
					if (pieceProps.color != -1)
						break;
				}
			}
		}
	}


	//if check, stop at first piece found

stop_attackers_search:
	return attackers.size();
}

int is_attacked_simple(const int& square, const int& color)
{
	if (square & 0x88 || !(color == 0 || color == 1))
		return 0;
	std::vector<int> squares;
	//check for pawn
	int from;
	if (color == 0) {
		from = square + NW;
		if (!((from) & 0x88) && board[from] == BP) {
			return 1;
		}
		from = square + NE;
		if (!((from) & 0x88) && board[from] == BP) {
			return 1;
		}
	}
	else
	{
		from = square + SW;
		if (!((from) & 0x88) && board[from] == WP) {
			return 1;
		}
		from = square + SE;
		if (!((from) & 0x88) && board[from] == WP) {
			return 1;
		}
	}
	//check for knight
	{
		int dir[8] = { -33, -31, -14, 18, 33, 31, 14, -18 };
		for (int i = 0; !(i & 8); i++) {
			int from = square + dir[i];

			if (!(from & 0x88)) {
				auto pieceProps = piece_props(board[from]);
				if (pieceProps.movedir & P_KNIGHT && pieceProps.color != color) {
					return 1;
				}
			}
		}
	}
	//other pieces
	// 
	{
		int dir[4] = { NORTH, EAST, SOUTH, WEST };
		for (int i = 0; !(i & 4); ++i) {
			int currentSq = square;
			for (int counter = 0; !(counter & 8); counter++) {
				currentSq += dir[i];
				if ((currentSq & 0x88))
					break;
				auto pieceProps = piece_props(board[currentSq]);
				if (pieceProps.color != color && (pieceProps.movedir & P_MOVE_STRAIGHT) && ((pieceProps.movedir & P_SLIDING) || counter == 0)) {
					return 1;
				}
				else {
					if (pieceProps.color != -1)
						break;
				}
			}
		}
	}
	{
		int dir[4] = { NW, NE, SE, SW };
		for (int i = 0; !(i & 4); ++i) {
			int currentSq = square;
			for (int counter = 0; !(counter & 8); counter++) {
				currentSq += dir[i];
				if ((currentSq & 0x88))
					break;
				auto pieceProps = piece_props(board[currentSq]);
				if (pieceProps.color != color && (pieceProps.movedir & P_MOVE_DIAG) && ((pieceProps.movedir & P_SLIDING) || counter == 0)) {
					return 1;
				}
				else {
					if (pieceProps.color != -1)
						break;
				}
			}
		}
	}
	return 0;

}

//TODO: return the checkers too
int is_checked(const int& color)
{
	std::vector<int> attackers;
	return is_attacked(king_pos(color), color, true, attackers);
}

int check_squares_equal(const int* squares, const size_t& size, const int& value)
{
	for (int i = 0; i < size; ++i) {
		if (board[squares[i]] != value)
			return 0;
	}
	return 1;
}

int check_squares_attacked(const int* squares, const size_t& size, const int& color)
{
	for (int i = 0; i < size; ++i) {
		std::vector<int> attackers;
		if (is_attacked_simple(squares[i], color))
			return 1;
	}
	return 0;
}

void load_from_fen(const std::string& fen) {

	empty_moveStack();
	material[0] = 0;
	material[1] = 0;

	std::stringstream ss(fen);
	std::string position, turn, castle, ep, halfmove, fullmove;
	ss >> position;
	ss >> turn;
	ss >> castle;
	ss >> ep;
	ss >> halfmove;
	ss >> fullmove;

	for (int i = 0; i < position.length(); ++i) {
		if (position[i] == '/') {
			position[i] = ' ';
		}
	}
	std::stringstream pos_ss(position);
	std::string row_info;
	int rank = 8;
	while (pos_ss >> row_info) {
		_ASSERT(rank > 0);
		int index = 16 * (rank-1);
		int info_index = 0, empties = 0;
		char info;

		for (char info : row_info) {
			if (info >= '1' && info <= '9') {
				for (int i = 0; i < info - '0'; i++) {
					board[index] = E;
					index++;
				}
			}
			else if (is_piece(fen_piece_to_piece(info))) {
				int piece = fen_piece_to_piece(info);
				board[index] = piece;
				material[piece_props(piece).color] += piece_val(piece);
				index++;
			}
			else std::cout << "es no bueno, amigo!" << std::endl;

		}
		rank--;
	}
	if (turn == "w")
		stm = 0;
	else
		if (turn == "b")
			stm = 1;

	castle_rights = 0;
	for (const auto& c : castle) {
		switch (c) {
		case 'K':
			castle_rights = castle_rights | CASTLERIGHTS_WK;
			break;
		case 'Q':
			castle_rights = castle_rights | CASTLERIGHTS_WQ;
			break;
		case 'k':
			castle_rights = castle_rights | CASTLERIGHTS_BK;
			break;
		case 'q':
			castle_rights = castle_rights | CASTLERIGHTS_BQ;
			break;
		default:break;
		}
	}
	en_passant = string_to_sq(ep);

	if (king_pos(WHITE) != E1) {
		castle_rights = castle_rights & ~(CASTLERIGHTS_WK | CASTLERIGHTS_WQ);
	}
	if (king_pos(BLACK) != E8) {
		castle_rights = castle_rights & ~(CASTLERIGHTS_BK | CASTLERIGHTS_BQ);
	}

	WK_pos = king_pos(WHITE);
	BK_pos = king_pos(BLACK);

}

void empty_moveStack()
{
	while (moveStack.size())
		moveStack.pop();
}

int king_pos(const int& color)
{
	if (color != 0 && color != 1)
		return -1;
	if (color == WHITE && WK_pos != -1) {
		return WK_pos;
	}
	else
		if (color == BLACK && BK_pos != -1) {
			return BK_pos;
	}
	int check_for = (color == WHITE ? WK : BK);
	for (int i = 0; !(i & 128); ++i) {
		if (i & 0x88) {
			i += 7;
			continue;
		}
		if (board[i] == check_for)
			return i;
	}
	return -1;
}

void board_to_stream(std::ostream& flow, const bool& blackPOV) {
	
	if (blackPOV) {
		for (int i = 0; !(i & 8); i++) {
			for (int j = 0; !(j & 8); j++)
			{
				flow << piece_ascii(board[(i << 4) + j]) << ' ';
			}
			flow << std::endl;
		}
		return;
	}
	for (int i = 7; !(i < 0); i--) {
		for (int j = 0; !(j & 8); j++)
		{
			flow << piece_ascii(board[(i << 4) + j]) << ' ';
		}
		flow << std::endl;
	}
}


