#include "RNA.h"
using namespace std;

RNA::RNA() {
    nuc_count = 0;
    sizet_count = 0;
    rna = nullptr;
}

RNA::~RNA() {
    delete rna;
}

RNA::reference::operator nucls() const {
    return rna.get_nucl(num);
}

RNA::reference RNA ::operator[](size_t idx) {
    return reference(idx, *this);
}

RNA::reference & RNA::reference :: operator=(nucls n) {
    if (num > rna.nuc_count){
        for( size_t i = 0; i < (rna.nuc_count - num); i++){
            rna.add_nucl(n);
        }
    } else {
        size_t idx_nuc = (size_t) ceil((float)num /(float) NUCL) - 1 ;
        size_t shift = (NUCL - (num - NUCL * idx_nuc)) * 2;
        rna.rna[idx_nuc] = (rna.rna[idx_nuc] & ~((size_t)3 << shift)) |((size_t)n << shift);
    }
    return (*this);
}

RNA::reference::~reference() {
    num = 0;
    rna.~RNA();
}

RNA::reference::reference(size_t n , RNA &rna) : num(n), rna(rna) {
}

RNA::reference &RNA::reference::operator=(reference reference1) {
    nucls n;
    n = reference1.rna.get_nucl(reference1.num);

    rna[num] = n;
    return (*this);
}

nucls RNA::get_nucl(size_t idx) const {
    size_t mask = 3;
    size_t idx_sizet =(size_t) ceil((float)idx /(float) NUCL) -1;
    auto nuc = static_cast<nucls>((rna[idx_sizet] & (mask << (NUCL - (idx - NUCL * idx_sizet)) * 2))>> ((NUCL - (idx - NUCL * idx_sizet)) * 2));
    return nuc;
}



RNA::RNA(const RNA& rna_to_copy) {
    nuc_count = rna_to_copy.nuc_count;
    sizet_count = rna_to_copy.sizet_count;
    rna = new size_t[sizet_count];
    for ( size_t i = 0; i < sizet_count; i++){
        rna[i] = rna_to_copy.rna[i];
    }
}


void RNA::add_nucl(int nucl) {
    if (rna == nullptr) {
        rna = new size_t[1];
        rna[0] = (size_t)nucl << ((NUCL * (sizet_count + 1) - nuc_count) * 2 - 2);
        nuc_count++;
        sizet_count++;
    }
    else if (nuc_count / sizet_count >= NUCL) {
        auto* new_arr = new size_t[sizet_count + 1];
        for (size_t i = 0; i < sizet_count; i++) {
            new_arr[i] = rna[i];
        }

        new_arr[sizet_count] = (size_t)nucl << ((NUCL * (sizet_count + 1) - nuc_count) * 2 - 2);
        delete[] rna;
       // rna = nullptr;
        rna = new_arr;
        sizet_count++;
        nuc_count++;
    }
    else {
        size_t mask;
        mask = ((size_t)nucl << ((NUCL * sizet_count - nuc_count) * 2 - 2));
        rna[sizet_count-1] = rna[sizet_count-1] | mask;
        nuc_count++;
    }
}

RNA RNA::split(size_t idx) {
    RNA second;
    for (size_t i = idx; i <= nuc_count; i++){
        size_t nuc = (*this)[i];
        second.add_nucl(nuc);
    }

    sizet_count = (size_t)ceil((float)(idx - 1)/(float)NUCL);
    nuc_count = idx-1;
    auto* foo = new size_t[sizet_count];
    for (size_t i = 0; i < sizet_count; i++) {
        foo[i] = rna[i];
    }
    delete[] rna;
    //rna = nullptr;
    rna = foo;
    return second;
}

RNA RNA::trim(size_t idx) {
    sizet_count = (size_t)ceil((float)(idx - 1)/(float)NUCL);
    nuc_count = idx-1;
    auto* foo = new size_t[sizet_count];
    for (size_t i = 0; i < sizet_count; i++) {
        foo[i] = rna[i];
    }
    delete[] rna;
    rna = foo;
    return (*this);
}

