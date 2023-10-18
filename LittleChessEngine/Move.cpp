#include "Move.h"

static std::unordered_map<int, char> pieceNotationMap = {
	std::make_pair<int, char>(WP, 'p'),
	std::make_pair<int, char>(WN, 'n'),
	std::make_pair<int, char>(WB, 'b'),
	std::make_pair<int, char>(WR, 'r'),
	std::make_pair<int, char>(WQ, 'q'),
	std::make_pair<int, char>(WK, 'k'),

	std::make_pair<int, char>(BP, 'p'),
	std::make_pair<int, char>(BN, 'n'),
	std::make_pair<int, char>(BB, 'b'),
	std::make_pair<int, char>(BR, 'r'),
	std::make_pair<int, char>(BQ, 'q'),
	std::make_pair<int, char>(BK, 'k'),
};

std::string Move::to_fen() const{
	auto mString = std::string(sq_to_string(this->from) + sq_to_string(this->to));
	if (this->flags & MOVEFLAG_PROMOTION)
		mString += pieceNotationMap[this->promote];
	return mString;
}

void Move::print(bool asfen, bool verbose, std::ostream& os) const{
	if (asfen) {
		os << this->to_fen();
		return;
		//os << sq_to_string(this->from)<< sq_to_string(this->to);
	}
	else {
		os << this->from << ' ' << this->to;
	}
	if (this->flags & MOVEFLAG_PROMOTION) {
		os << " " << pieceNotationMap[this->promote];
	}
}