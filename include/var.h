#ifndef _var
#define _var

#define MEMSIZE 30000

#include <iostream>
#include <assert.h>
#include <cstdio>
#include <cstdint>
#include <string>
#include <cstring>
#include <stack>
#include <vector>

extern int cur_data_ptr;

class var {
    int8_t data;
    int pool_index;

public:
    // var index starts from 1
    var(int8_t d = 0);

    var(const var &another, bool shadow = false);

    void output();

    void input();

    void test_output();

    void output_digit2char();

    void increment(const uint8_t d = 1);

    void operator+=(const uint8_t d);

    void decrement(const uint8_t d = 1);

    void operator-=(const uint8_t d);

    void while_begin();

    void while_end();

    void copy(var &another);

    var &operator=(var &another);

    void move_to(var &another);

    void clear();

    void set(const uint8_t v);

    var &operator=(const uint8_t v);

    void if_begin();

    void if_begin_zero();

    void if_end();

    void to_bool();

    void flip();

    void is_negative(var &result);

    void greater(var &another, var &result);

    var &operator>(var &another);

    var &operator>(const uint8_t d);

    void greater(const uint8_t d, var &result);

    void greater_eq(const uint8_t d, var &result);

    void greater_eq(var &another, var &result);

    var &operator>=(var &another);

    var &operator<(const uint8_t d);

    var &operator<(var &another);

    var &operator<=(var &another);

    var &operator<=(const uint8_t d);

    var &operator>=(const uint8_t d);

    void equal(var &another, var &ret);

    void equal(const uint8_t d, var &ret);

    var &operator==(var &another);

    var &operator==(const int8_t d);

    var &operator!=(var &another);

    var &operator!=(const int8_t d);

    void add(var &another, var &ret);

    var &operator+(var &another);

    var &operator+(const uint8_t d);

    void minus(var &another, var &ret);

    var &operator-(var &another);

    var &operator-(const uint8_t d);

    void multiply(var &another, var &ret);

    var &operator*(var &another);

    var &operator*(const int8_t d);

    void operator*=(const uint8_t d);

    void divide(var &another, var &ret);

    var &operator/(var &another);

    var &operator/(const int8_t d);

    void operator/=(const uint8_t d);

    void swap(var &another);

    void input_as_integer();

    void output_as_integer();

    var &operator&&(var &another);

    var &operator||(var &another);

    var &operator!();

    var &operator%(var &another);

    var &operator%(const uint8_t d);

};

void if_end();

void test_output(int index = cur_data_ptr);

void optimize(FILE *, FILE *);

void print_str(const char *str);

void mem_reset();

void output(char);

#endif
