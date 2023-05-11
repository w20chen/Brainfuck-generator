g++ ./src/main.cpp ./src/var.cpp ./include/var.h -o ./bin/bf
start ./bin/bf.exe out.bf
start ./com/compiler.exe out.bf
timeout /t -1
