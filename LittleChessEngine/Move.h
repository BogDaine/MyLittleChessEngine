#pragma once
#include <iostream>

#include "88stuff.h"
#include "flags.h"
#include "Pieces.h"

#define MOVEFLAG_CAPTURE		1

#define MOVEFLAG_CASTLE_WK		2
#define MOVEFLAG_CASTLE_WQ		4
#define MOVEFLAG_CASTLE_BK		8
#define MOVEFLAG_CASTLE_BQ		16

#define MOVEFLAG_EP				32
#define MOVEFLAG_PAWNX2			64
#define MOVEFLAG_PROMOTION		128

#define  CASTLERIGHTS_WK			1
#define  CASTLERIGHTS_WQ			2
#define  CASTLERIGHTS_BK			4
#define  CASTLERIGHTS_BQ			8

struct Move {
	int flags;
	int from, to, ep;
	int side;
	int capt, promote;
	int castle_rights;

	std::string to_fen ()const;
	void print(bool asfen = false, bool verbose = false, std::ostream& os = std::cout) const;
};