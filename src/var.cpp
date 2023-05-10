#include "../include/var.h"

#define print_times(ch, times) for(int i=0;i<(times);i++){putchar(ch);}


int8_t pool[MEMSIZE];
int cur_data_ptr = 0;
int cur_var_num = 0;


// elements in if-flag-stack cannot be reached by user
std::stack<var *> if_flag_stack;


// var index starts from 1
// pool[0] is a helper unit
var::var(int8_t d) {
    assert(pool[0] == 0);
    // if cur_data_ptr is not at #0, reset it as #0
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    this->data = d;
    pool[cur_var_num + 1] = d;
    this->pool_index = cur_var_num + 1;
    cur_var_num++;

    int inner_increment = 0;

    if (d > 8 && this->pool_index <= 16) {
        // this->pool_index <= 16 : do not take too long to reach #0
        printf("++++++++");
        inner_increment = data / 8;
        putchar('[');
        print_times('>', this->pool_index);
        print_times('+', inner_increment);
        print_times('<', this->pool_index);
        putchar('-');
        putchar(']');
    }

    print_times('>', this->pool_index);
    int outer_increment = data - inner_increment * 8;
    assert(outer_increment >= 0);
    print_times('+', outer_increment);
    print_times('<', this->pool_index);
}


var::var(const var &another, bool shadow) {

    if (shadow) {
        this->pool_index = another.pool_index;
        return;
    }

    assert(&another != this);
    // create a copy
    pool[cur_var_num + 1] = another.data;
    this->pool_index = cur_var_num + 1;
    cur_var_num++;

    // copy needs a cpp reference
    // create a shadow var
    var shad = var(another, true);
    this->copy(shad);  // this->data = another->data
}

// output the value in this unit
void var::output() {
    // if cur_data_ptr is not at #0, reset it as #0
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    print_times('>', pool_index);
    putchar('.');
    print_times('<', pool_index);
}

// place the input value in this unit
void var::input() {
    // if cur_data_ptr is not at #0, reset it as #0
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    print_times('>', pool_index);
    putchar(',');
    print_times('<', pool_index);
}

void test_output(int index) {
    assert(0);
    printf("test output: %c\n", pool[index]);
}

void var::test_output() {
    assert(0);
    printf("test output: %c\n", pool[this->pool_index]);
}

void var::output_digit2char() {
    var tmp(*this);
    tmp.increment('0');

    print_times('>', tmp.pool_index);
    printf(".[-]");
    print_times('<', tmp.pool_index);
    cur_var_num--;
}

void var::decrement(const uint8_t d) {
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    int inner_decrement = 0;
    if (d > 8 && pool_index <= 16) {
        inner_decrement = d / 8;
        print_times('+', 8);
        putchar('[');
        print_times('>', pool_index);
        print_times('-', inner_decrement);
        print_times('<', pool_index);
        putchar('-');
        putchar(']');
    }

    int outer_decrement = d - inner_decrement * 8;
    print_times('>', pool_index);
    print_times('-', outer_decrement);
    print_times('<', pool_index);
    pool[pool_index] -= d;
}

void var::operator-=(const uint8_t d) {
    decrement(d);
}

void var::increment(const uint8_t d) {
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    int inner_increment = 0;
    if (d > 8 && pool_index <= 16) {
        // pool_index <= 16 : do not take too long to reach #0
        inner_increment = d / 8;
        print_times('+', 8);
        putchar('[');
        print_times('>', pool_index);
        print_times('+', inner_increment);
        print_times('<', pool_index);
        putchar('-');
        putchar(']');
    }

    int outer_increment = d - inner_increment * 8;
    print_times('>', pool_index);
    print_times('+', outer_increment);
    print_times('<', pool_index);
    pool[pool_index] += d;
}

void var::operator+=(const uint8_t d) {
    increment(d);
}

void var::while_begin() {
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    print_times('>', pool_index);
    putchar('[');
    print_times('<', pool_index);
}

void var::while_end() {
    // if pc never enters the loop, it's still correct
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    print_times('>', pool_index);
    putchar(']');
    print_times('<', pool_index);
}

