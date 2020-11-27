#include <iostream>
#include <fstream>
#include <cstring>
#include "game_board.h"
#include "parser.h"
#include "console.h"

using namespace std;


int main() {
game_board g;
g.load_board();

//g.show_board();
cout << g;



    game_board game;
    console c;
    while (!game.end_game()){
       parser pars(&game);
       pars.get_comand(c);
    }

//    string str = "Hello man";
//    unsigned int k=0;
//    while(str[k]!=' ')
//    {  k++; }
//    k++;
//    //cout << endl;
//    while(str[k]!='\0')
//    { cout << str[k]; k++; }

//    char a[2][4] = { { LIVE, LIVE,LIVE, LIVE }, { LIVE, LIVE, LIVE, LIVE } };
//    char b[2][4] = { { DEAD, DEAD, DEAD, DEAD}, { DEAD, DEAD,DEAD, DEAD } };
//    swap(a,b);
//    for (int i =0;i < 2; i++){
//        for (int j =0; j < 4; j++){
//            cout << a[i][j] << " " << b[i][j] << endl;
//        }
//    }


   return 0;
}
