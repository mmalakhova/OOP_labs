#include "game_board.h"

using namespace std;

bool compare_matrix(char** m1, char** m2) {
    for ( size_t  i = 0; i < HEIGHT; i++){
        for ( size_t j = 0 ;j < WIDTH; j++){
            if (m1[i][j] != m2[i][j]) return false;
        }
    }
    return true;
}

void reassign_boards(char** m1, char** m2) {
    for (size_t  i = 0; i < HEIGHT; i++){
        memcpy(m1[i], m2[i], sizeof(char)*HEIGHT);
    }
}


bool game_board::load_board() {
    std::ifstream in;
    in.open(R"(C:\Users\user\CLionProjects\game_of_life\in.txt)");
    if (in.is_open()){
        for (size_t r =0; r < WIDTH; r++){
            for (size_t c =0; c < HEIGHT; c++){
                in >> curr_gen[r][c];
            }
        }
    }
    in.close();
    return false;

}

bool game_board::save_board() {
    ofstream  out;
    out.open(R"(C:\Users\user\CLionProjects\game_of_life\out.txt)");
    if (out.is_open()){
        for (size_t r =0; r < WIDTH; r++){
            for (size_t c =0; c < HEIGHT; c++){
                out << " " << curr_gen[r][c] << " ";
            }
            out << endl;
        }
    }
    out.close();
    return false;
}

void game_board::show_board() {
    for (size_t h = 0; h < HEIGHT; h ++){
        for (size_t w = 0; w < WIDTH; w++){
            cout << " " << curr_gen[h][w] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



void game_board::next_state() {

    reassign_boards(prev_gen, curr_gen);

    for (size_t h = 0; h < HEIGHT; h++){
        for (size_t w = 0; w < WIDTH; w++){
            size_t count_live;

            count_live = neighbour_count(h, w);

            //RULES
            if (count_live < 2 && curr_gen[h][w] == LIVE) { curr_gen[h][w] = DEAD;}
            else if ((count_live == 2 || count_live == 3) && curr_gen[h][w] == LIVE) { curr_gen[h][w] = LIVE;}
            else if (count_live > 3 && curr_gen[h][w] == LIVE) { curr_gen[h][w] = DEAD;}
            else if (count_live == 3 && curr_gen[h][w] == DEAD) { curr_gen[h][w] = LIVE;}
        }
    }
    step_count++;
    ispossible_go_back = true;
}

size_t game_board::neighbour_count(size_t x, size_t y) {
    size_t live_count = 0;
    bool is_not_lower = (y-1) >= 0;
    bool is_not_upper = (y+1) < HEIGHT;

    if ( x-1 >= 0){
        if (is_not_lower && (curr_gen[x-1][y-1] == LIVE)) {live_count++;}
        if (curr_gen[x-1][y] == LIVE) {live_count++;}
        if (is_not_upper && (curr_gen[x-1][y+1] == LIVE)) {live_count++;}
    }

    if (x+1 < WIDTH) {
        if(is_not_lower && (curr_gen[x+1][y-1] == LIVE) )
            live_count++;
        if(curr_gen[x+1][y] == LIVE)
            live_count++;
        if(is_not_upper && (curr_gen[x+1][y+1] == LIVE) )
            live_count++;
    }

    if( is_not_upper && curr_gen[x][y+1] == LIVE)
        live_count++;
    if(is_not_lower && (curr_gen[x][y-1] == LIVE) )
        live_count++;

    return live_count;
}

game_board::game_board() {
    Create();
    init_board();
    step_count = 0;
    ispossible_go_back = false;
}

game_board::~game_board() {
    Delete();
    step_count = 0;
}

game_board::game_board(const game_board &game_board_to_copy) {
    step_count = game_board_to_copy.step_count;
    for ( int  i = 0; i < HEIGHT; i++){
        memcpy(curr_gen[i], game_board_to_copy.curr_gen[i], sizeof(char)*HEIGHT);
        memcpy(prev_gen[i], game_board_to_copy.prev_gen[i], sizeof(char)*HEIGHT);
    }
}


void game_board::reset() {
    for (size_t h = 0; h < HEIGHT; h++){
        for (size_t w = 0; w < WIDTH; w++){
            curr_gen[h][w] = DEAD;
        }
    }
    step_count = 0;
    ispossible_go_back = false;
}

void game_board::clear() {
    for ( int h = 0; h < HEIGHT; h++){
        for ( int w = 0; w < WIDTH; w++){
            curr_gen[h][w] = DEAD;
        }
    }
    step_count++;
    ispossible_go_back = true;
}

void game_board::add_live_cell(size_t x, size_t y) {
    if ( x > HEIGHT || x < 0 || y > WIDTH || y < 0) return;
    if (curr_gen[x][y] == LIVE) { cout << "Oooops...this place's already taken"<< endl;}
    else { curr_gen[x][y] = LIVE;}
    ispossible_go_back = true;
}

void game_board::back() {
    if (step_count == 1) {
        cout << "It's impossible to step back....";
        return;
    }
    if (!ispossible_go_back) {
        cout << "It's impossible to step back....";
        return;
    }
    if (compare_matrix(prev_gen, curr_gen)) return;
    reassign_boards(curr_gen, prev_gen);
    show_board();
    ispossible_go_back = false;
}



bool game_board::end_game() {
    if (compare_matrix(prev_gen,curr_gen)) return true;
    else return false;
}

std::ostream &operator<<(ostream &out, game_board &game) {
    for (size_t h = 0; h < HEIGHT; h ++){
        for (size_t w = 0; w < WIDTH; w++){
            out << " " << game.curr_gen[h][w] << " ";
        }
        out << endl;
    }
    out << endl;
    return out;
}

