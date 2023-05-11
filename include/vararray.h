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
        // data[len : 2*len] = { 0, 1, ..., len-1 }
    }

    // return reference
    var &operator[](int index) {
        return this->data[index];
    }

    // return a rvalue
    var &val(var index) {
        var *ret = new var();
        for (int i = 0; i < length; i++) {
            (data[i + length] == index).if_begin();
            ret->copy(data[i]);
            if_end();
        }
        return *ret;
    }

    void set(var index, var value) {
        for (int i = 0; i < length; i++) {
            (data[i + length] == index).if_begin();
            data[i] = value;
            if_end();
        }
    }

    void set(var index, int value) {
        for (int i = 0; i < length; i++) {
            (data[i + length] == index).if_begin();
            data[i] = value;
            if_end();
        }
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