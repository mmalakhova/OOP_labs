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
    nucls n;
    size_t index = (size_t)ceil((float)(num) / (float)NUCL) - 1;
    size_t shift = (NUCL - ((num) - NUCL * index)) * 2;
    size_t mask = (3 << shift);
    n = static_cast<nucls>(((rna.rna[index]) & mask) >> shift);
    return n;
    //return rna.get_nucl(num);
}

RNA::reference RNA ::operator[](size_t idx) {
    return reference(idx, *this);
}

RNA::reference& RNA::reference :: operator=(nucls n) {
    size_t mask = 3;
    size_t idx_nuc = rna.nuc_count % NUCL + 1;
    rna.rna[rna.sizet_count] &= ~(mask << (NUCL - idx_nuc));
    mask = n;
    rna.rna[rna.sizet_count] |= (mask << (NUCL - idx_nuc));
    return *this;
}

RNA::reference::~reference() {
    num = 0;
    rna.~RNA();
}

RNA::reference::reference(size_t n , RNA &rna) :num(n), rna(rna) {
}

RNA::reference &RNA::reference::operator=(reference reference1) {
    nucls n;
    size_t index = (size_t)ceil((float)(reference1.num) / (float)NUCL) - 1;
    size_t shift = (NUCL - ((reference1.num) - NUCL * index)) * 2;
    size_t mask = (3 << shift);
    n = static_cast<nucls>(((reference1.rna.rna[index]) & mask) >> shift);

    rna[num] = n;
    return (*this);
}

nucls RNA::get_nucl(size_t idx) const {
    {
        size_t mask = 3;
        size_t idx_nuc = idx % NUCL + 1;
        size_t nuc = (rna[(size_t)ceil((float)idx/(float)NUCL)] & (mask << (NUCL - idx_nuc))) >> (NUCL - idx_nuc);
        switch (nuc) {
            case 0:
                return A;
            case 1:
                return G;
            case 2:
                return C;
            case 3:
                return T;
            default: break;
        }
    }
    return A;//Clion was mad
}



RNA::RNA(const RNA& rna_to_copy) {
    nuc_count = rna_to_copy.nuc_count;
    sizet_count = rna_to_copy.sizet_count;
    rna = new size_t[sizet_count];
    memcpy(rna, rna_to_copy.rna, sizeof(size_t)* sizet_count);
}