void var::move_to(var &another) {
    assert(&another != this);
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    print_times('>', pool_index);
    printf("[");
    printf("-");
    print_times('<', pool_index);
    print_times('>', another.pool_index);
    printf("+");
    print_times('<', another.pool_index);
    print_times('>', pool_index);
    printf("]");
    print_times('<', pool_index);

    pool[another.pool_index] = pool[pool_index];
    pool[pool_index] = 0;
}

void var::copy(var &another) {
    assert(&another != this);
    // create a temporary unit at the end of the pool
    var tmp;

    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    clear();

    print_times('>', another.pool_index);
    printf("[");
    printf("-");
    print_times('<', another.pool_index);
    print_times('>', pool_index);
    printf("+");
    print_times('<', pool_index);
    print_times('>', tmp.pool_index);
    printf("+");
    print_times('<', tmp.pool_index);
    print_times('>', another.pool_index);
    printf("]");
    print_times('<', another.pool_index);

    tmp.move_to(another);   // move back
    // tmp.clear();
    cur_var_num--;
    // tmp is the last one in pool
    this->data = another.data;
}

var &var::operator=(var &another) {
    // return an reference - this won't create a new object
    // *this <- anther
    // *this doesn't become an reference of another, so `pool_index` is not copied
    // only copy the value
    copy(another);
    return *this;
}

void var::clear() {
    print_times('<', cur_data_ptr);
    cur_data_ptr = 0;

    print_times('>', pool_index);
    printf("[-]");
    print_times('<', pool_index);
    data = 0;
}

void var::set(const uint8_t v) {
    clear();
    if (v == 0) {
        return;
    }

    print_times('<', cur_data_ptr);
    int inner_increment = 0;

    if (v > 8 && pool_index <= 16) {    // pool_index <= 16 : do not take too long to reach #0
        printf("++++++++");             // pool[0] = 8;
        inner_increment = v / 8;
        putchar('[');
        print_times('>', pool_index);
        print_times('+', inner_increment);
        print_times('<', pool_index);
        putchar('-');
        putchar(']');
    }
    print_times('>', pool_index);
    int outer_increment = v - inner_increment * 8;
    print_times('+', outer_increment);
    print_times('<', pool_index);
    // pool[0] = 0;
    // cur_data_ptr = 0;
    // current data pointer: #0
}

var &var::operator=(const uint8_t v) {
    set(v);
    return *this;
}

void var::to_bool() {
    var tmp(1);

    if_begin();
    set(1);
    tmp.clear();
    if_end();

    tmp.if_begin();
    clear();
    tmp.if_end();

    tmp.clear();
    cur_var_num -= 3;
    // destroy tmp ans 2 if-flags
}

void var::if_begin() {
    // execute when *this is non-zero
    var *flag = new var(*this);
    // *flag is a copy of *this
    if_flag_stack.emplace(flag);
    // enter while-loop when *flag is non-zero
    flag->while_begin();
    // make sure only execute once
    flag->clear();
    // if-flag cannot be accessed by user because it is in stack
}

void var::if_begin_zero() {
    // execute when *this is non-zero
    var *flag = new var(*this);
    // *flag is a copy of *this
    flag->flip();
    if_flag_stack.emplace(flag);
    // enter while-loop when *flag is zero
    flag->while_begin();
    // make sure only execute once
    flag->clear();
}

void var::if_end() {
    assert(!if_flag_stack.empty());
    var *flag = if_flag_stack.top();
    if_flag_stack.pop();

    flag->while_end();

    delete flag;
    // flag cannot be easily released in pool
    // (although destroyed in C++)
    // for the reason that *flag may not be at the last unit
}

void if_end() {
    assert(!if_flag_stack.empty());
    var *flag = if_flag_stack.top();
    if_flag_stack.pop();
    flag->while_end();
    delete flag;
}

void var::flip() {
    // flip a Boolean value
    var tmp(1);

    if_begin();
    clear();
    tmp.clear();
    if_end();

    tmp.if_begin();
    set(1);
    tmp.if_end();

    // release tmp from the pool
    // and 2 if-flags
    tmp.clear();
    cur_var_num -= 3;
}

