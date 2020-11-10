#ifndef RNA_RNA_H
#define RNA_RNA_H

#include <cstdio>
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <cmath>
//#define max(x, y) x >= (y) ? (x) : y
const size_t NUCL = sizeof(size_t) * 4;

enum nucls {
    A, T, C, G
};

class RNA {
    size_t* rna = nullptr;
    size_t nuc_count = 0;
    size_t sizet_count = 0;
    nucls get_nucl(size_t) const;
public:
    void print_rna() const;
    class reference {
        RNA& rna;
        size_t  num;
    public:
        reference(size_t, RNA&);
        ~reference();
        explicit operator nucls() const;
        reference& operator=(nucls);
        reference& operator=(reference);
    };

    RNA();
    ~RNA();
    RNA(const RNA&);

    void add_nucl(int);

    RNA split(size_t);
    RNA trim(size_t);

    bool is_Complementary(RNA&);
    static size_t  length(const RNA&);

    friend RNA operator +(RNA&, RNA&);
    bool operator !=(const RNA&);
    bool operator ==(const RNA&);
    RNA operator!();
    RNA& operator =(const RNA&);
    reference operator[](size_t);
    nucls operator[] (size_t) const;
};

#endif //RNA_RNA_H

