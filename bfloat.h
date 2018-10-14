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



#endif // BFLOAT_H_
