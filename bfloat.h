#ifndef BFLOAT_H_
#define BFLOAT_H_

#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;
class bfloat {
    uint16_t val;
public:
    bfloat(const bfloat &rv) : val(rv.val) {}
    //bfloat(bfloat &&rv) : val(std::move(rv.val)) {}
    template <typename T>
    explicit bfloat(T val) {
        float tmp = static_cast<float>(val);
        uint16_t* p = reinterpret_cast<uint16_t*>(&tmp);
        this->val = p[1];
    }
    bfloat() : val(0) {}

    operator float() const {
        float out = 0;
        uint16_t* outp = reinterpret_cast<uint16_t*>(&out);
        outp[1] = this->val;
        return out;
    }
    bfloat& operator +=(const bfloat& rv) {
        *this = *this + rv;
        return *this;
    }
    bfloat& operator -=(const bfloat& rv) {
        *this = *this - rv;
        return *this;
    }
    bfloat& operator *=(const bfloat& rv) {
        *this = *this * rv;
        return *this;
    }
    bfloat& operator /=(const bfloat& rv) {
        *this = *this / rv;
        return *this;
    }
    bool operator >(const bfloat& rv) {
        return static_cast<float>(*this) > static_cast<float>(rv);
    }
    bool operator >=(const bfloat& rv) {
        return static_cast<float>(*this) >= static_cast<float>(rv);
    }
    bool operator <(const bfloat& rv) {
        return static_cast<float>(*this) < static_cast<float>(rv);
    }
    bool operator <=(const bfloat& rv) {
        return static_cast<float>(*this) <= static_cast<float>(rv);
    }
    bfloat operator +(bfloat rv) {
        return bfloat(static_cast<float>(*this) + static_cast<float>(rv));
    }
    bfloat operator -(bfloat rv) {
        return bfloat(static_cast<float>(*this) - static_cast<float>(rv));
    }
    bfloat operator *(bfloat rv) {
        return bfloat(static_cast<float>(*this) * static_cast<float>(rv));
    }
    bfloat operator /(bfloat rv) {
        return bfloat(static_cast<float>(*this) / static_cast<float>(rv));
    }
    friend ostream& operator <<(ostream &os, const bfloat &val) {
        os << static_cast<float>(val);
        return os;
    }
};

class BFMat {
    int rows;
    int cols;
    bfloat* mat;
public:
    BFMat(int rows, int cols) : rows(rows), cols(cols) {
        this->mat = new bfloat[rows*cols];
    }
    BFMat* operator *(BFMat* rm) {
        assert(this->rows == rm->rows && this->cols == rm->cols);
        BFMat* out = new BFMat(this->rows, this->cols);
        for (int i = 0; i < this->rows*this->cols; ++i) {
            out->mat[i] = this->mat[i] * rm->mat[i];
        }
        return out;
    }
    BFMat* operator /(BFMat* rm) {
        assert(this->rows == rm->rows && this->cols == rm->cols);
        BFMat* out = new BFMat(this->rows, this->cols);
        for (int i = 0; i < this->rows*this->cols; ++i) {
            out->mat[i] = this->mat[i] / rm->mat[i];
        }
        return out;
    }
    BFMat* operator +(BFMat* rm) {
        assert(this->rows == rm->rows && this->cols == rm->cols);
        BFMat* out = new BFMat(this->rows, this->cols);
        for (int i = 0; i < this->rows*this->cols; ++i) {
            out->mat[i] = this->mat[i] + rm->mat[i];
        }
        return out;
    }
    BFMat* operator -(BFMat* rm) {
        assert(this->rows == rm->rows && this->cols == rm->cols);
        BFMat* out = new BFMat(this->rows, this->cols);
        for (int i = 0; i < this->rows*this->cols; ++i) {
            out->mat[i] = this->mat[i] - rm->mat[i];
        }
        return out;
    }
    BFMat* dot(BFMat* rm) {
        assert(this->cols == rm->rows);
        BFMat* out = new BFMat(this->rows, rm->cols);
        for (int i = 0; i < this->rows; ++i ) {
            for (int j = 0; j < rm->cols; ++j ) {
                for (int k = 0; k < rm->rows; ++k ) {
                    out->mat[i*rm->cols + j] += this->mat[i*this->cols + k] + rm->mat[j + k*rm->cols];
                }
            }
        }
        return out;
    }
};


#endif // BFLOAT_H_
