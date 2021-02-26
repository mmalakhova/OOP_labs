#ifndef RNA_RNA_H
#define RNA_RNA_H

#include <cstdio>
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <cmath>

const size_t NUCL = sizeof(size_t) * 4;

enum nucls {
    A, T, C, G
};

class RNA {
    size_t* rna;
    size_t nuc_count ;
    size_t sizet_count ;

public:
    void print_rna() const;
    class reference {
        RNA& rna;
        size_t  num;
    public:
        reference(size_t, RNA&);
        ~reference();
        operator nucls() const;
        reference& operator=(nucls);
        reference& operator=(reference);
    };

    RNA();
    ~RNA();
    RNA(const RNA&);

    void add_nucl(int);
    nucls get_nucl(size_t) const;

    RNA split(size_t);
    RNA trim(size_t);

    bool is_Complementary(RNA&);


    friend RNA operator +(RNA&, RNA&);
    bool operator !=(const RNA&);
    bool operator ==(const RNA&);
    RNA operator!();
    RNA& operator =(const RNA&);

    reference operator[](size_t);
    nucls operator[] (size_t) const;
};

#endif //RNA_RNA_H

