#include "console.h"
#include <iostream>

string console::get_com_option(){
    string comand;
    cin >> comand;
    return comand;
}

string console::get_com_arguments() {
    string com;
    char arg[2];
    getline(std::cin, com);

    arg[0] = com[com.length()-2];
    arg[1] = com[com.length()-1];

    return arg;
}



