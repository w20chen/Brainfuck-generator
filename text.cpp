vararray L(10);
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