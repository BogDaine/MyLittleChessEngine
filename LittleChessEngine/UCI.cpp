#include "UCI.h"

#include <sstream>
#include <iomanip>
#include <chrono>

void command_loop()
{
	char* command = new char[COMMAND_LENGTH + 1];


	while (std::cin.getline(command, COMMAND_LENGTH)) {

		if (strcmp("d", command) == 0)
		{
			board_to_stream(std::cout);
			//std::cout << std::setw(20);
			std::cout << std::setw(15) << "stm: " << get_stm() << std::endl;
			std::cout << std::setw(15) << "castle rights: " << get_castle_rights() << std::endl;
			std::cout << std::setw(15) << "en-passant: " << get_en_passant() << std::endl;
			continue;
		}
		if (strncmp("position fen ", command, 13) == 0)
		{
			//position fen xxxxxxxx/xxxxxxxx/xxxxxxxx/xxxxxxxx/xxxxxxxx/xxxxxxxx/xxxxxxxx/xxxxxxxx x x x x
			load_from_fen(command + 12);
			continue;
		}
		if (strcmp("lm", command) == 0)
		{
			auto mvs = legal_moves();
			std::cout << mvs.size() << " moves;" << std::endl;
			int i = 0;
			for (auto x : mvs) {
				std::cout << i++ << ": ";
				x.print(true);
				std::cout << std::endl;
			}
			continue;
		}
		if (strcmp("plm", command) == 0)
		{
			auto mvs = generate_moves();
			std::cout << mvs.size() << " moves;" << std::endl;
			int i = 0;
			for (auto x : mvs) {
				std::cout << i++ << ": ";
				x.print(true);
				std::cout << std::endl;
			}
			continue;
		}
		if (strncmp("mm ", command, 3) == 0) {
			std::stringstream ss(command + 3);
			int index = 0;
			ss >> index;
			auto mvs = legal_moves();
			if (index < mvs.size())
			{
				make_move(mvs[index]);
			}
			continue;
		}

		if (strcmp("umm", command) == 0) {
			if (get_moveStack()->size()) {

				unmake_move();
			}
		}
		if (strcmp("eval", command) == 0) {
			std::cout << eval() << std::endl;
			continue;
		}

		if (strcmp("go", command) == 0) {
			auto m = random_move();
			std::cout << m.from << " - " << m.to << std::endl;
			continue;
		}
		if (strncmp("go perft ", command, 9) == 0) {
			std::stringstream ss(command + 9);
			std::cout << "PERFORMANCE TEST!!" << std::endl;

			int depth;
			ss >> depth;

			const auto start{ std::chrono::steady_clock::now() };
			std::cout << "nodes searched: " << perft(depth, 0) << std::endl << std::endl;
			const auto end{ std::chrono::steady_clock::now() };
			std::chrono::duration<double> elapsed_seconds{ end - start };
			std::cout << "elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
			continue;
		}

		if (strcmp("kpw", command) == 0) {
			//std::cout << king_pos(0) << std::endl;
			std::cout << is_checked(0) << std::endl;
		}
		if (strcmp("kpb", command) == 0) {
			std::cout << is_checked(1) << std::endl;
		}
	}
}