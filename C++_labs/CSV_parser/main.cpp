#include <iostream>
#include <tuple>
#include <fstream>
#include "CSVParser.h"

using namespace std;

int main() {
    ifstream file("in.csv");
    CSVParser<int, string>parser (file, 1, '\n', ',', '\"');
    for (const tuple<int, std::string>& rs : parser) { // считываем по 1 кортежу из строки
        std::cout << rs << std::endl;
    }
}
