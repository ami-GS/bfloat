#include "bfloat.h"
#include <iostream>


extern "C" {
    bfloat* bfloat_new(int val) {return new bfloat(val);}
    void show(bfloat* bf) {std::cerr << *bf << std::endl;}
}

