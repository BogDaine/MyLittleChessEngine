#pragma once
#include <strstream>
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <string>


#include "Move.h"
#include "Pieces.h"



#define NORTH	-16
#define SOUTH	 16
#define WEST	-1
#define EAST	 1
#define NW		 -17
#define NE		 -15
#define SW		 15
#define SE		 17




struct Piece {
	int type;
	int square;
};

extern std::pair<std::vector<Piece>, std::vector<Piece>> pieces;

//TODO: make a board of references to pieces
//MAYBE
extern int board[];

static int stm;
static int castle_rights;
static int en_passant;

static int WK_pos;
static int BK_pos;

static std::stack<Move>moveStack;



std::vector<int>straight_moves(const int& sq, int color);

std::vector<Move>generate_moves();
std::vector<Move>legal_moves();

int get_castle_rights();
int get_stm();
int get_en_passant();
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

void board_to_stream(std::ostream& flow);
void board_init();

//nu se face validarea string-ului FEN!
void load_from_fen(const std::string& fen);

void empty_moveStack();

bool make_move(const Move& m);
void unmake_move();