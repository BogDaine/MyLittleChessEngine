#pragma once
#include "Eval.h"

long perft(const int& maxDepth, const int& depth);
int search(const int& depth);
int alphabeta_search(const int& depth, int alpha, int beta);
int alphabeta_root(const int& depth, int alpha, int beta);

Move best_move(const int& depth);

Move get_best_move();
static Move the_best_move;
