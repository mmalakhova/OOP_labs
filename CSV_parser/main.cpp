#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <algorithm>
#include "parser.h"

using namespace std;


template<class TupType, size_t... I>
void print(const TupType& _tup, index_sequence<I...>, ostream& out)
{

    (..., (out << (I == 0 ? "" : ", ") << get<I>(_tup)));

}


template<class...T>
ostream& operator<<(ostream& out, const tuple<T...>& tup) {
    
    print(tup, make_index_sequence<sizeof...(T)>(), out);
    return out;
}




int main()
{
    ifstream file("data2.csv");
 
    CSVParser<int, string> parser(file, true, ';');
    
    try {
        for (tuple<int, string> rs : parser) {
            cout << rs << endl;
            system("pause");
        }
    }
    catch (exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;

    }
 
    return 0;
}