void RNA::add_nucl(int nucl) {
    if (rna == nullptr) {
        rna = new size_t[1];
        rna[0] = (size_t)nucl << ((NUCL * (sizet_count + 1) - nuc_count) * 2 - 2);
        nuc_count++;
        sizet_count++;
    }else if (nuc_count / sizet_count >= NUCL) {
        auto* new_arr = new size_t[sizet_count + 1];
        for (size_t i = 0; i < sizet_count; i++) {
            new_arr[i] = rna[i];
        }

        new_arr[sizet_count] = (size_t)nucl << ((NUCL * (sizet_count + 1) - nuc_count) * 2 - 2);
        delete[] rna;
        rna = nullptr;
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
    for ( size_t i =idx; i <= nuc_count; i++){
        size_t nuc = (*this).rna[i];
        second.add_nucl(nuc);
    }
    trim(idx);
    /*auto new_sizet_count = (size_t)ceil((float)(nuc_count-idx)/(float)NUCL);
     second.rna = new size_t[new_sizet_count];
     second.sizet_count = new_sizet_count;
     second.nuc_count = nuc_count - idx;
     for (size_t i = 0; i < new_sizet_count; i++) {
         second.rna[i] = rna[i + sizet_count];
     }
     size_t new_num = sizet_count - (idx / NUCL + 1);
     for (size_t i = 0; i < new_num; i++) {
         second.rna[i] <<= idx - NUCL * (idx / NUCL);
     }
     // зануление скопированной части исходной цепочки
     rna[sizet_count - (idx / NUCL + 1)] >>= NUCL - (idx % NUCL);
     rna[sizet_count - (idx / NUCL + 1)] <<= NUCL - (idx % NUCL);
     */

    return second;
}

RNA RNA::trim(size_t idx) {
    sizet_count = (size_t)ceil((float)(idx - 1)/(float)NUCL);
    nuc_count = idx-1;
    auto* foo = new size_t[sizet_count];
    for (size_t i = 0; i < sizet_count; i++) {
        foo[i] = rna[i];
    }
    delete[](rna);
    rna = foo;
    return (*this);
}



size_t RNA::length(const RNA& some_rna) {
    return some_rna.nuc_count + 1;
}

RNA operator+( RNA& rna1, RNA& rna2) {
    RNA r;
    r = rna1;
    for ( size_t i =1; i <= rna2.nuc_count; i++) {

        size_t index = (size_t)ceil((float)i / (float)NUCL) - 1;
        size_t shift = (NUCL - (i - NUCL * index)) * 2;
        size_t mask = (3 << shift);
        nucls nucl = static_cast<nucls>((rna2.rna[index] & mask) >> shift);
        r.add_nucl(nucl);
    }
    return r;

   /* for (size_t i = rna1.sizet_count ; i < new_sizet_count; i++) {
        r.rna[i] = rna2.rna[i - rna1.sizet_count];
    }
    if ((rna1.nuc_count % NUCL) != 0) {
        //при сдвиге соответвующие биты будут на каждой итерации цикла зануляться
        //нужна маска - только потом сдвиг
        //а потом еще маска, чтобы перенести на предыдущий size_t нуклеотидики
        size_t mask1 = sizeof(size_t) * 8;
        size_t mask2;
        for (size_t i = rna1.sizet_count-1; i < new_sizet_count; i++) {
            mask1 <<= (rna1.nuc_count % NUCL);
            r.rna[i + 1] &= mask1;
            r.rna[i] <<= (NUCL - rna1.nuc_count % NUCL);
            mask2 = mask1;
            mask2 >>= (rna1.nuc_count % NUCL);
            r.rna[i] |= mask2;
        }
    }*/
    return r;
}

bool RNA::operator==(const RNA& rna2) {
    if ( nuc_count != rna2.nuc_count) return false;
    if ( nuc_count == rna2.nuc_count == 0) return true;

    for (size_t i = 0; i < sizet_count-1 ; i++) {
        if (rna[i] != rna2.rna[i]) return false;
    }
    for(size_t i = ((sizet_count - 1)* NUCL +1); i <= nuc_count; i++){
        size_t index = (size_t)ceil((float)i / (float)NUCL) - 1;
        size_t shift = (NUCL - (i - NUCL * index)) * 2;
        size_t mask = (3 << shift);
        auto n1 = static_cast<nucls>((rna[index] & mask) >> shift);
        auto n2 = static_cast<nucls>((rna2.rna[index] & mask) >> shift);
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
        rna = nullptr;
        rna = new size_t(sizet_count);
        memcpy(rna, rna2.rna, sizet_count*sizeof(size_t));
    }
    return *this;
}

void RNA::print_rna() const{
    size_t tail;
    size_t mask = (size_t)3 << (sizeof(size_t) * 8 - 2);

    for (size_t i = 0; i < sizet_count; i++)
    {
        if ((nuc_count - i * NUCL) < NUCL)
        {
            tail = nuc_count - i * NUCL;
        }
        else tail = NUCL;

        for (size_t j = 0; j < tail; j++)
        {
            int nuc = (int)((rna[i] & (mask >> (2 * j))) >> (sizeof(size_t)*8 - 2*j - 2));

            switch (nuc) {
                case 0:
                    cout << "A";
                    break;
                case 1:
                    cout << "G";
                    break;
                case 2:
                    cout << "C";
                    break;
                case 3:
                    cout << "T";
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
    return get_nucl(n) ;
}