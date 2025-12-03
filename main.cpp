#include <iostream>
#include <stdlib.h>
#include "Board.hpp"

using namespace std;

int main() {
    Board board;

    board.reset();  
    board.validation_and_move();

    return 0;
}
