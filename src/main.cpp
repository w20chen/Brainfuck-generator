#include "../include/var.h"
#include "../include/vararray.h"


void test() {
    // finish your code here
#include "../text.cpp"
    return;
}


int main(int argc, char **argv) {
    assert(freopen("tmp.bf", "w", stdout));
    test();

#ifndef __linux__
    assert(freopen("CON", "w", stdout));
#else
    assert(freopen("/dev/tty", "w", stdout));
#endif

    std::string name = "out.bf";
    if (argc == 2) {
        name = argv[1];
    }
    else if (argc > 2) {
        printf("invalid num of args");
        exit(-1);
    }

    FILE *fin = fopen("tmp.bf", "r");
    assert(fin);
    FILE *fout = fopen(name.c_str(), "w");
    assert(fout);

    optimize(fin, fout);

    printf("code is generated in %s\n", name.c_str());
    if (remove("tmp.bf") != 0) {
        perror("remove");
    }
#ifndef __linux__
    getchar();
#endif
    return 0;
}
