#include "var.h"

class vararray {
    int length;
    var *data;

public:
    vararray(int len) {
        length = len;
        data = new var[len * 2];
        for (int i = len; i <= 2 * len - 1; i++) {
            data[i] = i - len;
        }
        // data[len:2*len] = { 0, 1, ..., len-1 }
    }

    var &operator[](int index) {
        return this->data[index];
    }

    var &operator[](var &another) {
        var *ret = new var();
        for (int i = 0; i < length; i++) {
            (data[i + length] == another).if_begin();
            ret->copy(data[i]);
            if_end();
        }
        return *ret;
    }

    void output() {
        ::output('[');
        for (int i = 0; i < length; i++) {
            data[i].output_as_integer();
            if (i != length - 1) {
                ::output(',');
            }
        }
        ::output(']');
    }
};