void var::is_negative(var &result) {
    assert(&result != this);
    var tmp(127);
    result.clear();
    greater(tmp, result);
    // if (uint8_t)*this is greater than 0x7f,
    // then *this is negative as an unsigned

    tmp.clear();
    cur_var_num--;
}

void var::greater(var &another, var &result) {
    assert(&result != this);
    // `another` can be a reference of *this, that works!
    // return true if (uint8_t)*this > (uint8_t)another
    // assert(this->data >= 0 && another.data >= 0);
    // consider both as unsigned interger, although not always as such
    var tmp1(*this), tmp2(another), tmp3;
    result.clear();

    tmp1.while_begin();

    tmp3.copy(tmp2);
    tmp3.flip();
    tmp3.if_begin();    // when tmp2 is zero and tmp1 isn't zero
    result.set(1);      // the result is true
    tmp3.if_end();

    tmp1.decrement();
    tmp2.decrement();

    tmp1.while_end();

    // destroy tmp1, tmp2, tmp3 from the pool
    // and an if-flag
    // is this buggy?
    tmp1.clear();
    tmp2.clear();
    tmp3.clear();
    cur_var_num -= 4;
}

var &var::operator>(var &another) {
    var *p = new var;
    greater(another, *p);
    return *p;
}

void var::greater(const uint8_t d, var &result) {
    var D(d);
    greater(D, result);
    D.clear();
    cur_var_num--;
}

var &var::operator>(const uint8_t d) {
    var *p = new var;
    greater(d, *p);
    return *p;
}

void var::greater_eq(var &another, var &result) {
    var t;
    greater(another, t);

    var r(t);
    r.flip();
    r.if_begin();       // if *this <= another
    equal(another, t);
    r.if_end();
    result.copy(t);

    r.clear();
    t.clear();
    cur_var_num -= 3;   // also destroy if-flag
}

void var::greater_eq(const uint8_t d, var &result) {
    var t;
    greater(d, t);

    var r(t);
    r.flip();
    r.if_begin();       // if *this <= d
    equal(d, t);
    r.if_end();
    result.copy(t);

    r.clear();
    t.clear();
    cur_var_num -= 3;
}

var &var::operator>=(var &another) {
    var *p = new var;
    greater_eq(another, *p);
    return *p;
}

var &var::operator<(const uint8_t d) {
    var *p = new var;
    greater_eq(d, *p);
    p->flip();
    return *p;
}

var &var::operator>=(const uint8_t d) {
    var *p = new var;
    greater_eq(d, *p);
    return *p;
}

void var::equal(var &another, var &ret) {
    var ret1, ret2;
    greater(another, ret1);
    another.greater(*this, ret2);

    ret1.flip();
    ret2.flip();
    ret.clear();

    ret1.if_begin();    // if ret1 == 0 && ret2 == 0
    ret2.if_begin();
    ret.set(1);
    ret2.if_end();
    ret1.if_end();

    // destroy ret1, ret2 from the pool
    // and 2 if-flags
    ret1.clear();
    ret2.clear();
    cur_var_num -= 4;
}

void var::equal(const uint8_t d, var &ret) {
    var D(d);
    equal(D, ret);
    D.clear();
    cur_var_num--;
}

var &var::operator==(var &another) {
    var *p = new var;
    equal(another, *p);
    return *p;
}

var &var::operator==(const int8_t d) {
    var *p = new var;
    equal(d, *p);
    return *p;
}

var &var::operator!=(var &another) {
    var *p = new var;
    equal(another, *p);
    p->flip();
    return *p;
}

var &var::operator!=(const int8_t d) {
    var *p = new var;
    equal(d, *p);
    p->flip();
    return *p;
}

void var::add(var &another, var &ret) {
    var tmp(another);
    ret.copy(*this);

    tmp.while_begin();
    tmp.decrement();
    ret.increment();
    tmp.while_end();
    cur_var_num--;
}

