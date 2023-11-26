int chooseOption(char *option[], int length) {
    char *arrow = "\x1b[1m\x1b[94m> ";
    char *redArrow = "\x1b[1m\x1b[91m> ";
    char *noEffect = "\x1b[0m";
    for (int i = 0; i < length; i++) {
        printf("  %s\n", option[i]);
    }
    printf("\e[?25l");
    printf("\033[%dA\r", length);
    printf("%s", arrow);
    printf("%s%s", option[0], noEffect);
    int code = 0;
    int input, prev;
    do {
        prev = input;
        input = getch();

        if ((prev == '\0' || prev == 224) && input == 'P') {  // down
            printf("\r  %s%s", noEffect, option[code]);
            code++;
            if (code >= length) {
                code = 0;
                printf("\r\033[%dA%s%s%s", length - 1, arrow, option[code], noEffect);
            } else {
                if (code == length - 1) {
                    printf("\r\033[B%s%s%s", redArrow, option[code], noEffect);
                } else {
                    printf("\r\033[B%s%s%s", arrow, option[code], noEffect);
                }
            }
        } else if ((prev == '\0' || prev == 224) && input == 'H') {  // up
            printf("\r  %s%s", noEffect, option[code]);
            code--;
            if (code < 0) {
                code = length - 1;
                printf("\r\033[%dB%s%s%s", length - 1, redArrow, option[code], noEffect);
            } else {
                if (code == length - 1) {
                    printf("\r\033[A%s%s%s", redArrow, option[code], noEffect);
                } else {
                    printf("\r\033[A%s%s%s", arrow, option[code], noEffect);
                }
            }
        } else if (input == 3) {
            printf("\e[?25h");
            exit(0);
        } else if (input == 27) {
            printf("\e[?25h");
            return length - 1;
        }
    } while (input != 13);
    printf("\e[?25h");
    return code;
}