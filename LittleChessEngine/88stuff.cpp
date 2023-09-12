#include "88stuff.h"

static std::unordered_map<std::string, int> stringToSqMap = {
	std::make_pair<std::string, int>("a1", A1),
	std::make_pair<std::string, int>("a2", A2),
	std::make_pair<std::string, int>("a3", A3),
	std::make_pair<std::string, int>("a4", A4),
	std::make_pair<std::string, int>("a5", A5),
	std::make_pair<std::string, int>("a6", A6),
	std::make_pair<std::string, int>("a7", A7),
	std::make_pair<std::string, int>("a8", A8),

	std::make_pair<std::string, int>("b1", B1),
	std::make_pair<std::string, int>("b2", B2),
	std::make_pair<std::string, int>("b3", B3),
	std::make_pair<std::string, int>("b4", B4),
	std::make_pair<std::string, int>("b5", B5),
	std::make_pair<std::string, int>("b6", B6),
	std::make_pair<std::string, int>("b7", B7),
	std::make_pair<std::string, int>("b8", B8),

	std::make_pair<std::string, int>("c1", C1),
	std::make_pair<std::string, int>("c2", C2),
	std::make_pair<std::string, int>("c3", C3),
	std::make_pair<std::string, int>("c4", C4),
	std::make_pair<std::string, int>("c5", C5),
	std::make_pair<std::string, int>("c6", C6),
	std::make_pair<std::string, int>("c7", C7),
	std::make_pair<std::string, int>("c8", C8),

	std::make_pair<std::string, int>("d1", D1),
	std::make_pair<std::string, int>("d2", D2),
	std::make_pair<std::string, int>("d3", D3),
	std::make_pair<std::string, int>("d4", D4),
	std::make_pair<std::string, int>("d5", D5),
	std::make_pair<std::string, int>("d6", D6),
	std::make_pair<std::string, int>("d7", D7),
	std::make_pair<std::string, int>("d8", D8),

	std::make_pair<std::string, int>("e1", E1),
	std::make_pair<std::string, int>("e2", E2),
	std::make_pair<std::string, int>("e3", E3),
	std::make_pair<std::string, int>("e4", E4),
	std::make_pair<std::string, int>("e5", E5),
	std::make_pair<std::string, int>("e6", E6),
	std::make_pair<std::string, int>("e7", E7),
	std::make_pair<std::string, int>("e8", E8),

	std::make_pair<std::string, int>("f1", F1),
	std::make_pair<std::string, int>("f2", F2),
	std::make_pair<std::string, int>("f3", F3),
	std::make_pair<std::string, int>("f4", F4),
	std::make_pair<std::string, int>("f5", F5),
	std::make_pair<std::string, int>("f6", F6),
	std::make_pair<std::string, int>("f7", F7),
	std::make_pair<std::string, int>("f8", F8),

	std::make_pair<std::string, int>("g1", G1),
	std::make_pair<std::string, int>("g2", G2),
	std::make_pair<std::string, int>("g3", G3),
	std::make_pair<std::string, int>("g4", G4),
	std::make_pair<std::string, int>("g5", G5),
	std::make_pair<std::string, int>("g6", G6),
	std::make_pair<std::string, int>("g7", G7),
	std::make_pair<std::string, int>("g8", G8),

	std::make_pair<std::string, int>("h1", H1),
	std::make_pair<std::string, int>("h2", H2),
	std::make_pair<std::string, int>("h3", H3),
	std::make_pair<std::string, int>("h4", H4),
	std::make_pair<std::string, int>("h5", H5),
	std::make_pair<std::string, int>("h6", H6),
	std::make_pair<std::string, int>("h7", H7),
	std::make_pair<std::string, int>("h8", H8),
};
static std::unordered_map<int, std::string> sqToStringMap = {
	std::make_pair<int, std::string>(A1, "a1"),
	std::make_pair<int, std::string>(A2, "a2"),
	std::make_pair<int, std::string>(A3, "a3"),
	std::make_pair<int, std::string>(A4, "a4"),
	std::make_pair<int, std::string>(A5, "a5"),
	std::make_pair<int, std::string>(A6, "a6"),
	std::make_pair<int, std::string>(A7, "a7"),
	std::make_pair<int, std::string>(A8, "a8"),

	std::make_pair<int, std::string>(B1, "b1"),
	std::make_pair<int, std::string>(B2, "b2"),
	std::make_pair<int, std::string>(B3, "b3"),
	std::make_pair<int, std::string>(B4, "b4"),
	std::make_pair<int, std::string>(B5, "b5"),
	std::make_pair<int, std::string>(B6, "b6"),
	std::make_pair<int, std::string>(B7, "b7"),
	std::make_pair<int, std::string>(B8, "b8"),

	std::make_pair<int, std::string>(C1, "c1"),
	std::make_pair<int, std::string>(C2, "c2"),
	std::make_pair<int, std::string>(C3, "c3"),
	std::make_pair<int, std::string>(C4, "c4"),
	std::make_pair<int, std::string>(C5, "c5"),
	std::make_pair<int, std::string>(C6, "c6"),
	std::make_pair<int, std::string>(C7, "c7"),
	std::make_pair<int, std::string>(C8, "c8"),

	std::make_pair<int, std::string>(D1, "d1"),
	std::make_pair<int, std::string>(D2, "d2"),
	std::make_pair<int, std::string>(D3, "d3"),
	std::make_pair<int, std::string>(D4, "d4"),
	std::make_pair<int, std::string>(D5, "d5"),
	std::make_pair<int, std::string>(D6, "d6"),
	std::make_pair<int, std::string>(D7, "d7"),
	std::make_pair<int, std::string>(D8, "d8"),

	std::make_pair<int, std::string>(E1, "e1"),
	std::make_pair<int, std::string>(E2, "e2"),
	std::make_pair<int, std::string>(E3, "e3"),
	std::make_pair<int, std::string>(E4, "e4"),
	std::make_pair<int, std::string>(E5, "e5"),
	std::make_pair<int, std::string>(E6, "e6"),
	std::make_pair<int, std::string>(E7, "e7"),
	std::make_pair<int, std::string>(E8, "e8"),

	std::make_pair<int, std::string>(F1, "f1"),
	std::make_pair<int, std::string>(F2, "f2"),
	std::make_pair<int, std::string>(F3, "f3"),
	std::make_pair<int, std::string>(F4, "f4"),
	std::make_pair<int, std::string>(F5, "f5"),
	std::make_pair<int, std::string>(F6, "f6"),
	std::make_pair<int, std::string>(F7, "f7"),
	std::make_pair<int, std::string>(F8, "f8"),

	std::make_pair<int, std::string>(G1, "g1"),
	std::make_pair<int, std::string>(G2, "g2"),
	std::make_pair<int, std::string>(G3, "g3"),
	std::make_pair<int, std::string>(G4, "g4"),
	std::make_pair<int, std::string>(G5, "g5"),
	std::make_pair<int, std::string>(G6, "g6"),
	std::make_pair<int, std::string>(G7, "g7"),
	std::make_pair<int, std::string>(G8, "g8"),

	std::make_pair<int, std::string>(H1, "h1"),
	std::make_pair<int, std::string>(H2, "h2"),
	std::make_pair<int, std::string>(H3, "h3"),
	std::make_pair<int, std::string>(H4, "h4"),
	std::make_pair<int, std::string>(H5, "h5"),
	std::make_pair<int, std::string>(H6, "h6"),
	std::make_pair<int, std::string>(H7, "h7"),
	std::make_pair<int, std::string>(H8, "h8"),
};


std::string sq_to_string(const int& square)
{
	if (!(square & 0x88)) {
		return sqToStringMap[square];
	}
	return "";
}

int string_to_sq(const std::string& square)
{
	if (stringToSqMap.find(square) != stringToSqMap.end()) {
		return stringToSqMap[square];
	}
	return -1;
}