RNA operator+( RNA& rna1, RNA& rna2) {
    RNA r;
    r = rna1;
    for ( size_t i =1; i <= rna2.nuc_count; i++) {

//        size_t index = (size_t)ceil((float)i / (float)NUCL) - 1;
//        size_t mask = ((size_t)3 << ((NUCL - (i - NUCL * index)) * 2));
//        auto nucl = static_cast<nucls>((rna2.rna[index] & mask) >> ((NUCL - (i - NUCL * index)) * 2));
//        r.add_nucl(nucl);
        r.add_nucl(rna2[i]);
    }
    return r;
}

bool RNA::operator==(const RNA& rna2) {

    if ( nuc_count != rna2.nuc_count) return false;
    if ( nuc_count == rna2.nuc_count == 0) return true;
    for (size_t i = 0; i < sizet_count-1 ; i++) {
        if (rna[i] != rna2.rna[i]) return false;
    }
    for(size_t i = ((sizet_count - 1)* NUCL +1); i <= nuc_count; i++){
        size_t idx = (size_t)ceil((float)i / (float)NUCL) - 1;
        size_t shift = (NUCL - (i - NUCL * idx)) * 2;
        auto n1 = static_cast<nucls>((rna[idx] & ((size_t)3 << shift)) >> shift);
        auto n2 = static_cast<nucls>((rna2.rna[idx] & ((size_t)3 << shift)) >> shift);
        if ( n1 != n2) {
            return false;
        }
    }

    return true;

    //return !(rna[sizet_count] ^ rna2.rna[sizet_count]);
}

bool RNA::operator!=(const RNA& rna2) {
    return !(*this == rna2);
}


RNA RNA::operator!() {
    for (size_t i = 0; i < nuc_count / NUCL; i++) {
        rna[i] = ~rna[i];
    }
    if (nuc_count % NUCL != 0) {
        for (size_t i = 0; i < nuc_count / NUCL + 1; i++) {
            rna[i] = ~rna[i];
        }
        rna[nuc_count / NUCL + 1] >>= NUCL - (nuc_count % NUCL);
        rna[nuc_count / NUCL + 1] <<= NUCL - (nuc_count % NUCL);
    }
    return (*this);
}


RNA& RNA::operator=(const RNA& rna2) {
    if (this == &rna2) return (*this);

    nuc_count = rna2.nuc_count;
    sizet_count = rna2.sizet_count;
    if (sizet_count != 0) {
        delete[] rna;
        //rna = nullptr;
        rna = new size_t(sizet_count);
        memcpy(rna, rna2.rna, sizet_count*sizeof(size_t));
    }
    return (*this);
}

void RNA::print_rna() const{
    size_t tail;
    size_t mask = (size_t)3 << (sizeof(size_t) * 8 - 2);

    for (size_t i = 0; i < sizet_count; i++) {
        if ((nuc_count - i * NUCL) < NUCL) {
            tail = nuc_count - i * NUCL;
        }
        else tail = NUCL;
        for (size_t j = 0; j < tail; j++) {
            int nuc = (int)((rna[i] & (mask >> (2 * j))) >> (sizeof(size_t)*8 - 2*j - 2));
            switch (nuc) {
                case 0:
                    cout << "A";
                    break;
                case 1:
                    cout << "T";
                    break;
                case 2:
                    cout << "C";
                    break;
                case 3:
                    cout << "G";
                    break;
                default:  break;
            }
        }
    }
    cout << endl;
}

bool RNA::is_Complementary(RNA& rna2) {
    return (*this == !rna2);
}

nucls RNA::operator[](size_t n) const {
    size_t mask = 3;
    size_t idx_sizet =(size_t)ceil((float)n /(float) NUCL) - 1;
    auto nuc = static_cast<nucls>((rna[idx_sizet] & (mask << (NUCL - (n - NUCL * idx_sizet)) * 2))
            >> ((NUCL - (n - NUCL * idx_sizet)) * 2));
    return nuc;
}
