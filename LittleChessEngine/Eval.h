#pragma once
#include "board.h"
#include "util.h"

Move random_move();

float eval();

float piece_val(const int& piece);
float material(float& white, float& black);