var &var::operator+(var &another) {
    var *tmp = new var;
    add(another, *tmp);
    // when using a = b + c,
    // a call a.copy(*tmp) and only copy the value.
    // *tmp won't be destroyed from the pool
    // this should have been optimized
    return *tmp;
}

var &var::operator+(const uint8_t d) {
    var *p = new var(*this);     // *p is a copy of *this
    *p += d;                     // *p <- *this + d
    return *p;
}

void var::minus(var &another, var &ret) {
    var tmp(another);
    ret.copy(*this);
    // tmp is an copy of `another`

    tmp.while_begin();
    tmp.decrement();
    ret.decrement();
    tmp.while_end();
    cur_var_num--;
}

var &var::operator-(var &another) {
    var *tmp = new var;
    minus(another, *tmp);
    // when using a = b + c,
    // a call a.copy(*tmp) and only copy the value.
    // *tmp won't be destroyed from the pool
    // this should have been optimized
    return *tmp;
}

var &var::operator-(const uint8_t d) {
    var *p = new var(*this);    // *p is a copy of *this
    *p -= d;                    // *p <- *this + d
    return *p;
}

void var::multiply(var &another, var &ret) {
    var tmp(another);
    var tt(*this);
    tmp.while_begin();
    tmp.decrement();
    ret.add(*this, tt);     // tt <- ret + *this
    ret.copy(tt);           // ret <- tt
    tmp.while_end();
    tt.clear();
    cur_var_num -= 2;
}

var &var::operator*(var &another) {
    var *p = new var;
    multiply(another, *p);
    return *p;
}

var &var::operator*(const int8_t d) {
    var *p = new var(*this);
    *p *= d;
    return *p;
}

void var::operator*=(const uint8_t d) {
    var tmp;
    var t(*this);
    var s;
    for (int i = 0; i < d; i++) {
        s.add(t, tmp);      // tmp <- s + t
        s.copy(tmp);        // s <- tmp
    }
    copy(s);
    s.clear();
    t.clear();
    tmp.clear();
    cur_var_num -= 3;
}

void var::divide(var &another, var &ret) {
    // substract `another` until tmp is no greater than `another`
    // *this and `another` are considered as unsigned int (8 bits)
    var tmp(*this);
    var tt;
    var ttt;
    ret.clear();

    another.greater(tmp, tt);      // tt == (another > tmp)
    tt.flip();                     // tt == (tmp >= another)

    tt.while_begin();              // while tt is true
    ret.increment();               // ret++
    tmp.minus(another, ttt);
    tmp.copy(ttt);                 // tmp = tmp - another
    another.greater(tmp, tt);      // tt == (another > tmp)
    tt.flip();                     // tt == (tmp >= another)
    tt.while_end();

    ttt.clear();
    tmp.clear();
    cur_var_num -= 3;
}

var &var::operator/(var &another) {
    var *p = new var;
    divide(another, *p);
    return *p;
}

var &var::operator/(const int8_t d) {
    var *p = new var(*this);
    *p /= d;
    return *p;
}

void var::operator/=(const uint8_t d) {
    var rest(*this);
    var flag;
    var cnt;

    rest.greater_eq(d, flag);
    flag.while_begin();     // while rest >= d
    cnt += 1;
    rest -= d;
    rest.greater_eq(d, flag);
    flag.while_end();

    copy(cnt);

    cnt.clear();
    rest.clear();
    flag.clear();
    cur_var_num -= 3;
}

void var::swap(var &another) {
    var tmp(*this);
    copy(another);
    another.copy(tmp);
    tmp.clear();
    cur_var_num--;
}

void optimize(FILE *fin, FILE *fout) {
    assert(fin && fout);
    std::vector<char> S;
    char ch = 0;
    while (fscanf(fin, "%c", &ch) == 1 && !feof(fin)) {
        switch (ch) {
        case '<':
            if (!S.empty() && S.back() == '>') {
                S.pop_back();
            }
            else {
                S.emplace_back(ch);
            }
            break;
        case '>':
            if (!S.empty() && S.back() == '<') {
                S.pop_back();
            }
            else {
                S.emplace_back(ch);
            }
            break;
        default:
            for (auto c : S) {
                fprintf(fout, "%c", c);
            }
            fprintf(fout, "%c", ch);
            S.clear();
        }
    }
    fclose(fin);
    fclose(fout);
    // discard the '<' and '>' at the end
}

