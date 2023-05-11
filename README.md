#### Brainfuck generator

Describe your brainfuck program using C++.

已经实现：

- `while(!x)` 语句
- `if(condition)` 语句
- 八位整型运算 `+`、`-`、`*`、`/`
- 八位整型大小比较
- 运算符重载
- 数组，能通过变量访问数组

Not implemented yet:
- (condition).while_begin();
- else_beign(), else_end();


#### How to use

Implement your C++ code in text.cpp, then `bash run.sh` to compile and run.     
Brainfuck code will be generated in `out.bf`.

#### var 类型
**var 对象在调用构造函数时，会在 BF 机器内存中自动申请空间，且不会从 BF 内存中释放。**     
`var` 类型本质上是 `uint8_t`，也可以被理解为 `char` 或 `int8_t`。下面是一个例子。       

输入一个数(char, '0'~'9')，判断是否大于 '5'。     
```cpp
var i1 = '5';               // 实例化对象 '5'
var i2;                     // 实例化对象 0
i2.input();
var ret;
i2.greater(i1, ret);        // ret <- (i2 > i1)
ret.output_digit2char();
```

#### 输入输出
```cpp
var a;
a.input_as_integer();   // 作为 uint8_t 读入
a.output_as_integer();  // 作为 uint8_t 输出

a.input();              // 作为 char 读入
a.output();             // 作为 char 输出
```

#### if 语句
若 `a - b == 1`，则输出 'Y'；否则输出 'N'。
```cpp
var a, b;
a.input();
b.input();

var c = 'Y', d;
a.minus(b, d);      // d <- a - b

d -= 1;             // d <- d - 1

d.if_begin();       // if (d != 0)
c = 'N';

if_end();
c.output();
```

判断输入字符是否为数字，相当于 `isdigit(char)`
```cpp
var flag, val;
val.input();

val.greater_eq('0', flag);      // flag = (val >= '0');

flag.if_begin();                // if (flag)
    val.greater('9', flag);     // flag = (val > '9');
    flag.flip();                // flag = !flag
if_end();

flag.output_digit2char();
```

判断 `a` 是否为 `1`
```cpp
var a;
a.input();
(a == '1').if_begin();
    print_str("a==1");
if_end();

(a != '1').if_begin();
    print_str("a!=1,a==");
    a.output();
if_end();
```


#### while 语句

输出 `x` 个字符 `'5'`
```cpp
var x, r('5');
x.input_as_integer();

x.while_begin();   // while(!x)
    x -= 1;
    r.output();
x.while_end();
```

**Do not use `(condition).while_begin()` because the value of `condition` will only be computed once and will not change during loop**

#### 基本运算
```cpp
var a, b, ret;
a.input_as_integer();
b.input_as_integer();
ret = a * b;
ret.output_as_integer();
```

输入 `x` 输出 `2*x+3`   
```cpp
var x;
x.input_as_integer();
(x * 2 + 3).output_as_integer();
```

#### 运算符重载
注意：调用运算符函数的同时会创建**不可被回收的中间变量**     

等号
```cpp
var v0, v1('1'), v2, v3;
v2 = v0 = v1;
v0.output();        // '1'
v2.output();        // '1'
(v3 = v2) += 2;     // v3 <- v2; v3 += 2;
v2.output();        // '1'
v3.output();        // '3'
```

加号
```cpp
var v0, v1 = 5, v2 = 20;
v0 = 4;
v1 = v0 + v2 + 7 + v0;  // v1 == 35
v1.output();            // print '#'
v1.output_as_integer(); // print 35
```

减号
```cpp
var v0 = 45, v1(5), v2(100);
v1 = v0 - v2 / 20 - (v2 - 75) / v1;
v1.output();            // print '#'
```

乘号
```cpp
var v0, v1(5), v2(4);
v0 = 4;
v1 = v0 * 2 + v2 * v1 + 7;
v1.output();            // print '#'
```

除号
```cpp
var v0, v1(5), v2(100);
v0 = 40;
v1 = v0 / v1 + v2 / 5 + 7;
v1.output();            // print '#'
```

`>`和`>=`
```cpp
var v0 = 4, v1 = 2, v2 = 9, v3 = 9;
var result[6] = {v0 > v1, v2 >= v3, v1 > v3, v1 >= v0, v1 >= v3, v0 >= v1};
for (var &v : result) {
    v.output_digit2char();
}
// 110001
```

`==`和`!=`
```cpp
var v0 = 4, v1 = 2, v2 = 9, v3 = 9;
var result[7] = {v0 == 4, v2 == 9, v1 != v3, v2 == v3, v2 != v3, v0 != 4, v1 != 1};
for (var &v : result) {
    v.output_digit2char();
}
// 1111001
```

#### 字符打印
```cpp
// hello world
var v1('h'), v2('e'), v3('l'), v4('o'), v5(' '), v6('w'), v7('r'), v8('d');
v1.output();v2.output();v3.output();v3.output();
v4.output();v5.output();v6.output();v4.output();
v7.output();v3.output();v8.output();
```

```cpp
std::string s = "hello world\n";
for (char c : s) {
    var a(c);
    a.output();
}
```

```cpp
print_str("hello world\n");
```

#### vararray

`vararray` is an array of vars where the element can be accessed by index with dtype `var`,      
unlike `var[]` where index can only be `int`.

```cpp
vararray L(10);     // create an array with length 10

for (int i = 0; i < 10; i++) {
    L[i] = 9 - i;
}

L.output();         // [9,8,7,6,5,4,3,2,1,0]

var index;
index.input_as_integer();       // index starts from 0
L.val(index).output_as_integer();
```

#### 排序
输入10个 int，输出排序后的10个 int。     
这里，数组的意义在于批量地实例化 `var` 对象。
```cpp
var L[10];
for (int i = 0; i < 10; i++) {
    L[i].input_as_integer();
}

for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10 - i - 1; j++) {
        (L[j] > L[j + 1]).if_begin();
            L[j].swap(L[j + 1]);
        if_end();
    }
}

for (int i = 0; i < 10; i++) {
    L[i].output_as_integer();
    output(' ');
}
```

Sort with vararray:

```cpp
vararray L(10);
var tmp;
for (int i = 0; i < 10; i++) {
    tmp.input_as_integer();
    L.set(i, tmp);
}

for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10 - i - 1; j++) {
        (L.val(j) > L.val(j + 1)).if_begin();
        tmp = L.val(j);
        L.set(j, L.val(j + 1));
        L.set(j + 1, tmp);
        if_end();
    }
}

L.output();
```

input: 100 88 2 34 55 55 23 1 0 87
output: 0 1 2 23 34 55 55 87 88 100


```cpp
vararray L(32);
var N, tmp;
N.input_as_integer();

// input

var i = 0, j = 0;
var flag1 = 1, flag2 = 1;
flag1.while_begin();
    tmp.input_as_integer();
    L.set(i, tmp);
    i.increment();
    (i == N).if_begin();
        flag1 = 0;
    if_end();
flag1.while_end();

L.output();

// sort

i = 0;
flag1 = 1;

flag1.while_begin();
    print_str(".");
    j = 0;
    flag2 = 1;
    flag2.while_begin();
        (L.val(j) > L.val(j + 1)).if_begin();
            tmp = L.val(j);
            L.set(j, L.val(j + 1));
            L.set(j + 1, tmp);
        if_end();
        j += 1;
        (j == N - i - 1).if_begin();
            flag2 = 0;
        if_end();
    flag2.while_end();
    i += 1;
    (i == N).if_begin();
        flag1 = 0;
    if_end();
flag1.while_end();

L.output();
```