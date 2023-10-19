#pragma once
#include <strstream>
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <string>


#include "Move.h"
#include "eval_options.h"


#define NORTH	16
#define SOUTH	 -16
#define WEST	-1
#define EAST	 1
#define NW		 15
#define NE		 17
#define SW		 -17
#define SE		 -15

static const int knight_dir[8] = { -33, -31, -14, 18, 33, 31, 14, -18 };
static const int bishop_dir[4] = {NW, NE, SE, SW};
static const int rook_dir[4] = { NORTH, WEST, SOUTH, EAST };
static const int king_dir[8] = { NORTH, WEST, SOUTH, EAST, NW, NE, SE, SW };

static const std::string startfen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

struct Piece {
	int type;
	int square;
};

extern std::pair<std::vector<Piece>, std::vector<Piece>> pieces;

static int material[2] = { 0,0 };

//TODO: make a board of references to pieces
//MAYBE
extern int board[];

static int stm;
static int castle_rights;
static int en_passant;

static int WK_pos = -1;
static int BK_pos = -1;

static std::stack<Move>moveStack;


std::vector<Move>generate_moves(const bool& capturesOnly = false);
std::vector<Move>legal_moves(const bool& capturesOnly = false);

int get_castle_rights();
int get_stm();
int get_en_passant();

int get_material(const int& color);

std::stack<Move>* get_moveStack();
int* get_board();

int color(const int& piece);

int rank_of(const int& index);

int is_attacked(const int& square, const int& color, const bool& check, std::vector<int>&);
int is_attacked_simple(const int& square, const int& color);
int king_pos(const int& color);
int is_checked(const int& color);

int check_squares_equal(const int* squares, const size_t& size, const int& value);
int check_squares_attacked(const int* squares, const size_t& size, const int& color);

void board_to_stream(std::ostream& flow, const bool& blackPOV = false);
void board_init();

//nu se face validarea string-ului FEN!
void load_from_fen(const std::string& fen);

void empty_moveStack();

bool make_move(const Move& m);
void unmake_move();