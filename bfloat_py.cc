#include "bfloat.h"
#include <iostream>


extern "C" {
    bfloat* bfloat_new(int val) {return new bfloat(val);}
    void show(bfloat* bf) {std::cerr << *bf << std::endl;}
    BFMat* BFMat_new(int rows, int cols) {return new BFMat(rows, cols);}
    BFMat* EW_mul(BFMat* left, BFMat* right) {return *left * right;}
    BFMat* EW_div(BFMat* left, BFMat* right) {return *left / right;}
    BFMat* EW_add(BFMat* left, BFMat* right) {return *left + right;}
    BFMat* EW_sub(BFMat* left, BFMat* right) {return *left - right;}
    BFMat* dot(BFMat* left, BFMat* right) {return left->dot(right);}
}

