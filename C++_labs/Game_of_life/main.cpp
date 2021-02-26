#include <iostream>
#include "game_board.h"
#include "parser.h"
#include "console.h"


using namespace std;


int main() {
    game_board game;
    console c;
    while(!game.end_game()) {
        parser pars(&game);
        pars.get_comand(c);
    }
   return 0;
}
