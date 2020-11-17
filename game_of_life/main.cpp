#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;
const char LIVE = 'X';
const char DEAD = '.';


//char curr_board[HEIGHT+1][WIDTH+1];
//char prev_board[HEIGHT][WIDTH];

bool load_board(char** board/*, char filename[20] */){
//    ifstream in(filename);
//    in.open(filename);
//    if (in.is_open()) {
//     for (int r = 0; r < WIDTH; r++) {
//         for (int c = 0; c < HEIGHT; c++) {
//             in >> board[r][c];
//         }
//     }
//    }
//    in.close();
    ifstream in;
    in.open(R"(C:\Users\user\CLionProjects\game_of_life\in.txt)");
    if (in.is_open()){
        for ( int r =0; r < WIDTH; r++){
            for ( int c =0; c < HEIGHT; c++){
                in >> board[r][c];
            }
        }
    }
    in.close();
    return false;
}

bool save_board (char** board){
    ofstream  out;
    out.open(R"(C:\Users\user\CLionProjects\game_of_life\out.txt)");
    if (out.is_open()){
        for ( int r =0; r < WIDTH; r++){
            for ( int c =0; c < HEIGHT; c++){
                out << " " << board[r][c] << " ";
            }
            out << endl;
        }
    }
    out.close();
    return false;
}

void show_board( char** board){
    //cout << "   ";
    for (int h = 0; h < HEIGHT; h ++){
        for (int w = 0; w < WIDTH; w++){
            cout << " " <<board[h][w] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void compare_boards( char** board, char** next_board){
    for ( int  i = 0; i < HEIGHT; i++){
        memcpy(next_board[i], board[i], sizeof(char)*HEIGHT);
    }
}

/*int neighbour_count ( char** board, int x, int y){
    int live_count = 0;
    for ( int i = x - 1; i <=x+1; i++){
        for ( int j = y-1; j <= y+1; j++) {
            if (i != x && j != y) {
                if (board[(i+10) % 10][(j+10) % 10] == LIVE) { live_count++; }
            }
        }
    }
    return live_count;
}*/

int neighbour_count (char** board, int x , int y){
    int live_count = 0;
    bool is_not_lower = (y-1) >= 0;
    bool is_not_upper = (y+1) < HEIGHT;

    if ( x-1 >= 0){
        if ( is_not_lower && (board[x-1][y-1] == LIVE)) {live_count++;}
        if (board[x-1][y] == LIVE) {live_count++;}
        if (is_not_upper && (board[x-1][y+1] == LIVE)) {live_count++;}
    }

    if (x+1 < WIDTH) {
        if( is_not_lower && (board[x+1][y-1] == LIVE) )
            live_count++;
        if(board[x+1][y] == LIVE)
            live_count++;
        if( is_not_upper && (board[x+1][y+1] == LIVE) )
            live_count++;
    }

    if( is_not_upper && (board[x][y+1] == LIVE) )
        live_count++;
    if(is_not_lower && (board[x][y-1] == LIVE) )
        live_count++;

    return live_count;

}

void next_state (char** board){
    char** next_board = new char* [WIDTH];
    for ( int i = 0; i < HEIGHT; i++){
        next_board[i] = new char [HEIGHT];
    }

    compare_boards(board, next_board);

    for ( int h = 0; h < HEIGHT; h++){
        for ( int w = 0; w < WIDTH; w++){
            int count_live = 0;

            count_live = neighbour_count(next_board, h, w);

            //RULES
            if ( count_live < 2 && board[h][w] == LIVE) { board[h][w] = DEAD;}
            else if ((count_live == 2 || count_live == 3) && board[h][w] == LIVE) { board[h][w] = LIVE;}
            else if (count_live > 3 && board[h][w] == LIVE) { board[h][w] = DEAD;}
            else if (count_live == 3 && board[h][w] == DEAD) { board[h][w] = LIVE;}
        }
    }
}


void add_live_cell (char** board, int x, int y){
    if ( x > HEIGHT || x < 0 || y > WIDTH || y < 0) return;
    if (board[x][y] == LIVE) { cout << "Oooops...this place's already taken"<< endl;}
    else { board[x][y] = LIVE;}
    //iterate the number of steps
}

void reset_the_game (char** board){
    for ( int h = 0; h < HEIGHT; h++){
        for ( int w = 0; w < WIDTH; w++){
            board[h][w] = DEAD;
        }
    }
    //обнулить счетчик шагов
}

void back (char** board){

}





int main() {
    setlocale(LC_ALL, "Russian");
    char** board = new char* [WIDTH];
    for ( int i =0; i < HEIGHT; i++){
        board[i] = new char [HEIGHT];
    }
    //game doesn't while the prev and curr gen aren't equal!!!

//    char f[20];
//    cout << "input the filename" << endl;
//    cin >> f;
    load_board(board);
    //show_board(board);
//    int c = neighbour_count(board, 2, 2);
//    cout << endl << c << endl;
//    next_state(board);
    //show_board(board);
//    add_live_cell(board, 5, 5);
    show_board(board);
//    add_live_cell(board, 2, 2);
//    show_board(board);
//    save_board(board);



    return 0;
}
