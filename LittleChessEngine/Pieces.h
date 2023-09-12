#pragma once
#include <unordered_map>
#include <string.h>

#define WHITE 0
#define BLACK 1

#define P_SLIDING			1
#define P_PAWN				2
#define P_KNIGHT			4

#define P_MOVE_STRAIGHT		8
#define P_MOVE_DIAG			16
//#define P_MOVE_N			8
//#define P_MOVE_E			16
//#define P_MOVE_S			32
//#define P_MOVE_W			64
//
//#define P_MOVE_NW			128
//#define P_MOVE_NE			256
//#define P_MOVE_SE			512
//#define P_MOVE_SW			1024



enum PIECES {
	E, WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK, O
};

struct PieceProps {
	int movedir;
	int color;
};

PieceProps piece_props(const int& piece);
bool is_piece(const int& piece);
bool is_piece(const char& piece);

char piece_ascii(const int& piece);
int fen_piece_to_piece(const char& piece);