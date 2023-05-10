#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <assert.h>

#define MEMSIZE (500000 + 128)
#define PROG_LEN 500000

typedef int8_t dtype;

char program[PROG_LEN];

dtype *data_ptr;
dtype *mem;


dtype input() {
    char ch;
    if (scanf("%c", &ch)) {
        return (dtype)ch;
    }
    return (dtype)0;
}

void output(dtype *p) {
    printf("%c", *p);
}


int L[PROG_LEN];
int R[PROG_LEN];
#define Left(x) L[x]
#define Right(x) R[x]

void parser(char *str) {
    std::stack<int> stk;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '[') {
            stk.push(i);
        }
        else if (str[i] == ']') {
            assert(!stk.empty());
            R[stk.top()] = i;
            L[i] = stk.top();
            stk.pop();
        }
    }

    if (!stk.empty()) {
        printf("\e[1;31munbalanced brackets\n\e[0m");
        exit(1);
    }
}



void init() {
    mem = (dtype *)malloc(sizeof(dtype) * MEMSIZE);
    if (!mem) {
        printf("\e[1;31mcannot allocate memory\n\e[0m");
        exit(1);
    }

    // set all memory zero
    memset(mem, 0, sizeof(dtype) * MEMSIZE);

    data_ptr = mem + 128;
    parser(program);
}


void execute(char *str) {
    for (int pc = 0; str[pc]; pc++) {
        switch (str[pc]) {
        case '>':
            data_ptr++;
            break;
        case '<':
            data_ptr--;
            break;
        case '+':
            (*data_ptr)++;
            break;
        case '-':
            (*data_ptr)--;
            break;
        case '.':
            output(data_ptr);
            break;
        case ',':
            *data_ptr = input();
            break;
        case '[':
            if (*data_ptr == 0) {
                pc = Right(pc);
            }
            break;
        case ']':
            if (*data_ptr != 0) {
                pc = Left(pc);
            }
            break;
        case '\n':
            break;
        default:
            // comment
            break;
        }
    }
}



int main(int argc, char **argv) {
    assert(argc > 1);

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("\e[1;31mcannot find file %s\n\e[0m", argv[1]);
        exit(1);
    }

    int cnt = -1;
    do {
        assert(cnt + 1 < MEMSIZE);
        program[++cnt] = fgetc(fp);
    }
    while (program[cnt] != EOF);
    program[cnt] = 0;
    fclose(fp);

    init();

    execute(program);

    return 0;
}