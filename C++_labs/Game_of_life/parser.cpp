#include "parser.h"

parser::parser(game_board* g) {
    game = g;
}

void parser::get_comand(console &c) {
    string comand_opt;
    comand_opt = c.get_com_option();

    if (comand_opt == "reset"){
        game->reset();
        game->show_board();
        game->show_step_count();
    } else if (comand_opt == "clear"){
        string arg;
        arg = c.get_com_arguments();
        size_t x = arg[0] - '0' - 17;
        size_t y = arg[1] - '0';
        game->clear(x,y);
        game->show_board();
        game->show_step_count();
    } else if (comand_opt == "set"){
        string arg;
        arg = c.get_com_arguments();
        size_t x = arg[0] - '0' - 17;
        size_t y = arg[1] - '0';
        game->add_live_cell(x,y);
        game->show_board();
        game->show_step_count();
    } else if (comand_opt == "step"){
        game->next_state();
        game->show_board();
        game->show_step_count();
    } else if (comand_opt == "back"){
        game->back();
        game->show_board();
        game->show_step_count();
    } else if (comand_opt == "save"){
        game->save_board();
        game->show_board();
    } else if (comand_opt == "load"){
        game->load_board();
        game->show_board();
    }
}