void output(char c) {
    var a(c);
    a.output();
    a.clear();
    cur_var_num--;
}

void print_str(const char *str) {
    size_t l = strlen(str);
    int start_index = cur_var_num + 1;
    int end_index = cur_var_num + l;

    var *arr = new var[l];
    for (int i = 0; str[i]; i++) {
        arr[i] = str[i];
    }
    print_times('>', start_index);
    for (int i = start_index; i < end_index; i++) {
        printf(".>");
    }
    printf(".");

    for (int i = end_index; i > start_index; i--) {
        printf("[-]<");
    }
    printf("[-]");
    print_times('<', start_index);
    delete[] arr;
    cur_var_num -= l;
}

var &var::operator<=(const uint8_t d) {
    var *p = new var;
    greater(d, *p);
    p->flip();
    return *p;
}

var &var::operator<(var &another) {
    var *p = new var;
    greater_eq(another, *p);
    p->flip();
    return *p;
}

var &var::operator<=(var &another) {
    var *p = new var;
    greater(another, *p);
    p->flip();
    return *p;
}

var &var::operator!() {
    var *p = new var;
    *p = *this;
    p->flip();
    return *p;
}

var &var::operator&&(var &another) {
    return !(!*this || !another);
}

var &var::operator||(var &another) {
    var *p = new var;
    var &r1 = (*this != 0);
    var &r2 = (another != 0);

    r1.if_begin();
    *p = 1;
    if_end();

    r2.if_begin();
    *p = 1;
    if_end();

    r1.clear();
    r2.clear();
    cur_var_num -= 4;
    // destroy r1, r2 and 2 if-flags
    delete& r1;
    delete& r2;
    return *p;
}


void var::input_as_integer() {
    int old_var_num = cur_var_num;
    clear();

    var tmp, loop(1);
    tmp.input();

    loop.while_begin();         // (tmp == ' ').while_begin() is prohibited!
    (tmp < '0' || tmp > '9').if_begin();
    // eat all ' ', '\n', '\t' before the number
    tmp.input();
    if_end();
    // else
    (tmp >= '0' && tmp <= '9').if_begin();
    loop = 0;   // break
    if_end();
    loop.while_end();

    loop = 1;
    loop.while_begin();
    (tmp >= '0' && tmp <= '9').if_begin();
    *this = *this * 10 + tmp - '0';
    tmp.input();
    if_end();
    // else
    (tmp < '0' || tmp > '9').if_begin();
    loop = 0;   // break
    if_end();
    loop.while_end();

    // destory all rubbish
    print_times('>', old_var_num + 1);
    for (int i = old_var_num + 1; i <= cur_var_num; i++) {
        printf("[-]>");
    }
    print_times('<', cur_var_num + 1);
    cur_var_num = old_var_num;
}

var &var::operator%(var &another) {
    return *this - (*this / another) * another;
}

var &var::operator%(const uint8_t d) {
    return *this - (*this / d) * d;
}

void var::output_as_integer() {
    int old_var_num = cur_var_num;

    var &v2 = *this / 100;
    v2.if_begin();
    v2.output_digit2char();
    if_end();

    var &v1 = (*this / 10) % 10;
    (v1 || v2).if_begin();
    v1.output_digit2char();
    if_end();

    var &v0 = *this % 10;
    v0.output_digit2char();

    // destroy in C++
    delete& v2;
    delete& v1;
    delete& v0;

    // destory all rubbish in bf
    print_times('>', old_var_num + 1);
    for (int i = old_var_num + 1; i <= cur_var_num; i++) {
        printf("[-]>");
    }
    print_times('<', cur_var_num + 1);
    cur_var_num = old_var_num;
}

void mem_reset() {
    print_times('>', cur_var_num);
    for (int i = cur_var_num; i > 0; i--) {
        printf("[-]>");
    }
}
