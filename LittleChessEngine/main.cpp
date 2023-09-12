#include <iostream>
#include "UCI.h"
#include "board.h"

void say_hello()
{
    std::cout << "Little Chess Engine says hello!\n";
}

int main()
{
    board_init();

    say_hello();    
    command_loop();
}