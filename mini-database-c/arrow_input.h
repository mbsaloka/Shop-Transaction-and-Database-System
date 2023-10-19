int chooseOption(char *option[], int length) {
    char *arrow = "\x1b[94m> ";
    char *noEffect = "\x1b[0m";
    for (int i = 0; i < length; i++) {
        printf("  %s\n", option[i]);
    }
    printf("\033[%dA\r", length);
    printf("%s", arrow);
    printf("%s%s\r", option[0], noEffect);
    int code = 0;
    int input, prev;
    do {
        prev = input;
        input = getch();

        if ((prev == '\0' || prev == 224) && input == 'P') {  // down
            printf("\x1b[0m  %s%s\r", option[code], noEffect);
            code++;
            if (code >= length) {
                code = 0;
                printf("\033[%dA%s%s%s\r", length - 1, arrow, option[code], noEffect);
            } else {
                printf("\033[B%s%s%s\r", arrow, option[code], noEffect);
            }
        } else if ((prev == '\0' || prev == 224) && input == 'H') {  // up
            printf("\x1b[0m  %s\r", option[code], noEffect);
            code--;
            if (code < 0) {
                code = length - 1;
                printf("\033[%dB%s%s%s\r", length - 1, arrow, option[code], noEffect);
            } else {
                printf("\033[A%s%s%s\r", arrow, option[code], noEffect);
            }
        } else if (input == 3) {
            exit(0);
        } else if (input == 27) {
            return 0;
        }
    } while (input != 13);
    return code;
}

/* Cara Basic
printBold("Selamat Datang di Sistem\n");
puts("(0) Akhiri Program");
puts("(1) Login Sebagai Admin");
puts("(2) Login Sebagai Pelanggan");
code = getNumINT();
*/