#include "console.h"
#include <iostream>

string console::get_com_option(){
    string com;
    cin >> com;
    return com;
}

string console::get_com_arguments() {
    string com, arg;
    cin >> com;
    unsigned int k=0;
    while(com[k]!=' '){
        k++; }
    k++;
    for ( unsigned int i =0; i<2; i++){
        arg[i] = com[k];
        k++;
    }
return arg;
}



