#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename I, typename S>
class CSVParser {
private:

    ifstream& data;
    const char separ;
    const char scr_sym;
    const bool scr_mode;

public:

 CSVParser(ifstream& data,  bool scr_mode = false, char separ = ',', char scr_sym = '"') :data(data), scr_mode(scr_mode), separ(separ), scr_sym(scr_sym) {}

    class iterator : public std ::iterator
        < input_iterator_tag,   //тип итератора
          tuple<I, S>,          //тип значения
          long,                 //расстояние между ними
          const tuple<I, S>*,   //тип указателя
          const tuple<I, S>& >  //тип ссылки
    {
    private:

        ifstream& file;
        tuple<I, S>* T = nullptr;


        vector<string> vec_of_str;
        int pos_in_vec = -1;

        CSVParser* parser = nullptr;

        int curr_row = 0;
        int curr_col = 0;

    public:

        //берем одну строку, они разделены запятой, делим на слова, экранированные с двух сторон, и засовываем в вектор строк

        vector<string> splitByDelim(const string& s) {
            
            vector<string> table_fields;
            int prev_pos = -1;

            for (int i = 0; i < s.size(); ++i) {

                //проверяем вокруг
                if (s[i] != parser->separ)continue;
                if (parser->scr_mode && i > 0 && i < s.size() - 1 && s[i - 1] == parser->scr_sym && s[i + 1] == parser->scr_sym)
                {
                    continue;
                }

                //если экранирование только с одной стороны, считаем за ошибку
                if (parser->scr_mode && i > 0 && i < s.size() - 1 && s[i - 1] == parser->scr_sym && s[i + 1] != parser->scr_sym) 
                {
                    throw exception((string("Error: Row = ") + to_string(curr_row + 1) + " Column: " + to_string(curr_col + 1)).c_str());
                }

                //добавляем подстроку в вектор
                table_fields.push_back(s.substr(prev_pos + 1, i - prev_pos - 1));
                prev_pos = i;

            }
            table_fields.push_back(s.substr(prev_pos + 1, s.size() - prev_pos + 1));

            return table_fields;
        }



        //конструктор - берем строку -> обрезаем слово и засовываем в кортеж двойной 
        explicit iterator(ifstream& file, CSVParser* pm) : file(file), parser(pm) {
            S str;
            getline(file, str);

            vec_of_str = splitByDelim(str);

            T = new tuple<I, S>(1, vec_of_str[0]);
            pos_in_vec = 0;
        }

       
        explicit iterator(tuple<I, S>* ptr, ifstream& file, CSVParser* pm) : file(file), parser(pm) {
            T = ptr;
        }

   

       //итерируемся по файлу
        iterator& operator++() {
                  
            if (pos_in_vec >= vec_of_str.size() - 1) {
                S str;

                //проверяем данные в строке
                if (file.good() == false) {
                    throw exception("File error!");

                }

                //не дойдя до конца - берем строку
                while (!file.eof()) {
                    getline(file, str);
                    if (str.size() > 0) {
                        break;
                    }
                }
             

                if (str.size() == 0 && file.eof()) 
                { 
                    delete T;
                    T = nullptr; 
                    return *this; 
                }

                curr_row++;
                vec_of_str = splitByDelim(str);

                //при переходе на след строку инкриментируемм индекс
                //изначально единица
                get<0>(*T)++;
                get<1>(*T) = vec_of_str[0];
                pos_in_vec = 0;
                curr_col = 0;
            }
            else {
                get<0>(*T)++;
                get<1>(*T) = vec_of_str[++pos_in_vec];
                }

            return *this;

        }
       
        
        bool operator==(iterator other) const { return T == other.T; }

        bool operator!=(iterator other) const { return T != other.T; }

        tuple<I, S> operator*() const { return *T; }
    };
    
    
    iterator begin() { return iterator(data, this); }
    
    iterator end() { return iterator(nullptr, data, this); }

};
