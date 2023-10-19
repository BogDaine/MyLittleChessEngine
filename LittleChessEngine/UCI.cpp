#include "UCI.h"

#include <sstream>
#include <iomanip>
#include <chrono>

#include <unordered_set>

void command_loop()
{
	char* command = new char[COMMAND_LENGTH + 1];


	while (std::cin.getline(command, COMMAND_LENGTH)) {

		execute_command(command);
	}
}
void parse_command(char* command, std::string& cmd, std::string& params) {
	std::stringstream ss(command);
	
	params = "";

	ss >> cmd;
	int index = ss.str().find_first_of(' ');
	if (index != std::string::npos) {
		params = ss.str().substr(index+1);
	}
}

void cmd_uci(const std::string& params) {
	std::cout << "id name Little Chess Engine\nid author Bogdan Osian" << std::endl;
	std::cout << "uciok" << std::endl;
}
void cmd_isready(const std::string& params) {
	std::cout << "readyok" << std::endl;
}

void cmd_ucinewgame(const std::string& params) {
	load_from_fen(startfen);
}

void cmd_position(const std::string& params) {
	if (params.size() < 4)
		return;
	if(params == "startpos")
		load_from_fen(startfen);
	if (params.substr(0, 4) == "fen ") {
		load_from_fen(params.substr(4));
	}
}

void cmd_d(const std::string& params) {
	board_to_stream(std::cout);
	
	std::cout << std::setw(15) << "stm: " << get_stm() << std::endl;
	std::cout << std::setw(15) << "castle rights: " << get_castle_rights() << std::endl;
	std::cout << std::setw(15) << "en-passant: " << get_en_passant() << std::endl;

	//TODO: print checkers!
}

void cmd_go(const std::string& params) {
	//TODO: perft
	//TODO: change depth

	/*if (params != "") {
		
	}
	else*/
	{
		if (params.size() > 6 && params.substr(0, 6) == "perft ") {

			std::stringstream ss(params.substr(6));
			std::cout << "PERFORMANCE TEST!!" << std::endl;

			int depth;
			ss >> depth;

			const auto start{ std::chrono::steady_clock::now() };
			std::cout << "nodes searched: " << perft(depth, 0) << std::endl << std::endl;
			const auto end{ std::chrono::steady_clock::now() };
			std::chrono::duration<double> elapsed_seconds{ end - start };
			std::cout << "elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
			return;

		}

		alphabeta_root(5, - 99999999, 99999999);
		std::cout << "bestmove " << get_best_move().to_fen() << std::endl;
	}
}

void cmd_eval(const std::string& params) {
	std::cout << eval() << std::endl;
}

void cmd_mm(const std::string& params) {
	auto mvs = legal_moves();

	std::unordered_map<std::string, Move> moveMap;
	for (const auto& m : mvs) {
		moveMap.insert(std::make_pair<std::string, const Move&>(m.to_fen(), m));
	}

	if (moveMap.count(params)){
		make_move(moveMap[params]);
	}
}
void cmd_umm(const std::string& params) {
	unmake_move();
}

//TODO: move this initialization
typedef void (*cmd_func)(const std::string&);

static std::unordered_map < std::string, cmd_func> command_map = {
	std::make_pair<std::string, cmd_func>("uci", &cmd_uci),
	std::make_pair<std::string, cmd_func>("isready", &cmd_isready),
	std::make_pair<std::string, cmd_func>("ucinewgame", &cmd_ucinewgame),
	std::make_pair<std::string, cmd_func>("position", &cmd_position),
	std::make_pair<std::string, cmd_func>("go", &cmd_go),
	std::make_pair<std::string, cmd_func>("d", &cmd_d),
	std::make_pair<std::string, cmd_func>("eval", &cmd_eval),

	std::make_pair<std::string, cmd_func>("mm", &cmd_mm),
	std::make_pair<std::string, cmd_func>("umm", &cmd_umm),
};

void execute_command(char* command)
{
	std::string cmd, params;
	parse_command(command, cmd, params);
	
	if (command_map.count(cmd))
		command_map[cmd](params);
}
